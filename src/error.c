#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void Error(char *msg)
{
    fprintf(stderr,"Error: %s\n",msg);
}

void FatalError(char *msg)
{
    fprintf(stderr,"FatalError: %s\n",msg);
    exit(2);
}
