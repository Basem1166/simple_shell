#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0.
 */
int main(void)
{
	char *command = NULL;
	char *line = NULL;
	size_t line_size = 0;
	ssize_t nread;
	int check = errno;
	char *argv[MAX];
	char *nnread = NULL;

	while (1)
	{
		nread = getline(&line, &line_size, stdin);

		if (checkbuiltins(check, line, nread) == 0)
			continue;

		if (tokenize(nnread, argv, line) == 0)
			continue;

		if (access(argv[0], X_OK) != 0)
			if (nopath(command, argv) == 0)
				continue;
		if (access(argv[0], X_OK) == 0)
			forking(argv);
		else
		{
			free(line);
			perror(argv[0]);
			continue;
		}
	}

	free(line);
	return (0);
}
