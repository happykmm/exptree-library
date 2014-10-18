#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exptree.h"


int main(int argc, char *argv[])
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    char input[100], *Prefix, *Infix, *Postfix;
    Tree ExpTree;
    double result;
    fgets(input, 100, stdin);
    ExpTree = InToTree  (input);
    Prefix  = TreeToPre (ExpTree);
    Infix   = TreeToIn  (ExpTree);
    Postfix = TreeToPost(ExpTree);
    result  = CalcTree  (ExpTree);
    printf("Prefix:  %s\n\n\n", Prefix);
    printf("Infix:   %s\n\n\n", Infix);
    printf("Postfix: %s\n\n\n", Postfix);
    printf("result:  %lf\n\n\n", result);
    return 0;
}
