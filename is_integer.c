#include "monty.h"

/**
 * is_integer - Checks if a string represents a valid integer.
 * @str: The input string to check.
 *
 * Return: 1 if the string is a valid integer, 0 otherwise.
 */

int is_integer(const char *str)
{
	int index;

	if (str == NULL || str[0] == '\0')
	{
		return (0);
	}
	index = 0;
	if (str[index] == '+' || str[index] == '-')
	{
		index++;
	}
	while (str[index] != '\0')
	{
		if (!isdigit(str[index]))
		{
			return (0);
		}
		index++;
	}
	return (1);
}
