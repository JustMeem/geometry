#pragma once

#include <stdlib.h>
#include <math.h>
#ifndef PI
#define PI 3.14159265358979323846
#endif
#include "strfuncs.h"
#ifndef MOD
#define MOD(x) ((x) < 0 ? (-x) : (x))
#endif

typedef struct Circle Circle;

typedef struct Triangle Triangle;

typedef struct Shape Shape;

char *toString(const Circle *c);

char *toString(const Shape *s);

char *toString(const Triangle *t);

int interpret(char *string, void *figure);

int isIntersects(const Circle *c1, const Circle *c2);

int isIntersects(const Shape *s1, const Shape *s2);

int isIntersects(const Triangle *t1, const Triangle *t2);

int isIntersects(const Circle *circle, const Shape *shape);

int isIntersects(const Shape *shape, const Circle *circle);

int isIntersects(const Shape *shape, const Triangle *trgl);

int isIntersects(const Triangle *trgl, const Shape *shape);

float getPerimeter(const Circle *circle);

float getPerimeter(const Shape *shape);

float getPerimeter(const Triangle *trgl);

float getArea(const Shape *shape);

float getArea(const Circle *circle);

float getArea(const Triangle *trgl);
