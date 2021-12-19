#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

typedef struct node NODE;
typedef NODE *LIST;

void init(LIST *list);

int len_list(LIST *list);

int add_item(LIST *list, int index, int x);

int del_item(LIST *list, int index);

void print_list(LIST *list);

void clear(LIST *list);

void destory(LIST *list);

int main(void)
{
	LIST list;

	init(&list);

	// [] -> [1]
	add_item(&list, 0, 1);
	// [1] -> [1, 2]
	add_item(&list, 1, 2);
	// [1, 2] -> [3, 1, 2]
	add_item(&list, 0, 3);

	// [3, 1, 2] -> [1, 2]
	if (!del_item(&list, 0))
	{
		printf("delete failed\n");
	}

	// print "[1, 2]"
	print_list(&list);

	clear(&list);

	return 0;
}

void init(LIST *list)
{
	*list = NULL;
}

int len_list(LIST *list)
{
	NODE *cur = *list;
	int count = 0;

	while (cur)
	{
		++count;
		cur = cur->next;
	}

	return count;
}

int add_item(LIST *list, int index, int x)
{
	NODE *cur = *list;
	NODE *prev = NULL;

	for (int i = 0; i < index; ++i)
	{
		if (cur == NULL)
			return 0;

		prev = cur;
		cur = cur->next;
	}

	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if (new_node == NULL)
		return 0;
	new_node->data = x;

	if (prev == NULL)
	{
		new_node->next = *list;
		*list = new_node;
	}
	else
	{
		prev->next = new_node;
		new_node->next = cur;
	}

	return 1;
}

int del_item(LIST *list, int index)
{
	NODE *cur = *list;
	NODE *prev = NULL;

	for (int i = 0; i < index; ++i)
	{
		if (cur == NULL)
			return 0;

		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return 0;

	if (prev == NULL)
		*list = cur->next;
	else
		prev->next = cur->next;

	free(cur);

	return 1;
}

void print_list(LIST *list)
{
	NODE* cur = *list;

	printf("[");
	while (cur)
	{
		printf("%d", cur->data);
		printf("%s", (cur->next == NULL ? "" : ", "));
		cur = cur->next;
	}
	printf("]");
}

void clear(LIST* list)
{
	NODE* cur = *list;
	NODE* to_del;

	while (cur)
	{
		to_del = cur;
		cur = cur->next;
		free(to_del);
	}

	*list = NULL;
}

void destory(LIST* list)
{
	clear(list);
}