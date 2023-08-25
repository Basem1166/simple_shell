#include "shell.h"

/**
 * _memcpy - Copies memory area
 * @dest: Pointer to the destination memory area
 * @src: Pointer to the source memory area
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination memory area
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *ptr = dest;
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (ptr);
}

/**
 * _strncmp - Compares two strings up to a specified length.
 * @str1: The first string.
 * @str2: The second string.
 * @n: The number to compare
 *
 * Return: The difference between the strings,
 *         or 0 if true.
 */
int _strncmp(const char *str1, const char *str2, int n)
{
	while (n > 0 && *str1 == *str2)
	{
		if (*str1 == '\0')
			return (0);
		str1++;
		str2++;
		n--;
	}

	if (n == 0)
		return (0);
	else
		return (*str1 - *str2);
}
/**
 * _strcpy - Copies a string from src to dest
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: The pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (dest_start);
}
