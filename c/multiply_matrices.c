#include "matmult.h"

/*
 * see header file
 */
void multiply_matrices(struct mat c, struct mat a, struct mat b)
{
  size_t x, y, i;
  size_t index = 0;
  for(y = 0; y < c.n; ++y)
    {
      for(x = 0; x < c.n; ++x)
	{
	  index = y * c.n + x;
	  c.data[index] = 0;
	  for(i = 0; i < c.n; ++i)
	    {
	      c.data[index] += a.data[y * c.n + i] * b.data[i * c.n + x];
	    }
	}
    }
}
