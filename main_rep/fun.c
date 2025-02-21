#include "h.h"

void print_array(int *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

void fprint_array(FILE *f, int *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		fprintf(f, "%d ", array[i]);
	fprintf(f, "\n");
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

int *copy_array(int *array, int n)
{
	int *new_array, i;

	new_array = (int *)malloc(n * sizeof(int));
	for(i = 0; i < n; ++i)
		new_array[i] = array[i];
	return new_array;
}

void add_coefficient(int *a, int *b, int n, int c)
{
	int i;

	for(i = 0; i < n; ++i)
		a[i] += b[i] * c;
}

int get_sign(double x)
{
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	else
		return 0;
}

void add_coefficient_double(double *a, double *b, int n, int c)
{
	int i;

	for(i = 0; i < n; ++i)
		a[i] += b[i] * c;
}

void print_array_double(double *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		printf("%.3lf ", array[i]);
	printf("\n");
}

void fprint_array_double(FILE *f, double *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		fprintf(f, "%.3lf ", array[i]);
	fprintf(f, "\n");
}

double *read_array_double(FILE *f, int *n)
{
	double *array;
	int len, i;

	if (fscanf(f, "%d", &len) != 1)
	{
		printf("ERROR EMPTY FILE\n");
		return NULL;
	}
	*n = len;

	array = (double *)malloc(len * sizeof(double));

	for (i = 0; i < len; ++i)
		fscanf(f, "%lf", &(array[i]));
	return array;
}

double *read_array_smart_double(FILE *f, int *n)
{
	double *array;
	int len = 0, max_len = 256;

	array = (double *)malloc(max_len * sizeof(double));
	while (fscanf(f, "%lf", &(array[len])) == 1)
	{
		len++;
		if (len >= max_len - 1)
		{
			max_len *= 2;
			array = (double *)realloc(array, max_len * sizeof(double));
		}
	}
	*n = len;
	return array;
}

void sort_array_double(double *array, int n)
{
	int i, j;
	double x;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n - 1; ++j)
			if (array[j] > array[j + 1])
			{
				x = array[j + 1];
				array[j + 1] = array[j];
				array[j] = x;
			}
}

void sort_array_decreasing_double(double *array, int n)
{
	int i, j;
	double x;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n - 1; ++j)
			if (array[j] < array[j + 1])
			{
				x = array[j + 1];
				array[j + 1] = array[j];
				array[j] = x;
			}
}


