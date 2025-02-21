#include "h.h"

/*
12.  Пусть даны два массива вещественных чисел А и В 
одинаковой длины N. Будем говорить, что массивы А и В 
альтернируют, если после упорядочивания этих массивов по 
возрастанию разность A[i]-B[i] ненулевая и меняет свой знак 
при переходе от i к i+1 для всех возможных i. 
Будем считать, что при N=1 и при различных значениях A[0] и B[0]
массивы альтернируют. 
Определить, альтернируют ли данные два массива А и В. 

Ответом является слово YES, если массивы A и B альтернируют,
и слово NO в противном случае.
Это слово надо вывести в файл output.txt.
*/

int alternation_check(double* arr_a, double* arr_b, int n)
{
	int sign, cur_sign, i, k = -1;

	if (n == 0)
		return 1;

	add_coefficient_double(arr_a, arr_b, n, -1);
	print_array_double(arr_a, n);
	sign = get_sign(arr_a[0]);
	if ((n == 1) && sign)
		return 1;

	for (i = 1; i < n; ++i)
	{
		cur_sign = get_sign(arr_a[i]);
		if (cur_sign == 0)
			return 0;
		if (cur_sign != sign)
			sign *= -1;
		else
			return 0;
	}
	return 1;
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

	if ((n != n_b))
	{
		free(a);
		free(b);
		printf("Error, bad length");
		return -1;
	}

	sort_array_double(a, n);
	sort_array_double(b, n);

	f = fopen("output.txt", "w");
	
	if (alternation_check(a, b, n))
		fprintf(f, "YES");
	else
		fprintf(f, "NO");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
