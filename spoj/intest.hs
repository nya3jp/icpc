import Control.Monad

main = do [n, k] <- getLine >>= return . map read . words
          res <- replicateM n $ do
                   a <- getLine >>= return . read
                   return (if a `mod` k == 0 then 1 else 0)
          print $ sum res
