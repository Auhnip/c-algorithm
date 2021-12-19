#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ELEM_TYPE;

typedef struct
{
	ELEM_TYPE* array;
	size_t size;
	size_t capacity;
} ARRAY_LIST;

void init_arr(ARRAY_LIST* arr)
{
	arr->array = NULL;
	arr->size = 0;
	arr->capacity = 0;
}

static void adjust_arr(ARRAY_LIST* arr, size_t space)
{
	if (arr->size + space <= arr->capacity)
		return;
	
	size_t new_cap = (arr->capacity ? arr->capacity << 1 : 1);
	while (new_cap < arr->size + space)
		new_cap <<= 1;

	ELEM_TYPE* new_arr = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * new_cap);
	if (!new_arr)
	{
		fprintf(stderr, "bad alloc\n");
		exit(EXIT_FAILURE);
	}

	memcpy(new_arr, arr->array, arr->size * sizeof(ELEM_TYPE));

	free(arr->array);
	arr->array = new_arr;
	arr->capacity = new_cap;
}

// insert a elements: x
_Bool insert_arr(ARRAY_LIST* arr, size_t index, ELEM_TYPE x)
{
	if (index < 0 || index > arr->size)
		return 0;
	
	adjust_arr(arr, 1);

	for (int i = arr->size; i != index; --i)
		arr->array[i] = arr->array[i - 1];

	arr->array[index] = x;
	++ arr->size;
	
	return 1;
}

// insert a array: x_arr[len]
_Bool insert_arra(ARRAY_LIST* arr, size_t index, const ELEM_TYPE* x_arr, size_t len)
{
	if (index < 0 || index > arr->size)
		return 0;
	
	adjust_arr(arr, len);

	for (int i = arr->size - 1; i != index - 1; --i)
		arr->array[i + len] = arr->array[i];
	
	memcpy(arr->array + index, x_arr, len * sizeof(ELEM_TYPE));
	arr->size += len;

	return 1;
}

_Bool del_arr(ARRAY_LIST* arr, size_t index)
{
	if (index < 0 || index >= arr->size)
		return 0;
	
	for (int i = index; i != arr->size - 1; ++i)
		arr->array[i] = arr->array[i + 1];
	--arr->size;

	return 1;
}

void for_arr(ARRAY_LIST* arr, void (*func)(ELEM_TYPE*))
{
	for (int i = 0; i < arr->size; ++i)
		func(& arr->array[i]);
}

void print_arr_as_int(const ARRAY_LIST* arr)
{
	printf("[");
	for (int i = 0; i < arr->size; ++i)
	{
		printf("%d", arr->array[i]);
		if (i != arr->size - 1)
			putchar(',');
	}
	puts("]");
}

void mul2(int* i)
{
	*i *= 2;
}

void destroy_arr(ARRAY_LIST* arr)
{
	free(arr->array);
	arr->array = NULL;
	arr->capacity = arr->size = 0;
}

int main(void)
{
	ARRAY_LIST arr;

	int a[3] = {1, 2, 3};

	// initialize arr, arr = []
	init_arr(&arr);
	// print content of arr
	printf("after init_arr(&arr),\narr = ");
	print_arr_as_int(&arr);

	// insert a[3] to arr[0], arr = [1, 2, 3]
	insert_arra(&arr, 0, a, 3);
	// print content of arr
	printf("after insert_arra(&arr, 0, a, 3),\narr = ");
	print_arr_as_int(&arr);

	// insert a[3] to arr[1], arr = [1, 1, 2, 3, 2 ,3]
	insert_arra(&arr, 1, a, 3);
	// print content of arr
	printf("after insert_arra(&arr, 1, a, 3),\narr = ");
	print_arr_as_int(&arr);

	// let arr = arr * 2, arr = [2, 2, 4, 6, 4, 6]
	for_arr(&arr, mul2);
	// print content of arr
	printf("after for_arr(&arr, mul2),\narr = ");
	print_arr_as_int(&arr);

	destroy_arr(&arr);

	puts("print enter to exit");
	getchar();

	return 0;
}