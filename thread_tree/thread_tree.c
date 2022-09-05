#include "thread_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_LAST 0x4
#define IS_LEFT 0x2
#define IS_ROOT 0x1

static THREAD_TREE_NODE *create_node(void *data, th_siz_t data_size)
{
	THREAD_TREE_NODE *node = (THREAD_TREE_NODE *)malloc(sizeof(THREAD_TREE_NODE));
	void *data_m = malloc(data_size);

	if (!node || !data_m)
	{
		fprintf(stderr, "no memory\n");
		exit(EXIT_FAILURE);
	}

	memcpy(data_m, data, data_size);

	node->data = data_m;
	node->left = node->right = NULL;
	node->ltag = node->rtag = 0;

	return node;
}

static void destroy(THREAD_TREE_NODE *root)
{
	if (!root)
		return;

	if (root->ltag == 0)
		destroy(root->left);

	if (root->rtag == 0)
		destroy(root->right);

	free(root->data);
	free(root);
}

static int insert(THREAD_TREE_NODE **node, void *data, THREAD_TREE *tree)
{
	if (!*node)
	{
		THREAD_TREE_NODE *new_node = create_node(data, tree->data_size);
		*node = new_node;
		return 1;
	}

	int comp_result = tree->compare(data, (*node)->data);

	if (comp_result < 0)
	{
		return insert(&(*node)->left, data, tree);
	}
	else if (comp_result > 0)
	{
		return insert(&(*node)->right, data, tree);
	}

	return 0;
}

static THREAD_TREE_NODE *nlr_thread(THREAD_TREE_NODE *root, THREAD_TREE_NODE *prev)
{
	if (!root)
		return prev;

	prev = nlr_thread(root->left, prev);

	if (root->left == NULL)
	{
		root->left = prev;
		root->ltag = 1;
	}

	if (prev && prev->right == NULL)
	{
		prev->right = root;
		prev->rtag = 1;
	}

	return nlr_thread(root->right, root);
}

static void print(THREAD_TREE_NODE *root,
				  void (*print_data)(void *),
				  int depth,
				  int *prefixes,
				  int max_depth,
				  int tag)
{
	static char *prefix[2] = {"|    ", "     "};

	if (depth == max_depth || !root)
		return;

	for (int i = 0; i < depth; ++i)
		printf("%s", prefix[prefixes[i]]);

	if (tag & IS_LAST)
	{
		prefixes[depth++] = 1;
		printf("`----");
	}
	else
	{
		prefixes[depth++] = 0;
		printf("|----");
	}

	printf("[addr = %p,data = ", root);
	print_data(root->data);
	printf(",ltag = %d,rtag = %d]", root->ltag, root->rtag);

	if (root->ltag)
		printf("[lthread = %p]", root->left);
	if (root->rtag)
		printf("[rthread = %p]", root->right);

	if (!(tag & IS_ROOT))
	{
		printf("<%c>", tag & IS_LEFT ? 'L' : 'R');
	}
	putchar('\n');

	if (!root->ltag)
		print(root->left, print_data, depth, prefixes, max_depth,
			  IS_LEFT | (root->rtag || !root->right ? IS_LAST : 0));

	if (!root->rtag)
		print(root->right, print_data, depth, prefixes, max_depth, IS_LAST);
}

static THREAD_TREE_NODE *first_node(THREAD_TREE_NODE *root)
{
	while (root->left && root->ltag == 0)
		root = root->left;

	return root;
}

static THREAD_TREE_NODE *next_node(THREAD_TREE_NODE *root)
{
	if (root->rtag)
		return root->right;

	return first_node(root->right);
}

THREAD_TREE *th_tree_init(th_siz_t data_size, int (*compare)(void *, void *))
{
	THREAD_TREE *tree = (THREAD_TREE *)malloc(sizeof(THREAD_TREE));

	tree->root = NULL;
	tree->data_size = data_size;
	tree->compare = compare;

	return tree;
}

int th_tree_insert(THREAD_TREE *tree, void *data)
{
	return insert(&tree->root, data, tree);
}

void th_tree_destroy(THREAD_TREE *tree)
{
	destroy(tree->root);

	free(tree);
}

void th_tree_nlr_thread(THREAD_TREE *tree)
{
	THREAD_TREE_NODE *prev = nlr_thread(tree->root, NULL);

	prev->right = NULL;
	prev->rtag = 1;
}

void th_tree_print(THREAD_TREE *tree, void (*print_data)(void *), int max_depth)
{
	int *prefixes = (int *)malloc(sizeof(int) * max_depth);
	if (!prefixes)
	{
		fprintf(stderr, "no memory\n");
		exit(EXIT_FAILURE);
	}

	print(tree->root, print_data, 0, prefixes, max_depth, IS_LAST | IS_ROOT);

	free(prefixes);
}

void th_tree_print_ordered(THREAD_TREE *tree, void (*print_data)(void *))
{
	for (THREAD_TREE_NODE *p = first_node(tree->root); p; p = next_node(p))
	{
		printf("[");
		print_data(p->data);
		printf("]");
	}
}