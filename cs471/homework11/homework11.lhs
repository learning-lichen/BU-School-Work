> module Haskell1S12
> where

Problem 1

> composeList (x:[]) input = x input
> composeList (x:xs) input = (x . composeList xs) input

Problem 2

> tetrahedral :: Integer -> Integer
> tetrahedral n 
>     | n > 1 = (tetrahedral (n - 1)) + (sum [1..n])
>     | n == 1 = 1
>     | otherwise = error "Bad n"

Problem 3

> newtonAppr n guess epsilon
>     | ((average * average) - n) < epsilon = average
>     | otherwise = newtonAppr n average epsilon
>     where average = (((n / guess) + guess) / 2)