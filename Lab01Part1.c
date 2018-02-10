//
// Created by Sarah Depew on 2/10/18.
//

/*Write a program where the parent forks off one child, have child send SIGUSR1 to
parent, have parent send SIGUSR2 to child. Register handlers that will print which
sigs were received (for both parent and child). Then have parent kill child by sending
SIGTERM. Wait on status and then report child terminated.
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//signal handler
void parentHandler(int value);
void childHandler(int value);

int main() {
    pid_t pid;
    int status;

    //register signal handlers
    signal(SIGUSR1, childHandler);
    signal(SIGUSR2, parentHandler);

    //fork from parent
    pid = fork();

    if (pid == 0) {
        kill(getppid(), SIGUSR1);
        sleep(1000);
    } else if (pid > 0) {
        kill(pid, SIGUSR2);
        sleep(1000);
        //wait does not go here because child finishes before wait and then waiting on a process that no longer exists
        kill(pid, SIGTERM);
        wait(&status);
        //examine status
        printf("Status value: %d\n", status);
    } else {
        printf("%s\n", "Fork returned error code.");
    }
}

//signal handler
void parentHandler(int value) {
    printf("Parent signal sent: %d\n", value);
}

void childHandler(int value) {
    printf("Child signal sent: %d\n", value);
}