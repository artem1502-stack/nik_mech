#include "h.h"

/*
11.  Пусть даны два массива вещественных чисел А и В
одинаковой длины N (N>2). Будем говорить, что массивы А и В 
пересекаются по позиции k (0<k<N-1), если после упорядочивания 
этих массивов по возрастанию найдется k, такое, 
что разность A[i]-B[i] сохраняет свой знак при i<=k и меняет
его на противоположный при i>k. При этом равенство нулю для этой
разности возможно только при i=k. Если массивы не пересекаются,
то позиция пересечения считается равной -1. 
Определить позицию, по которой пересекаются данные два массива.

Ответом является одно число --- позиция пересечения.
Это число надо вывести в файл output.txt.

*/

int intersection_position(double* arr_a, double* arr_b, int n)
{
	int sign, cur_sign, i, k = -1;

	add_coefficient_double(arr_a, arr_b, n, -1);

	sign = get_sign(arr_a[0]);
	if (sign == 0)
		return k;

	for (i = 1; i < n; ++i)
	{
		cur_sign = get_sign(arr_a[i]);
		if (cur_sign != sign)
		{
			if (k != -1)
				return -1;
			sign *= -1;
			k = i;
		}
	}
	return k;
}

int main(void)
{
	double *a, *b;
	int n, n_b;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array_smart_double(f, &n);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array_smart_double(f, &n_b);
	fclose(f);

	if ((n != n_b) || (n < 2))
	{
		free(a);
		free(b);
		printf("Error, bad length");
		return -1;
	}

	sort_array_double(a, n);
	sort_array_double(b, n);

	f = fopen("output.txt", "w");
	
	fprintf(f, "%d", intersection_position(a, b, n));
	fclose(f);
	free(a);
	free(b);
	return 0;
}
