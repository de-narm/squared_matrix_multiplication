#Fortran Version

`gcc-fortran` and `python` need to be installed.

##Build application

`make`

##Generate random matrix

`make matrix N=<size>`

##Run
`./matmul` will read `matrix.csv` and print the result out. The runtime is
printed to stderr. To get only the runtime use `./matmul >/dev/null`.
