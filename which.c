#include "main.h"

/**
 * get_full_name - gets full name of a given command
 * @name: string
 * @env_list: list of environment variables
 *
 * Return: full name of given command . Otherwise NULL
 */
char *get_full_name(char *name, list_t *env_list)
{
	char *path, *fullname;
	list_t *path_dir_list;

	if (name == NULL)
		return (NULL);

	/* get value of PATH */
	path = _getenv(env_list, "PATH");

	/* split path */
	path_dir_list = split_string(path, ":");

	/* get full path of filename */
	fullname = get_full_path(name, path_dir_list);

	free_list(path_dir_list);

	return (fullname);
}

/**
 * get_full_path - checks if a given file is in PATH and returns its full path
 * @filename: filename as string
 * @path_list: list of the directories in PATH
 *
 * Return: full path of filename. Otherwise NULL
 */
char *get_full_path(char *filename, list_t *path_list)
{
	char *full_path;
	list_t *trav;

	if (filename == NULL || *filename == '\0')
	{
		return (NULL);
	}

	/* check if filename starts with . or / */
	if (filename[0] == '/' || filename[0] == '.')
	{
		if (is_command(filename))
			return (_strdup(filename));

		return (NULL);
	}

	/* check for filename in all the directories */
	for (trav = path_list; trav; trav = trav->next)
	{
		/* get fullpath */
		full_path = create_path(trav->name, filename);
		if (full_path)
		{
			if (is_command(full_path))
				return (full_path);

			free(full_path);
		}
	}

	return (NULL);
}

/**
 * create_path - concatenates directory name and filename to create full path
 * @dir: directory name
 * @filename: filename
 *
 * Return: new string representing full file path. Otherwise NULL
 */
char *create_path(char *dir, char *filename)
{
	unsigned int i, j, k, len_d, len_f;
	char *full_path;

	if (dir == NULL || filename == NULL)
		return (NULL);

	len_d = _strlen(dir);
	len_f = _strlen(filename);

	/* allocate space for new string */
	full_path = malloc(sizeof(char) * (len_d + len_f + 2));
	if (full_path == NULL)
		return (NULL);

	/* copy contents of dir */
	for (i = 0, k = 0; i < len_d; i++, k++)
		full_path[k] = dir[i];

	full_path[k++] = '/';

	/* copy contents of filename */
	for (j = 0; j < len_f; j++, k++)
		full_path[k] = filename[j];

	full_path[k] = '\0';

	return (full_path);
}

/**
 * is_command - checks if a given filename is a valid command
 * @filename: string
 *
 * Return: 1 if filename is valid command. 0 otherwise.
 */
int is_command(char *filename)
{
	struct stat sfile;

	if (filename == NULL)
		return (0);

	/* if file exists and can be executed */
	if (access(filename, X_OK) == 0)
	{
		stat(filename, &sfile);
		if (sfile.st_mode & S_IFREG) /* ensure it's a regular file */
			return (1);
	}

	return (0);
}
