#pragma once
#include <math.h>
#include <stdlib.h>
#include "strfuncs.h"

#ifndef MOD
#define MOD(x) ((x) < 0 ? (-x) : (x))
#endif

typedef struct Point
{
    float x, y;
} Point;

typedef struct Shape
{
    Point *points;
    float radius;
    int n;
} Shape;

char *toString(const Shape *s);
int interpret(char *string, Shape **s);
int isIntersects(const Shape *s1, const Shape *s2);
float getPerimeter(const Shape *shape);
float getArea(const Shape *shape);