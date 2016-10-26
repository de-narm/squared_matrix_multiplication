F90=gfortran
PYTHON=python

TARGET=matmul
SOURCE=$(TARGET).f90
N=50

all: matrix $(TARGET)

%: %.f90
	$(F90) $(FFLAGS) -o $@ $<

matrix: matrix.csv

matrix.csv:
	$(PYTHON) genmatrix.py $(N) >$@

clean:
	rm -f matmul matrix.mod matrix.csv

.PHONY: clean all matrix matrix.csv
