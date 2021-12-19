#include <stdio.h>

void quick_sort_base(int* array, int head, int tail) //[head, tail]
{
	if (head >= tail)
		return;
	
	int h = head;
	int t = tail;
	int mark = array[head];
	
	while (head != tail)
	{
		while (head != tail && array[tail] >= mark)
			--tail;
		array[head] = array[tail];

		while (head != tail && array[head] <= mark)
			++head;
		array[tail] = array[head];
	}

	array[head] = mark;

	quick_sort_base(array, h, head - 1);
	quick_sort_base(array, head + 1, t);
}

void quick_sort(int* array, size_t size)
{
	if (size <= 1)
		return;
	
	quick_sort_base(array, 0, size - 1);
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
	int a[] = {10, 9, 8, 7};

	quick_sort(a, 4);
	print_array(a, 4);

	return 0;
}