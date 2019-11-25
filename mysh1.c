#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main ()
{
	int str = 1;
	char exit[4];
	strcpy(exit, "exit");
	char *line = NULL;
	char *args[64];
while (str != 0) {
	printf("$ ");
        ssize_t bufsize = 0;
        getline(&line, &bufsize, stdin);
        char **next = args;
        char *temp = strtok(line, " \n");
	str = strcmp(line, exit);
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
	//if (args != exit) {
	   // we are the child
		if (execvp(args[0],args) == -1)
		{
		     //   perror ("exec");  // exec never returns
		}
	//}
	}
}
return 0;
}
