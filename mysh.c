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
* //TODO: figure out how to do this...
 * Note that your shell should be able to perform standard path search according to the search path defined by the PATH
 * environment variable. Hint: remember execvp. //TODO: figure out how to path searching in shell..
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
#define MAX_BUFFER 4096
#ifndef _REENTRANT
#define _REENTRANT
#endif

//Structs
typedef struct command
{
    char* command;
    char* arguments;
} command;

//Method declarations
char *read_command_line(void); //took method from website https://brennan.io/2015/01/16/write-a-shell-in-c/
command* parse_command(char* line);
int execute_command(command cmd);
void execute_built_in_command(command* command);
int command_equals(command command1, command command2);
int is_built_in(command cmd);
void initialize_built_in_commands();
void error_message();

//Global variables and arrays
command built_in_commands[NUM_COMMANDS];

/*
 * Method main()
 */
int main(int argc, char** argv) {
    pid_t pid;
    char *cmd_line;
    int status;
    command *cmd; //TODO: fix this...
    char string[MAX_BUFFER];

    //Initialize and setup commands for the system
    initialize_built_in_commands();

    while (TRUE) {
        //Print prompt and read the command line
        printf("Shell>> ");
        cmd_line = read_command_line();

        //Parse command line into command and arguments
        cmd = parse_command(cmd_line);

        //Fork from parent as long as command exists
        if (cmd->command!=NULL && !is_built_in(*cmd)) {
            pid = fork(); //TODO: check error checked

            if (pid == 0) {
                execute_command(*cmd);
            } else if (pid > 0) {
                waitpid(pid, &status, 0); //wait on the forked child...
            } else {
                //something went wrong with forking
                error_message();
            }
            if (cmd_line != NULL) {
                free(cmd_line);
                cmd_line = NULL;
            }
        } else {
            if (cmd_line != NULL) {
                free(cmd_line);
                cmd_line = NULL;
            }
            execute_built_in_command(cmd);
        }

        if (cmd_line != NULL) {
            free(cmd_line);
            cmd_line = NULL;
        }
    }
    return EXIT_SUCCESS;
}

void execute_built_in_command(command* command) {
    if (command_equals(built_in_commands[0], *command)) {
        //TODO: free memory here
        free(command);
        exit(EXIT_SUCCESS);
    }
}

/*
 * Method to check if a command is valid
 */
int is_built_in(command cmd) {
    for(int i=0; i<NUM_COMMANDS; i++) {
        if(command_equals(cmd, built_in_commands[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

int execute_command(command cmd) {
    if (execvp(cmd.command, &(cmd.arguments)) == -1) {
        printf("-bash: %s: command not found\n", cmd.command);
    }
    return 0;
}

/*
 * Method to parse input shell command
 */ //TODO: prevent memory leak here!
command* parse_command(char* line) {
    //parse here
    //parse if there is something to parse
    command *return_command = (command *) malloc(sizeof(command));
    return_command->command = "exit";
    return_command->arguments = NULL;

    return return_command;

    //TODO: add null terminator at end
}

/*
char* read_command_line(char* prompt) {
    //return readline("Shells by the Seashore$ "); //TODO: free when done! //use fgets() not readline(), since there are a lot of leaks here
    fgets(prompt, MAX_BUFFER, stdin);
}
 */

/*
 * Took method, below, from website: https://brennan.io/2015/01/16/write-a-shell-in-c/
 */
char* read_command_line(void)
{
    int bufsize = MAX_BUFFER;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += MAX_BUFFER;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


 /*
  * Method to initialize commands
  */
void initialize_built_in_commands() {
     built_in_commands[0].command = "exit";
     built_in_commands[0].arguments = NULL;
 }

int command_equals(command command1, command command2) {
    int compare_value = strcmp(command1.command, command2.command);
    if (compare_value == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
 * Error method
 */
void error_message() {
    printf("I am sorry, but there has been an error. Exiting now.\n");
    exit(EXIT_FAILURE);
}