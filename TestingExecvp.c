//
// Created by Sarah Depew on 2/11/18.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//Took code from https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/execvp.htm to learn about execvp
int main()
{
    pid_t pid;
    int status;
    char *const parmList[] = {"emacs", NULL};

    if ((pid = fork()) == -1)
        perror("fork() error");
    else if (pid == 0) {
        execvp("emacs", parmList);
        printf("Return not expected. Must be an execvp() error.n");
    }
    else if(pid > 0) {
        wait(&status);
    }
    exit(EXIT_SUCCESS);
}
