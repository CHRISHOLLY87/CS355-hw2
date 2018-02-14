//
// Created by Sarah Depew on 2/13/18.
//

#ifndef HW2_MYSH_H
#define HW2_MYSH_H

#ifndef _REENTRANT
#define _REENTRANT
//Macros
#define TRUE 1
#define FALSE 0
#define NUM_COMMANDS 1
#define MAX_BUFFER 4096

//Variable if we have a signal upon which we want to exit or not
int EXIT = FALSE;

//Struct for the command string and the argument values passed
typedef struct command
{
    char* command;
    char** arguments;
} command;

/*
 * Signal Handler that handles ctrl-C and ctrl-Z
 */
void sig_handler(int value);

/*
 * Method for reading the command line input from the user prompt line. Return TRUE on success and FALSE on failure.
 * Took parts of method, below, from website: https://brennan.io/2015/01/16/write-a-shell-in-c/. I also modified it to use methods I had written.
 */
int read_command_line(char**); //took method from website https://brennan.io/2015/01/16/write-a-shell-in-c/

/*
 * Method to parse input shell command. Returns TRUE upon success and FALSE upon error.
 * Used some copy and paste from method, below. (did look at https://brennan.io/2015/01/16/write-a-shell-in-c/)
 * Looked at https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm for help understanding the functionality of strtok()
 */
int parse_command_line(char*** parsed_words, char* line);

/*
 * Method to take words from command line and return TRUE/FALSE on success/failure
 */
void parse_command(command* parsed_command, char** words);

/*
 * Method to execute a command using standard path search; returns if success or not
 */
int execute_command(command cmd);

/*
 * Method to execute built-in commands; the only supported command, currently, is exit. Please note that all memory is freed before exiting.
 * Talked with classmates in TA session
 */
int execute_built_in_command(command* command);

/*
 * Method to compare the command portion of the struct and see if they are equal; mainly used for built-in commands to know what to do
 */
int command_equals(command command1, command command2);

/*
 * Method to check if a command is built-in or not
 */
int is_built_in(command cmd);

/*
 * Method to initialize built-in commands
 */
void initialize_built_in_commands();

/*
 * Method to free memory used in the program
 */
void free_memory(char** cmd_line, char*** cmd_words, command** cmd);

/*
 * Error method
 */
void error_message();

#endif //HW2_MYSH_H
#endif
