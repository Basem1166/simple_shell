#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(char *name)
{
	size_t name_len = _strlen(name);

	for (int i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
	}

	return (NULL);
}

/**
 * print_env - Prints the current environment variables.
 */
void print_env(void)
{

	for (int i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}
