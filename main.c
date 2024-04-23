#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_TOKENS 10  /* Nombre maximum de tokens */

/**
 * main - Boucle principale du shell
 *
 * Affiche un prompt, attend les commandes, gère la commande "exit",
 * affiche les variables d'environnement avec "env", et exécute des programmes.
 *
 * Retour: 0 en cas de succès, autre chose sinon.
 */
int main(void)
{
    char *line = NULL; /* Ligne de commande */
    size_t len = 0; /* Taille de la ligne */
    ssize_t nread; /* Nombre de caractères lus */
    char *prompt = "simple_shell$ "; /* Prompt du shell */

    while (1) /* Boucle principale */
    {
        printf("%s", prompt); /* Afficher le prompt */
        nread = getline(&line, &len, stdin); /* Lire la commande de l'utilisateur */

        if (nread == -1) /* Gérer Ctrl+D (fin de fichier) */
        {
            printf("\n"); /* Nouvelle ligne pour le terminal */
            break; /* Quitter la boucle, arrêter le shell */
        }

        if (line[nread - 1] == '\n') /* Enlever le retour à la ligne */
        {
            line[nread - 1] = '\0';
        }

        char *tokens[MAX_TOKENS]; /* Stocker les parties de la commande */
        int token_count = 0; /* Compteur de tokens */

        /* Découper la ligne en parties (tokens) */
        char *token = strtok(line, " ");
        while (token != NULL && token_count < MAX_TOKENS)
        {
            tokens[token_count++] = token; /* Ajouter le token */
            token = strtok(NULL, " ");
        }

        tokens[token_count] = NULL; /* Marquer la fin des tokens */

        if (token_count == 0) /* Si la ligne est vide, continuer */
        {
            continue;
        }

        /* Vérifier la commande "exit" */
        if (strcmp(tokens[0], "exit") == 0)
        {
            break; /* Quitter la boucle pour arrêter le shell */
        }

        /* Vérifier la commande "env" */
        if (strcmp(tokens[0], "env") == 0)
        {
            char **env; /* Pointeur sur les variables d'environnement */
            for (env = environ; *env != NULL; env++)
            {
                printf("%s\n", *env); /* Afficher chaque variable */
            }
            continue; /* Afficher le prompt à nouveau */
        }

        /* Si ce n'est pas "exit" ou "env", exécuter la commande */
        pid_t pid = fork(); /* Créer un processus enfant */

        if (pid == -1) /* Erreur de fork */
        {
            perror("Erreur de fork");
            continue; /* Afficher le prompt à nouveau */
        }

        if (pid == 0) /* Dans le processus enfant */
        {
            execve(tokens[0], tokens, environ); /* Exécuter la commande */
            perror("Erreur d'exécution"); /* Si execve échoue */
            exit(EXIT_FAILURE); /* Quitter le processus enfant */
        }

        /* Attendre que le processus enfant se termine */
        waitpid(pid, NULL, 0); /* Le processus parent attend */
    }

    /* Libérer la mémoire utilisée pour lire les commandes */
    free(line);

    /* Terminer le programme */
    return 0;
}

