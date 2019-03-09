#pragma once

#ifndef PI
#define PI 3.14159265358979323846
#endif

typedef struct Point;
typedef struct Circle;
typedef struct Shape;
char *toString(const Circle *circle);
char *toString(const Shape *shape);
int interpret(char *string, void *figure);
int isIntersects(const Circle *c1, const Circle *c2);
int isIntersects(const Circle *circle, const Shape *shape);
int isIntersects(const Shape *shape, const Circle *circle);
float getPerimeter(const Circle *circle);
float getArea(const Circle *circle);
float getPerimeter(const Shape *shape);
float getArea(const Shape *shape);