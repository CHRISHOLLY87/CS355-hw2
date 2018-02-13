#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <zconf.h>

//constants
#ifndef _REENTRANT
#define _REENTRANT
#endif

#define N 3

//matrices
long A[N][N];
long B[N][N];
long C[N][N];

//variables
long MAX_ROW_SUM = 0;
pthread_mutex_t lock;

//methods
void* put_value(void * parameters);
void* matrix_multiplication(void* parameters);
void* row_computation(void* row);
void print_array(long array[N][N]);
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
    int rows[N]; 

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

    printf("Matrix A:\n");
    print_array(A);
    printf("Matrix B:\n");
    print_array(B);

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

    printf("Matrix C:\n");
    print_array(C);
    printf("Calculating max row sum... (this may take a few seconds).\n");

    //threads for getting the max sum of the rows in C
    for (int i = 0; i < N; i++) {
      rows[i] = i; 

        //error handling
        if(pthread_create(&row_threads[i], NULL, row_computation, &rows[i]) !=0) {
            error_message();
        }
        if(pthread_join(row_threads[i], NULL)!=0){
            error_message();
        }
    }

    //Print messages
    printf("Max row sum: %ld.\n", MAX_ROW_SUM);

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
void* put_value(void* parameters) {
    //variables
    struct timeval now;
    unsigned int millisecs;
    put_parameters *row_and_column = parameters;
    int row = row_and_column->row;
    int column = row_and_column->column;

    gettimeofday(&now, NULL);
    millisecs = now.tv_usec;

    int random_value_A = rand_r(&(millisecs)) % 10 ; //I chose to make random value be between 0 and 9, so that overflow did not happen
    A[row][column] = random_value_A;

    gettimeofday(&now, NULL);
    millisecs = now.tv_usec;

    int random_value_B = rand_r(&(millisecs)) % 10; //I chose to make random value be between 0 and 9, so that overflow did not happen
    B[row][column] = random_value_B;

    return NULL;
}

/*
 * Method to multiply AxB and put the entries into C
 */
void* matrix_multiplication(void* parameters) {
    put_parameters *row_and_column = parameters;
    int row = row_and_column->row;
    int column = row_and_column->column;

    for (int i = 0; i < N; i++) {
        C[row][column] += (A[row][i] * B[i][column]);
    }

    return NULL;
}

/*
 * Method to figure out what the maximum row sum is for the matrix in question
 */
 void* row_computation(void* row) {
    long sum = 0; //single row value/variable
    int row_to_add = *((int*) row); //cast the passed in void parameter
    struct timeval now;
    unsigned int millisecs;

    //random time for sleep
    gettimeofday(&now, NULL);
    millisecs = now.tv_usec;

    int random_time = rand_r(&(millisecs)) % 9 + 2; //number between 2 and 10

    for (int i = 0; i < N; i++) {
        sum += C[row_to_add][i];
    }

    //replace max row sum's value if needed...
    //critical region, since MAX_ROW_SUM is on the heap and is global to the function as a whole
    if (pthread_mutex_lock(&lock) != 0) {
        error_message();
    }

    if (MAX_ROW_SUM < sum) {
        sleep(random_time);
        MAX_ROW_SUM = sum;
    }

    if (pthread_mutex_unlock(&lock) != 0) {
        error_message();
    }

    return NULL;
}

/*
 * Method to print out values in an array
 */
void print_array(long array[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%ld\t", array[i][j]);
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

