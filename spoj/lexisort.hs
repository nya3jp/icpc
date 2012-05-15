import Control.Monad

main = do [a, b] <- getLine >>= mapM readIO . words
          replicateM_ a $ print b
