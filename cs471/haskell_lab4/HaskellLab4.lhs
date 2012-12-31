Max Gale
mgale4@binghamton.edu

> module HaskellLab4 where

Part A

1. (\x -> x) :: t -> t

2. 
    a. ((\x -> x) 3) = 3
    b. ((\x -> x) +) = +
    c. A descriptive name would be the identity function.

3. 
    a. (\x -> x + x) 3 = 6
    b. The expression is 3 + 3

4.
    a. (\x -> 3) 6 = 3
    b. A descriptive name would be constant function equal to 3.

Part B

> hLen :: (Num u, Eq t) => ([t] -> u) -> [t] -> u 
> hLen = (\f x -> if x == [] then 0 else 1 + (f (tail x)))
> myLength ls = if ls == [] then 0 else 1 + myLength (tail ls)

1.
    1. hLen is not recursive, because it does not call itself.
    2. hLen is a HOF because it takes another function as input.
    3. The value of 
        a. hLen sum [4, 5, 6] = 12
	b. hLen head [4,5,6] = 6

hLen has nothing to do with sum or head.

2. The value of hLen myLength [4,5,6] = 3

3. The relationship between hLen and myLength is that myLength is a function
   that takes a list as a paramtere, so hLen can call myLength.

Part C

> factorial :: Integral a => a -> a
> factorial n = if n ==0 then 1 else n * (factorial (n - 1))

1.

> hFact = (\f x -> if x == 0 then 1 else x * f (x- 1))

2. The value of hFact (^ 2) 4 = 16

3. The value for both is 120.

Part D

> factorial' = hFact factorial'

1. factorial' :: Integer -> Integer

2. 

> fix f = f (fix f)

    a. fix :: (t -> t) -> t
    b. The difference is the bottom code can call f with 2 paramters, whereas
       the top code calls fix first with one parameter, and then calls f
       with one parameter, which is the return value from f. 

3. The values of all of these are 720.