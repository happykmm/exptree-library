#include <stdlib.h>
#include <string.h>
#include "exptree.h"


static int   Priority(char chr);
static int  sPriority(char chr);

/*
 * Function: Priority
 * Usage: pri = Priority(chr);
 * ----------------------
 * This function returns NORMAL priority of chr.
 * If chr is not an operator, it returns 0. 
 */
static int Priority(char chr) 
{
    static const char opt[] = {'#','=',')','+','-','*','/','('};
    static const int  pri[] = {  5, 10, 10, 20, 20, 30, 30, 40};
    int i;
    for (i=0; i<sizeof(opt)/sizeof(char); i++) {
        if (opt[i] == chr)
            return pri[i];
    }
    return 0;  // return false when chr isn't an operator 
}

/*
 * Function: sPriority
 * Usage: pri = sPriority(chr);
 * ----------------------
 * This function returns STACK priority of chr.
 * If chr is not an operator, it returns 0. 
 */
static int sPriority(char chr)
{
    if (chr == '(')
        chr = ')';
    return Priority(chr); 
}

/*
 * Function: InToPost
 * Usage: postfix-exp = InToPost(infix-exp);
 * ----------------------
 * This function converts an infix expression   
 * to an postfix expression.
 */
char* InToPost(const char* Infix)
{
	if (Infix==NULL) return NULL;
    char *Input = strFilter(strClone(Infix));
    strcat(Input, "=");
    Stack S = CreateStack(strlen(Input)/2+1);
    char *Postfix;
    char *chi = Input;
    char *chj = Input;
    char *tmp = (char*)malloc(strlen(Input)+1);
    int priority;
    Push((void*)"#\0", S);
    while (*chi) {
        priority = Priority(*chi);
        if (priority == 0) {
            chi++;
            continue;
        }
        // if (priority != 0)  
        Postfix = strMerge(Postfix, trim(substr(chj, chi-chj)));
        while (priority <= sPriority(cTop(S))) {
            tmp[0] = cPop(S);
            if (tmp[0] == '(') 
                break;
            tmp[1] = 0;
            Postfix = strMerge(Postfix,tmp);
        } 
        switch (*chi) {
            case '=':
                free(tmp); free(Input);
                return Postfix;
            case ')':
                break;
            default:
                Push(chi, S);
        }
        chi++;
        chj = chi;
    } 
    free(tmp); free(Input);
    return Postfix;
}

/*
 * Function: ToExpTree
 * Usage: exptree = ToExpTree(infix-exp);
 * ----------------------
 * This function builds an expression tree from   
 * an infix expression.
 */
Tree InToTree(const char* Infix)
{
    return PostToTree(InToPost(Infix));
}

/*
 * Function: CalcInfix
 * Usage: result = CalcInfix(infix-exp);
 * ----------------------
 * This function calculates an infix expression and  
 * returns the result as a double.
 */
double CalcInfix(const char* Infix) 
{
    return CalcPost(InToPost(Infix));
}

/*
 * Function: CalcPostfix
 * Usage: result = CalcPostfix(postfix-exp);
 * ----------------------
 * This function calculates a postfix expression and  
 * returns the result as a double.
 */
double CalcPost(const char* Postfix)
{
	if (Postfix==NULL) return 0;
    char *Input = strFilter(strClone(Postfix));
    strcat(Input, " ");
    Stack S = CreateStack(strlen(Input)/2+1);
    char *chi = Input;
    char *chj = Input;
    double result;
    while (*chi) {
        if (*chi != ' ') {
           chi++;
           continue;
        }
        // if (*chi == ' ')
        if (chi>chj) {
            if (*chj == '+')
    	        result = dPop(S) + dPop(S);
    	    else if (*chj == '-')
    	        result = 0 - dPop(S) + dPop(S);
    	    else if (*chj == '*')
    	        result = dPop(S) * dPop(S);
            else if (*chj == '/')
    	        result = 1 / dPop(S) * dPop(S);
    	    else 
    	        result = strtod(substr(chj,chi-chj),NULL);
            dPush(result,S);
        }
        chi++;  
        chj = chi;
    }
    free(Input); 
    result = dPop(S);
    if (IsEmpty(S)) {
        DisposeStack(S);
    	return result;
    } 
    DisposeStack(S);
    Error("Illegal expression!");
    return 0;
}

