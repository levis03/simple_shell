#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024

/**
 * main - entry point
 *
 * Return: 0 on success , 1 on error
 */

int main(int argc, char** argv, char** envp)
{
	char command[MAX_LINE_LENGTH];

	while (1) {
		printf("simple_shell> ");
		if (fgets(command, MAX_LINE_LENGTH, stdin) == NULL) {
			printf("\n");
			break;
		}

		// Remove newline character from command

		command[strcspn(command, "\n")] = '\0';

		pid_t pid = fork();
		if (pid == 0) {
			int exec_result = execve(command, NULL, envp);
			if (exec_result == -1) {
				perror("Error");
			}
			exit(0);
		} else if (pid > 0) {
			int status;
			waitpid(pid, &status, 0);
		} else {
			perror("Error");
		}
	}

	return 0;
}
