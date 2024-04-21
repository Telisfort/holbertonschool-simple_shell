#include "shell.h"

/* Vérifie si la commande spécifiée est une commande intégrée et l'exécute si c'est le cas */
int check_builtin(char **arg)
{
    // Définition d'une structure pour stocker les commandes intégrées et les fonctions associées
    bl_t array[] = {
        {"exit", exit_func},        // Commande "exit" pour quitter le shell
        {"env", printenv_func},     // Commande "env" pour afficher l'environnement
        {NULL, NULL}                // Marqueur de fin du tableau
    };
    int i;

    // Parcours du tableau de commandes intégrées
    for(i = 0; array[i].command; i++)
    {
        // Comparaison de la commande spécifiée avec les commandes intégrées
        if (strcmp(array[i].command, *arg) == 0)
        {
            // Si la commande est trouvée, exécute la fonction associée et renvoie 1
            array[i].func(arg);
            return (1);
        }
    }
    // Si la commande n'est pas trouvée dans les commandes intégrées, renvoie 0
    return (0);
}

/* Fonction pour quitter le shell */
void exit_func(char **arg)
{
    // Libération de la mémoire allouée pour le tableau d'arguments
    free_tab(arg);
    // Quitte le programme avec un code de sortie de 2
    exit(2);
}

/* Fonction pour imprimer l'environnement */
void printenv_func(char **arg)
{
    char **cp_env = environ;
    (void)arg;  // Utilisé pour éviter un avertissement sur la variable non utilisée
    
    // Parcours du tableau des variables d'environnement et affichage de chaque variable
    for (; *cp_env; cp_env++)
    {
        printf("%s\n", *cp_env);
    }
}

