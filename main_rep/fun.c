#include "h.h"

void print_array(int *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

int is_in(int *arr, int n, int x)
{
	int i;

	for (i = 0; i < n; ++i)
		if (arr[i] == x)
			return 1;
	return 0;
}

int *read_array(FILE *f, int *n)
{
	int *array;
	int len, i;

	if (fscanf(f, "%d", &len) != 1)
	{
		printf("ERROR EMPTY FILE\n");
		return NULL;
	}
	*n = len;

	array = (int *)malloc(len * sizeof(int));

	for (i = 0; i < len; ++i)
		fscanf(f, "%d", &(array[i]));
	return array;
}

int *read_array_smart(FILE *f, int *n)
{
	int *array;
	int len = 0, max_len = 256;

	array = (int *)malloc(max_len * sizeof(int));
	while (fscanf(f, "%d", &(array[len])) == 1)
	{
		len++;
		if (len >= max_len - 1)
		{
			max_len *= 2;
			array = (int *)realloc(array, max_len * sizeof(int));
		}
	}
	*n = len;
	return array;
}

void sort_array(int *array, int n)
{
	int i, j;
	int x;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n - 1; ++j)
			if (array[j] > array[j + 1])
			{
				x = array[j + 1];
				array[j + 1] = array[j];
				array[j] = x;
			}
}
