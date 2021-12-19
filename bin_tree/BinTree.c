#include "BinTree.h"

#include <stdlib.h>
#include <stdio.h>

void initBinTree(BinTree* tree)
{
    *tree = NULL;
}

static BinTreeNode* createNewNode(const ElementType* x)
{
    BinTreeNode* newNode = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if (!newNode)
    {
        fprintf(stderr, "bad alloc");
        exit(EXIT_FAILURE);
    }

    newNode->data = *x;
    newNode->bf = 0;
    newNode->lchild = newNode->rchild = NULL;

    return newNode;
}

int insertBinTree(BinTree* tree, const ElementType* x,
        int(*less)(const ElementType*, const ElementType*))
{
    int sign;

    if (*tree == NULL)
    {
        *tree = createNewNode(x);
        return 1;
    }
    else if (less(&(*tree)->data, x))
    {
        return insertBinTree(&(*tree)->rchild, x, less);
    }
    else if (less(x, &(*tree)->data))
    {
        return insertBinTree(&(*tree)->lchild, x, less);
    }
    else
        return 0;
}

static ElementType findMin(BinTree tree)
{
    while (tree->lchild)
    {
        tree = tree->lchild;
    }
    return tree->data;
}

int removeBinTree(BinTree* tree, const ElementType* x,
        int(*less)(const ElementType*, const ElementType*))
{
    if (*tree == NULL)
        return 0;
    
    int sign;
    
    if (less(&(*tree)->data, x))
    {
        return removeBinTree(&(*tree)->rchild, x, less);
    }
    else if (less(x, &(*tree)->data))
    {
        return removeBinTree(&(*tree)->lchild, x, less);
    }
    else
    {
        if (!(*tree)->lchild)
        {
            *tree = (*tree)->rchild;
        }
        else if (!(*tree)->rchild)
        {
            *tree = (*tree)->lchild;
        }
        else
        {
            (*tree)->data = findMin((*tree)->rchild);
            return removeBinTree(& (*tree)->rchild, & (*tree)->data, less);
        }
        return 1;
    }
}

static void clearBinTree_s(BinTree tree)
{
    if (!tree)
        return;

    clearBinTree_s(tree->lchild);

    clearBinTree_s(tree->rchild);

    free(tree);
}

void clearBinTree(BinTree* tree)
{
    clearBinTree_s(*tree);
    *tree = NULL;
}

static int max(int lhs, int rhs)
{
    return lhs < rhs ? rhs : lhs;
}

static int calBf(BinTree tree)
{
    if (!tree)
        return 0;

    int leftHeight = calBf(tree->lchild);
    int rightHeight = calBf(tree->rchild);

    tree->bf = leftHeight - rightHeight;

    return max(leftHeight, rightHeight) + 1;
}

void calculateBalance(BinTree* tree)
{
    calBf(*tree);
}

static void printBinTree_s(BinTree tree, int deepth)
{
    if (tree)
        printBinTree_s(tree->rchild, deepth + 1);

    for (int i = 0; i < deepth; ++i)
    {
        printf("\t\t");
    }
    if (tree)
        printf("--[data = %d][bf = %d]\n", tree->data, tree->bf);
    else
        printf("--------------NULL\n");
    
    if (tree)
        printBinTree_s(tree->lchild, deepth + 1);
}

void printBinTree(BinTree* tree)
{
    printBinTree_s(*tree, 0);
}