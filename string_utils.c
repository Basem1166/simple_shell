#include "shell.h"

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if the strings are equal, -1 otherwise.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (-1);
}

/**
 * _strlen - Computes the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */
size_t _strlen(char *s)
{
	size_t len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strdup - Creates a duplicate of a string.
 * @str: The input string.
 *
 * Return: The pointer to the duplicated string, or NULL if allocation fails.
 */
char *_strdup(char *str)
{
	size_t len = _strlen(str) + 1;
	char *dup = malloc(len);

	if (dup == NULL)
		return (NULL);

	return (_memcpy(dup, str, len));
}

/**
 * _memcpy - fuunction that copies memory area
 * @dest: memory area
 * @src: copy memory area
 * @n: number of copied bytes
 * Return: pointer to dest
*/

char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *start = dest;

	while (n-- > 0)
		*dest++ = *src++;
	return (start);
}

