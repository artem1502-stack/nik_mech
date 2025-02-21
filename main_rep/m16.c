#include "h.h"

/*

16.  Пусть даны два массива целых чисел А и В длиной M и N
соответственно.  Требуется упорядочить эти два массива по
возрастанию, уплотнить эти массивы, удалив из них все
повторяющиеся элементы, кроме первого из них 
(т.е. вместо всех повторяющихся элементов остается только
первый из них), и определить новые получившиеся длины массивов
после такого уплотнения. После этого в файл output.txt надо
вывести эти новые длины массивов А и В и далее по возрастанию
все элементы нового массива А, которые не содержатся в массиве В.

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
	int *new_arr_a, *new_arr_b;
	int new_n_a, new_n_b;
	int i;
	
	new_arr_a = get_ideal(arr_a, n_a, &new_n_a);
	new_arr_b = get_ideal(arr_b, n_b, &new_n_b);
	fprintf(f, "%d %d\n", new_n_a, new_n_b);
	print_array(new_arr_a, new_n_a);
	print_array(new_arr_b, new_n_b);
	for (i = 0; i < new_n_a; i++)
		if (!is_in(new_arr_b, new_n_b, new_arr_a[i]))
			fprintf(f, "%d ", new_arr_a[i]);
	free(new_arr_a);
	free(new_arr_b);
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
