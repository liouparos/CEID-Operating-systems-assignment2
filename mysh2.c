#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main ()
{
	int str2;
	int str;
	char *line = NULL;
	char *args[64];
	do {
		printf("$ ");
        	ssize_t bufsize = 0;
        	getline(&line, &bufsize, stdin);
        	char **next = args;
        	char *temp = strtok(line, " 	\n");
		str = strcmp(line, "exit");
		str2 = strcmp(line, "cd");
		if (str==0) break;
        	while (temp != NULL)
        	{
        		*next++ = temp;
        		temp = strtok(NULL, " \n");
        	}
        	*next = NULL;
        	for (next = args; *next != 0; next++);
        	pid_t pid = fork();
		if (pid == -1)
		{
		    // error, failed to fork()
		}
		else if (pid > 0)
		{
		    int status;
		    waitpid(pid, &status, 0);
		}
		else
		{
		 if (str==0)
                {
                 return 0;
                }
			if (str2==0){
				chdir(args[1]);
			}
		   // we are the child
			else if (execvp(args[0],args) == -1)
			{
			      // perror ("exec");  // exec never returns
			}
		}
	}
	while (str != 0);
	exit(0);
}

