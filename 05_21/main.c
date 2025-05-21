#include <stdlib.h>
#include <stdio.h>

double test_function(double x)
{
	return 1 / (x*x*x*x + 25);
}

void make_test(const char *sf, int n, double step)
{
	int i;
	double t = 0;
	FILE *f = fopen(sf, "w");

	fprintf(f, "%d ", n);
	for (i = 0; i < n; i++)
	{
		fprintf(f, "%lf %lf ", t, test_function(t));
		t += step;
	}
	fclose(f);
}

// Массив t - отсортирован
double interpolate(double *x, double *t, int n, double t0)
{
	int i;

	for (i = 1; i < n - 1; i++)
	{
		if (t[i + 1] >= t0)
			break ;
	}
	return x[i] + (x[i + 1] - x[i]) * (t0 - t[i]) / (t[i + 1] - t[i])
				+ (x[i + 1] - 2 * x[i] + x[i - 1]) * (t0 - t[i]) * (t0 - t[i + 1]) / (2 * (t[i + 1] - t[i]) * (t[i + 1] - t[i]));
}


int read_file(const char *sf, double **x, double **t, int *n)
{
	FILE *f = fopen(sf, "r");
	int i;

	if (!f)
		return -1;

	fscanf(f, "%d", n);
	*x = (double *)malloc((*n) * sizeof(double));
	*t = (double *)malloc((*n) * sizeof(double));

	for (i = 0; i < *n; i++)
	{
		fscanf(f, "%lf %lf", &(*t)[i], &(*x)[i]);
	}
	fclose(f);
	return 0;
}

void swap(double *a, double *b)
{
	double c = *a;
	*a = *b;
	*b = c;
}

void sort_values(double *x, double *t, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n - 1; j++)
		{
			if (t[j] > t[j + 1])
			{
				swap(&t[j], &t[j + 1]);
				swap(&x[j], &x[j + 1]);
			}
		}
}

void print_arr(double *arr, int n)
{
	int i;

	for (i = 0; i < n; ++i)
		printf("%lf\t", arr[i]);
	printf("\n");
}

// ./a.out n_точек шаг test_t
int main(int argc, char *argv[])
{
	double *x, *t, t0;
	double step;
	int n;

	if (argc != 4)
	{
		printf("Incorrect arguments\n");
		return -1;
	}
	n = atoi(argv[1]);
	step = atof(argv[2]);
	t0 = atof(argv[3]);

	printf("n = %d\nstep = %lf\n", n, step);
	make_test("torpedo_x.txt", n, step);

	read_file("torpedo_x.txt", &x, &t, &n);
	sort_values(x, t, n);
	print_arr(x, n);
	print_arr(t, n);
	printf("t0 = %lf\n", t0);
	printf("Interpolation:%lf\n", interpolate(x, t, n, t0));
	printf("True:%lf\n", test_function(t0));
}
