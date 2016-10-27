#Haskell Version

This is the Haskell version of the project. 

##Build

Build with GHC, using `ghc --make matrix_multiplication.hs`.
You will need the System.Random library, which you can get with `cabal` - 
a package manager for Haskell.

To get cabal using Arch Linux write:
```
pacman -S cabal-install
cabal update
```

As for System.Random you need:
```
cabal install random
```
##Usage
```
matrix_multiplication <number>
```
