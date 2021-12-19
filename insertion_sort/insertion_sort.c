#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* array, size_t size)
{
	size_t tail;
	size_t in;
	int temp;

	for (tail = 1; tail < size; ++tail)
	{
		temp = array[tail];
		for (in = tail; in > 0 && array[in - 1] > temp; --in)
		{
			array[in] = array[in - 1];
		}
		array[in] = temp;
	}
}

void print_array(int* array, size_t size)
{
	printf("[");
	for (int i = 0; i < size; ++i)
	{
		printf("%d", array[i]);
		if (i != size - 1)
			printf(", ");
	}
	printf("]");
}

int main(void)
{
	int n;
	
	printf("input N: ");
	scanf("%d", &n);

	printf("input N digits: ");
	int* array = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &array[i]);
	
	printf("before insertion sort: ");
	print_array(array, n);
	putchar('\n');

	insertion_sort(array, n);

	printf("after insertion sort: ");
	print_array(array, n);
	putchar('\n');

	free(array);

	return 0;
}