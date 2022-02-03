/*
    Universidade Estadual de Londrina;
    Bacharelado em Ciência da Computação - Sistemas Operacionais; 
    Rafael Furlanetto Casamaximo;
    Referência: Operating System Concepts 9ª edição (Capítulo 9);
*/

// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Inclusões
#include "argumentManager.h"
#include "memoryManager.h"
#include "translationLookasideBuffer.h"

// Constantes e Macros
#include "macros.h"

int main(int argc, char **argv)
{
    // Estatísticas
    int addressAcessCounter = 0;
    int pageFaultCounter = 0;
    int tlbHitCounter = 0;

    // Constantes Auxiliares

    verifyArguments(argc, argv);

    // Arquivos
    FILE *outputFile = fopen("output.txt", "w");
    verifyOpenFile(outputFile, "output.txt");

    FILE *addressesFile = fopen(argv[1], "rb");
    verifyOpenFile(addressesFile, argv[1]);

    FILE *backingStoreFile = fopen("BACKING_STORE.bin", "rb");
    verifyOpenFile(backingStoreFile, "BACKING_STORE.bin");

    // Estruturas de Dados
    signed char page[PAGE_SIZE_IN_BYTES];
    int pageTable[PAGE_TABLE_ENTRIES];
    int physicalMemory[FRAME_AMOUNT][FRAME_SIZE_IN_BYTES];

    // Inicializa estruturas e define memória
    TLB tlb = createTLB();
    void *mem = memset(physicalMemory, -1, sizeof(physicalMemory[0][0]) * FRAME_AMOUNT * FRAME_SIZE_IN_BYTES);

    // Lê addresses.txt
    int virtualAddress = 0;
    while (fscanf(addressesFile, "%d", &virtualAddress) == 1)
    {
        // Atualiza o número de endereços virtuais lidos
        addressAcessCounter++;

        // Usa as macros para descobrir o número da página, do offset e do frame
        // As macros são usadas pra fazer o bit shift nos números
        int pageNumber = GET_PAGE_NUMBER(virtualAddress);
        int offsetNumber = GET_OFFSET_NUMBER(virtualAddress);
        int frameNumber = -1;

        // Consulta na TLB a entrada de acordo com o número da página
        TLBEntry *tlbEntry = query(tlb, pageNumber);

        // Quando acha a entrada...
        if (tlbEntry != NULL)
        {
            // Atualiza o número de encontrados na TLB
            tlbHitCounter++;
            // Carrega o número do frame
            frameNumber = tlbEntry->frameNumber;
        }

        // Quando tlbEntry não é encontrada...
        if (frameNumber == -1)
        {
            // Verifica se existe na PageTable e ou insere do backstore ou define o valor
            int pageTableFrameNumber = verifyPageTable(pageNumber, pageTable);
            //int pageTableFrameNumber = -1;
            frameNumber = (pageTableFrameNumber == -1) ? insertFromBackStore(pageNumber, physicalMemory, pageTable, page, backingStoreFile) : pageTableFrameNumber;
            // Atualiza o número de pageFault
            pageFaultCounter++;
        }

        // Cria e insere uma nova entrada
        TLBEntry *newEntry = malloc(sizeof(TLBEntry));
        newEntry->frameNumber = frameNumber;
        newEntry->pageNumber = pageNumber;
        newEntry->isFree = 1;
        newEntry->entryAge = 0;
        insertEntry(&tlb, newEntry);

        // Insere o frame e pageNumber na TLB
        int physicalAddress = GET_PHYSICAL_ADDRESS(frameNumber, offsetNumber);
        signed char value = physicalMemory[frameNumber][offsetNumber];

        fprintf(outputFile, "Virtual Address: %d\tPhysical Address: %d\tValue: %d\n", virtualAddress, physicalAddress, value);
    }
    fprintf(outputFile, "\n\t---Estatísticas---\n");
    fprintf(outputFile, "Endereços Acessados: %d\n", addressAcessCounter);
    if (addressAcessCounter != 0)
    {
        fprintf(outputFile, "Taxa de Page Fault: %f\n", (double)(pageFaultCounter / addressAcessCounter));
        fprintf(outputFile, "Taxa de Acertos na TLB: %f\n", (double)(tlbHitCounter / addressAcessCounter));
    }

    delete (tlb);

    // Fechando Arquivos
    fclose(outputFile);
    fclose(addressesFile);
    fclose(backingStoreFile);
}