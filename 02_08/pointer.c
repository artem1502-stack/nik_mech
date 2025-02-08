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

int main(void)
{
	int x[N];
	int *y;
	int i;


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
