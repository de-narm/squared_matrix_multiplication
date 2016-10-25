#include "matmult.h"

/*
 * opens the output file
 * @param path (use 'NULL' for standard out)
 * @return file descriptor or -1 on error
 */
int open_output_file(const char* path)
{
  //NULL: return standard out
  if(path == NULL)
    return 0;
  //otherwise: open path
  return open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}

/*
 * writes a 0-terminated string to a file
 * @param file descriptor
 * @param data
 * @return number of wrote bytes
 */
int write_output_file(int fd, const char* data)
{
  return write(fd, data, strlen(data));
}

/*
 * closes the output file
 * @param file descriptor
 * @return -1 on error, 0 otherwise
 */
int close_output_file(int fd)
{
  //0: leave standard out open
  if(fd == 0)
    return 0;
  //otherwise: close file
  return close(fd);
}

/*
 * handles the complete open - write - close routine to write 'data' to 'path'
 * @param path (use 'NULL' for standard out)
 * @param data
 * return EXIT_FAILURE on error, EXIT_SUCCESS otherwise
 */
int output_to_file(const char* path, const char* data)
{
  int err = 0;
  int fd = open_output_file(path);
  unsigned int read_bytes = 0;
  if(fd < 0)
    {
      printf("ERROR: opening output file \"%s\" failed!\n", ((path == NULL) ? "0" : path));      
      return EXIT_FAILURE;
    }
  read_bytes = write_output_file(fd, data);
  if(read_bytes < strlen(data))
    {
      printf("ERROR: writing to output file \"%s\" failed!\n", ((path == NULL) ? "0" : path));
      return EXIT_FAILURE;
    }
  err = close_output_file(fd);
  if(err < 0)
    {
      printf("ERROR: closing output file \"%s\" failed!\n", ((path == NULL) ? "0" : path));
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

/*
 * see header file
 */
int write_matrix(const char* path, struct mat m)
{
  size_t s = (m.n * m.n) * 7;
  char* data = (char*)malloc(sizeof(char) * (s + 1));
  size_t x, y;
  unsigned int index = 0;
  for(y = 0; y < m.n; ++y)
    {
      for(x = 0; x < m.n; ++x)
	{
	  int err = snprintf(&data[index], 8, "%1.4f%c", m.data[y * m.n + x], ((x == m.n - 1) ? '\n' : '\t'));
	  if(err < 0)
	    {
	      return EXIT_FAILURE;
	    }
	  index += 7;
	}
    }
  return output_to_file(path, data);
}

/*
 * see header file
 */
void print_help(void)
{
  printf("usage:\n");
  printf("matmult [-f | --file <path>] [-h | --help] [-s | --size <size>]\n");
  printf("\t-f, --file\tpath to output file (leave blank for standard out)\n");
  printf("\t-h, --help\tdisplays this message\n");
  printf("\t-s, --size\tnumber of columns and rows\n");
}


/*
 * see header file
 */
int get_cmd_args(int argc, char* argv[], int* help, size_t* size, char** path)
{
  //handle invalid argument
  if(help == NULL || size == NULL || path == NULL)
    {
      return EXIT_FAILURE;
    }
  if(argc == 1)
    {
      *help = 1;
      return EXIT_SUCCESS;
    }
  if(argc >= 2)
    {
      int c = 0;
      int has_args = 0;
      struct option options[3];
      //help
      options[0].name = "help";
      options[0].has_arg = no_argument;
      options[0].flag = NULL;
      options[0].val = 'h';
      //size
      options[1].name = "size";
      options[1].has_arg = required_argument;
      options[1].flag = NULL;
      options[1].val = 's';
      //file
      options[2].name = "file";
      options[2].has_arg = required_argument;
      options[2].flag = NULL;
      options[2].val = 'f';
      //get arguments
      while(c != -1)
	{
	  c = getopt_long(argc, argv, "hs:f:", options, NULL);
	  switch(c)
	    {
	    case 'h':
	      *help = 1;
	      has_args = 1;
	      break;
	    case 's':
	      *size = atoi(optarg);
	      has_args = 1;
	      break;
	    case 'f':
	      *path = optarg;
	      has_args = 1;
	      break;
	    default:
	      break;
	    };
	}
      if(argc == 2 && has_args == 0)
	{
	  *size = atoi(argv[1]);
	}
    }  
  return EXIT_SUCCESS;
}

/*
 * see header file
 */
long int get_num_cpus()
{
  return sysconf(_SC_NPROCESSORS_ONLN);
}
