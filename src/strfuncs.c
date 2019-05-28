#include "strfuncs.h"

int lsearch(char *chars, int n, char c)
{
	for (int i = 0; i < n; i++)
	{
		if (chars[i] == c)
			return i;
	}
	return -1;
}

char **split(char *string, char *chars, int n)
/* замещает символы строки встречающиеся в chars на NULL
и возвращает массив подстрок, заканчивающийся нулевым адресом*/
{
	int counter = 0;
	char *buffer = string;
	size_t s_size = 0;
	while (*(string++))
	{
		s_size++;
		for (int i = 0; i < n; i++)
		{
			if (*string == chars[i])
			{
				counter++;
			}
		}
	}

	char **strings = malloc(sizeof(char *) * counter + 2);
	if (strings == NULL)
	{
		return NULL;
	}
	string = buffer;
	int j = 1;
	*strings = buffer;
	for (int i = 0; i < s_size; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (string[i] == chars[k])
			{
				string[i] = '\0';
			}
		}
	}
	for (int i = 0; i < s_size - 1; i++)
	{
		if (string[i] == '\0' && string[i + 1] != '\0')
		{
			strings[j++] = string + i + 1;
		}
	}
	strings[j] = NULL;
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
		num += (int)(*string - 48) * powf(10, i--);
	}
	return flag ? -num : num;
}
