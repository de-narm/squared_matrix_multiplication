#C Version

This is the C version of the project. 

##Build

Use `make` to build and `make clean` to remove build files.

##Usage
```
matmult [-f | --file <path>] [-h | --help] [-s | --size <size>]
	-f, --file	path to output file (leave blank for standard out)
	-h, --help	displays this message
	-s, --size	number of columns and rows
```
`matmult <number>` is also valid. It is equivalent to `matmult -s <number>` or `matmult --size <number>`.
