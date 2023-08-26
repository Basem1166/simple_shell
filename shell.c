#include "shell.h"


/**
 * main - Entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	int status = 0;
	char *line = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
		if (interactive(line, &status) == 0)
			continue;
		}
		else
		{
			if (interactive(line, &status) == 0)
				continue;
		}
	}
	if (line)
		free(line);
	return (0);
}
