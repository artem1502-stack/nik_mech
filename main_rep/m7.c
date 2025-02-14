#include "h.h"

/*
7.  Будем называть два массива целых чисел А и В длиной M и N
соответственно параллельными, если после упорядочивания 
каждого из них по возрастанию их элементов 
мы имеем соотношение A[i]-B[i] = const для всех
0 <= i < min{M,N}. Для двух заданных массивов А и В нужно
определить, являются ли они параллельными. 

Ответом является слово YES, если массивы параллельны,
и слово NO в противном случае. 
Это слово надо вывести в файл output.txt.
*/

int check_arrays(int* arr_a, int n_a, int* arr_b, int n_b)
{
	int i, ln = MIN(n_a, n_b);
	int delta;

	if (ln <= 0)
		return 1;
	delta = arr_a[0] - arr_b[0];
	for (i = 1; i < ln; ++i)
	{
		if (delta != arr_a[i] - arr_b[i])
			return 0;
	}
	return 1;
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

	sort_array(a, m);
	sort_array(b, n);

	f = fopen("output.txt", "w");
	if (check_arrays(a, m, b, n))
		fprintf(f,"YES\n");
	else
		fprintf(f,"NO\n");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
