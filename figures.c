#include <stdlib.h>
#include <math.h>
#ifndef PI
#define PI 3.14159265358979323846
#endif
#include "strfuncs.h"
#ifndef MOD
#define MOD(x) ((x) < 0 ? (-x) : (x))
#endif

typedef struct
{
	float x, y;
} Point;

typedef struct
{
	float rad;
	Point center;

} Circle;

typedef struct
{
	Point *points;
} Triangle;

typedef struct
{
	Point *points;
	int n;
} Shape;

char *toString(const Circle *circle)
{
	char *string = malloc(sizeof(char) * 255);
	if (string == NULL)
		return NULL;

	return string;
}

char *toString(const Shape *shape)
{
}

char *toString(const Triangle *trgl)
{
}

int interpret(char *string, void *figure)
/*функция распознающая входные данные из строк, создающая объекты-фигуры
и записывающая их в аргумент-указатель
возвращает код ошибки, где:
"1" - корректная работа
"-1" - ошибка выделения памяти
"-2" - неизвестная фигура*/
{
	char chars[] = {'(', ')', ' ', ','};
	char **strings = split(string, chars, 4);
	if (equals(strings[1], "circle"))
	{
		figure = malloc(sizeof(Circle));
	}
	else if (equals(strings[1], "triangle"))
	{
		/* code */
	}
	else if (equals(strings[1], "polygon"))
	{
		/* code */
	}
	else
	{
		return -2;
	}
}

int isIntersects(const Circle *c1, const Circle *c2)
{
	return sqrt(powf(c1->center.x - c2->center.x, 2) + powf(c1->center.y - c2->center.y, 2)) <=
		   c1->rad + c2->rad; // сравнение растояния между точками и суммой радиусов
}

int isIntersects(const Shape *s1, const Shape *s2) {}

int isIntersects(const Triangle *t1, const Triangle *t2) {}

int isIntersects(const Circle *circle, const Shape *shape)
{
}

int isIntersects(const Shape *shape, const Circle *circle)
{
	return isIntersects(circle, shape);
}

int isIntersects(const Shape *shape, const Triangle *trgl) {}

int isIntersects(const Triangle *trgl, const Shape *shape)
{
	return isIntersects(shape, trgl);
}

float getPerimeter(const Circle *circle)
{
	return 2 * PI * circle->rad;
}

float getPerimeter(const Shape *shape)
{

}

float getArea(const Shape *shape) // возвращеает ориентированную площадь
//формула площади Гаусса
{
	float S = 0;
	for (int i = 0; i < shape->n; i++)
	{
		S += shape->points[i].x * shape->points[i+1].y -
			shape->points[i].y * shape->points[i+1].x; 
	}
	return MOD(S/2);
}

float getArea(const Circle *circle)
{
	return PI * powf(circle->rad, 2);
}

float getArea(const Triangle *trgl) // возвращеает ориентированную площадь
//формула площади Гаусса
{
	float S = 0;
	for (int i = 0; i < 4; i++)
	{
		S += trgl->points[i].x * trgl->points[i+1].y -
			trgl->points[i].y * trgl->points[i+1].x;  
	}
	return MOD(S/2);
}
