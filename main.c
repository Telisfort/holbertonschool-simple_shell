#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

int main() {
	char line[MAX_LINE];
	char *args[2];
	int status;
	pid_t pid = fork();

	while (1) 
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(line, MAX_LINE, stdin) == NULL) 
		{
			/* Handle Ctrl+D (EOF) */
			printf("\n");
			break;
		}

		/* Remove trailing newline character */
		line[strcspn(line, "\n")] = '\0';

		/* Split the command line into args */
		args[0] = line;
		args[1] = NULL;


		if (pid == -1) 
		{
			/* Error forking */
			perror("fork");
			continue;
		} else if (pid == 0) 
		{
			/* Child process */
			if (execvp(args[0], args) == -1) 
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else 
		{
			/* Parent process*/
			waitpid(pid, &status, 0);
		}
	}

	return 0;
}
