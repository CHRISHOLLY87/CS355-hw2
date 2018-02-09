/*
* 1. Threads
* (a) Create two matrices A and B of size N × N where N is a #defined constant. Create N × N threads each of which
* writes a random positive integer into a distinct location in matrix A (i.e. no two threads write into the same
* location in A) and another random positive integer into the same location in matrix B. //TODO: make sure approach here is correct...do I want global matrices?
* (b) Print out the two matrices A and B.
* (c) Now create N × N threads each of which computes a distinct element of the matrix C = A × B. //TODO: clarify what this means...
* (d) Print out matrix C.
* (e) Now compute the sum of elements in each row of C, and find the maximum of all row- sums. First initialize a
* single variable MAX ROW SUM = 0, this is the variable that should hold the maximum of the row-sums at the end of
* this step. Create N threads each of which computes the sum of a distinct row in C, and update MAX ROW SUM if necessary.
* To make things a bit more interesting, after reading but before updating MAX ROW SUM, let each thread sleep some
* random amount of time (few seconds).
* (f) Print the maximum row-sum.
* Note: Do NOT use any intermediate variables to store individual row-sums.
* (g) I hope that by now you clearly see that we were intentionally generating a race condi- tion in (e). Using POSIX
* thread mutexes, add code to resolve the race condition (consult manual pages on pthread mutex *, i.e. pthread mutex
* init(), pthread mutex lock(), etc.
*/

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

//constants
#ifndef _REENTRANT
#define _REENTRANT
#endif

#define N 2

//matrices
int A[N][N];
int B[N][N];
int C[N][N];

//methods
void* put_value(void * parameters);
void print_array(int array[N][N]);

//structs (to pass more than one parameter into thread method)
typedef struct put_parameters
{
    int row;
    int column;
} put_parameters;


int main() {
    //arrays
    pthread_t threads[N][N];
    pthread_t multiplication_threads[N][N];
    put_parameters parameters[N][N];

    //create threads for matrix value generation //TODO: add error handling! //TODO: Ask about joining and creating at one? or not at all?
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            parameters[i][j].row = i;
            parameters[i][j].column = j;
            pthread_create(&threads[i][j], NULL, put_value, &parameters[i][j]);
            pthread_join(threads[i][j], NULL);
        }
    }

    //threads for multiplying A and B together to get C
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

        }
    }

    printf("Matrix A:\n");
    print_array(A);
    printf("Matrix B:\n");
    print_array(B);
    printf("Matrix C:\n");
    print_array(C);

    return 0;
}

/*
 * Method for inserting array values in unique way
 */
//TODO: make sure method is acceptable
void* put_value(void* parameters) {
    //variables
    struct timeval now;
    unsigned int secs;
    put_parameters *row_and_column = parameters;
    int row = row_and_column->row;
    int column = row_and_column->column;

    gettimeofday(&now, NULL);
    secs = now.tv_usec;

    int random_value_A = rand_r(&(secs))%100; //TODO: remove the mod
    A[row][column] = random_value_A;

    gettimeofday(&now, NULL);
    secs = now.tv_usec;

    int random_value_B = rand_r(&(secs))%100;
    B[row][column] = random_value_B;

    //(void * return); //what do I do with this? //TODO: what/how do you return from a thread method?
}

/*
 * Method to multiply AxB and put the entries into C
 */
void* matrix_multiplication(void* parameters) {

}

/*
// multiplies an N1xM1 matrix by a M1xM2 matrix, storing the result in `result`
void matrix_mult(int n1, int m1, int mat1[n1][m1], int m2, int mat2[m1][m2], int result[n1][m2]) {

    //value to hold the result of the matrix multiplication and the value that is inserted into the result matrix
    int result_multi = 0;

    //tripple nested for loop that does the multiplication
    for (int i = 0; i < m2; i++) {
        for (int j = 0; j < n1; j++) {
            for (int k = 0; k < m1; k++) {
                //result accumulates in result
                result_multi += (mat1[j][k] * mat2[k][i]);
            }

            //assigns the result to the proper location in the result matrix
            result[j][i] = result_multi;

            //resets the result value each time
            result_multi = 0;
        }
    }
}
 */

/*
 * Method to print out values in an array
 */
void print_array(int array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

