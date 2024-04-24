#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100

int main() {
    char buffer[1024];
    char *args[MAX_ARGS];
    int arg_count = 0;
    char *token;

    while (1) {
        printf("$ ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 
	/* Remove the newline character */
        /* Split the command into tokens */
        token = strtok(buffer, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        /* Check if the executable file exists and is accessible */
        if (access(args[0], X_OK) == 0) {
            /* Create a child process to execute the command */
            pid_t pid = fork();
            if (pid == 0) {
                /* Child process code */
                execvp(args[0], args);
                perror("Error executing the command");
                exit(1);
            } else if (pid > 0) {
                /* Parent process code */
                int status;
                waitpid(pid, &status, 0);
            } else {
                perror("Error creating the child process");
            }
        } else {
            printf("Command not found: %s\n", args[0]);
        }

        arg_count = 0;
    }

    return 0;
}
