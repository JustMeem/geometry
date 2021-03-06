#include "shape.h"

int isSectionIntersects(const Point* sect1, const Point* sect2)
{ //проверка пересечения двух отрезков
    if (sect1->x < sect2->x) {
        if (sect1->y > sect2->x)
            return 1;
        return 0;
    } else {
        if (sect1->x < sect2->y)
            return 1;
        return 0;
    }
}

char* toString(const Shape* s)
{
    char* string = malloc(sizeof(char) * 200);
    if (!string)
        return NULL;
    if (s->radius) {
        sprintf(string,
                "circle(%f %f, %f)",
                s->points->x,
                s->points->y,
                s->radius);
    } else {
        char* buffer = string;
        if (s->n == 4) {
            sprintf(string, "triangle((");
            string += 10;
        } else {
            sprintf(string, "polygon((");
            string += 9;
        }
        for (int i = 0; i < s->n; i++) {
            sprintf(string, "% .4f % .4f ,", s->points[i].x, s->points[i].y);
            string += abs((int)(s->points[i].x / 10)) + 5
                    + abs((int)(s->points[i].y / 10)) + 5 + 7;
        }
        string--;
        sprintf(string, "))");
        string += 3;
        string[-1] = '\0';
        string = buffer;
    }
    return string;
}

int interpret(char* string, Shape** s)
/*функция распознающая входные данные из строк, создающая объекты-фигуры
и записывающая их адрес в аргумент-указатель,
возвращает код, где:
"0" - нормальная работа
"1" - ошибка выделения памяти
"-1" - неизвестная фигура
"-2" - неправильные параметры*/
{
    char chars[] = {'(', ')', ' ', ','};
    char** strings = split(string, chars, 4);
    if (strcmp(strings[0], "circle") == 0) {
        Shape* circle = malloc(sizeof(Shape));
        if (circle == NULL)
            return 0;
        int counter = 0;
        while (strings[1 + counter++])
            ;
        counter--;
        if (counter != 3) {
            free(circle);
            return -2;
        }
        circle->points = malloc(sizeof(Point) * 4);
        if (circle->points == NULL) {
            free(circle);
            return 1;
        }
        circle->points[0].x = strtof(strings[1], '\0');
        circle->points[0].y = strtof(strings[2], '\0');
        circle->radius = strtof(strings[3], '\0');
        circle->n = 1;
        *s = circle;
        free(strings);
        return 0;
    } else if (strcmp(strings[0], "triangle") == 0) {
        strings++;
        Shape* trgl = malloc(sizeof(Shape));
        if (trgl == NULL)
            return 1;
        int counter = 0;
        while (strings[counter++])
            ;
        counter--;
        if (counter != 8) {
            free(trgl);
            return -2;
        }
        trgl->points = malloc(sizeof(Point) * 4);
        if (trgl->points == NULL) {
            free(trgl);
            return 1;
        }
        Point* p;
        int j = 0;
        for (int i = 0; i < 8; i += 2) {
            p = trgl->points + j++;
            p->x = strtof(strings[i], '\0');
            p->y = strtof(strings[i + 1], '\0');
        }
        p = trgl->points;
        if (p->x != p[3].x || p->y != p[3].y) {
            for (int i = 0; i < 4; i++) {
                free(p + i);
            }
            free(trgl);
            return -2;
        }
        trgl->radius = 0;
        trgl->n = 4;
        *s = trgl;
        free(--strings);
        return 0;
    } else if (strcmp(strings[0], "polygon") == 0) {
        strings++;
        Shape* shape = malloc(sizeof(Shape));
        if (shape == NULL)
            return 1;
        int counter = 0;
        while (strings[counter++])
            ;
        counter--;
        if ((counter % 2 == 1) || (counter < 8)) {
            free(shape);
            return -2;
        }
        shape->n = counter / 2;
        shape->points = malloc(sizeof(Point) * (counter / 2));
        if (shape->points == NULL) {
            free(shape);
            return 1;
        }
        Point* p;
        int j = 0;
        for (int i = 0; i < counter; i += 2) {
            p = shape->points + j++;
            p->x = strtof(strings[i], '\0');
            p->y = strtof(strings[i + 1], '\0');
        }
        p = shape->points;
        if (p->x != p[counter / 2].x || p->y != p[counter / 2].y) {
            for (int i = 0; i < counter / 2; i++) {
                free(p + i);
            }
            free(shape);
            return -2;
        }
        shape->radius = 0;
        shape->n = counter / 2;
        *s = shape;
        free(--strings);
        return 0;
    } else {
        return -1;
    }
}

