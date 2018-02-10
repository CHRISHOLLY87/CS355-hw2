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
* • exit: Exits mysh and returns to whatever shell you started mysh from.
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
    int command;
    int arguments[];
} command;

//Method declarations
void print_prompt();
char *read_command_line(char *prompt);
command parse_command(char *line);
void execute_command(command cmd);
int is_valid(command cmd);
void error_message();




//Global variables and arrays
int commands[NUM_COMMANDS];



/*
 * Method main
 */

/*
 *
 * int
     main (int argc, char **argv)
     {
	while (1){
		int childPid;
		char * cmdLine;

	        printPrompt();

	        cmdLine= readCommandLine(); //or GNU readline("");

		cmd = parseCommand(cmdLine);

		record command in history list (GNU readline history ?)

		if ( isBuiltInCommand(cmd)){
		    executeBuiltInCommand(cmd);
		} else {
		     childPid = fork();
		     if (childPid == 0){
			executeCommand(cmd); //calls execvp

		     } else {
			if (isBackgroundJob(cmd)){
			        record in list of background jobs
			} else {
				waitpid (childPid);

			}
		    }
	        }
     }
 */
int main(int argc, char** argv) {
    pid_t child_pid;
    char cmd_line[MAX_BUFFER];
    command cmd; //TODO: fix this...
    int status;
    int c;
    int need_to_print_prompt = TRUE;

    while (TRUE) {
        //Print prompt
        if(need_to_print_prompt) {
            print_prompt();
            need_to_print_prompt = FALSE;
        }

        //read the command line to see if there is information to print out
        read_command_line(cmd_line);

        //Parse command line into command and arguments
        cmd = parse_command(cmd_line);

        //Fork from parent as long as command exists
        if (is_valid(cmd)) {
            child_pid = fork();

            if (child_pid == 0) {
                execute_command(cmd);
            } else if (child_pid > 0) {
                waitpid(child_pid, &status, 0);
            } else {
                //something went wrong with forking
                error_message();
            }
        }

        //if we are done waiting, print the prompt again
        if (wait(&status) != -1) {
            //print prompt again
            need_to_print_prompt = TRUE;
        }
            //an error occured
        else {
            error_message();
        }
    }

    return EXIT_SUCCESS;
}

int is_valid(command cmd) {
    return 0;
}

void execute_command(command cmd) {

}

command parse_command(char *line) {
    command cmd;
    return cmd;
}

char* read_command_line(char * prompt) {
    //fgets(prompt, MAX_BUFFER, STDIN_FILENO);
    printf("%s \n", prompt);
    return prompt;
}

void print_prompt() {
    //Print prompt using path name
    //printf("Shells by the Seashore$ ");
    char current_working_directory[MAX_BUFFER];
    if(getcwd(current_working_directory, sizeof(current_working_directory)) != NULL) {
        printf("%s$ ", current_working_directory);
        fflush(stdout);
    }
    else {
        error_message();
    }
}

/*
 * Error method
 */
void error_message() {
    printf("I am sorry, but there has been an error. Exiting now.\n");
    exit(EXIT_FAILURE);
}



