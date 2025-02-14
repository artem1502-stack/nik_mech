#include "h.h"

/*
4. Будем говорить, что для двух массивов целых чисел А и В
длиной M и N соответственно выполнено вложение А в В, 
если после упорядочивания по возрастанию каждого из этих
массивов массив А является непрерывным участком в массиве В,
т.е. для некоторого k и всех i=0,...,M-1 выполнено A[i]=B[i+k],
при этом, если M>N, то вложение считается сразу невыполненным. 
Для двух заданных массивов А и В проверить выполнение вложения
А и В. 

Ответом является слово YES, если вложение A в B выполнено, 
и слово NO в противном случае. Это слово надо вывести 
в файл output.txt.
*/

int is_included(int *arr_a, int n_a, int *arr_b, int n_b)
{
	int i = 0, j = 0;
	if (n_a > n_b)
		return 0;

	for (i = 0; i < n_b; ++i)
	{
		if (arr_b[i] == arr_a[0])
		{
			for (j = 0; (j < n_a) && (i + j < n_b); ++j)
			{
				if (arr_b[i + j] != arr_a[j])
					break;
			}
			if (j >= n_a)
				return 1;
		}
	}
	return 0;
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
	if (is_included(a, m, b, n))
		fprintf(f,"YES\n");
	else
		fprintf(f,"NO\n");
	fclose(f);
	free(a);
	free(b);
	return 0;
}
