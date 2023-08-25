#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX 1024
extern char **environ;

int interactive(char *line);
void non_interactive(char *line);
char *_strcat(char *dest, char *src);
int _strlen(const char *s);
int print_env(void);
int _strcmp(const char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, int n);
char *_getenv(const char *name);
int nopath(char *command, char *argv[]);
int tokenize(char *nnread, char *argv[], char *line);
int checkbuiltins(int check, char *line, ssize_t nread);
char *_strdup(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
void forking(char *argv[], int mode, char *line);
char *_strcpy(char *dest, char *src);
void setline(char **lineptr, ssize_t position, size_t *n, char *buffer);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/**
 * _strdup - Creates a duplicate of a string.
 * @str: The input string.
 *
 * Return: The pointer to the duplicated string, or NULL if allocation fails.
 */
char *_strdup(char *str)
{
	char *dup = NULL;
	size_t len = _strlen(str) + 1;

	dup = malloc(len);
	if (dup == NULL)
		return (NULL);

	return (_memcpy(dup, str, len));
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the resulting string.
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, c = 0;

	while (dest[i] != '\0')
		i++;

	while (src[c] != '\0')
	{
		dest[i] = src[c];
		i++;
		c++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strlen - Calculates the length of a string.
 * @s: The input string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int c = 0;

	for (c = 0; *s != '\0'; s++)
		c++;
	return (c);
}

/**
 * print_env - Prints the environment variables.
 *
 * Return: 0 on success, -1 on failure.
 */
int print_env(void)
{
	int i;

	if (!environ)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The difference between strings.
 */
int _strcmp(const char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
/**
 * _memcpy - Copies memory area
 * @dest: Pointer to the destination memory area
 * @src: Pointer to the source memory area
 * @n: Number of bytes to copy
 *
 * Return: Pointer to the destination memory area
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *ptr = dest;
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (ptr);
}

/**
 * _strncmp - Compares two strings up to a specified length.
 * @str1: The first string.
 * @str2: The second string.
 * @n: The number to compare
 *
 * Return: The difference between the strings,
 *         or 0 if true.
 */
int _strncmp(const char *str1, const char *str2, int n)
{
	while (n > 0 && *str1 == *str2)
	{
		if (*str1 == '\0')
			return (0);
		str1++;
		str2++;
		n--;
	}

	if (n == 0)
		return (0);
	else
		return (*str1 - *str2);
}
/**
 * _strcpy - Copies a string from src to dest
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: The pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (dest_start);
}
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
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	if (access(command, X_OK) == -1)
	{
		perror(argv[0]);
		free(command);
		return (0);
	}
	if (!command)
	{
		perror("NOT FOUND");
		free(command);
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
		return (0);
	return (1);
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
	else if ((nread == -1 && check == errno) || (_strcmp(line, "exit\n") == 0) ||
			(_strcmp(line, "exit") == 0))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	return (1);
}
/**
 * forking - Creates a child process and executes a program in it.
 * @argv: An array of strings containing the program path and arguments.
 * @mode: 1 for interactive and 2 for non interactive
 * @line: line from user
 */
void forking(char *argv[], int mode, char *line)
{
	char *newargv[2];
	pid_t pid;

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
		wait(NULL);
	}
}
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

	nread = _getline(&line, &line_size, stdin);

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
	if (line)
		free(line);
	if (argv[0])
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

	nread = _getline(&line, &line_size, stdin);
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

/**
* _getline - gets input from user
* @lineptr: line
* @n: buffer size
* @stream: stream
* Return: -1 on error other wise number of bytes read
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t position;
	char *buffer, c = 'i';
	int rinput;
	ssize_t ret;

	if (stream == NULL)
		return (-1);
	if (position == 0)
		fflush(stream);
	else
		return (-1);
	position = 0;
	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);
	while (c != '\n')
	{
		rinput = read(STDIN_FILENO, &c, 1);
		if (rinput == 0 && position != 0)
		{
			position++;
			break;
		}
		if (rinput == -1 || (rinput == 0 && position == 0))
		{
			free(buffer);
			return (-1);
		}
		if (position >= 120)
		{
			buffer = _realloc(buffer, position, position + 1);
		}
		buffer[position++] = c;
	}
	buffer[position] = '\0';
	setline(lineptr, position, n, buffer);
	ret = position;
	position = 0;
	return (ret);
}
/**
 * setline - setsline for the _getline function
 * @lineptr: Pointer to the line's content
 * @position: Current position within the line's content
 * @n: Pointer to the allocated size of lineptr
 * @buffer: Buffer containing new content
 *
 */
void setline(char **lineptr, ssize_t position, size_t *n, char *buffer)
{
	if (*lineptr != NULL && *n >= (size_t)position)
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
	else if ((*lineptr != NULL && *n < (size_t)position) || *lineptr == NULL)
	{
		if (position < 120)
			*n = 120;
		else
			*n = (size_t)position;
		*lineptr = buffer;
	}
}
/**
 * _realloc - Entry point
 * @ptr: pointer to the memory previously allocated
 * @old_size: size of the allocated ptr
 * @new_size: size of new memory block
 *
 * Return: a pointer to an array
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *array = NULL;
	char *p = NULL;
	unsigned int i;
	char *px = NULL;

	if (ptr == NULL)
	{
		array = malloc(new_size);
		if (array == NULL)
			return (NULL);
		return (array);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (p != NULL)
	{
		px = (char *)ptr;
		for (i = 0; i < old_size; i++)
			p[i] = px[i];
		free(ptr);
		return (p);
	}

	return (NULL);
}
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
