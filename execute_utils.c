#include "shell.h"

/**
 * prompt - Prints the shell prompt.
 */
void prompt(void)
{
	char *c = "$ ";

	write(STDOUT_FILENO, c, _strlen(c));
}

/**
 * read_line - Reads a line of input from the user.
 * @line: Pointer to the buffer where the line will be stored.
 * @line_size: The size of the buffer.
 * @check: Original value of errno for error handling.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t read_line(char **line, size_t *line_size, int check)
{
	ssize_t nread;

	nread = getline(line, line_size, stdin);

	if (nread == -1)
	{
		if (errno == EINTR)
			return (read_line(line, line_size, check));
		if (check == errno)
			return (-2);
		perror("getline");
		return (-1);
	}
	(*line)[nread - 1] = '\0';
	return (nread);
}

/**
 * tokenize_line - Tokenizes a line of input.
 * @line: The input line to tokenize.
 * @argv: Array to store the tokens.
 *
 * Return: The number of tokens.
 */
int tokenize_line(char *line, char *argv[])
{
	int i = 0;
	char *token;

	token = strtok(line, " ");

	while (token != NULL)
	{
		argv[i] = token;
		i++;
		token = strtok(NULL, " ");
	}
	return (i);
}

/**
 * execute_command - Executes a command.
 * @argv: The command and its arguments.
 *
 * Return: 1 if the command is a built-in command, 0 otherwise.
 */
int execute_command(char *argv[])
{
	if (_strcmp(argv[0], "exit") == 0)
		return (1);
	if (_strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		char *command = _getenv(argv[0]);

		if (command == NULL)
		{
			printf("%s: command not found\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		execve(command, argv, environ);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
	return (0);
}

/**
 * shell_loop - Main loop of the shell program.
 */

void shell_loop(void)
{
	char *line = NULL;
	size_t line_size = 0;
	ssize_t nread;
	int check = errno;

	while (1)
	{
		char *argv[MAX_ARGS];
		int argc;

		prompt();
		nread = read_line(&line, &line_size, check);

		if (nread == -1)
			break;
		else if (nread == -2)
			continue;
		argc = tokenize_line(line, argv);

		if (argc == 0)
			continue;
		if (execute_command(argv))
			break;
	}
	free(line);
}
