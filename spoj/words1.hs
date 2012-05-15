import Data.Char
import Control.Monad

solve :: [String] -> Bool
solve ss = let adj = make_adj ss
               v = foldl1 (zipWith (+)) adj in
           if length (filter (\x -> x < -1 || x > 1) v) > 0 then False
           else
               let pos = length $ filter (> 0) v
                   neg = length $ filter (< 0) v in
               (pos == 0 && neg == 0) || (pos == 1 && neg == 1)
    where
      make_adj :: [String] -> [[Int]]
      make_adj = map (\s -> let a = ord $ head s
                                b = ord $ last s in
                            take 256 $
                                 zipWith (+) (replicate a 0 ++ [1] ++ repeat 0) (replicate b 0 ++ [-1] ++ repeat 0))


main :: IO ()
main = do cases <- getLine >>= readIO
          replicateM_ cases $ do n <- getLine >>= readIO
                                 ss <- replicateM n getLine
                                 putStrLn $ case solve ss of
                                                True -> "Ordering is possible."
                                                False -> "The door cannot be opened."

