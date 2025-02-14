#include "h.h"

/*
5. Для двух массивов вещественных чисел А и В длиной M и N
соответственно назовем порядком сравнения A<B следующую
величину: массивы А и В упорядочиваются 
по убыванию их элементов и после этого подсчитывается
количество выполненных неравенств A[i]<B[i] при
0<= i < min{M,N}. 
Для двух заданных массивов 
А и В нужно определить порядки сравнений A<B и B<A. 

Ответом являются два целых числа --- указанные порядки 
cравнения. 
Эти два числа надо вывести в файл output.txt.

*/

void comparison(double* arr_a, int n_a, double* arr_b, int n_b, int *ans1, int *ans2)
{
	int i, ln = MIN(n_a, n_b);

	for(i = 0; i < ln; ++i)
		if (arr_a[i] < arr_b[i])
			(*ans1)++;
		else if (arr_a[i] > arr_b[i])
			(*ans2)++;
}

int main(void)
{
	double *a, *b;
	int ans1 = 0, ans2 = 0;
	int m, n;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array_smart_double(f, &m);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array_smart_double(f, &n);
	fclose(f);

	sort_array_decreasing_double(a, m);
	sort_array_decreasing_double(b, n);

	comparison(a, m, b, n, &ans1, &ans2);

	f = fopen("output.txt", "w");
	fprintf(f, "%d %d\n", ans1, ans2);
	fclose(f);
	free(a);
	free(b);
	return 0;
}