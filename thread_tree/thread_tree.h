#ifndef THREAD_TREE_H_
#define THREAD_TREE_H_

#include <stdint.h>

typedef struct thread_tree_node
{
	void* data;
	struct thread_tree_node* left;
	struct thread_tree_node* right;
	int ltag;
	int rtag;
} THREAD_TREE_NODE;

typedef uint32_t th_siz_t;

typedef struct thread_tree
{
	THREAD_TREE_NODE* root;
	th_siz_t data_size;
	int (*compare)(void*, void*);
} THREAD_TREE;

THREAD_TREE *th_tree_init(th_siz_t data_size, int (*compare)(void *, void *));

int th_tree_insert(THREAD_TREE *tree, void *data);

void th_tree_destroy(THREAD_TREE *tree);

void th_tree_lnr_thread(THREAD_TREE *tree);

void th_tree_print(THREAD_TREE *tree, void (*print_data)(void *), int max_depth);

void th_tree_print_ordered(THREAD_TREE *tree, void (*print_data)(void *));

#endif