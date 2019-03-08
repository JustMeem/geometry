#include <stdio.h>
#include "figures.h"

int getstring(char *string)
{
	char buffer;
	int i = 0;
	while ((buffer = getchar()) != '\n')
	{
		if ((buffer == EOF) || (i > 254))
			return 0;
		string[i++] = buffer;
	}
	return 1;
}

int main()
{
	char string[255];
}