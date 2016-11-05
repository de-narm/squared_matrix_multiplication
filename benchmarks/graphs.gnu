set terminal pngcairo enhanced font "arial,10" fontscale 1.0 size 800, 600
set key left box
set xlabel "height/width of matrices"
set ylabel "time in milliseconds"
set grid ytics lc rgb "#999999" lw 1 lt 0
set grid xtics lc rgb "#999999" lw 1 lt 0

# C
set title "Matrix multiplication in C"
set output "benchmark-c.png"
set datafile separator ","
plot "c_µs.csv" using 1:($2/1000) title " C (OpenMP)" with linespoint

# Fortran
set title "Matrix multiplication in Fortran"
set output "benchmark-fortran.png"
set datafile separator ","
plot "fortran_sec.csv" using 1:($2*1000) title "Fortran" with linespoint

# Haskell
set title "Matrix multiplication in Haskell"
set output "benchmark-haskell.png"
set datafile separator ","
plot "haskell_sec.csv" using 1:($2*1000) title "Haskell" with linespoint

# Java
set title "Matrix multiplication in Java"
set output "benchmark-java.png"
set datafile separator ";"
plot "java.csv" using 1:2 title "sequential" with lines, \
     "java.csv" using 1:3 title "2 threads" with lines, \
     "java.csv" using 1:4 title "3 threads" with lines, \
     "java.csv" using 1:5 title "4 threads" with lines, \

# C, Fortran and Java
set title "Matrix multiplication in C, Fortran and Java"
set output "benchmark-c+fortran+java.png"
set datafile separator ","
plot "<sed 's/;/,/g' java.csv" using 1:5 title "Java (4 threads)" with linespoint, \
     "fortran_sec.csv" using 1:($2*1000) title "Fortran" with linespoint, \
     "c_µs.csv" using 1:($2/1000) title "C (OpenMP)" with linespoint
