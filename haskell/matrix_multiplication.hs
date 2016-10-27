import System.Random
import System.Environment
import Data.Time.Clock

main = do
	getN
	
getN = do
	input <- getArgs;
    --create random generators
	g1 <- newStdGen;
	g2 <- newStdGen;
        if input == []
            then do
		        putStr "Please use `./matrix_multiplication <<int>>`\n";
            else do 
                --loop getN until we get an int
	            case reads (head input) :: [(Int, String)] of 
		            [(n, _)] -> randomFillMatrices n g1 g2 
		            _ -> putStr "Please use `./matrix_multiplication <<int>>`\n"

randomFillMatrices :: Int -> StdGen -> StdGen ->  IO() 
randomFillMatrices i g1 g2 =
	if  i > 0 
        --set up both lists with endless random values
	    then initMul i (randomRs (0,1) g1) (randomRs (0,1) g2)
	    else putStr "Only use positive numbers!"

initMul :: Int -> [Double] -> [Double] -> IO()
initMul i xs ys = do
    putStr "\n";
    --force haskell to set all needed random values before mul
    print (xs!!((i*2)-1));
    print (ys!!((i*2)-1));
    putStr "\n";
    --timestamp begin mul
	print =<< getCurrentTime;
	endMul i (doMul i 0 (getRows i xs) (getColumns i 0 ys));

getRows :: Int -> [Double] -> [[Double]]
getRows i [] = []
getRows i xs = [(take i xs)] ++ getRows i (drop i xs)

getColumns :: Int -> Int -> [Double] -> [[Double]]
getColumns i j xs =
    if i > j
        then [(singleColumn i j 0 xs)] ++ getColumns i (j+1) xs
        else []

singleColumn :: Int -> Int -> Int -> [Double] -> [Double]
singleColumn i j k xs =
    if i > k
        then [head(drop j xs)] ++ singleColumn i j (k+1) (drop i xs)
        else []

doMul :: Int -> Int -> [[Double]] -> [[Double]] -> [Double]
doMul i j xs ys 
    | j >= 0 && j < (i*i) = [scalar i 0 (xs!!(div j i)) (ys!!(mod j i))]
        ++ doMul i (j+1) xs ys
    | otherwise = []

scalar :: Int -> Int -> [Double] -> [Double] -> Double
scalar i j xs ys 
    | i > j = (xs!!j)*(ys!!j) + scalar i (j+1) xs ys
    | otherwise = 0

endMul :: Int -> [Double] -> IO()
endMul i xs = do
    putStr "\n";
    --haskell is lazy, meaning it only does what it has to
    --therefore we print the very last value of our new matrix
    print (xs!!((i*i)-1));
    putStr "\n";
    --timestamp end mul
    print =<< getCurrentTime;

--debug fuction to control values
printMatrix :: Int -> Int -> [Double] -> IO()
printMatrix i j xs =
    if j > 0 
        then do
            putStr "\n";
            print (take i xs);
            printMatrix i (j-1) (drop i xs);
        else do
            putStr "\n";
