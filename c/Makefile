CC=gcc
OFLAGS=-O3 -march=native
OPENMP=-fopenmp
NO_OPENMP=-pthread -D NO_OPENMP
CFLAGS=-Wall -Wextra $(OFLAGS)
TARGET=matmult
DEP=$(TARGET).c common.c multiply_matrices.c

all: $(TARGET)
$(TARGET): $(DEP)
	$(CC) -o $(TARGET) $(DEP) $(CFLAGS) $(OPENMP)

.PHONY: clean all no_openmp

no_openmp:
	$(CC) -o $(TARGET) $(DEP) $(CFLAGS) $(NO_OPENMP)

clean:
	rm -f $(TARGET) *.o *~
