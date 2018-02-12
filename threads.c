/*
* 1. Threads
* (a) Create two matrices A and B of size N × N where N is a #defined constant. Create N × N threads each of which
* writes a random positive integer into a distinct location in matrix A (i.e. no two threads write into the same
* location in A) and another random positive integer into the same location in matrix B. //TODO: make sure approach here is correct...do I want global matrices?
* (b) Print out the two matrices A and B.
* (c) Now create N × N threads each of which computes a distinct element of the matrix C = A × B. //TODO: clarify what this means...
* (d) Print out matrix C. //TODO: check up to this point...
* (e) Now compute the sum of elements in each row of C, and find the maximum of all row- sums. First initialize a
* single variable MAX ROW SUM = 0, this is the variable that should hold the maximum of the row-sums at the end of
* this step. Create N threads each of which computes the sum of a distinct row in C, and update MAX ROW SUM if necessary.
* To make things a bit more interesting, after reading but before updating MAX ROW SUM, let each thread sleep some
* random amount of time (few seconds).
* (f) Print the maximum row-sum.
* Note: Do NOT use any intermediate variables to store individual row-sums.
* (g) I hope that by now you clearly see that we were intentionally generating a race condition in (e). Using POSIX
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

#define N 3

//matrices
int A[N][N];
int B[N][N];
int C[N][N];

//variables
int MAX_ROW_SUM = 0;
pthread_mutex_t lock;

//methods
void* put_value(void * parameters);
void* matrix_multiplication(void* parameters);
void* row_computation(void* row);
void print_array(int array[N][N]);
void error_message();

//structs (to pass more than one parameter into thread method)
typedef struct put_parameters
{
    int row;
    int column;
} put_parameters;

/*
 * Method main for the program. Also where threads are created and joined.
 */
int main() {
    //arrays
    pthread_t threads[N][N];
    pthread_t multiplication_threads[N][N];
    pthread_t row_threads[N];
    put_parameters parameters[N][N];
    put_parameters multiplication_parameters[N][N];

    //TODO: add error checking
    //mutex
    if(pthread_mutex_init(&lock, NULL) != 0) {
        error_message();
    }

    //create threads for matrix value generation
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            parameters[i][j].row = i;
            parameters[i][j].column = j;

            //error handling
            if (pthread_create(&threads[i][j], NULL, put_value, &parameters[i][j]) != 0) {
                error_message();
            }
            if (pthread_join(threads[i][j], NULL) != 0) {
                error_message();
            }
        }
    }

    //threads for multiplying A and B together to get C
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            multiplication_parameters[i][j].row = i;
            multiplication_parameters[i][j].column = j;

            //error handling
            if (pthread_create(&multiplication_threads[i][j], NULL, matrix_multiplication,
                               &multiplication_parameters[i][j]) != 0) {
                error_message();
            }
            if (pthread_join(threads[i][j], NULL) != 0) {
                error_message();
            }
        }
    }

    //threads for getting the max sum of the rows in C
    for (int i = 0; i < N; i++) {
        void* row = (void*) (size_t) i;

        //error handling
        if(pthread_create(&row_threads[i], NULL, row_computation, row) !=0) {
            error_message();
        }
        if(pthread_join(row_threads[i], NULL)!=0){
            error_message();
        }
    }

    //Print messages
    printf("Matrix A:\n");
    print_array(A);
    printf("Matrix B:\n");
    print_array(B);
    printf("Matrix C:\n");
    print_array(C);
    printf("Max row sum: %d.\n", MAX_ROW_SUM);

    //Done with mutex now, so destroy it
    if(pthread_mutex_destroy(&lock)!=0) {
        error_message();
    }

    //Everything turned out well
    return EXIT_SUCCESS;
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

    int random_value_A = rand_r(&(secs)) % 5; //TODO: remove the mod
    A[row][column] = random_value_A;

    gettimeofday(&now, NULL);
    secs = now.tv_usec;

    int random_value_B = rand_r(&(secs)) % 5;
    B[row][column] = random_value_B;

    return NULL;
}

/*
 * Method to multiply AxB and put the entries into C
 */
//TODO: make sure method is acceptable (race conditions could occur?)
void* matrix_multiplication(void* parameters) {
    put_parameters *row_and_column = parameters;
    int row = row_and_column->row;
    int column = row_and_column->column;

    for (int i = 0; i < N; i++) {
        C[row][column] += (A[row][i] * B[i][column]);
    }

    return NULL;
}

//TODO: resolve race condition (goal was to generate race condition) (check with TA's that I have resolved the race condition)
/*
 * Method to figure out what the maximum row sum is for the matrix in question
 */
 void* row_computation(void* row) {
    int sum = 0; //single row value/variable
    int row_to_add = (int) row; //cast the passed in void parameter
    for (int i = 0; i < N; i++) {
        sum += C[row_to_add][i];
    }

    //replace max row sum's value if needed...
    //critical region, since MAX_ROW_SUM is on the heap and is global to the function as a whole
    if (pthread_mutex_lock(&lock) != 0) {
        error_message();
    }

    if (MAX_ROW_SUM < sum) {
        MAX_ROW_SUM = sum;
    }

    if (pthread_mutex_unlock(&lock) != 0) {
        error_message();
    }
    printf("row sum: %d\n", sum);

    return NULL;
}

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

/*
 * Error method
 */
void error_message() {
    printf("I am sorry, but there has been an error. Exiting now.");
    exit(EXIT_FAILURE);
}

