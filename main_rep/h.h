#ifndef H_H
#define H_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void	print_array(int *array, int n);
void	sort_array(int *array, int n);
int		is_in(int *arr, int n, int x);
int		*read_array(FILE *f, int *n);
int		*read_array_smart(FILE *f, int *n);

#endif
