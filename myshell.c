#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100

int main(void)
{
    close(2);
    dup(1);
    char command[BUFFER_SIZE];

    int condi = 0;
    char* com[BUFFER_SIZE];

    while (1)
    {
        condi = 0;
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);
        if (strncmp(command, "exit", 4) == 0)
        {
            break;
        }

        if (strchr(command, '&') != NULL)
        {
            condi = 1;
            strtok(command, "&");
        }


        pid_t pid;
        if ((pid = fork()) < 0) {
            printf("** ERROR: fork process has failed\n");
            exit(1);
        }
        else if (pid == 0) {

            if(command[strlen(command)-1]== '\n'){
               command[strlen(command)-1]= '\0';
            }
            com[0] = strtok(command, " ");
            int i = 0;
            while (com[i] != NULL)
            {
                com[++i] = strtok(NULL, " ");
            }

            execvp(com[0], com);
            exit(0);

        }

        else {

            if (condi == 0)
                waitpid(pid, NULL, 0);
        }
    }

    return 0;
}
