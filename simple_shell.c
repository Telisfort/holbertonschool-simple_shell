#include "shell.h"

/**
 * handle_command - Function that handles command line arguments
 * @buffer: char to a ptr
 */
void handle_command(char *buffer)
{
	char *token;
	char *args[100];
	int arg_count = 0;

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;

	if (access(args[0], X_OK) == 0)
	{
		if (fork() == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
}

