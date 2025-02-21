#include "h.h"

/*
13.  Пусть даны два массива целых чисел А и В длиной M и N
соответственно. Будем говорить, что массив А дополняет массив В,
если объединенное множество значений элементов этих массивов
заполняет целиком некоторый отрезок ряда целых чисел. 
Например, массив А={1,3,7} дополняет массив B={2,6,4,5},
но не дополняет массив В1={4,5}. Определить, дополняет ли
данный массив А данный массив В. 

Ответом является слово YES, если массив А дополняет В,
и слово NO в противном случае.
Это слово надо вывести в файл output.txt.

*/

int *read_two_arrays(const char *file1, const char *file2, int *n)
{
	int *array;
	int len = 0, max_len = 256;
	FILE *f;

	array = (int *)malloc(max_len * sizeof(int));
	f = fopen(file1, "r");
	while (fscanf(f, "%d", &(array[len])) == 1)
	{
		len++;
		if (len >= max_len - 1)
		{
			max_len *= 2;
			array = (int *)realloc(array, max_len * sizeof(int));
		}
	}
	fclose(f);
	f = fopen(file2, "r");
	while (fscanf(f, "%d", &(array[len])) == 1)
	{
		len++;
		if (len >= max_len - 1)
		{
			max_len *= 2;
			array = (int *)realloc(array, max_len * sizeof(int));
		}
	}
	fclose(f);
	*n = len;
	return array;
}

int check_complete(int *array, int n)
{
	int i;

	for (i = 1; i < n; ++i)
		if (array[i] - array[i - 1] > 1)
			return 0;
	return 1;
}

int main(void)
{
	int *a;
	int n;
	FILE *f;
	
	a = read_two_arrays("f_a", "f_b", &n);
	sort_array(a, n);

	print_array(a, n);

	f = fopen("output.txt", "w");
	if (check_complete(a, n))
		fprintf(f, "YES");
	else
		fprintf(f, "NO");
	fclose(f);
	free(a);
	return 0;
}
