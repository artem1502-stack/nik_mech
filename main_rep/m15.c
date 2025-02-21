#include "h.h"

/*
15.  Пусть даны два массива целых чисел А и В длиной M и N 
соответственно. Определим мощность массива как количество 
различных значений в этом массиве, а приведенным состоянием 
массива назовем упорядоченный по возрастанию набор всех 
его различных значений. Для двух массивов А и В определить,
какой массив имеет больше мощность и получить приведенное 
состояние массива с большей мощностью. 

В файл output.txt нужно вывести имя массива 
(т.е. латинскую букву А или В), 
имеющего большую мощность, и далее все упорядоченные значения 
приведенного состояния массива с большей мощностью. 
Если массивы имеют одинаковую мощность, то вывести ответ для 
массива А.


*/

int count_power(int *array, int n)
{
	int i, power = 1;

	if (n <= 1)
		return n;

	for (i = 1; i < n; ++i)
	{
		if (array[i] != array[i - 1])
			power++;
	}
	return power;
}

int *get_ideal(int *array, int n, int *new_n)
{
	int *new_array, i, new_i;

	*new_n = count_power(array, n);
	new_array = (int *)malloc((*new_n) * sizeof(int));
	new_array[0] = array[0];


	for (new_i = 1, i = 1; i < n; ++i)
		if (array[i] != array[i - 1])
		{
			new_array[new_i] = array[i];
			new_i++;
		}
	return new_array;
}

void work_with_arrays(int* arr_a, int* arr_b, int n_a, int n_b, FILE *f)
{
	int *arr;

	if (count_power(arr_a, n_a) >= count_power(arr_b, n_b))
	{
		fprintf(f, "A\n");
		arr = get_ideal(arr_a, n_a, &n_a);
		fprint_array(f, arr, n_a);
		free(arr);
	}
	else
	{
		fprintf(f, "B\n");
		arr = get_ideal(arr_b, n_b, &n_b);
		fprint_array(f, arr, n_b);
		free(arr);
	}
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
	work_with_arrays(a, b, n_a, n_b, f);
	fclose(f);
	free(a);
	free(b);
	return 0;
}
