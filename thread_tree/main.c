#include "thread_tree.h"

#include <stdio.h>

int compare(void *lhs, void *rhs)
{
	return *(int *)lhs - *(int *)rhs;
}

void print_int(void* data)
{
	printf("%d", *(int*)data);
}

int main()
{
	THREAD_TREE *tree = th_tree_init(sizeof(int), compare);

	int digits[10] = {5, 4, 3, 6, 2, 1, 10, 8, 9, 7};
	for (int i = 0; i < 10; ++i)
	{
		th_tree_insert(tree, (void *)&digits[i]);
	}

	th_tree_print(tree, print_int, 6);
	th_tree_lnr_thread(tree);
	th_tree_print(tree, print_int, 6);

	th_tree_print_ordered(tree, print_int);
	putchar('\n');

	th_tree_destroy(tree);

	return 0;
}