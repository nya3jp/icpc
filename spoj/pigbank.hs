import Control.Monad
import Data.Queue

main =
    do n <- liftM read $ getLine
       replicateM_ n onecase

inf = 30000000 :: Int

onecase =
    do wline <- getLine
       let [w1, w2] = map read $ words wline
           w = w2 - w1
       n <- liftM read $ getLine
       items <- replicateM n readItem
       putStrLn $ format $ knapsack w items
    where
      readItem = do line <- getLine
                    let [a, b] = words line
                    return ((read a, read b) :: (Int, Int))
      format ans | ans == inf = "This is impossible."
                 | otherwise  = "The minimum amount of money in the piggy-bank is " ++ (show ans) ++ "."


knapsack0 capacity items =
    (knapsack' items) !! capacity
    where
      knapsack' [] = 0:(repeat inf)
      knapsack' ((v, w):rem) =
          knapsack1 prev (replicate w inf)
          where
            prev = (knapsack' rem)
            knapsack1 (up:ups) (left:lefts) =
                this:(knapsack1 ups (lefts++this))
                where
                  this = min up (left+v)
