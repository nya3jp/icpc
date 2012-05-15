import Control.Monad

main = do n <- getLine >>= readIO
          replicateM_ n $ do k <- getLine >>= readIO
                             print $ solve k

solve :: Int -> Int
solve n =
    sum $ takeWhile (> 0) $ map (n `div`) (iterate (* 5) 5)
