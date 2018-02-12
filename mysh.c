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
#include <zconf.h>
#include <memory.h>

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
    char** arguments;
} command;

//Method declarations
char *read_command_line(void); //took method from website https://brennan.io/2015/01/16/write-a-shell-in-c/
char** parse_command_line(char* line);
command* parse_command(char** words);
int execute_command(command cmd);
int execute_built_in_command(command* command);
int command_equals(command command1, command command2);
int is_built_in(command cmd);
void initialize_built_in_commands();
void free_memory(char* cmd_line, char** cmd_words, command* cmd);
void error_message();

//Global variables and arrays
command built_in_commands[NUM_COMMANDS];

/*
 * Method main()
 * Referenced pseudocode layout on https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html
 */
int main(int argc, char** argv) {
    pid_t pid;
    char *cmd_line;
    int status;
    command *cmd; //TODO: fix this...
    char **cmd_words;

    //Initialize and setup commands for the system
    initialize_built_in_commands();

    while (TRUE) {
        //Print prompt and read the command line
        printf("Shell>> ");
        cmd_line = read_command_line();

        //Parse command line into command and arguments
        cmd_words = parse_command_line(cmd_line);
        cmd = parse_command(cmd_words);
        printf("%s\n", cmd->command);

        //Fork from parent as long as command exists
        if (cmd->command != NULL) {
            printf("Is built in?: %d\n", is_built_in(*cmd));
            if (!is_built_in(*cmd)) {
                pid = fork(); //TODO: check error checked

                if (pid == 0) {
                    execute_command(*cmd);
                } else if (pid > 0) {
                    waitpid(pid, &status, 0); //wait on the forked child...
                } else {
                    //something went wrong with forking
                    error_message();
                }

                free_memory(cmd_line, cmd_words, cmd);
            } else {
                printf("Command is built in...\n");
                int return_val = execute_built_in_command(cmd);

                free_memory(cmd_line, cmd_words, cmd);

                //want to exit ONLY after freeing all memory
                if (return_val == TRUE) {
                    break;
                }
            }

            free_memory(cmd_line, cmd_words, cmd);
        }
    }
    return EXIT_SUCCESS;
}

/*
 * Method to free all memory used in program
 */
void free_memory(char* cmd_line, char** cmd_words, command* cmd) {
    if (cmd_line != NULL) {
        free(cmd_line);
        cmd_line = NULL;
    }

    if (cmd_words != NULL) {
        free(cmd_words);
        cmd_words = NULL;
    }

    if (cmd != NULL) {
        free(cmd);
        cmd = NULL;
    }
}

/*
 * Method to execute built-in commands; the only supported command, currently, is exit. Please note that all memory is freed before exiting.
 * Talked with classmates in TA session
 */
int execute_built_in_command(command* command) {
    if (command_equals(built_in_commands[0], *command)) {
        return TRUE; //want to exit and break the while loop
    }
    return FALSE;
}

/*
 * Method to check if a command is built-in or not
 */
int is_built_in(command cmd) {
    for(int i=0; i<NUM_COMMANDS; i++) {
        if(command_equals(cmd, built_in_commands[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

/*
 * Method to execute a command using standard path search
 */
int execute_command(command cmd) {
    if (execvp(cmd.command, cmd.arguments) == -1) {
        printf("-bash: %s: command not found\n", cmd.command);
    }
    return 0;
}

/*
 * Method to parse input shell command
 * Used some copy and paste from method, below. (did look at https://brennan.io/2015/01/16/write-a-shell-in-c/)
 * Looked at https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm for help understanding the functionality of strtok()
 */ //TODO: prevent memory leaks here! also make sure to terminate arguments array with null, so that it can be processed by execvp if it is destined to go there...
char** parse_command_line(char* line) {
    int bufsize = MAX_BUFFER;
    int position = 0;
    char** tokens = malloc(sizeof(char*) * bufsize);
    const char s[2] = " "; //want to separate using spaces or other deliminators
    char* current_token;

    if (!tokens) {
        error_message();
    }

    current_token = strtok(line, s);
    while(current_token!=NULL) {
            tokens[position] = current_token;
            position++;


        // If we have exceeded the buffer, reallocate. (copied and pasted from, below...)
        if (position >= bufsize) {
            bufsize += MAX_BUFFER;
            tokens = realloc(tokens, bufsize);
            if (!tokens) {
                error_message();
            }
        }

        current_token = strtok(NULL, s);
    }

    //NULL terminate the buffer
    tokens[position] = NULL;

    //Return the words
    return tokens;
}

/*
 * Method to take words from command line and
 */
command* parse_command(char** words) {
    command* return_value = malloc(sizeof(command));
    return_value->command = words[0];
    return_value->arguments = words; //TODO: make sure this is null terminated like required for execvp!
    return return_value;
}

/*
 * Method for reading the command line input from the user prompt line.
 * Took parts of method, below, from website: https://brennan.io/2015/01/16/write-a-shell-in-c/. I also modified it to use methods I had.
 */
char* read_command_line(void) {
    int bufsize = MAX_BUFFER;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        error_message();
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
                error_message();
            }
        }
    }
}

 /*
  * Method to initialize built-in commands
  */
void initialize_built_in_commands() {
     built_in_commands[0].command = "exit";
     built_in_commands[0].arguments = NULL;
 }

/*
 * Method to compare the command portion of the struct and see if they are equal; mainly used for built-in commands to know what to do
 */
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