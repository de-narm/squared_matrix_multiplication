CC=gcc
OFLAGS=-O3 -march=native
LIBS=-pthread
CFLAGS=-Wall -Wextra $(OFLAGS)
TARGET=matmult
DEP=$(TARGET).c common.c multiply_matrices.c

$(TARGET): $(DEP)
	$(CC) -o $(TARGET) $(DEP) $(CFLAGS) $(LIBS)

.PHONY: clean benchmark

clean:
	rm -f $(TARGET) *.o *~
