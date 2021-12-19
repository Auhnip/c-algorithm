#ifndef BINTREE_C_
#define BINTREE_C_

typedef int ElementType;

typedef struct bin_tree_node
{
    ElementType data;
    struct bin_tree_node * lchild;
    struct bin_tree_node * rchild;
    int bf;
} BinTreeNode, * BinTree;

void initBinTree(BinTree* tree);

int insertBinTree(BinTree* tree, const ElementType* x,
        int(*less)(const ElementType*, const ElementType*));

int removeBinTree(BinTree* tree, const ElementType* x,
        int(*less)(const ElementType*, const ElementType*));

void clearBinTree(BinTree* tree);

void calculateBalance(BinTree* tree);

void printBinTree(BinTree* tree);

#endif