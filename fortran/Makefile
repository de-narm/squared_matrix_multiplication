F90=gfortran
FFLAGS=-O3

TARGET=matmul matmul_openmp
SOURCE=$(TARGET:=.f90)

all: $(TARGET)

%_openmp: %.f90
	$(F90) $(FFLAGS) -fopenmp -o $@ $<

%: %.f90
	$(F90) $(FFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: clean all
