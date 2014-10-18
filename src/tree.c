#include <stdlib.h>
#include "tree.h"




Tree NewTree(void *Element, Tree Left, Tree Right)
{
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->Element = Element;
    T->Left = Left;
    T->Right = Right;
    return T;
}

Tree dNewTree(double Element, Tree Left, Tree Right)
{
    double *pD = (double*)malloc(sizeof(double));
    *pD = Element;
    return NewTree(pD,Left,Right);
}

Tree cNewTree(char Element, Tree Left, Tree Right)
{
    char *pC = (char*)malloc(sizeof(char)*2);
    pC[0] = Element;
    pC[1] = 0;
    return NewTree(pC,Left,Right);
}

