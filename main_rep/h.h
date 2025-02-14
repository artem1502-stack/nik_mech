#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN(a, b) (a * (a <= b) + b * (a > b))
#define ABS(a) (a * (a >= 0) - a * (a < 0))

void	print_array(int *array, int n);
void	sort_array(int *array, int n);
int		is_in(int *arr, int n, int x);
int		*read_array(FILE *f, int *n);
int		*read_array_smart(FILE *f, int *n);

void	print_array_double(double *array, int n);
void	sort_array_double(double *array, int n);
void	sort_array_decreasing_double(double *array, int n);
double	*read_array_double(FILE *f, int *n);
double	*read_array_smart_double(FILE *f, int *n);


#endif
