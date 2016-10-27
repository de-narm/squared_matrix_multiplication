#ifndef _MATMULT_H_
#define _MATMULT_H_

#include <getopt.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/*
 * defines the maximal size of matrices to execute only using one core
 * NOTE: this has to be at least 4
 */
#define SINGLE_THREADED_UPPER_LIMIT 4

/*
 * struct for matrices
 */
struct mat
{
  size_t n;
  double* data;
};

/*
 * writes a matrix to a file
 * @param path (use 'NULL' for standard out)
 * @param matrix
 * @return EXIT_FAILURE on error, EXIT_SUCCCESS otherwise
 */
int write_matrix(const char* path, struct mat m);

/*
 * prints the help
 */
void print_help(void);

/*
 * checks the command line options or help, size and file options
 * @param argc
 * @param argv
 * @param help (int* for reference)
 * @param size (size_t* for reference)
 * @param path (char** for reference)
 * @return EXIT_FAILURE on error, EXIT_SUCCESS otherwise
 */
int get_cmd_args(int argc, char* argv[], int* help, size_t* size, char** path);

/*
 * multiplies matrices (c = a x b)
 * note: if matrix sizes don't match, nothing is done
 * @param c
 * @param a
 * @param b
 */
void multiply_matrices(struct mat c, struct mat a, struct mat b);

/*
 * get number of cores
 * @return number of cores
 */
long int get_num_cpus();

#endif //_MATMULT_H_
