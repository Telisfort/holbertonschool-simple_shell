#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUF 1024

int main(int argc, char *argv[])
{
	size_t len = 0;
	char *temp, *args[BUF];
	ssize_t nread;
	/* Déclaration des variables */

	/* Initialisation des variables */
	pid_t pid;

	/* Ignorer les arguments non utilisés */
	(void)argc, (void)argv;

	/* Boucle principale du shell */
	while (1)
	{
		/* Affichage du prompt */
		printf("$ ");
		fflush(stdout);

		/* Lecture de la commande depuis stdin */
		nread = getline(&temp, &len, stdin);

		/* Vérifier s'il y a une erreur de lecture */
		if (nread == -1)
			exit(1);

		/* Supprimer le caractère de nouvelle ligne du buffer */
		if (temp[nread - 1] == '\n')
			temp[nread - 1] = '\0';

		/* Ignorer les commandes vides */
		if (!strlen(temp))
			continue;

		/* Tokenisation de la commande */
		tokenizer(args, temp);

		/* Création d'un nouveau processus */
		pid = fork();

		/* Gestion des erreurs lors de la création du processus */
		if (pid == -1)
		{
			perror("./shell");
			exit(1);
		}
		/* Code exécuté par le processus enfant */
		else if (pid == 0)
		{
			/* Exécuter la commande */
			if (execve(args[0], args, NULL) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		/* Code exécuté par le processus parent */
		else
			wait(NULL); /* Attendre la fin du processus enfant */
	}
}

