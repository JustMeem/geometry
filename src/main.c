#include <stdio.h>
#include "shape.h"

int stringStream(char *string)
{
	char buffer;
	int i = 0;
	while ((buffer = getchar()) != '\n')
	{
		if ((buffer == EOF) || (i > 254))
			return 0;
		string[i++] = buffer;
	}
	string[i] = EOF;
	return 1;
}

typedef struct stringlistnode{
	stringlistnode *next;
	char *string;
}stringlistnode;

typedef struct listnode
{
	Shape* s;
	listnode *next;
	stringlistnode *intersections;
}listnode;


int main()
{
	char string[255];
	listnode shapelist = {NULL, NULL, NULL};
	listnode *buffer = &shapelist;
	size_t counter = 0;
	while(stringStream(string)){
		counter++;
		if(!(buffer->next = malloc(sizeof(listnode)))){
			printf("Memory access error");
			return 0;
		}
		switch(interpret(string, &(buffer->next->s))){
			case(1):
				printf("Memory access error");
				return 0;
			case(-1):
				printf("Unexpected figure type");
				break;
			case(-2):
				printf("Invaild figure parameters");
				break;
			default:
				buffer = buffer->next;
				buffer->next = NULL;
		}
	}
	

}