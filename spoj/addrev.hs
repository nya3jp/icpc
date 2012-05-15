import Control.Monad

main = do n <- getLine >>= readIO
          replicateM_ n $ do
            [a, b] <- getLine >>= mapM readIO . words
            print $ rev $ rev a + rev b
    where
      rev n = rev' n 0
      rev' 0 m = m
      rev' n m = rev' (n `div` 10) (m*10 + (n `mod` 10))
