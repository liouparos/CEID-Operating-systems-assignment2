#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main ()
{
int str3;
        int str;
        char *line = NULL;
        char *args1[64];
        char *args2[64];
        do {
                printf("$ ");
                ssize_t bufsize = 0;
                getline(&line, &bufsize, stdin);
                char *user = line;
                char *str1 = strsep(&user, "|");
                char *str2 = strsep(&user, "\n");
                char **next = args1;
                char *temp = strtok(str1, "     \n");
                str = strcmp(str1, "exit");
                str3 = strcmp(line, "cd");
                if (str==0) break;
                while (temp != NULL)
                {
                        *next++ = temp;
                        temp = strtok(NULL, " \n");
                }
                *next = NULL;
                for (next = args1; *next != 0; next++);
                char **next1 = args2;
                char *temp1 = strtok(str2, "     \n");
                while (temp1 != NULL)
                {
                        *next1++ = temp1;
                        temp1 = strtok(NULL, " \n");
                }
		*next1 = NULL;
                for (next1 = args2; *next1 != 0; next1++);
        int fd[2];
        if(pipe(fd) == -1) {
          perror("Pipe failed");
          exit(1);
        }

        if(fork() == 0)            //first fork
        {
            close(STDOUT_FILENO);  //closing stdout
            dup(fd[1]);         //replacing stdout with pipe write
            close(fd[0]);       //closing pipe read
            close(fd[1]);

            execvp(args1[0], args1);
            perror("execvp of ls failed");
            exit(1);
        }

        if(fork() == 0)            //creating 2nd child
        {
            close(STDIN_FILENO);   //closing stdin
            dup(fd[0]);         //replacing stdin with pipe read
            close(fd[1]);       //closing pipe write
            close(fd[0]);

            //char* prog2[] = { "wc", "-l", 0};
            execvp(args2[0], args2);
            perror("execvp of wc failed");
            exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        wait(0);
        wait(0);
} while (str != 0);
return 0;
}

