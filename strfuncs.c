#include <stdio.h>
#include <math.h>
#ifndef MOD
#define MOD(x) (x < 0 ? (-x) : x)
#endif

int lsearch(char *chars, int n, char c)
{
	for (int i = 0; i < n; i++)
	{
		if (chars[i] == c)
			return i;
	}
	return -1;
}

int equals(char *string1, char *string2)
{
	while (*(string1++) && *(string2++))
	{
		if (*string1 != *string2)
			return 0;
	}
	return 1;
}

char **split(char *string, char *chars, int n)
/* замещает символы строки встречающиеся в chars на NULL
и возвращает массив подстрок*/
{
	int counter = 0;
	char *buffer = string;
	while (*(string++))
	{
		for (int i = 0; i < n; i++)
		{
			if (*string == chars[i])
			{
				counter++;
			}
		}
	}

	char **strings = calloc(sizeof(char *) * counter);
	if (strings == NULL)
	{
		return NULL;
	}

	string = buffer;
	int j = 0;
	while (*(string++))
	{
		for (int i = 0; i < n; i++)
		{
			if (*string == chars[i])
			{
				*string = EOF;
				if ((string + 1) && (lsearch(chars, n, string[1]) == -1))
				{
					strings[j++] = string + 1;
				}
			}
		}
	}
	return strings;
}

float parseFloat(char *string) // на вход принимается только строка, состоящая только из числа
//увидел стандартную функцию делающую то же самое, жаль удалять родное Г****
{
	int flag = *string == '-';
	char c = '.';
	split(string, &c, 1);
	float num = 0;
	while (*(string++))
	{
		num *= 10;
		num += *string - 48;
	}
	string++;
	int i = -1;
	while (*(string++))
	{
		num += (int)(string - 48) * powf(10, i--);
	}
	return flag ? -num : num;
}

