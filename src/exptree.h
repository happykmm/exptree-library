#ifndef _exptree_h

#define _exptree_h

#include "extstring.h"
#include "extstack.h"
#include "tree.h"
#include "error.h"


char*   InToPre    (const char* Infix);
char*   InToPost   (const char* Infix);
Tree    InToTree   (const char* Infix);
double  CalcIn     (const char* Infix);
char*   PostToPre  (const char* Postfix);
char*   PostToIn   (const char* Postfix);
Tree    PostToTree (const char* Postfix);
double  CalcPost   (const char* Postfix);
char*   TreeToPre  (const Tree ExpTree);
char*   TreeToIn   (const Tree ExpTree);
char*   TreeToPost (const Tree ExpTree);
double  CalcTree   (const Tree ExpTree);



#endif
