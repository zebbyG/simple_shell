#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>

/**
 * struct list_s - singly linked list of values
 * @name: string
 * @value: string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *name;
	char *value;
	struct list_s *next;
} list_t;

/**
 * struct built_s - Struct built_s
 * @name: built-in command
 * @f: function associated
 *
 * Description: struct representing shell built-in command
 */
typedef struct built_s
{
	char *name;
	int (*f)(list_t *input_list, char *shell_name, list_t **env_list_ptr);
} built_s;

/* main.c */
void sig_handler(int sig);

/* env_list.c */
list_t *create_env(char **env, list_t *env_list);
char *_getenv(list_t *env_list, char *name);
void print_env(list_t *env_list);
int _setenv(list_t *env_list, const char *name, const char *value, int ow);
int _unsetenv(list_t *env_list, const char *name);

/* lists.c */
list_t *add_node_end(list_t **head, const char *name, const char *value);
list_t *create_node(const char *name, const char *value);
list_t *split_string(char *str, char *delim);
void free_node(list_t *h);
void free_list(list_t *h);
size_t list_len(const list_t *h);
char **list_to_array(const list_t *h);
void free_array(char **arr);
size_t print_list(const list_t *h);
int find_name(list_t *h, const char *name);
int update_value(list_t *h, int index, const char *value);
int delete_node_index(list_t **head, int index);

/* shell.c */
int shell(list_t *env_list, char *shell_name);
char *get_input(void);
void print_error(char *shell_name, char *message);

/* built.c */
int get_built(list_t *input_list, char *shell_name, list_t *env_list);
int exit_shell(list_t *input_list, char *shell_name, list_t **env_list_ptr);
int env_func(list_t *input_list, char *shell_name, list_t **env_list_ptr);
int setenv_func(list_t *input_list, char *shell_name, list_t **env_list_ptr);
int unsetenv_func(list_t *input_list, char *shell_name, list_t **env_list_ptr);

/* which.c */
char *get_full_name(char *name, list_t *env_list);
char *get_full_path(char *filename, list_t *path_list);
char *create_path(char *dir, char *filename);
int is_command(char *filename);

/* strings.c */
char *_strcpy(char *dest, const char *src);
unsigned int _strlen(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *str);
char *_strtok(char *str, const char *delim);
int is_in_str(const char *str, char c);
int _atoi(char *str);

#endif
