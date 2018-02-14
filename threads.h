//
// Created by Sarah Depew on 2/13/18.
//

#ifndef HW2_THREADS_H
#define HW2_THREADS_H

#ifndef _REENTRANT
#define _REENTRANT

#define N 3

//struct (to pass more than one parameter into thread method)
typedef struct put_parameters
{
    int row;
    int column;
} put_parameters;

/*
 * Method for inserting array values in unique way
 */
void* put_value(void * parameters);

/*
 * Method to multiply AxB and put the entries into C
 */
void* matrix_multiplication(void* parameters);

/*
 * Method to figure out what the maximum row sum is for the matrix in question
 */
void* row_computation(void* row);

/*
 * Method to print out values in an array
 */
void print_array(long array[N][N]);

/*
 * Error method
 */
void error_message();

#endif //HW2_THREADS_H
#endif

