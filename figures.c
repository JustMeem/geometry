#include "figures.h"

char *toString(const Circle *c)
{
	char *string = malloc(sizeof(char) * 100);
	if (string)
		return NULL;
	sprintf(string, "Circle(%f %f, %f)", c->center.x, c->center.y, c->rad);
	return string;
}

char *toString(const Shape *s) // Закончить
{
	char *string = malloc(sizeof(char) * 100);
	if (string)
		return NULL;
	for (int i = 0; i < s->n; i++)
	{
	}

	return string;
}

char *toString(const Triangle *t)
{
	char *string = malloc(sizeof(char) * 100);
	if (string)
		return NULL;
	sprintf(string, "Triangle((%f %f, %f %f, %f %f))",
			t->points[0].x, t->points[0].y,
			t->points[1].x, t->points[1].y,
			t->points[2].x, t->points[2].y);
	return string;
}

int interpret(char *string, void *figure)
/*функция распознающая входные данные из строк, создающая объекты-фигуры
и записывающая их адрес в аргумент-указатель,
возвращает код, где:
"3" - полигон
"2" - треугольник
"1" - круг
"0" - ошибка выделения памяти
"-1" - неизвестная фигура
"-2" - неправильные параметры*/
{
	char chars[] = {'(', ')', ' ', ','};
	char **strings = split(string, chars, 4);
	if (equals(strings[0], "circle"))
	{
		Circle *circle = malloc(sizeof(Circle));
		if (circle == NULL)
			return 0;
		int counter = 0;
		while (strings[1 + counter++]);
		if (counter != 3)
		{
			free(circle);
			return -2;
		}
		circle->center.x = parseFloat(strings[1]);
		circle->center.y = parseFloat(strings[2]);
		circle->rad = parseFloat(string[3]);
		figure = circle;
		free(strings);
		return 1;
	}
	else if (equals(strings[0], "triangle"))
	{
		strings++;
		Triangle *trgl = malloc(sizeof(Shape));
		if (trgl == NULL)
			return 0;
		int counter = 0;
		while (strings[counter++]);
		if (counter != 8)
		{
			free(trgl);
			return -2;
		}
		trgl->points = malloc(sizeof(Point) * 4);
		if (trgl->points == NULL)
		{
			free(trgl);
			return 0;
		}
		Point p;
		int j = 0;
		for (int i = 0; i < 8; i += 2)
		{
			p = trgl->points[j++];
			p.x = parseFloat(strings[i]);
			p.y = parseFloat(strings[i + 1]);
		}
		figure = trgl;
		free(strings);
		return 3;
	}
	else if (equals(strings[0], "polygon"))
	{
		strings++;
		Shape *shape = malloc(sizeof(Shape));
		if (shape == NULL)
			return 0;
		int counter = 0;
		while (strings[counter++]);
		if ((counter % 2 == 1) || (counter < 8)){
			free(shape);
			return -2;
		}
		shape->n = counter / 2;
		shape->points = malloc(sizeof(Point) * (counter / 2));
		if (shape->points == NULL)
		{
			free(shape);
			return 0;
		}
		Point p;
		int j = 0;
		for (int i = 0; i < counter; i += 2)
		{
			p = shape->points[j++];
			p.x = parseFloat(strings[i]);
			p.y = parseFloat(strings[i + 1]);
		}
		figure = shape;
		free(strings);
		return 3;
	}
	else
	{
		return -1;
	}
}

int isIntersects(const Circle *c1, const Circle *c2)
{
	return sqrt(powf(c1->center.x - c2->center.x, 2) + powf(c1->center.y - c2->center.y, 2)) <=
		   c1->rad + c2->rad; // сравнение растояния между центрами и суммой радиусов
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

int isIntersects(const Circle *circle, const Triangle *trgl) {}

int isIntersects(const Triangle *trgl, const Circle *circle)
{
	return isIntersects(circle, trgl);
}

float getPerimeter(const Circle *circle)
{
	return 2 * PI * circle->rad;
}

float getPerimeter(const Shape *shape)
{
	float P = 0;
	for (int i = 0; i < shape->n - 1; i++)
	{
		P += sqrtf(fpow(shape->points[i].x - shape->points[i + 1].x, 2) +
				   fpow(shape->points[i].y - shape->points[i + 1].y, 2));
	}
	return P;
}

float getPerimeter(const Triangle *trgl)
{
	float P = 0;
	for (int i = 0; i < 3; i++)
	{
		P += sqrtf(fpow(trgl->points[i].x - trgl->points[i + 1].x, 2) +
				   fpow(trgl->points[i].y - trgl->points[i + 1].y, 2));
	}
	return P;
}

float getArea(const Shape *shape)
//формула площади Гаусса
{
	float S = 0;
	for (int i = 0; i < shape->n - 1; i++)
	{
		S += shape->points[i].x * shape->points[i + 1].y -
			 shape->points[i].y * shape->points[i + 1].x;
	}
	return MOD(S / 2);
}

float getArea(const Circle *circle)
{
	return PI * powf(circle->rad, 2);
}

float getArea(const Triangle *trgl)
//формула площади Гаусса
{
	float S = 0;
	for (int i = 0; i < 3; i++)
	{
		S += trgl->points[i].x * trgl->points[i + 1].y -
			 trgl->points[i].y * trgl->points[i + 1].x;
	}
	return MOD(S / 2);
}
