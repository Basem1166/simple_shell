#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int n = strlen(name);
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
 * @status: status of exit
 * Return: 0 to continue
 */
int nopath(char *command, char *argv[], int *status)
{
	char *path = _getenv("PATH");
	char *path_copy = _strdup(path);
	char *dir = NULL;
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
		_strcpy(command, dir);
		_strcat(command, "/");
		_strcat(command, argv[0]);
		if (access(command, X_OK) == 0)
			break;
		free(command);
		command = NULL;
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	if (!command)
	{
		if (access(command, X_OK) == -2)
		{
			perror(argv[-1]);
			free(command);
			return (-1);
		}
		*status = 2;
		perror("");
		return (0);
	}
	argv[0] = command;
	return (1);
}

/**
 * tokenize - Tokenizes a string into an array of strings.
 * @nnread: Pointer to store the token during tokenization.
 * @argv: Array of strings to store the tokens.
 * @line: The input string to be tokenized.
 *
 * Return: 0 on failure.
 */
int tokenize(char *nnread, char *argv[], char *line)
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
	{
		free(line);
		return (0);
	}
	return (1);
}

/**
 * checkbuiltins - Checks for built-in shell commands and handles them.
 * @check: An error code for checking errors.
 * @line: The input line from the user.
 * @nread: The number of characters read from the input line.
 * @last_exit: exit status from forking
 * Return: 0 to continue
 */
int checkbuiltins(int check, char *line, ssize_t nread, int last_exit)
{
	int n;

	if ((nread == -1 && check == errno))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	if ((_strcmp(line, "exit\n") == 0) || (_strcmp(line, "exit") == 0))
	{
		free(line);
		exit(last_exit);
	}
	if (_strcmp(line, "env\n") == 0 || _strcmp(line, "env") == 0)

	{
		n = print_env();
		if (n == -1)
			perror("environ");
	}
	if (nread == 1)
	{
		free(line);
		return (0);
	}

	if (nread == -1 && check != errno)
	{
		perror("getline");
		free(line);
		exit(EXIT_FAILURE);
	}
	return (1);
}
/**
 * forking - Creates a child process and executes a program in it.
 * @argv: An array of strings containing the program path and arguments.
 * @mode: 1 for interactive and 2 for non interactive
 * @line: line from user
 * Return: status number
 */
int forking(char *argv[], int mode, char *line)
{
	char *newargv[2];
	pid_t pid;
	int status = 0;

	pid = fork();

	if (pid == -1)
	{
		free(line);
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (mode == 1)
		{
			execve(argv[0], argv, environ);
		}
		else
		{
			newargv[0] = argv[0];
			newargv[1] = NULL;
			execve(argv[0], newargv, environ);
		}
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
	}
	return (status);
}
