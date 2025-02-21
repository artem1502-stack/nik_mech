#include "h.h"

/*
14.  Пусть даны два массива целых чисел А и В длиной M и N
соответственно. Будем говорить, что массив А более устойчив,
чем массив В, если наибольшее количество одинаковых значений
в массиве А строго больше, чем наибольшее количество 
одинаковых значений в массиве В. Например, массив 
А={1,3,7,3,4,3} более устойчив, чем массив В1={4,5,4,5,2}
(в А значение 3 повторяется 3 раза, но в В любые значения
встречаются не более 2 раз). 
Определить, какой из данных массивов более устойчив. 

Ответом является число 1, если  А более устойчив, чем В, 
число -1, если В более устойчив, чем А, и число 0 в противном
случае. Это слово надо вывести в файл output.txt.

*/

int count_stable(int *array, int n)
{
	int i, cur_stable = 1, max_stable = 1;

	if (n <= 1)
		return n;

	for (i = 1; i < n; ++i)
	{
		if (array[i] != array[i - 1])
		{
			max_stable = MAX(max_stable, cur_stable);
			cur_stable = 1;
		}
		else
			cur_stable++;
	}
	return MAX(max_stable, cur_stable);
}

int check_arrays(int* arr_a, int* arr_b, int n_a, int n_b)
{
	return get_sign(count_stable(arr_a, n_a) - count_stable(arr_b, n_b));
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
	fprintf(f, "%d", check_arrays(a, b, n_a, n_b));
	fclose(f);
	free(a);
	free(b);
	return 0;
}