/*
 * Function: ToExpTree
 * Usage: exptree = ToExpTree(postfix-exp);
 * ----------------------
 * This function builds an expression tree from   
 * a postfix expression.
 */
Tree PostToTree(const char* Postfix)
{
	if (Postfix==NULL) return NULL;
    char* Input = strFilter(strClone(Postfix));
    strcat(Input, " ");
    Stack S = CreateStack(strlen(Input)/2+1);
    char *chi = Input;
    char *chj = Input;
    Tree Left, Right, ExpTree;
    while (*chi) {
        if (*chi != ' ') {
           chi++;
           continue;
        }
        // if (*chi == ' ')
        if (chi>chj) {
            if (Priority(*chj)) { // *chj is an operator
                Right = (Tree)TopAndPop(S);
                Left = (Tree)TopAndPop(S);
                Push(cNewTree(*chj,Left,Right),S);
            } else { // *chj is not an operator
                Push(NewTree(substr(chj,chi-chj),NULL,NULL),S);
            };
        }
        chi++;  
        chj = chi;
    }
	free(Input); 
    ExpTree = (Tree)TopAndPop(S);
    if (IsEmpty(S)) {
        DisposeStack(S);     
    	return ExpTree;
    } 
    DisposeStack(S); 
    free(ExpTree);
    Error("Illegal expression!");
    return 0;
}

/*
 * Function: ToPrefix
 * Usage: prefix-exp = ToPrefix(exptree);
 * ----------------------
 * This function returns the preorder traversal of    
 * an expression tree. It converts the expression tree
 * to a prefix expression.
 */
char *TreeToPre(const Tree ExpTree)
{
    if (!ExpTree)
         return 0;
     char *chL, *chR, *chE, *Prefix;
     chL = TreeToPre(ExpTree->Left);
     chR = TreeToPre(ExpTree->Right);
     chE = strClone((char*)ExpTree->Element);
     Prefix = strMerge3(chE, chL, chR);    
     free(chL); free(chR); free(chE);
     return Prefix;
}

/*
 * Function: ToInfix
 * Usage: infix-exp = ToInfix(exptree);
 * ----------------------
 * This function returns the inorder traversal of    
 * an expression tree. It converts the expression tree
 * to an infix expression.
 */
char *TreeToIn(const Tree ExpTree)
{
    if (!ExpTree)
        return 0;
    char *chL, *chR, *chE, *Infix;
    chL = TreeToIn(ExpTree->Left);
    chR = TreeToIn(ExpTree->Right);
    chE = strClone((char*)ExpTree->Element);
    Infix = strMerge3(chL, chE, chR);
	Infix = strMerge3("(", Infix, ")");
    free(chL); free(chR); free(chE);
    return Infix;
}

/*
 * Function: ToPostfix
 * Usage: postfix-exp = ToPostfix(exptree);
 * ----------------------
 * This function returns the postorder traversal of    
 * an expression tree. It converts the expression tree
 * to an postfix expression.
 */
char *TreeToPost(const Tree ExpTree)
{
    if (!ExpTree)
        return 0;
    char *chL, *chR, *chE, *Postfix;
    chL = TreeToPost(ExpTree->Left);
    chR = TreeToPost(ExpTree->Right);
    chE = strClone((char*)ExpTree->Element);
    Postfix = strMerge3(chL, chR, chE);    
    free(chL); free(chR); free(chE);
    return Postfix;
}


/*
 * Function: ClacExpTree
 * Usage: result = ClacExpTree(exptree);
 * ----------------------
 * This function calculates the expression tree and     
 * returns the result as a double.
 */
double CalcTree(const Tree ExpTree)
{
    return CalcPost(TreeToPost(ExpTree));
}

