#include "shell.h"

/**
 * interactive - Handles interactive mode of the shell.
 * @line: Pointer to the input line from the user.
 * @last_exit: exit status
 * Return: 0 to continue looping
 */
int interactive(char *line, int *last_exit)
{
	ssize_t nread;
	size_t line_size = 0;
	char *command = NULL;
	int check = errno, flag = 0;
	char *argv[MAX];
	char *nnread = NULL;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	nread = getline(&line, &line_size, stdin);

	if (checkbuiltins(check, line, nread, *last_exit) == 0)
		return (0);
	if (tokenize(nnread, argv, line) == 0)
		return (0);
	if (access(argv[0], X_OK) != 0)
	{
		flag = 1;
		if (nopath(command, argv, last_exit) == 0)
		{
			free(line);
			return (0);
		}
	}
	if (access(argv[0], X_OK) == 0)
		*last_exit = forking(argv, 1, line);
	else
	{
		perror(argv[0]);
		return (0);
	}
	if (line)
		free(line);
	if (argv[0] && flag == 1)
		free(argv[0]);
	return (1);
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
		if (checkbuiltins(check, argv[i], nread, 0) == 0)
		{
			i++;
			continue;
		}
		if (access(argv[i], X_OK) != 0)
			if (nopath(command, &argv[i], NULL) == 0)
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
