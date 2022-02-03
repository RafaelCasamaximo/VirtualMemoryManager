#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "translationLookasideBuffer.h"

#define TLB_ENTRIES 16

/*
    Cria uma nova Translation Lookaside Buffer
    Retorna TLB
*/
TLB createTLB()
{
    TLB tlb;
    tlb.curr_len = 0;
    tlb.tlb_len = TLB_ENTRIES;
    tlb.head = NULL;
    tlb.last = NULL;

    return tlb;
}

/*
    Realiza a busca de pageNumber na TLB table
    Retorna TLBEntry ou NULL
*/
TLBEntry *query(TLB table, int pageNumber)
{
    // Percorre as entradas procurando o número da página
    // Atualiza a idade da página que não é a desejada
    // Retorna a entrada quando encontra
    // Retorna NULL quando não acha nada
    TLBEntry *current = table.head;

    while (current != NULL)
    {
        if (current->pageNumber == pageNumber)
        {
            return current;
        }

        current->entryAge++;
        current = current->next;
    }

    return NULL;
}

/*
    Insere nova entrada e gerencia a TLB
*/
void insertEntry(TLB *table, TLBEntry *entry)
{
    if (table->last == table->head)
    {
        table->head = entry;
        table->last = entry;
    }
    else if (table->curr_len == table->tlb_len - 1)
    {
        // Método de inserção por FIFO
        // Aqui caberia uma implementação do algoritmo LRU
        table->head = entry;
        table->last = entry;
    }
    else
    {
        table->last->next = entry;
    }

    table->curr_len++;
}

void delete (TLB tlb)
{
    TLBEntry *start = tlb.head;
    TLBEntry *aux = NULL;

    while (start != NULL)
    {
        aux = start;
        start = start->next;
        free(aux);
    }
}
