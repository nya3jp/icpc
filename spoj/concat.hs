
main = print $ sum (range 1 100000)

range a b | a == b    = [a]
          | otherwise = (range a (mid-1)) ++ (range mid b)
    where
      mid = (a+b+1) `div` 2

