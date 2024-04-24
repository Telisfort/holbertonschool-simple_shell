#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


#define MAX_ARGS 100

int main() {
    char input[1024];
    char *args[MAX_ARGS];
    int status;

    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; 
	/* Remove the newline character */

        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == 0) {
            /* Child process */
            if (args[0] == NULL || strlen(args[0]) == 0) {
                /* The command is empty, do nothing */
                exit(EXIT_SUCCESS);
            }

            if (execvp(args[0], args) == -1) {
                /* Failed to execute the command */
                fprintf(stderr, "Error executing command '%s': %s\n", args[0], strerror(errno));
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) {
            /* Parent process */
            waitpid(pid, &status, 0);
        } else {
            /* Fork() error */
            perror("fork");
            continue;
        }
    }

    return 0;
}
