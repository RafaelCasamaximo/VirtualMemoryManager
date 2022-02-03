#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "argumentManager.h"

void verifyArguments(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("\n-Execute o programa com:");
        printf("\n   ./a.out <path/addresses.txt>   ");
        exit(-1);
    }

    printf("Endereços utilizados de: %s", argv[1]);
}

void verifyOpenFile(FILE *file, char *fileName)
{
    if (!file)
    {
        printf("\n-O arquivo <%s> não pode ser aberto. Verifique o path.", fileName);
        exit(-1);
    }
}