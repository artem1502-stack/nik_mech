#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

1 3 7 8
5 7 10
if (max(a) > min(b))
	1 случай
else if (max(x) == min(b))
	выводим 1
else
	выводим 0

a_max, b_min

for (i = a_max; i >= 0 && a[i] > b[b_min]; i--)
	

int *read_array(FILE *f, int *n)
{
	int *array;
	int len, i;

	if (fscanf(f, "%d", &len) != 1)
	{
		printf("ERROR EMPTY FILE\n");
		return NULL;
	}
	*n = len;

	array = (int *)malloc(len * sizeof(int));

	for (i = 0; i < len; ++i)
		fscanf(f, "%d", &(array[i]));
	return array;
}

void print_array(int *array, int n)
{
	int i;

	for(i = 0; i < n; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

void sort_array(int *array, int n)
{
	int i, j;
	int x;

	for(i = 0; i < n; ++i)
		for(j = 0; j < n - 1; ++j)
			if (array[j] < array[j + 1])
			{
				x = array[j + 1];
				array[j + 1] = array[j];
				array[j] = x;
			}

}


int power_of_intersection(int *a, int *b, int m, int n)
{
	int i, counter = 0, k;

	k = m ? m<n : n;

	for (i = 0; i < k; ++i)
	{
		if (a[i] < b[i])
			counter++;
	}
	return counter > k - counter;
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
	print_array(a, m);
	print_array(b, n);

	f = fopen("output.txt", "w");
	fprintf(f, "%d\n", power_of_intersection(a, b, m, n));
	fclose(f);
	free(a);
	free(b);
	return 0;
}
