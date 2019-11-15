#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//Declaration of variables
	pid_t childprocess;	
	int exitstatus = -1;
	char input[100];
	char *readinput;
	char *command[40];
	char delimeter[40];
	char *args[20];
	int i = 0;
	char *tokens;
	int a = 0;
	int k = 0;
	int l = 0;
	
	//Initializing mini-bash shell:
	while (1)
	{
		i = 0;
		printf("minibash@assignment3:~$\n");
		//Using system call 'read()'
		int number = read(0, &input, 100);
		input[number] = '\0';
		readinput = strdup(input);
		
		// Identifying delimeters

		tokens = strtok(input, "&;|\n"); 
		while (tokens != NULL)
		{
			delimeter[i] = readinput[tokens - input + strlen(tokens)];
			command[i] = tokens;
			i++;
			tokens = strtok(NULL, "&;|\n"); 
		}
		command[i] = NULL;

		k = i;
		i = 0;

		while (i <= k)
		{
			i++;
		}
		i = 0;
		exitstatus = -1;
		while (i < k)
		{
			if (exitstatus > -1) {
				if (delimeter[i - 1] == '&') {
					if (exitstatus != 0) {
						break;
					}
				} 
			}

			tokens = strtok(command[i], " ");
			a = 0;
			while (tokens != NULL & a < 10)
			{
				args[a] = tokens;
				a++;
				tokens = strtok(NULL, " ");
			}
			args[a] = NULL;
			l = a;
			a = 0;
			if (strcmp(args[0], "exit") == 0)
			{
				exit(0);
			}

			while (a <= l)
			{
			
				a++;
			}
			if ((childprocess = fork()) == 0)
			{
				execvp(args[0], args);
				fprintf(stderr, "Previous command failed  and child process could not run execvp. \n Please try a new command \n");
				exit(1);
			}
			else
			{
				//Check for if fork failed
				if (childprocess == (pid_t)(-1))
				{
					fprintf(stderr, "Fork failed.\n");
					exit(1);
				}
				else
				{
					wait(&exitstatus);
				}
			}
			i++;
		}
	}
	return 0;
}