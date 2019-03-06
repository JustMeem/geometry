#include <stdio.h>
#define PI 3.14159265358979323846
#define MOD(x) (x < 0 ? (-x) : x)

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

int equals (char* string1, char* string2)
{
	while(*(string1++) && *(string2++)){
		if(*string1 != *string2)
			return 0;
	}
	return 1;
}

int split (char* string, char c)
{
	int flag = 0;
	while (*(string++)){
		if(*string == c){
			*string = EOF;
			flag = 1;
		}
	}
	return flag;
}

float indegree (int base, int n){
	int buffer = 1;
	for(int i = 0; i < MOD(n); i++){
		buffer *= base;
	}
	return n < 0 ? 1/buffer : buffer;
}

float parsefloat (char* string)
{
	int flag = *string == '-';
	split(string, '.');
	float num = 0;
	while (*(string++)){
		num *= 10;
		num += *string - 48;
	}
	string++;
	int i = -1;
	while (*(string++)){
		num += (string - 48) * indegree(10, i--);
	}
	return flag ? -num : num;
}

int interpret (char* string, void* figure)
{
	
}

int getstring (char* string)
{
	char buffer;
	int i = 0;
	while((buffer = getchar()) != "\n"){
		if ((buffer == EOF)||(i > 254))
			return 0;
		string[i++] = buffer;
	}
	return 1;
}

int main ()
{
	Circle circles[40];
	char string [255];
}
