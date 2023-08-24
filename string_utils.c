#include "shell.h"

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if the strings are equal, -1 otherwise.
 */
int _strcmp(const char *s1, char *s2)
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
int _strlen(const char *s)
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

/**
 * _strncmp - function that compares two string
 * @str1: string
 * @str2: string 2
 * @n: bytes to be compared
 * Return: 0 for true
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
