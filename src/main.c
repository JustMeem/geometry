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

typedef struct stringlistnode
{
	stringlistnode *next;
	char *string;
} stringlistnode;

typedef struct listnode
{
	Shape *s;
	listnode *next;
	stringlistnode *intersections;
} listnode;

void addIntersection(stringlistnode *node, const Shape *s, size_t n)
{
	while (node->next != NULL)
	{
		node = node->next;
	}
	if (!(node->next = malloc(sizeof(stringlistnode))))
	{
		printf("Memory access error");
		return;
	}
	node = node->next;
	node->next = NULL;
	switch (s->n)
	{
	case 1:
		sprintf(node->string, "%d. circle", n);
		return;
	case 4:
		sprintf(node->string, "%d. triangle", n);
		return;
	default:
		sprintf(node->string, "%d. polygon", n);
	}
}

int main()
{
	char string[255];
	listnode shapelist = {NULL, NULL, NULL};
	listnode *buffer = &shapelist;
	size_t counter = 0;
	while (stringStream(string))
	{
		counter++;
		if (!(buffer->next = malloc(sizeof(listnode))))
		{
			printf("Memory access error");
			return 0;
		}
		switch (interpret(string, &(buffer->next->s)))
		{
		case 1:
			printf("Memory access error");
			return 0;
		case -1:
			printf("Unexpected figure type");
			break;
		case -2:
			printf("Invaild figure parameters");
			break;
		default:
			buffer = buffer->next;
			buffer->next = NULL;
			buffer->intersections = NULL;
		}
	}
	listnode *s = &shapelist;
	int j;
	for (int i = 0; i < counter - 1; i++)
	{
		s = s->next;
		buffer = s->next;
		j = i + 1;
		while (buffer != NULL)
		{
			if (isIntersects(s->s, buffer->s))
			{
				if (s->intersections == NULL)
				{
					if (!(s->intersections = malloc(sizeof(stringlistnode))))
					{
						printf("Memory access error");
						return 0;
					}
					s->intersections->next = NULL;
				}
				addIntersection(s->intersections, buffer->s, j);
				if (buffer->intersections == NULL)
				{
					if (!(buffer->intersections = malloc(sizeof(stringlistnode))))
					{
						printf("Memory access error");
						return 0;
					}
					s->intersections->next = NULL;
				}
				addIntersection(buffer->intersections, s->s, i);
			}
			buffer = buffer->next;
			j++;
		}
	}
	j = 1;
	buffer = &shapelist;
	stringlistnode *intersection;
	while (buffer != NULL)
	{
		printf("%d. %s\n", j++, toString(buffer->s));
		intersection = buffer->intersections;
		printf("\tperimeter: %f\n\tarea: %f\n\tintersects:\n",
			   getPerimeter(buffer->s), getArea(buffer->s));
		while (intersection != NULL)
		{
			printf("\t  %s\n", intersection->string);
			intersection = intersection->next;
		}
		buffer = buffer->next;
	}
	return 1;
}