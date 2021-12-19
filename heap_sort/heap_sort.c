#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int int_cmp(int lhs, int rhs)
{
	return lhs - rhs;
}

// assume array[1...size] is a heap, move heap[pos] to right location
static void heap_adjust(int *array, int pos, int size, int (*cmp)(int, int))
{
	int temp, child;

	temp = array[pos];
	// for (child = pos * 2; child <= size; pos = child, child *= 2)
	for (child = (pos << 1); child <= size; pos = child, child <<= 1)
	{
		if (child != size && cmp(array[child + 1], array[child]) < 0)
			++child;

		if (cmp(array[child], temp) > 0)
			break;

		array[pos] = array[child];
	}
	array[pos] = temp;
}

// let [head, tail) be a heap
void heap_init(int *head, int *tail, int (*cmp)(int, int))
{
	if (head >= tail - 1)
		return;

	int *array = head - 1;
	int size = tail - head;

	for (int cur = size / 2; cur >= 1; --cur)
	{
		heap_adjust(array, cur, size, cmp);
	}
}

// assume [head, tail) is heap, pop top of heap to leaf node
void heap_pop(int* head, int* tail, int (*cmp)(int, int))
{
	int temp = *head;
	*head = *(tail - 1);
	*(tail - 1) = temp;

	heap_adjust(head - 1, 1, tail - head - 1, cmp);
}

// sort [head, tail)
void heap_sort(int* head, int* tail, int (*cmp)(int, int))
{
	heap_init(head, tail, cmp);

	while (head < tail - 1)
	{
		heap_pop(head, tail, cmp);
		--tail;
	}
}

void print_array(int *array, size_t size)
{
	printf("[");
	for (int i = 0; i < size; ++i)
	{
		printf("%d", array[i]);
		if (i != size - 1)
			printf(", ");
	}
	printf("]\n");
}

int main(void)
{
	int n;
	srand(time(NULL));

	printf("input N: ");
	scanf("%d", &n);

	int *array = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i)
		array[i] = rand();

	printf("origin:\n");
	print_array(array, n);

	printf("after heap sort:\n");
	heap_sort(array, array + n, int_cmp);
	print_array(array, n);

	free(array);

	return 0;
}