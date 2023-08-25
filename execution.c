#include "shell.h"
/**
 * interactive - Handles interactive mode of the shell.
 * @line: Pointer to the input line from the user.
 *
 * Return: 0 to continue looping
 */
int interactive(char *line)
{
	ssize_t nread;
	size_t line_size = 0;
	char *command = NULL;
	int check = errno;
	char *argv[MAX];
	char *nnread = NULL;

	write(1, "$ ", 2);

	nread = getline(&line, &line_size, stdin);

	if (checkbuiltins(check, line, nread) == 0)
		return (0);

	if (tokenize(nnread, argv, line) == 0)
		return (0);

	if (access(argv[0], X_OK) != 0)
		if (nopath(command, argv) == 0)
			return (0);

	if (access(argv[0], X_OK) == 0)
	{
		forking(argv, 1, line);
	}
	else
	{
		perror(argv[0]);
		return (0);
	}
	return (1);
	free(argv[0]);
}

/**
 * non_interactive - Handles non-interactive mode of the shell.
 * @line: Pointer to the input line from the user.
 *
 */
void non_interactive(char *line)
{
	ssize_t nread;
	size_t line_size = 0;
	char *command = NULL;
	int check = errno;
	char *argv[MAX];
	char *nnread = NULL;
	int i = 0;

	nread = getline(&line, &line_size, stdin);
	if (tokenize(nnread, argv, line) == 0)
		return;

	while (argv[i] != NULL)
	{
		if (checkbuiltins(check, argv[i], nread) == 0)
		{
			i++;
			continue;
		}
		if (access(argv[i], X_OK) != 0)
			if (nopath(command, &argv[i]) == 0)
			{
				i++;
				continue;
			}

		if (access(argv[i], X_OK) == 0)
		{
			forking(&argv[i], 2, line);
		}
		else
		{
			free(line);
			perror(argv[i]);
			i++;
			continue;
		}

		i++;
	}
}

