#include "h.h"

/*
8.  Для двух массивов вещественных чисел А и В длиной M и N
соответственно определим операцию A = max{A,B} следующим
образом: массивы А и В упорядочиваются по возрастанию их
элементов и после этого значения элементов массива А заменяются 
соответствующими максимумами, т.е. A[i] = max{A[i],B[i]},
для всех 0<= i < min{M,N}. Если M>N и i выходит за границы
индексов массива В, то оставшиеся элементы (упорядоченного)
массива А не изменяются. Для двух заданных массивов А и В нужно 
вычислить  А = max{A,B}. 
*/

void max_array(double* arr_a, int n_a, double* arr_b, int n_b)
{
	int i, ln = MIN(n_a, n_b);

	for (i = 0; i < ln; ++i)
		arr_a[i] = MAX(arr_a[i], arr_b[i]);
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
	max_array(a, m, b, n);
	fprint_array_double(f, a, m);
	fclose(f);
	free(a);
	free(b);
	return 0;
}
