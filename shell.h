#ifndef SHELL_H
#define SHELL_H

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

#define MAX_ARGS 1024

extern char **environ;

/* Function prototypes */
char *_strcat(char *dest, char *src);
int _strlen(const char *s);
void print_env(void);
void shell_loop(void);
int execute_command(char *argv[]);
void prompt(void);
ssize_t read_line(char **line, size_t *line_size, int check);
int tokenize_line(char *line, char *argv[]);
int _strcmp(const char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, int n);
char *_getenv(const char *name);
char *_memcpy(char *dest, char *src, unsigned int n);
#endif /* SHELL_H */
