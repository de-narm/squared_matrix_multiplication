import System.Random
import Data.Time.Clock

main = do
	getN
	
getN = do
	putStr "\ESC[2Jnxn matrix multiplication\nplease define n as number\n\n"
	input <- getLine
        --create random generators
	g1 <- newStdGen
	g2 <- newStdGen
        --loop getN until we get an int
	case reads input :: [(Int, String)] of 
		[(n, _)] -> randomFillMatrices n g1 g2 
		_ -> getN

randomFillMatrices :: Int -> StdGen -> StdGen ->  IO() 
randomFillMatrices i g1 g2 =
	if  i > 0 
        --set up both lists with endless random values
	then initMul i (randomRs (0,1) g1) (randomRs (0,1) g2)
	else getN

initMul :: Int -> [Double] -> [Double] -> IO()
initMul i xs ys = do
	putStr "\ESC[2J" 
        --timestamp begin mul
	print =<< getCurrentTime
	endMul i (doMul i 0 xs ys)

doMul :: Int -> Int ->  [Double] -> [Double] -> [Double]
doMul i j xs ys 
    | j >= 0 && j < (i*i) = [scalar i j 0 xs ys] 
        ++ doMul i (j+1) xs ys
    | otherwise = []

scalar :: Int -> Int -> Int -> [Double] -> [Double] -> Double
scalar i j k xs ys 
    | k < i = (xs!!(((div j i)*i)+k)) * (ys!!((mod j i)+(k*i)))
        + scalar i j (k+1) xs ys
    | otherwise = 0

endMul :: Int -> [Double] -> IO()
endMul i xs = do
    putStr "\n"
    --haskell is lazy, meaning it only does what it has to
    --therefore we print the very last value of our new matrix
    print (xs!!((i*i)-1))
    putStr "\n"
    --timestamp end mul
    print =<< getCurrentTime

--debug fuction to control values
printMatrix :: Int -> Int -> [Double] -> IO()
printMatrix i j xs =
    if j > 0 
    then do
        putStr "\n"
        print (take i xs)
        printMatrix i (j-1) (drop i xs)
    else
        putStr "\n"
