import Prelude
import Numeric
import Control.Monad
import Data.Char

main =
    do n <- liftM read $ getLine
       replicateM_ n $ liftM solve getLine >>= putStr

solve line = solve' $ filter (not . isSpace) line
solve' [] = []
solve' line =
    fst $ parse1 line
    where
      parse1 cs =
          case rem of
            '+':next -> (rpn ++ rpn' ++ "+", rem')
                   where (rpn', rem') = parse1 next
            _ -> (rpn, rem)
          where
            (rpn, rem) = parse2 cs
      parse2 cs =
          case rem of
            '-':next -> (rpn ++ rpn' ++ "-", rem')
                   where (rpn', rem') = parse2 next
            _ -> (rpn, rem)
          where
            (rpn, rem) = parse3 cs
      parse3 cs =
          case rem of
            '*':next -> (rpn ++ rpn' ++ "*", rem')
                   where (rpn', rem') = parse3 next
            _ -> (rpn, rem)
          where
            (rpn, rem) = parse4 cs
      parse4 cs =
          case rem of
            '/':next -> (rpn ++ rpn' ++ "/", rem')
                   where (rpn', rem') = parse4 next
            _ -> (rpn, rem)
          where
            (rpn, rem) = parse5 cs
      parse5 cs =
          case rem of
            '^':next -> (rpn ++ rpn' ++ "^", rem')
                   where (rpn', rem') = parse5 next
            _ -> (rpn, rem)
          where
            (rpn, rem) = parse6 cs
      parse6 ('(':r) = (rpn, rem)
          where
            (rpn,')':rem) = parse1 r
      parse6 (c:r)   = ([c], r)

