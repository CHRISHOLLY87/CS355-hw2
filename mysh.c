/*
* 2. Simple Shell: design and implement a simple shell mysh. The basic function of a shell is to accept lines of text as
* input and execute programs in response.
* The requirements are listed below:
* (a) Simple execution of commands in the foreground. These are the steps of the most basic shell function, which are looped:
* i. Print a prompt of your choice
* ii. Get the command line
* iii. Parse the command line into command and arguments
* iv. Fork a child which executes the command with its arguments, wait for the child to terminate
* Relevant system calls are fork(), wait(), exec() families and exit().
* //TODO: figure out how to do this... Note that your shell should be able to perform standard path search according to the search path defined by the PATH environment variable. Hint: remember execvp. //TODO: figure out how to path searching in shell..
* (b) Built-in commands
* • exit: Exits mysh and returns to whatever shell you started mysh from. //TODO: clarify what this means?
* (c) When parsing the command line, mysh should ignore all white spaces. You should find the Clib functions isspace() and strtok() useful.
* We are going to build on this shell, so please have future expansions in mind when you write your parser.
* (d) Thou shall not crash. Since the shell is at the front line of user interaction, and its quality reflects heavily on the usability
* of an OS, it is paramount that mysh does not crash under any circumstances. Granted it doesn’t do much yet compared to a real shell
* and feel free to simply report error for all things you do not know how to handle. However, your shell must be able to check for
* and catch all the exceptions. Also remember to check for memory leaks.
* (e) When in doubt, consult the man pages and do what Linux does.
*/

//Imports
#include <stdlib.h>
#include <printf.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <zconf.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

//Macros
#define TRUE 1
#define FALSE 0
#define NUM_COMMANDS 1
#define MAX_BUFFER 1024
#ifndef _REENTRANT
#define _REENTRANT
#endif

//Structs
typedef struct command
{
    char* command;
    int arguments[];
} command;

//Method declarations
void print_prompt();
char *read_command_line(char *prompt);
command parse_command(char* line);
int execute_command(command cmd);
int is_valid(command cmd);
void initialize_commands(command* commands);
void error_message();

//Global variables and arrays
command commands[NUM_COMMANDS];

/*
 * Method main()
 */
int main(int argc, char** argv) {
    pid_t child_pid;
    char *cmd_line;
    int status;
    int need_to_print_prompt = TRUE;
    command cmd; //TODO: fix this...

    //Initialize and setup commands for the system
    initialize_commands(commands);

    while (TRUE) {
        //Print prompt and read the command line
        cmd_line = read_command_line(cmd_line);
        printf("%s\n", cmd_line);

        //Parse command line into command and arguments
        cmd = parse_command(cmd_line);
        printf("%s\n", cmd.command);

        //Fork from parent as long as command exists
        if (is_valid(cmd)) {
            child_pid = fork();

            if (child_pid == 0) {
                execute_command(cmd);
            } else if (child_pid > 0) {
                waitpid(child_pid, &status, 0); //wait on the forked child...
            } else {
                //something went wrong with forking
                error_message();
            }
        } else {
            if (strlen(cmd_line) > 0) {
                printf("-bash: %s: command not found\n", cmd_line);
            }
        }
    }
    return EXIT_SUCCESS;
}

/*
 * Method to check if a command is valid
 */
int is_valid(command cmd) {
    /*
    for(int i=0; i<NUM_COMMANDS; i++) {
        if(strcmp(commands[i].command, cmd.command) == 0) {
            return TRUE;
        }
    }
     */
    return TRUE;
}

int execute_command(command cmd) {
//    printf("command: %s, %d\n", cmd.command, strcmp(cmd.command, "exit\0")==0);
//    if(strcmp(cmd.command, "exit")==0) {
//        exit(EXIT_SUCCESS);
//    }
    if(TRUE) {
        exit(EXIT_SUCCESS);
    }

    //Return NULL on error
    else {
        return 0; //Return Null
    }
}

command parse_command(char* line) {
    printf("%d \n", strcmp(line, "exit")==0);
    if(strcmp(line, "exit")==0) {
        return commands[0];
    }

    //TODO: Return something like NULL if command is not recognized
    //return NULL;
    return commands[0]; //TODO: fix this!
}

char* read_command_line(char* prompt) {
    return readline("Shells by the Seashore$ "); //TODO: free when done!
}

/*
 * Method to initialize commands
 */
void initialize_commands(command* commands) {
    //Existing system. commands
    commands[0].command = "exit";
    commands[0].arguments[0] = 0;
}

/*
 * Error method
 */
void error_message() {
    printf("I am sorry, but there has been an error. Exiting now.\n");
    exit(EXIT_FAILURE);
}



