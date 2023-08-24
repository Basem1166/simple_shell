#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int n = _strlen(name);
	int i = 0;

	while (environ[i])
	{
		if (_strncmp(name, environ[i], n) == 0 && environ[i][n] == '=')
			return (&environ[i][n + 1]);
		i++;
	}
	return (NULL);
}

/**
 * nopath - Searches for an executable in directories specified by PATH.
 * @command: A pointer to store the resulting full path of the executable.
 * @argv: An array of strings containing command and arguments.
 *
 * Return: 0 to continue
 */
int nopath(char *command, char *argv[])
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);
	char *dir;
	int ndir;

	if (!path)
	{
		perror("PATH");
		return (0);
	}
	dir = strtok(path_copy, ":");
	while (dir)
	{
		ndir = _strlen(dir) + _strlen(argv[0]) + 2;
		command = malloc(sizeof(char) * ndir);
		command[0] = '\0';
		_strcat(command, dir);
		_strcat(command, "/");
		_strcat(command, argv[0]);
		if (access(command, X_OK) == 0)
			break;
		free(command);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	if (access(command, X_OK) == -1)
	{
		perror(argv[0]);
		return (0);
	}
	if (!command)
	{
		perror("NOT FOUND");
		return (0);
	}
	argv[0] = command;
}

/**
 * tokenize - Tokenizes a string into an array of strings.
 * @nnread: Pointer to store the token during tokenization.
 * @argv: Array of strings to store the tokens.
 * @line: The input string to be tokenized.
 *
 * Return: 0 on failure.
 */
int tokenize(char nnread, char argv[], char *line)
{
	int i = 0;

	nnread = strtok(line, " \n");

	while (nnread != NULL)
	{
		argv[i] = nnread;
		i++;
		nnread = strtok(NULL, " \n");
	}

	argv[i] = NULL;

	if (argv[0] == NULL)
		return (0);
}

/**
 * checkbuiltins - Checks for built-in shell commands and handles them.
 * @check: An error code for checking errors.
 * @line: The input line from the user.
 * @nread: The number of characters read from the input line.
 *
 * Return: 0 to continue
 */
int checkbuiltins(int check, char *line, ssize_t nread)
{
	int n;

	if (_strcmp(line, "env\n") == 0)
		n = print_env();

	if (n == -1)
		perror("environ");

	if (nread == 1)
	{
		return (0);
	}

	if (nread == -1 && check != errno)
	{
		perror("getline");
		exit(1);
	}
	else if ((nread == -1 && check == errno) || (_strcmp(line, "exit\n") == 0))
	{
		free(line);
		printf("\nEnd of input. Exiting shell.\n");
		exit(EXIT_SUCCESS);
	}
}
/**
 * forking - Creates a child process and executes a program in it.
 * @argv: An array of strings containing the program path and arguments.
 *
 * Return: This function does not return any value.
 */
void forking(char *argv[])
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}

	if (pid == 0)
	{
		execve(argv[0], argv, environ);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}

	if (!isatty(STDIN_FILENO))
		exit(1);
}
