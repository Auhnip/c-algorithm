#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int* arr, int* tmp_arr, int head1, int head2, int tail)
{
	int cur = head1;
	int head = head1;
	int tail1 = head2 - 1, tail2 = tail;

	while (head1 <= tail1 && head2 <= tail2)
	{
		if (arr[head1] < arr[head2])
		{
			tmp_arr[cur++] = arr[head1++];
		}
		else
		{
			tmp_arr[cur++] = arr[head2++];
		}
	}

	while (head1 <= tail1)
		tmp_arr[cur++] = arr[head1++];
	
	while (head2 <= tail2)
		tmp_arr[cur++] = arr[head2++];
	
	for (cur = head; cur <= tail; ++cur)
	{
		arr[cur] = tmp_arr[cur];
	}
}

void merge_sort_base(int* arr, int* tmp_arr, int head, int tail)
{
	if (head >= tail)
		return;
	
	int mid = (head + tail) / 2;
	merge_sort_base(arr, tmp_arr, head, mid);
	merge_sort_base(arr, tmp_arr, mid + 1, tail);
	merge(arr, tmp_arr, head, mid + 1, tail);
}

void merge_sort(int* array, size_t size)
{
	if (!size)
		return;
	
	int* tmp_arr = (int*)malloc(sizeof(int) * size);

	if (!tmp_arr)
	{
		fprintf(stderr, "no memory\n");
	}
	else
	{
		merge_sort_base(array, tmp_arr, 0, size - 1);
		free(tmp_arr);
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

	printf("after merge sort:\n");
	merge_sort(array, n);
	print_array(array, n);

	free(array);

	return 0;
}