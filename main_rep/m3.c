#include "h.h"

/*
3. Для двух массивов целых чисел А и В
длиной M и N соответственно определим понятие степени
пересечения как количество различных целых чисел,
присутствующих хотя бы в одном из массивов А и В и
принадлежащих диапазону от min{B[j]} до max{A[i]} включительно.
Например, степень пересечения массивов A={1,3,7,8} и 
B={5,7,10} есть 3.
Ответом является целое число --- искомая степень пересечения.
Это одно число надо вывести в файл output.txt.
*/

int count_intersection(int *arr_a, int n_a, int *arr_b, int n_b)
{
	int i, j;
	int *intresection_array, inter_n = 0;

	if (arr_a[n_a - 1] < arr_b[0])
		return 0;
	else if (arr_a[n_a - 1] == arr_b[0])
		return 1;

	for (i = 0; i < n_a; ++i)
		if (arr_a[i] >= arr_b[0])
			break;

	for (j = n_b - 1; j >= 0; --j)
		if (arr_b[j] <= arr_a[n_a - 1])
			break;

	intresection_array = (int *)malloc((n_a - i + 1 + j + 1) * sizeof(int));
	for (; i < n_a; ++i)
		if (!is_in(intresection_array, inter_n, arr_a[i]))
		{
			intresection_array[inter_n] = arr_a[i];
			inter_n++;
		}
	for (; j >= 0; --j)
		if (!is_in(intresection_array, inter_n, arr_b[j]))
		{
			intresection_array[inter_n] = arr_b[j];
			inter_n++;
		}
	free(intresection_array);
	return inter_n;
}

int main(void)
{
	int *a, *b;
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

	f = fopen("output.txt", "w");
	fprintf(f, "%d\n", count_intersection(a, m, b, n));
	fclose(f);
	free(a);
	free(b);
	return 0;
}
