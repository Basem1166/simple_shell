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
	int check = errno, flag = 0;
	char *argv[MAX];
	char *nnread = NULL;

	write(1, "$ ", 2);

	nread = _getline(&line, &line_size, stdin);

	if (checkbuiltins(check, line, nread) == 0)
		return (0);

	if (tokenize(nnread, argv, line) == 0)
		return (0);

	if (access(argv[0], X_OK) != 0)
	{
		flag = 1;
		if (nopath(command, argv) == 0)
		{
			free(line);
			return (0);
		}
	}
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


