#ifndef _MACROS_H_
#define _MACROS_H_

// Constantes
#define PAGE_TABLE_ENTRIES 256
#define PAGE_SIZE_IN_BYTES 256
#define PAGE_NUMBER_SIZE_BITS 8
#define FRAME_AMOUNT 256
#define FRAME_SIZE_IN_BYTES 256
#define TLB_ENTRIES 16
#define PHYSICAL_MEM_SIZE (FRAME_AMOUNT * FRAME_SIZE_IN_BYTES)
#define PAGE_NUMBER_MASK 0xff00
#define OFFSET_NUMBER_MASK 0xff

// MACROS
#define GET_PAGE_NUMBER(virtualAddress) (((virtualAddress) & (PAGE_NUMBER_MASK)) >> PAGE_NUMBER_SIZE_BITS)
#define GET_OFFSET_NUMBER(virtualAddress) ((virtualAddress) & (OFFSET_NUMBER_MASK))
#define GET_PHYSICAL_ADDRESS(frameNumber, offsetNumber) ((frameNumber << PAGE_NUMBER_SIZE_BITS) | (offsetNumber))

#endif