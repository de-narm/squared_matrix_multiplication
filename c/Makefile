CC=gcc
OFLAGS=-O3
#DFLAGS=-g -O0
LIBS=-pthread
CFLAGS=-Wall -Wextra $(OFLAGS)
TARGET=matmult
DEP=$(TARGET).c common.c multiply_matrices.c

$(TARGET): $(DEP)
	$(CC) -o $(TARGET) $(DEP) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET) *.o *~
