#include "BinTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int less(const int* lhs, const int* rhs)
{
    return *lhs < *rhs;
}

int main(void)
{
    int digit;
    int count;
    BinTree tree;

    initBinTree(&tree);
    srand(time(NULL));

    scanf("%d", &count);

    while (count--)
    {
        digit = rand();
        insertBinTree(&tree, &digit, less);
    }

    printBinTree(&tree);

    printf("after calculate bf:\n");
    calculateBalance(&tree);

    printBinTree(&tree);

    clearBinTree(&tree);

    return 0;
}