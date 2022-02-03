#ifndef _MEMORYMANAGER_H_
#define _MEMORYMANAGER_H_

#include "macros.h"

int verifyPageTable(int pageNumber, int pageTable[PAGE_TABLE_ENTRIES]);
char *getFrameFromBackStore(int pageNumber, FILE *backingStoreFile, signed char page[PAGE_SIZE_IN_BYTES]);
int insertFromBackStore(int pageNumber, int physicalMemory[FRAME_AMOUNT][FRAME_SIZE_IN_BYTES], int pageTable[PAGE_TABLE_ENTRIES], signed char page[PAGE_SIZE_IN_BYTES], FILE *backingStoreFile);

#endif