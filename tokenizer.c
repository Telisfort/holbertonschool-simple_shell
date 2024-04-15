#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BUF 1024

/* Fonction de tokenisation */
char **tokenizer(char *args[], char *temp)
{
	int i = 0;
	char *tokenized;

	/* Découpe de la chaîne en jetons */
	tokenized = strtok(temp," ");
	while(tokenized)
	{
		/* Stockage des jetons dans le tableau d'arguments */
		args[i] = tokenized;
		tokenized = strtok(NULL," ");
		i++;
	}
	/* Ajout d'un pointeur NULL pour marquer la fin du tableau d'arguments */
	args[i] = NULL;
	return (args);
}

