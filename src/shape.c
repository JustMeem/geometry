#include "shape.h"

double getAngle(const Point *p1, const Point *p2){
	Point vector = {p2->x - p1->x, p2->y - p1->y};
	float module = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));
	return acos((vector.x + vector.y)/module);
}

char *toString(const Shape *s)
{
	char *string = malloc(sizeof(char) * 100);
	if (string)
		return NULL;
	if (s->radius)
	{
		sprintf(string, "Circle(%f %f, %f)", s->points->x, s->points->y, s->radius);
	}
	else
	{
		char *buffer = string;
		if (s->n == 4)
		{
			sprintf(string, "Triangle((");
			string += 10;
		}else{
			sprintf(string, "Shape((");
			string += 7;
		}
		for (int i = 0; i < s->n; i++)
		{
			sprintf(string, "% .4f % .4f ,", s->points[i].x, s->points[i].y);
			string += abs((int)(s->points[i].x / 10)) + abs((int)(s->points[i].y / 10)) + 15;
		}
		string[-1] = '\0';
	}
	return string;
}



int interpret(char *string, Shape **s)
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
		Shape *circle = malloc(sizeof(Shape));
		if (circle == NULL)
			return 0;
		int counter = 0;
		while (strings[1 + counter++])
			;
		if (counter != 3)
		{
			free(circle);
			return -2;
		}
		circle->points[0].x = parseFloat(strings[1]);
		circle->points[0].y = parseFloat(strings[2]);
		circle->radius = parseFloat(strings[3]);
		*s = circle;
		free(strings);
		return 1;
	}
	else if (equals(strings[0], "triangle"))
	{
		strings++;
		Shape *trgl = malloc(sizeof(Shape));
		if (trgl == NULL)
			return 0;
		int counter = 0;
		while (strings[counter++])
			;
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
		trgl->radius = 0;
		*s = trgl;
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
		while (strings[counter++])
			;
		if ((counter % 2 == 1) || (counter < 8))
		{
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
		shape->radius = 0;
		*s = shape;
		free(strings);
		return 3;
	}
	else
	{
		return -1;
	}
}


int isIntersects(const Shape *s1, const Shape *s2){
	if(s1->radius){
		if(s2->radius){
			return sqrt(powf(s1->points[0].x - s2->points[0].x, 2) + powf(s1->points[0].y - s2->points[0].y, 2)) <=
		   s1->radius + s2->radius; // сравнение растояния между центрами и суммой радиусов
		}else{

		}
	}else{

	}
}

float getPerimeter(const Shape *shape)
{	
	if(shape->radius){
		return 2 * M_PI * shape->radius;
	}
	float P = 0;
	for (int i = 0; i < shape->n - 1; i++)
	{
		P += sqrtf(pow(shape->points[i].x - shape->points[i + 1].x, 2) +
				   pow(shape->points[i].y - shape->points[i + 1].y, 2));
	}
	return P;
}

float getArea(const Shape *shape)

{
	if(shape->radius){
		return M_PI * powf(shape->radius, 2);
	}
	//формула площади Гаусса
	float S = 0;
	for (int i = 0; i < shape->n; i++)
	{
		S += shape->points[i].x * shape->points[i + 1].y -
			 shape->points[i].y * shape->points[i + 1].x;
	}
	return MOD(S / 2);
}

