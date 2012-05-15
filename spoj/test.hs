main = do cs <- getLine
          case cs of
            "42" -> return ()
            _ -> do putStrLn cs
                    main


