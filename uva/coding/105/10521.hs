f :: Integer -> Integer -> String
f p q = case p `divMod` q of
        (d, 0) -> show d
        (d, r) -> show d ++ "+1/{" ++ f q r ++ "}"

main = flip catch (const (return ())) $ do
         [p, q] <- getLine >>= return . map read . words
         putStrLn $ show p ++ "/" ++ show q ++ " = " ++ f p q
         main
