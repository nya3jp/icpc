module Main where

f :: Int -> Int -> Int
f 0 0 = 1
f n _ | n < 0 = -1
f _ 0 = 0
f n m = sum $ takeWhile (>= 0) $ map (\k -> f (n-(m*k)) (m-1)) [0..]

main = do [n,m] <- getLine >>= return . map read . words
          print $ f n m
          main

