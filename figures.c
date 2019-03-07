#ifndef NULL
    #include <stdlib.h>
#endif

#ifndef PI
    #define PI 3.14159265358979323846
#endif


typedef struct{
	float x,y;
}Point;

typedef struct{
	float rad;
        Point center;

}Circle;

int isIntersects ()
{

}

int getPerimeter (Circle circle)
{
	return 2 * PI * circle.rad;
}

int getArea (Circle circle)
{
	return PI * circle.rad * circle.rad;
}
