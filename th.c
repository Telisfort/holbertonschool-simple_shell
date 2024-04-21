#include "shell.h"

/**
 * _path - Crée une liste chaînée pour les répertoires du chemin d'accès
 * @path: chaîne de caractères contenant la valeur du chemin d'accès
 * Return: pointeur vers la liste chaînée créée, ou NULL en cas d'échec
 */
list_path *_path(const char *path)
{
	char *cpath, *token;
	list_path *head;

	if (!path)
		return (NULL); /* Gère gracieusement une entrée NULL */

	cpath = strdup(path); /* Utilisation de strdup pour copier le chemin d'accès */
	if (!cpath)
		return (NULL); /* Échec d'allocation mémoire */

	head = NULL;
	token = strtok(cpath, ":"); /* Découpe la chaîne en tokens en utilisant ":" comme délimiteur */

	while (token)
	{
		if (!add_node_end(&head, token))
		{
			/* Libère la liste et cpath en cas d'erreur */
			free_list(head);
			free(cpath);
			return (NULL);
		}
		token = strtok(NULL, ":"); /* Récupère le prochain token */
	}
	free(cpath);
	return (head);
}

/**
 * add_node_end - Ajoute un nouveau nœud à la fin d'une liste chaînée
 * des répertoires du chemin d'accès.
 * @head: Pointeur vers le début de la liste chaînée.
 * @path: Chaîne de chemin d'accès à ajouter à la liste.
 * Return: Pointeur vers le nouveau nœud ajouté, ou NULL en cas d'échec.
 */

list_path *add_node_end(list_path **head, const char *path)
{
	/* Alloue de la mémoire pour le nouveau nœud */
	list_path *new_node = (list_path *)malloc(sizeof(list_path));

	if (!new_node)
		return (NULL); /* Échec d'allocation mémoire */

	/* Alloue de la mémoire pour la chaîne de chemin d'accès dans le nouveau nœud */
	new_node->path = (char *)malloc(strlen(path) + 1);
	if (!new_node->path)
	{
		free(new_node);
		return (NULL); /* Échec d'allocation mémoire */
	}

	/* Copie la chaîne de chemin d'accès dans le nouveau nœud */
	strcpy(new_node->path, path);

	/* Initialise le pointeur suivant à NULL */
	new_node->next = NULL;

	/* Vérifie si la liste chaînée est vide */
	if (*head == NULL)
	{
		*head = new_node; /* Définit le nouveau nœud comme début de la liste */
	}
	else
	{
		/* Traverse la liste pour trouver la fin */
		list_path *current = *head;

		while (current->next != NULL)
			current = current->next;

		/* Ajoute le nouveau nœud à la fin de la liste */
		current->next = new_node;
	}

	/* Renvoie le nouveau nœud ajouté */
	return (new_node);
}

/**
 * which_path - trouve le chemin d'accès d'un fichier
 * @filename: nom du fichier ou de la commande
 * @head: début de la liste chaînée des répertoires du chemin d'accès
 * Return: chemin d'accès du fichier ou NULL s'il n'y a pas de correspondance ou en cas d'erreur
 */
char *which_path(char *filename, list_path *head)
{
	struct stat st;
	char *string = NULL;
	size_t required_length;

	list_path *tmp = head;

	if (filename == NULL)  /* Vérifie si filename est NULL */
		return (NULL);

	while (tmp) /* Parcourt chaque répertoire de la liste */
	{
		/* Alloue de la mémoire pour le chemin d'accès concaténé */
		required_length = strlen(tmp->path) + strlen("/") + strlen(filename) + 1;
		string = (char *)malloc(required_length);
		strcpy(string, tmp->path);

		if (string == NULL)
			return (NULL); /* Erreur d'allocation mémoire */

		/* Construit le chemin d'accès complet */
		strcpy(string, tmp->path);
		strcat(string, "/");
		strcat(string, filename);

		/* Vérifie si le fichier existe à ce chemin d'accès */
		if (stat(string, &st) == 0)
			return (string); /* Fichier trouvé */

		/* Libère la mémoire allouée pour le chemin d'accès */
		free(string);
		string = NULL;

		tmp = tmp->next; /* Passe au répertoire suivant */
	}

	return (NULL); /* Fichier non trouvé */
}

/**
 * free_list - Libère une liste chaînée des répertoires du chemin d'accès.
 * @head: Pointeur vers le début de la liste chaînée.
 */
void free_list(list_path *head)
{
	/* Variable pour stocker le nœud suivant lors du parcours de la liste */
	list_path *next_node;

	while (head) /* Parcourt la liste et libère chaque nœud */
	{
		next_node = head->next; /* Stocke le nœud suivant */
		free(head->path); /* Libère la chaîne de chemin d'accès */
		free(head); /* Libère le nœud courant */
		head = next_node; /* Passe au nœud suivant */
	}
}	

