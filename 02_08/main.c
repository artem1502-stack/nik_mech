#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
1.  Для двух массивов вещественных чисел А и В длиной M и N
соответственно определим процедуру сравнения следующим
образом: A<B если после упорядочивания каждого из этих массивов
по возрастанию его элементов для всех i выполнено 
неравeнство A[i] < B[i], при этом, если i выходит за границы
индексов какого-то из массивов, то вместо значения i-го элемента
рассматривается максимальное значение в соответствующем массиве. 
Для двух заданных массивов А и В нужно проверить выполнение 
неравенства A < B.
*/

double *read_array(FILE *f, int *n)
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

void print_array(double *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		printf("%.3lf ", array[i]);
	printf("\n");
}

void sort_array(double *array, int n)
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

double find_max(double *array, int n)
{
	int i;
	double cur_max = array[0];

	for (i = 1; i < n; ++i)
	{
		if (array[i] > cur_max)
			cur_max = array[i];
	}
	return cur_max;
}

int is_less(double *a, double *b, int m, int n)
{
	double max_a = find_max(a, m), max_b = find_max(b, n);
	int i = 0, j = 0;

	while ((i < m) && (j < n))
	{
		if (a[i] >= b[i])
			return 0;
		i++;
		j++;
	}
	if (m == n)
	{
		return 1;
	}
	else if (i >= m)
	{
		if (max_a >= b[i])
			return 0;
	}
	else
	{
		if (a[m - 1] >= max_b)
			return 0;
	}
	return 1;
}

int main(void)
{
	double *a, *b;
	int m, n;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array(f, &m);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array(f, &n);
	fclose(f);

	sort_array(a, m);
	sort_array(b, n);
	print_array(a, m);
	print_array(b, n);

	if (is_less(a, b, m, n))
		printf("A < B\n");
	else
		printf("A не < B\n");
	free(a);
	free(b);
	return 0;
}




