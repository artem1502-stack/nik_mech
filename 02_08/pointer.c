#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void plus_one(int *a)
{
	*a += 1;
}

void bad_plus_one(int b)
{
	b += 1;
}

double *read_array(FILE *f, int *n)
{
	double *array;
	int len;

	if (fscanf(f, "%d", &len) != 1)
	{
		printf("ERROR EMPTY FILE\n");
		return NULL;
	}
	*n = len;

}

int main(void)
{
	int x[N];
	int *y;
	int i, n;


	y = (int *)malloc(N * sizeof(int));

	for(i = 0; i < N; ++i)
	{
		x[i] = (i + 1) * (i + 1);
		y[i] = (i + 1) * (i + 1);
		printf("%d\t%d\n", x[i], y[i]);
	}

/*
	*y = y[0]
	y[2] = *(y + 2)
	y[i] = *(y + i)
*/
	printf("%d\n", *y);

	free(y);

	return 0;
}
