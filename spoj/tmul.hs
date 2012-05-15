import Control.Monad

main = do n <- return . read =<< getLine
          replicateM_ n $ do [a, b] <- return . map read . words =<< getLine
                             print (a*b :: Integer)

