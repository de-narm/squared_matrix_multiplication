import System.Random
import System.IO
import System.Environment
import Data.Time.Clock
import Control.DeepSeq
import Control.Parallel.Strategies

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
    | j < (i*i) = [sum(zipWith (*) 
        (head(drop ((div j i)-1) xs)) 
        (head(drop ((mod j i)-1) xs)))]
        ++ doMul i (j+1) xs ys
    | otherwise = []

endMul :: Int -> [Double] -> IO()
endMul i zs = do
    --timestamp begin mul
    tstpBeg <- getCurrentTime;
    --timestamp end mul
    tstpEnd <- (deepseq 
        (using zs (parListChunk (div (i*i) 4) rdeepseq)) 
        getCurrentTime);
    print (diffUTCTime tstpEnd tstpBeg);
