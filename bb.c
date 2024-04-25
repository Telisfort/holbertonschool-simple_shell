#include "shell.h"

// Déclaration des prototypes des fonctions
void exit_func(char **arg);
void printenv_func(char **arg);

// Structure pour stocker une commande intégrée et sa fonction associée
typedef struct {
    const char *command;
    void (*func)(char **);
} builtin_command;

// Tableau des commandes intégrées
static const builtin_command builtin_commands[] = {
    {"exit", exit_func},      // Commande "exit" pour quitter le shell
    {"env", printenv_func},   // Commande "env" pour afficher l'environnement
    {NULL, NULL}              // Marqueur de fin du tableau
};

// Fonction de hachage simple pour les chaînes de caractères
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str++;
    }
    return hash;
}

// Vérifie si la commande spécifiée est une commande intégrée et l'exécute si c'est le cas
int check_builtin(char **arg) {
    const char *command = arg[0];
    unsigned int index = hash(command) % (sizeof(builtin_commands) / sizeof(builtin_commands[0]));
    
    // Parcours du tableau de commandes intégrées à partir de l'index calculé
    for (; builtin_commands[index].command != NULL; index = (index + 1) % (sizeof(builtin_commands) / sizeof(builtin_commands[0]))) {
        if (strcmp(builtin_commands[index].command, command) == 0) {
            // Si la commande est trouvée, exécute la fonction associée
            builtin_commands[index].func(arg);
            return 1;
        }
    }
    // Si la commande n'est pas trouvée dans les commandes intégrées, renvoie 0
    return 0;
}

// Fonction pour quitter le shell
void exit_func(char **arg) {
    // Libération de la mémoire allouée pour le tableau d'arguments
    free_tab(arg);
    // Quitte le programme avec un code de sortie de 2
    exit(2);
}

// Fonction pour imprimer l'environnement
void printenv_func(char **arg) {
    char **cp_env = environ;
    (void)arg;  // Utilisé pour éviter un avertissement sur la variable non utilisée
    
    // Parcours du tableau des variables d'environnement et affichage de chaque variable
    for (; *cp_env; cp_env++) {
        printf("%s\n", *cp_env);
    }
}

