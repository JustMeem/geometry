#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#ifndef MOD
#define MOD(x) ((x) < 0 ? (-x) : (x))
#endif

int lsearch(char *chars, int n, char c);

int equals(char *string1, char *string2);

char **split(char *string, char *chars, int n);

float parseFloat(char *string);