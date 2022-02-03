// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Constantes e Macros
#include "macros.h"

// Inclusões
#include "memoryManager.h"

int verifyPageTable(int pageNumber, int pageTable[PAGE_TABLE_ENTRIES])
{
    for (int pageEntry = 0; pageEntry < PAGE_TABLE_ENTRIES; pageEntry++)
    {
        if (pageTable[pageEntry] == pageNumber || pageTable[pageEntry] == -1)
        {
            return pageTable[pageEntry];
        }
        else if (pageTable[pageNumber] == pageNumber)
        {
            return pageTable[pageNumber];
        }
    }
    return -1;
}

char *getFrameFromBackStore(int pageNumber, FILE *backingStoreFile, signed char page[PAGE_SIZE_IN_BYTES])
{
    fseek(backingStoreFile, (PAGE_SIZE_IN_BYTES * pageNumber), SEEK_SET);
    fread(page, PAGE_SIZE_IN_BYTES, sizeof(signed char), backingStoreFile);

    return (char *)page;
}

int insertFromBackStore(int pageNumber, int physicalMemory[FRAME_AMOUNT][FRAME_SIZE_IN_BYTES], int pageTable[PAGE_TABLE_ENTRIES], signed char page[PAGE_SIZE_IN_BYTES], FILE *backingStoreFile)
{
    char *result = getFrameFromBackStore(pageNumber, backingStoreFile, page);

    for (int frameNumber = 0; frameNumber < FRAME_AMOUNT; frameNumber++)
    {
        for (int frameByte = 0; frameByte < FRAME_SIZE_IN_BYTES; frameByte++)
        {
            if (physicalMemory[frameNumber][frameByte] == -1)
            {
                physicalMemory[frameNumber][frameByte] = result[frameByte];
                pageTable[pageNumber] = frameNumber;
            }
        }
    }

    return -1;
}