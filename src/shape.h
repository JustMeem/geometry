#pragma once
#include "strfuncs.h"
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef MOD
#define MOD(x) ((x) < 0 ? (-x) : (x))
#endif

typedef struct Point {
    float x, y;
} Point;

typedef struct Shape {
    Point* points;
    float radius;
    int n;
} Shape;

char* toString(const Shape* s);
int interpret(char* string, Shape** s);
int isIntersects(Shape* s1, Shape* s2);
float getPerimeter(const Shape* shape);
float getArea(const Shape* shape);