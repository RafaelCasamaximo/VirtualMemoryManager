#ifndef __TLB_H_
#define __TLB_H_

typedef struct TLBEntryStruct
{
    int pageNumber;
    int frameNumber;
    int isFree;
    int entryAge;
    struct TLBEntryStruct *next;
} TLBEntry;

typedef struct TLBStruct
{
    int tlb_len;
    int curr_len;
    TLBEntry *head;
    TLBEntry *last;
} TLB;

/*
    Cria uma nova Translation Lookaside Buffer
    Retorna TLB
*/
TLB createTLB();

/*
    Realiza a busca de pageNumber na TLB table
    Retorna TLBEntry ou NULL
*/
TLBEntry *query(TLB table, int pageNumber);

/*
    Insere nova entrada e gerencia a TLB
*/
void insertEntry(TLB *table, TLBEntry *entry);

/*
    Remove a TLB
*/
void delete (TLB tlb);

#endif