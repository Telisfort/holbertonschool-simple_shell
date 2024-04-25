#include "shell.h"

// Déclaration des prototypes des fonctions
int execute_builtin(char *command, char **args, char *flags, char **env, int count, int out);
int search_command(char **args, char *flags, char **env, int count);

// Fonction principale pour obtenir et exécuter une commande
int get_and_execute_command(char *input, char *file, char **env, int count, int out) {
    char **args = NULL;
    int index = 0;

    // Allocation mémoire pour les arguments
    args = malloc(64 * sizeof(char *));
    if (!args) {
        perror("Error on allocation");
        exit(EXIT_FAILURE);
    }

    // Séparation de la chaîne d'entrée en arguments
    char *token = strtok(input, " ");
    while (token) {
        args[index++] = token;
        token = strtok(NULL, " ");
    }
    args[index] = NULL;

    // Exécution de la commande
    out = execute_builtin(args[0], args, file, env, count, out);

    // Libération de la mémoire allouée pour les arguments
    free(args);
    return out;
}

// Fonction pour exécuter une commande intégrée ou chercher une commande externe
int execute_builtin(char *command, char **args, char *flags, char **env, int count, int out) {
    // Recherche de la commande intégrée
    int (*builtin_func)(char *, char **, char *, char **, int, int) = builtin(command);
    if (builtin_func)
        out = builtin_func(command, args, flags, env, count, out);
    else
        // Recherche de la commande externe
        out = search_command(args, flags, env, count);
    return out;
}

