import Data.Array

memoize :: (Int, Int) -> ((Int -> a) -> Int -> a) -> Int -> a
memoize range@(first, last) maker =
    memoized
    where
      memoized = (memo !)
      memo = array range [(i, maker memoized i) | i <- [first..last]]

fib :: Int -> Int
fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib (n-2)

fib2 :: [Int]
fib2 = 1:1:zipWith (+) fib2 (tail fib2)

fibmaker :: (Int -> Int) -> Int -> Int
fibmaker f 0 = 1
fibmaker f 1 = 1
fibmaker f n = f (n-1) + f (n-2)

fibm :: Int -> Int
fibm = memoize (0, 100) fibmaker

ack :: Int -> Int -> Int
ack 0 n = n+1
ack m 0 = ack (m-1) 1
ack m n = ack (m-1) (ack m (n-1))

ackmaker :: (Int -> Int -> Int) -> Int -> Int -> Int
ackmaker f 0 n = n+1
ackmaker f m 0 = f (m-1) 1
ackmaker f m n = f (m-1) (f m (n-1))

ackm = memoize (0,100) $ memoize (0,100) ack
