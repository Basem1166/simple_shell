#include "shell.h"

/**
 * _strdup - Creates a duplicate of a string.
 * @str: The input string.
 *
 * Return: The pointer to the duplicated string, or NULL if allocation fails.
 */
char *_strdup(char *str)
{
	char *dup = NULL;
	size_t len = _strlen(str) + 1;

	dup = malloc(len);
	if (dup == NULL)
		return (NULL);

	return (_memcpy(dup, str, len));
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the resulting string.
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, c = 0;

	while (dest[i] != '\0')
		i++;

	while (src[c] != '\0')
	{
		dest[i] = src[c];
		i++;
		c++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strlen - Calculates the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int c = 0;

	for (c = 0; *s != '\0'; s++)
		c++;
	return (c);
}

/**
 * print_env - Prints the environment variables.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_env(void)
{
	int i;

	if (!environ)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The difference between strings.
 */
int _strcmp(const char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
