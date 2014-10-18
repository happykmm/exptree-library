#ifndef _tree_h

typedef struct TreeNode *PtrToNode;
typedef PtrToNode Tree;

struct TreeNode
{
    void *Element;
    Tree Left, Right;
};

Tree  NewTree(void  *Element, Tree Left, Tree Right);
Tree dNewTree(double Element, Tree Left, Tree Right);
Tree cNewTree(char   Element, Tree Left, Tree Right);

#endif