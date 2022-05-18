#include "main.h"

/**
 * shell - implement shell functionality
 * @env_list: list of environment variables
 * @shell_name: name of shell program
 *
 * Return: 0 success. Non-zero otherwise
 */
int shell(list_t *env_list, char *shell_name)
{
	char *input, *full_name;
	list_t *input_list;
	char **input_array;
	pid_t child_pid;
	int status, built_ret;

	while (1)
	{
		input = get_input();
		if (input == NULL)
		{
			return (0);
		}

		if (input[0] == '\n')
		{
			free(input);
			continue;
		}

		/* check input */
		input_list = split_string(input, " ");
		if (input_list == NULL)
		{
			free(input);
			continue;
		}

		/* check if input is a built-in command */
		built_ret = get_built(input_list, shell_name, env_list);
		if (built_ret < -1)
		{
			free_list(input_list);
			free(input);
			continue;
		}
		else if (built_ret >= 0)
		{
			free_list(input_list);
			free(input);
			return (built_ret);
		}

		/* check if 1st string is a valid command */
		full_name = get_full_name(input_list->name, env_list);
		if (full_name == NULL)
		{
			print_error(shell_name, "No such file or directory\n");
			free_list(input_list);
			free(input);
			continue;
		}

		/* change name of command to its full name */
		free(input_list->name);
		input_list->name = full_name;

		/* change input_list to input_array */
		input_array = list_to_array(input_list);
		free_list(input_list);
		if (input_array == NULL)
		{
			print_error(shell_name, "No commands\n");
			free(input);
			continue;
		}

		/* create child process */
		child_pid = fork();
		if (child_pid == -1)
		{
			print_error(shell_name, "fork error\n");
			free_array(input_array);
			free(input);
			return (1);
		}

		/* execute command */
		if (child_pid == 0)
		{
			if (execve(input_array[0], input_array, NULL) == -1)
			{
				print_error(shell_name, "execve error\n");
				free_array(input_array);
				free(input);
				return (126);
			}
		}

		wait(&status);
		free_array(input_array);
		free(input);
	}

	return (0);
}

/**
 * get_input - gets input from the terminal
 *
 * Return: string input. Otherwise NULL
 */
char *get_input(void)
{
	char *buffer = NULL;
	size_t bufferSize = 0;
	char prompt[] = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, sizeof(prompt));
	if (getline(&buffer, &bufferSize, stdin) == -1)
	{
		write(STDOUT_FILENO, "\n", 2);
		free(buffer);
		return (NULL);
	}

	return (_strlen(buffer) == 1 ? buffer : _strtok(buffer, "\n"));
}

/**
 * print_error - prints given error message to stderr
 * @shell_name: name of shell program
 * @message: error message
 */
void print_error(char *shell_name, char *message)
{
	write(STDERR_FILENO, shell_name, _strlen(shell_name) + 1);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, message, _strlen(message) + 1);
}
