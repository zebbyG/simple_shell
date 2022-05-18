#include "main.h"

/**
 * create_env - creates a list of environment variables
 * @env: array of environment variables
 * @env_list: list of environment variables
 *
 * Return: new head of list. Otherwise NULL
 */
list_t *create_env(char **env, list_t *env_list)
{
	unsigned int i;
	char *name, *value;

	if (env == NULL)
	{
		return (NULL);
	}

	for (i = 0; env[i]; i++)
	{
		name = _strtok(env[i], "=");
		value = _strtok(NULL, "\n");

		if (add_node_end(&env_list, name, value) == NULL)
		{
			return (NULL);
		}
	}

	return (env_list);
}

/**
 * _getenv - gets the value of an environment variable
 * @env_list: list of environment variables
 * @name: environment variable
 *
 * Return: value of name. Otherwise NULL
 */
char *_getenv(list_t *env_list, char *name)
{
	list_t *trav = env_list;

	if (name == NULL)
	{
		return (NULL);
	}

	while (trav && _strcmp(trav->name, name))  /* check each node for a match */
	{
		trav = trav->next;
	}

	if (trav)
		return (trav->value);

	return (NULL);
}

/**
 * print_env - prints all the environment variables
 * @env_list: list of environment variables
 */
void print_env(list_t *env_list)
{
	list_t *trav = env_list;

	while (trav != NULL)
	{
		/*printf("[%d] ", trav->index);*/
		/*printf("%s=%s\n", trav->name, trav->value);*/

		write(STDOUT_FILENO, trav->name, _strlen(trav->name) + 1);
		write(STDOUT_FILENO, "=", 2);
		write(STDOUT_FILENO, trav->value, _strlen(trav->value) + 1);
		write(STDOUT_FILENO, "\n", 2);

		trav = trav->next;
	}
}

/**
 * _setenv - changes or adds an environment variable
 * @env_list: list of environment variables
 * @name: name of environment variable
 * @value: value of environment variable
 * @ow: overwrite flag
 *
 * Return: 0 if successful. Otherwise -1
 */
int _setenv(list_t *env_list, const char *name, const char *value, int ow)
{
	int index;

	if (name == NULL || value == NULL || is_in_str(name, '='))
		return (-1);

	/* find index of node with name */
	index = find_name(env_list, name);

	/* if name not in list */
	if (index == -1)
	{
		if (add_node_end(&env_list, name, value) == NULL)
			return (-1);

		return (0);
	}

	/* update node at index */
	if (ow)
		return (update_value(env_list, index, value));

	return (0);
}

/**
 * _unsetenv - deletes the variable name from the environment
 * @env_list: list of environment variables
 * @name: name of variable to delete
 *
 * Return: 0 success. -1 otherwise
 */
int _unsetenv(list_t *env_list, const char *name)
{
	int index;

	if (name == NULL)
		return (-1);

	/* find index of node to delete */
	index = find_name(env_list, name);

	/* if name is not in the list */
	if (index == -1)
		return (0);

	/* delete node at index */
	if (delete_node_index(&env_list, index) == -1)
		return (-1);

	return (0);
}
