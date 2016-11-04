#include "matmult.h"

/*
 * struct for the multithreaded multiply_matrices_part() function
 */
struct mult_mat_struct
{
  struct mat a, b, c;
  size_t first_row, last_row;
};

/*
 * multiplies some rows of matrix a with the matrix b
 * if first row is bigger than last row, first row is out of bound, last row is out of bound or the matrix sizes don't match, nothing is done
 * note: the last row is not included in the calculation
 * @param pointer to mat_mult_struct with matrices and
 * @return nothing
 */
void* multiply_matrices_part(void* p)
{
  size_t x, y, i;
  size_t index = 0;
  struct mult_mat_struct* s = (struct mult_mat_struct*)p;
  //exit if the argument was a null pointer
  //exit if the matrix sizes don't match
  if(s->a.n != s->c.n || s->b.n != s->c.n)
    return NULL;
  //exit if first_row or last_row are out of bound
  if(s->first_row >= s->c.n || s->last_row > s->c.n)
    return NULL;
  //multiply part of the matrix
  for(y = s->first_row; y < s->last_row; ++y)
    {
      for(x = 0; x < s->c.n; ++x)
	{
	  //scalar product
	  index = y * s->c.n + x;
	  s->c.data[index] = 0;
	  for(i = 0; i < s->c.n; ++i)
	    {
	      s->c.data[index] += s->a.data[y * s->c.n + i] * s->b.data[i * s->c.n + x];
	    }
	}
    }
  return NULL;
}

/*
 * see header file
 */
void multiply_matrices(struct mat c, struct mat a, struct mat b)
{
  #ifdef NO_OPENMP
  long int num_cores = get_num_cpus();
  int use_single_core = 1;
  size_t rows;
  unsigned int i;
  pthread_t* threads;
  struct mult_mat_struct* args;
  if(num_cores > 1)
    {
      if((size_t)num_cores > c.n)
	{
	  //use fewer cores to match the matrix sizes
	  num_cores = c.n;
	}
      threads = (pthread_t*)malloc(sizeof(pthread_t) * num_cores);
      args = (struct mult_mat_struct*)malloc(sizeof(struct mult_mat_struct) * num_cores);
      //start threads
      if(threads != NULL && args != NULL)
	{
	  use_single_core = 0;
	  for(i = 0; i < num_cores; ++i)
	    {
	      rows = c.n / num_cores;
	      args[i].a = a;
	      args[i].b = b;
	      args[i].c = c;
	      args[i].first_row = i * rows;
	      args[i].last_row = args[i].first_row + rows;
	      if(i == (num_cores - 1))
		{
		  //avoid leaving out the last lines because of inaccuracy
		  args[i].last_row = c.n;
		}
	      if(pthread_create(&threads[i], NULL, multiply_matrices_part, &args[i]) != 0)
		{
		  use_single_core = 1;
		  break;
		}
	    }
	  //join threads
	  for(i = 0; i < num_cores; ++i)
	    {
	      if(pthread_join(threads[i], NULL) != 0)
		{
		  //NOTE: do not break here to allow other threads to finish!
		  use_single_core = 1;
		}
	    }
	}
    }
  //use only 1 cpu if there are not more available or something failed
  if(use_single_core == 1)
    {
      struct mult_mat_struct s;
      s.a = a;
      s.b = b;
      s.c = c;
      s.first_row = 0;
      s.last_row = c.n;
      multiply_matrices_part(&s);
    }
  #else
  size_t x, y, i, index;
  //exit if the matrix sizes don't match
  if(a.n != c.n || b.n != c.n)
    return;
  #pragma omp parallel for
  for(y = 0; y < c.n; ++y)
    {
      for(x = 0; x < c.n; ++x)
        {
          //scalar product
          index = y * c.n + x;
          c.data[index] = 0;
          for(i = 0; i < c.n; ++i)
            {
              c.data[index] += a.data[y * c.n + i] * b.data[i * c.n + x];
	    }
        }
    }
  #endif
}
