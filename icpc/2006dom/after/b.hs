import Control.Monad
import Data.List

main = do n <- getLine >>= readIO
          replicateM_ n $ getLine >>= print . solve

solve s = length $ nub $ sort $ concat $ zipWith make (inits s) (tails s)
    where
      make a b = (liftM2 (++) la lb) ++ (liftM2 (++) lb la)
          where
            la = [a, reverse a]
            lb = [b, reverse b]


