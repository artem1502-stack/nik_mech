#include "h.h"

/*
9.  Пусть даны два массива целых чисел А и В одинаковой длины N.
Будем говорить, что эти два массива независимы,
если значения разностей A[i]-B[i] не повторяются,
т.е. все различны. Будем считать, что массивы, состоящие из 
одного элемента, независимы. Для двух заданных массивов 
А и В нужно определить, являются ли они независимыми в
исходном состоянии и после упорядочивания каждого из этих
массивов по возрастанию. 

Ответом являются два слова вида YES NO:
первое (YES или NO) обозначает 
независимость исходных массивов,
второе (YES или NO) обозначает независимость 
массивов после их упорядочивания. 
Эти слова надо вывести в файл output.txt.

*/

int is_unique(int *arr, int n)
{
	int i;

	for(i = 0; i < n - 1; ++i)
		if (arr[i] == arr[i + 1])
			return 0;
	return 1;
}

void check_arrays(int* arr_a, int* arr_b, int n, FILE *f)
{
	int *temp;

	temp = copy_array(arr_a, n);
	add_coefficient(temp, arr_b, n, -1);
	sort_array(temp, n);
	if (is_unique(temp, n))
		fprintf(f, "YES ");
	else
		fprintf(f, "NO ");
	free(temp);
	sort_array(arr_a, n);
	sort_array(arr_b, n);
	add_coefficient(arr_a, arr_b, n, -1);
	sort_array(arr_a, n);
	if (is_unique(arr_a, n))
		fprintf(f, "YES");
	else
		fprintf(f, "NO");
}

int main(void)
{
	int *a, *b;
	int m, n;
	FILE *f;

	f = fopen("f_a", "r");
	a = read_array_smart(f, &m);
	fclose(f);
	f = fopen("f_b", "r");
	b = read_array_smart(f, &n);
	fclose(f);
	if (n != m)
	{
		printf("Error. Wrong sizes\n");
		free(a);
		free(b);
		return -1;
	}

	f = fopen("output.txt", "w");
	check_arrays(a, b, n, f);
	fclose(f);
	free(a);
	free(b);
	return 0;
}
