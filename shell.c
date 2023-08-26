#include "shell.h"


/**
 * main - Entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			if (interactive(line) == 0)
				continue;
		}
		else
		{
			non_interactive(line);
			break;
		}
	}
	if (line)
		free(line);
	return (0);
}
