#include "shell.h"

/**
 * handle_command - Fonction qui gère les arguments de ligne de commande
 * @buffer: Pointeur vers une chaîne de caractères contenant la commande
 */
void handle_command(char *buffer)
{
    char *token;
    char *args[100];  // Tableau pour stocker les arguments de la commande
    int arg_count = 0; // Compteur d'arguments

    // Découpage de la commande en tokens en utilisant l'espace comme délimiteur
    token = strtok(buffer, " ");
    while (token != NULL)
    {
        args[arg_count] = token; // Stockage de chaque token dans le tableau d'arguments
        arg_count++; // Incrémentation du compteur d'arguments
        token = strtok(NULL, " "); // Récupération du prochain token
    }

    args[arg_count] = NULL; // Marquage de la fin du tableau d'arguments avec NULL

    // Vérification si le fichier exécutable existe et est accessible
    if (access(args[0], X_OK) == 0)
    {
        // Création d'un processus fils pour exécuter la commande
        if (fork() == 0)
        {
            // Exécution de la commande à l'aide de execve
            if (execve(args[0], args, NULL) == -1)
            {
                perror(args[0]); // Affichage d'une erreur si l'exécution a échoué
                exit(EXIT_FAILURE); // Sortie du processus fils avec un code d'échec
            }
        }
        else
        {
            wait(NULL); // Attente de la fin de l'exécution du processus fils
        }
    }
}

