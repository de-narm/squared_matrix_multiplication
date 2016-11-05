#Documentation

##General Information

This project is meant compare the speed of different implementations of matrix multiplications (double precission).

All versions in the 4 programming languages (FORTRAN, C (with OpenMP and pthread; selected via compiler flag), Java and Haskell) are multithreaded. The Java version additionally benchmarks the single core performance for reference. Haskell is more or less just a proof of concept and is not really comparable to the other languages.

##Algorithm

![Algorithm](/Diagramm/Nassi-Shneidermann-Diagramm.png)

##Benchmarking system

All implementations were benchmarked on an Intel Core i5 6200U. 

CPU-features:
 * 2 Cores (with 2 Threads each)
 * 2.3 GHz base frequency
 * 2 FPU operations per clock
 * AVX 2 (256 Bit)
 * Fused Multiply Add
 
The resulting theoretical Floating Point Peak Performance (FPPP) is calculated as follows:

```2 Cores * 2.3 GHz * 2 FPU operations / clock * (256 Bit AVX / 64 Bit Double Precision) * 2 = 73.6 GFLOPS```

##Benchmarks

For detailed performance graphs please see [benchmarks/README.md](/benchmarks/README.md).

A performance table is also available at [benchmarks/benchmarks.csv](benchmarks/benchmarks.csv).

##Contributers

FORTRAN: Aaron Bulmahn (arbu) <br>
C: Jonas Schenke (kloppstock) <br>
Java: Matthias Nickel (matzeni07) <br>
Haskell: Sebastian Benner (De-Narm)
