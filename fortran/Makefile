F90=gfortran
FFLAGS=-O3
PYTHON=python

TARGET=matmul matmul_openmp
SOURCE=$(TARGET:=.f90)
N=50

all: matrix $(TARGET)

%_openmp: %.f90
	$(F90) $(FFLAGS) -fopenmp -o $@ $<

%: %.f90
	$(F90) $(FFLAGS) -o $@ $<

matrix: matrix.csv

matrix.csv:
	$(PYTHON) genmatrix.py $(N) >$@

clean:
	rm -f $(TARGET) matrix.mod matrix.csv

.PHONY: clean all matrix matrix.csv
