#include "shell.h"

/**
 * exuc_non - function that execute non-interacrive mode
 * @line: buffer
 * @line_size: buffer size
 * @stdin: input
 */
void exuc_non(char **line, size_t *line_size, FILE *stream)
{
	ssize_t nread = getline(&line, &line_size, stdin);

	if (nread == -1)
		return;
	if (checkbuiltins(check, line, nread) == 0)
		return (exuc_non(&line, &line_size, stdin));
	if (tokenize(nnread, argv, line) == 0)
		return (exuc_non(&line, &line_size, stdin));
	if (access(argv[0], X_OK) != 0)
	{
		if (nopath(command, argv) == 0)
			return (exuc_non(&line, &line_size, stdin));
	}
	if (access(argv[0], X_OK) == 0)
		forking(argv);
	else
	{
		free(line);
		perror(argv[0]);
		 return (exuc_non(&line, &line_size, stdin));
	}
}

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

	if (!isatty(STDIN_FILENO))
	{
		exuc_non(&line, &line_size, stdin);
		free(line);
		return (0);
	}
	while (1)
	{
		write(1, "#cisfun$ ", 9);
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
