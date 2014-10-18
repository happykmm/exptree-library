#include <stdlib.h>
#include "extstack.h"

/*
 * Function: dPop
 * Usage: d = dPop(S);
 * ----------------------
 * This function pops a (void*) pointer from Stack S 
 * and converts it to (double*) and return its value.
 */
double dPop(Stack S)
{
    double *pD = (double*)TopAndPop(S);
    return (pD==NULL) ? 0 : *pD;
}

/*
 * Function: dPush
 * Usage: dPush(d,S);
 * ----------------------
 * This procedure creates a pointer for double d and push 
 * the pointer into Stack S.
 */
void dPush(double d, Stack S)
{
    double *pD = (double*)malloc(sizeof(double));
    *pD = d;
    Push(pD, S);
}

/*
 * Function: cTop
 * Usage: chr = cTop(S);
 * ----------------------
 * This function gets the top element from Stack S
 * as (void*), converts it to (char*) and return its value.
 */
char cTop(Stack S)
{
    char *chr = (char*)Top(S);
    return (chr==NULL) ? 0 : *chr;
}

/*
 * Function: cPop
 * Usage: chr = cPop(S);
 * ----------------------
 * This function pops a (void*) pointer from Stack S 
 * and converts it to (char*) and return its value.
 */
char cPop(Stack S)
{
    char *chr = (char*)TopAndPop(S);
    return (chr==NULL) ? 0 : *chr;
}
