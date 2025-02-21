#include "h.h"

/*
14.  Пусть даны два массива целых чисел А и В длиной M и N соответственно. 
Будем говорить, что массив А более устойчив, чем массив В, если наибольшее 
количество одинаковых значений в массиве А строго больше, чем наибольшее количество 
одинаковых значений в массиве В. Например, массив А={1,3,7,3,4,3} более 
устойчив, чем массив В1={4,5,4,5,2} (в А значение 3 повторяется 3 раза, но в В 
любые значения встречаются не более 2 раз). 
Определить, какой из данных массивов более устойчив. 

Ответом является число 1, если  А более устойчив, чем В, число -1, если 
В более устойчив, чем А, и число 0 в противном случае. 
Это слово надо вывести в файл output.txt.


*/

int is_unique(int *arr, int n)
{
	int i;

	for(i = 0; i < n - 1; ++i)
		if (arr[i] == arr[i + 1])
			return 0;
	return 1;
}

int check_arrays(int* arr_a, int* arr_b, int n_a, int n_b)
{
	int i = 0, j = 0, flag_a;

	if ((n_a == 0) || ((n_a == 1) && (n_b == 0)))
		return 1;
	if (n_b == 0)
		return 0;


	if (arr_a[0] < arr_b[0])
	{
		i++;
		flag_a = 1;
	}
	else
	{
		j++;
		flag_a = 0;
	}

	while((i < n_a) && (j < n_b))
	{
		if (arr_a[i] < arr_b[j])
		{
			if (flag_a)
				return 0;
			i++;
			flag_a = 1;
		}
		else
		{
			flag_a = 0;
			j++;
		}
	}
	if ((i >= n_a) || ((i == n_a - 1) && (!flag_a)))
		return 1;
	return 0;
}

int main(void)
{
	int *a, *b;
	int n_a, n_b;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array_smart(f, &n_a);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array_smart(f, &n_b);
	fclose(f);

	sort_array(a, n_a);
	sort_array(b, n_b);

	f = fopen("output.txt", "w");
	if (check_arrays(a, b, n_a, n_b))
		fprintf(f, "YES");
	else
		fprintf(f, "NO");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
