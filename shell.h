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

#define MAX 1024
extern char **environ;

int interactive(char *line, int *n);
void non_interactive(char *line);
char *_strcat(char *dest, char *src);
int _strlen(const char *s);
int print_env(void);
int _strcmp(const char *s1, char *s2);
int _strncmp(const char *str1, const char *str2, int n);
char *_getenv(const char *name);
int nopath(char *command, char *argv[], int *q);
int tokenize(char *nnread, char *argv[], char *line);
int checkbuiltins(int check, char *line, ssize_t nread, int n);
char *_strdup(char *str);
char *_memcpy(char *dest, char *src, unsigned int n);
int forking(char *argv[], int mode, char *line);
char *_strcpy(char *dest, char *src);
void setline(char **lineptr, ssize_t position, size_t *n, char *buffer);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *ret_nondelim(char *str1, char *str2);
char *ret_noofbytes(char *str1, char *str2);
char *_strtok(char *str1, char *str2);
#endif /* SHELL_H */
