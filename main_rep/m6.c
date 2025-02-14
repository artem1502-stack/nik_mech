#include "h.h"

/*

6.  Пусть даны два массива вещественных чисел А и В длиной
M и N соответственно. Будем говорить, что эти два массива
сближаются, если после упорядочивания каждого 
из них по возрастанию их элементов величины |A[i]-B[i]|
образуют невозрастающую последовательность при 
0<= i < min{M,N}. Последовательность из одного элемента 
считается невозрастающей. Для двух заданных массивов А и В 
нужно определить, являются ли они сближающимися. 
 
Ответом является слово YES, если массивы сближаются, 
и слово NO в противном случае. 
Это слово надо вывести в файл output.txt.

*/

int check_arrays(double* arr_a, int n_a, double* arr_b, int n_b)
{
	int i, ln = MIN(n_a, n_b);
	double prev, new;

	if (ln <= 0)
		return 1;
	prev = ABS(arr_a[0] - arr_b[0]);
	for (i = 1; i < ln; ++i)
	{
		new = ABS(arr_a[i] - arr_b[i]);
		if (new > prev)
			return 0;
		prev = new;
	}
	return 1;
}

int main(void)
{
	double *a, *b;
	int m, n;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array_smart_double(f, &m);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array_smart_double(f, &n);
	fclose(f);

	sort_array_double(a, m);
	sort_array_double(b, n);

	f = fopen("output.txt", "w");
	if (check_arrays(a, m, b, n))
		fprintf(f,"YES\n");
	else
		fprintf(f,"NO\n");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
