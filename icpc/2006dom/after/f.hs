
solve :: [Complex Double] -> (Double, Double)
solve points =
    foldl selectMinMax (0, 0) angles
    where
      selectMinMax (minAngle, maxAngle) newAngle = 
          let minArea = calcArea points minAngle
              maxArea = calcArea points maxAngle
              newArea = calcArea points newAngle in
          if newArea < minArea then (newAngle, maxAngle)
          else if newArea > maxArea then (minAngle, newAngle)
               else (minAngle, maxAngle)
      angles = gatherAngles points


gatherAngles :: [Complex Double] -> [Double]
gatherAngles points =
    tangentAngles ++ zipWith (calcExtremalAngle points) tangentAngles (tail tangentAngles)
    where
      tangentAngles = sort $ ([0, 2*pi] ++) $ concat $ liftM2 calcTangentAngles points points

calcTangentAngles :: Complex Double -> Complex Double -> [Double]
calcTangentAngles a b =
    [t, t+dt, t-dt]
    where
      x = b - a
      d = abs x
      t = phase x
      dt = asin (2 / d)

calcExtremalAngle :: [Complex Double] -> Double -> Double -> Double
calcExtremalAngle points ta tb =
    - atan2 (-coefCos) coefSin
    where
      coefCos = sum $ zipWith (*) sgns (map (negate . imagPart) points)
      coefSin = sum $ zipWith (*) sgns (map realPart points)
      sgns = determineSigns points ((ta+tb)/2)

project :: [Complex Double] -> Double -> [Double]
project points th =
    map project' points
    where
      project' = imagPart . (* mkPolar 1 (-th))

determineSigns :: [Complex Double] -> Double -> [Double]
determineSigns points th =
    

calcArea :: [Complex Double] -> Double -> Double