int isIntersects(Shape* s1, Shape* s2)
{ // работа по принципу теоремы о разделяющей оси
    double cosinus;
    Point* points2 = s2->points;
    Point* points1 = s1->points;
    if (s1->radius) {
        if (s2->radius) {
            return sqrt(powf(s1->points[0].x - s2->points[0].x, 2)
                        + powf(s1->points[0].y - s2->points[0].y, 2))
                    <= s1->radius + s2->radius; // сравнение растояния между
                                                // центрами и суммой радиусов
        } else {
        PolyCircle:
            points2 = s2->points;
            for (int i = 0; i < s2->n - 1; i++) {
                Point vector = {points2[i + 1].x - points2[i].x,
                                points2[i + 1].y - points2[i].x};
                cosinus = (vector.x - vector.y)
                        / sqrt(pow(vector.x, 2) + pow(vector.y, 2));
                Point proj1 = {s1->points[0].x * cosinus + s1->radius,
                               s1->points[0].x * cosinus - s1->radius};
                Point proj2 = {points2[0].x * cosinus, points2[0].x * cosinus};
                for (int j = 1; j < s2->n - 1; j++) {
                    if (points2[i].x * cosinus < proj2.x)
                        proj2.x = points2[i].x * cosinus;
                    if (points2[i].x * cosinus > proj2.y)
                        proj2.y = points2[i].x * cosinus;
                }
                if (!isSectionIntersects(&proj1, &proj2))
                    return 0;
            }
            return 1;
        }
    } else {
        if (s2->radius) {
            Shape* buffer = s1;
            s1 = s2;
            s2 = buffer;
            goto PolyCircle;
        } else {
            for (int k = 0; k < 2; k++) {
                for (int i = 0; i < s2->n - 1; i++) {
                    Point vector = {points2[i + 1].x - points2[i].x,
                                    points2[i + 1].y - points2[i].x};
                    cosinus = (vector.x - vector.y)
                            / sqrt(pow(vector.x, 2) + pow(vector.y, 2));
                    Point proj1
                            = {points1[0].x * cosinus, points1[0].x * cosinus};
                    for (int j = 1; j < s1->n - 1; j++) {
                        if (points1[i].x * cosinus < proj1.x)
                            proj1.x = points1[i].x * cosinus;
                        if (points1[i].x * cosinus > proj1.y)
                            proj1.y = points1[i].x * cosinus;
                    }
                    Point proj2
                            = {points2[0].x * cosinus, points2[0].x * cosinus};
                    for (int j = 1; j < s2->n - 1; j++) {
                        if (points2[i].x * cosinus < proj2.x)
                            proj2.x = points2[i].x * cosinus;
                        if (points2[i].x * cosinus > proj2.y)
                            proj2.y = points2[i].x * cosinus;
                    }
                    if (!isSectionIntersects(&proj1, &proj2))
                        return 0;
                }
                Shape* buffer = s1;
                s1 = s2;
                s2 = buffer;
                Point* pbuffer = points1;
                points1 = points2;
                points2 = pbuffer;
            }
            return 1;
        }
    }
}

float getPerimeter(const Shape* shape)
{
    if (shape->radius) {
        return 2 * M_PI * shape->radius;
    }
    float P = 0;
    for (int i = 0; i < shape->n - 1; i++) {
        P += sqrtf(
                pow(shape->points[i].x - shape->points[i + 1].x, 2)
                + pow(shape->points[i].y - shape->points[i + 1].y, 2));
    }
    return P;
}

float getArea(const Shape* shape)

{
    if (shape->radius) {
        return M_PI * powf(shape->radius, 2);
    }
    //формула площади Гаусса
    float S = 0;
    for (int i = 0; i < shape->n; i++) {
        S += shape->points[i].x * shape->points[i + 1].y
                - shape->points[i].y * shape->points[i + 1].x;
    }
    return MOD(S / 2);
}
