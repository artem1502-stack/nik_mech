#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
2.  Для двух массивов вещественных чисел А и В длиной M и N
соответственно определим процедуру сравнения следующим
образом: A<B если после упорядочивания каждого из этих 
массивов по убыванию его элементов количество таких i, для 
которых выполнено неравенство A[i]<B[i] больше, чем тех, для
которых оно не выполнено,  при этом, если i выходит за границы
индексов какого-то из массивов, то соответствующее неравенство
исключается из рассмотрения и не учитывается при формировании
ответа. Для двух заданных массивов А и В нужно проверить
выполнение неравенства A<B. Ответом является слово YES, если неравенство A<B выполнено, и слово NO в противном случае. Это слово надо вывести в файл output.txt.

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
			if (array[j] < array[j + 1])
			{
				x = array[j + 1];
				array[j + 1] = array[j];
				array[j] = x;
			}

}


int is_less(double *a, double *b, int m, int n)
{
	int i, counter = 0, k;

	k = m ? m<n : n;

	for (i = 0; i < k; ++i)
	{
		if (a[i] < b[i])
			counter++;
	}
	return counter > k - counter;
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

	f = fopen("output.txt", "w");
	if (is_less(a, b, m, n))
		fprintf(f, "YES\n");
	else
		fprintf(f, "NO\n");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
