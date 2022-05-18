#include "main.h"

/* REMOVE THIS!!! */
/**
 * print_list - prints all the elements of a list_t list in a given format
 * @h: pointer to a list_t
 *
 * Return: number of nodes in given list_t
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		printf("%s\n", h->name);

		count++;
		h = h->next;
	}

	return (count);
}

/**
 * add_node_end - adds a new node at the end of a list_s list
 * @head: pointer to the address of the first node
 * @name: the value of the name field of the new node
 * @value: the value of the value field of the new node
 *
 * Return: head of the new list. Otherwise NULL
 */
list_t *add_node_end(list_t **head, const char *name, const char *value)
{
	list_t *trav, *new;

	if (head == NULL || name == NULL || value == NULL)
		return (NULL);

	trav = *head;

	/* create the new node */
	new = create_node(name, value);
	if (new == NULL)
		return (NULL);

	/* if the list has no elements */
	if (trav == NULL)
	{
		*head = new;
		return (*head);
	}

	/* traverse to the end of the list */
	while (trav->next != NULL)
		trav = trav->next;

	trav->next = new;

	return (*head);
}

/**
 * list_len - finds the number of elements in a linked list_t list
 * @h: pointer to a list_t
 *
 * Return: number of elements in the list_t
 */
size_t list_len(const list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		count++;
		h = h->next;
	}

	return (count);
}

/**
 * create_node - creates a new list_t node
 * @name: value of the name field
 * @value: value of the value field
 *
 * Return: address of new node. Otherwise NULL
 */
list_t *create_node(const char *name, const char *value)
{
	list_t *new;

	if (name == NULL || value == NULL)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);

	new->name = _strdup(name);
	new->value = _strdup(value);
	new->next = NULL;

	return (new);
}

/**
 * split_string - splits a given string using a given delimiter
 * @s: string to split
 * @delim: delimiter
 *
 * Return: list of strings
 */
list_t *split_string(char *s, char *delim)
{
	char *str, *next_str;
	list_t *strings = NULL;

	if (s == NULL || delim == NULL)
	{
		return (NULL);
	}

	str = _strdup(s);

	/* get first string */
	add_node_end(&strings, _strtok(str, delim), "");

	/* get all other strings */
	while ((next_str = _strtok(NULL, delim)))
		add_node_end(&strings, next_str, "");

	free(str);

	return (strings);
}

/**
 * free_node - frees a list_t node
 * @h: pointer to list_t node
 */
void free_node(list_t *h)
{
	if (h == NULL)
		return;

	if (h->name)
		free(h->name);

	if (h->value)
		free(h->value);

	free(h);
	h = NULL;
}

/**
 * free_list - frees a list_t list
 * @h: list_t head
 */
void free_list(list_t *h)
{
	list_t *current;

	if (h == NULL)
		return;

	while (h != NULL)
	{
		current = h;
		h = h->next;
		free_node(current);
	}

}

/**
 * list_to_array - converts a given list of strings into an array of strings
 * @h: head of given list
 *
 * Return: an array of strings. Otherwise NULL
 */
char **list_to_array(const list_t *h)
{
	char **array;
	unsigned int i, length;

	if (h == NULL)
		return (NULL);

	/* allocate space for array */
	length = list_len(h);
	array = malloc(sizeof(char *) * (length + 1));
	if (array == NULL)
		return (NULL);

	for (i = 0; i < length && h; i++, h = h->next)
		array[i] = _strdup(h->name);

	array[length] = NULL;

	return (array);
}

/**
  * free_array - frees an array of strings
  * @arr: array
  */
void free_array(char **arr)
{
	unsigned int i;

	for (i = 0; arr && arr[i]; i++)
		free(arr[i]);

	if (arr)
	{
		free(arr);
	}

	arr = NULL;
}

/**
 * find_name - finds the index of a node with the given name in a list_t
 * @h: head of list_t
 * @name: name of node
 *
 * Return: index of node if found. Otherwise -1
 */
int find_name(list_t *h, const char *name)
{
	list_t *trav = h;
	int index = 0;

	if (h == NULL || name == NULL)
		return (-1);

	/* find matching node */
	while (trav && (_strcmp(trav->name, name)))
	{
		index++;
		trav = trav->next;
	}

	return (trav ? index : -1);
}

/**
 * update_value - updates value field list_t node at given index
 * @h: head of list_t
 * @index: index of node to update
 * @value: new value
 *
 * Return: 0 success. -1 Otherwise
 */
int update_value(list_t *h, int index, const char *value)
{
	list_t *trav = h;

	if (h == NULL || index < 0 || value == NULL)
		return (-1);

	/* find node to update */
	while (index && trav)
	{
		index--;
		trav = trav->next;
	}

	/* update node */
	if (trav)
	{
		free(trav->value);
		trav->value = _strdup(value);
		/*printf("UPDATE SUCCESSFUL!!!!\n");*/
		return (0);
	}

	return (-1);
}

/**
 * delete_node_index - deletes the node at given name of a linked list
 * @head: pointer to the pointer of the 1st node in the list
 * @index: the index of the node that should be deleted
 *
 * Return: 0 is successful. Otherwise -1
 */
int delete_node_index(list_t **head, int index)
{
	list_t *current, *del;
	int i;

	/* if list does not exist or list is empty */
	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;

	/* if you are deleting the 1st node */
	if (index == 0)
	{
		*head = (*head)->next;
		free_node(current);
		return (0);
	}

	/* go to the node just before the node we are supposed to delete */
	for (i = 0; (i < index - 1) && current->next; i++)
		current = current->next;

	/* delete the node */
	if (current->next && i == index - 1)
	{
		del = current->next;
		current->next = current->next->next;
		free_node(del);
	}

	return (0);
}
