#include "matmult.h"

/*
TODO:
- USE RANDOM VALUES FOR THE MATRIX VALUES!
 */

/*
 * creates matrices, initialises them, multiplies them and write the result to a file
 * command line arguments:
 *   -s or --size for the number of columns and rows (has to be greater than 0)
 *   -f or --file for the output file (leave blank for standard out)
 *   additional ./main <size> is also possibly (standard out used for output) 
 */
int main (int argc, char* argv[])
{
  //declare variables
  size_t n = 0;
  char* path = NULL;
  struct mat m[3];
  int i = 0;
  int err = 0;
  struct timespec begin = {0, 0};
  struct timespec  end = {0, 0};
  double time_taken = 0.0;
  int help = 0;

  srand(time(NULL));
  
  //handle command line arguments
  err = get_cmd_args(argc, argv, &help, &n, &path);
  if(err != EXIT_SUCCESS)
    {
      printf("ERROR: couldn't get command line arguments!\n");
      return EXIT_FAILURE;
    }
  if(help == 1)
    {
      print_help();
      return EXIT_SUCCESS;
    }
  if(n == 0)
    {
      printf("ERROR: invalid size!\n");
      return EXIT_FAILURE;
    }
  //allocating resources
  for(i = 0; i < 3; ++i)
    {
      m[i].n = n;
      m[i].data = (double*)malloc(sizeof(double) * n * n);
      if(m[i].data == NULL)
	{
	  printf("ERROR: memory allocation matrix %d failed!\n", i);
	  int j;
	  for(j = 0; j < i; ++j)
	    {
	      free(m[j].data);
	    }
	  return EXIT_FAILURE;
	}
    }
  //initialise resources
  for(i = 0; i < 2; ++i)
    {
      size_t x, y;
      for(x = 0; x < n; ++x)
	{
	  for(y = 0; y < n; ++y)
	    {
              //TODO: use random numbers here
	      m[i].data[y * n + x] = 1.0 / (double)(y * n + x + 1);
	    }
	}
    }  
  //do the main task and measure the time
  err = clock_gettime(CLOCK_REALTIME, &begin);
  if(err == -1)
    {
      printf("ERROR: couldn't get time!\n");
      for(i = 0; i < 3; ++i)
	{
	  free(m[i].data);
	}
      return EXIT_FAILURE;
    }
  multiply_matrices(m[2], m[0], m[1]);
  err = clock_gettime(CLOCK_REALTIME, &end);
  if(err == -1)
    {
      printf("ERROR: couldn't get time!\n");
      for(i = 0; i < 3; ++i)
	{
	  free(m[i].data);
	}
    }
  err = write_matrix(path, m[2]);
  //free resources
  for(i = 0; i < 3; ++i)
    {
      free(m[i].data);
    }
  if(err < 0)
    {
      printf("ERROR: couldn't save matrix!\n");
      return EXIT_FAILURE;
    }
  time_taken = (double)(end.tv_sec - begin.tv_sec) * 1000.0 * 1000.0 + (double)(end.tv_nsec - begin.tv_nsec) / 1000.0;
  err = printf("Time taken: %f µs\n", time_taken);
  if(err < 0)
    {
      printf("ERROR: couldn't display result!\n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
