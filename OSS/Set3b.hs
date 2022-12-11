-- Exercise set 3b
--
-- This is a special exercise set. The exercises are about
-- implementing list functions using recursion and pattern matching,
-- without using any standard library functions. For this reason,
-- you'll be working in a limited environment where almost none of the
-- standard library is available.
--
-- At least the following standard library functions are missing:
--  * (++)
--  * head
--  * tail
--  * map
--  * filter
--  * concat
--  * (!!)
--
-- The (:) operator is available, as is list literal syntax [a,b,c].
--
-- Feel free to use if-then-else, guards, and ordering functions (< and > etc.).
--
-- The tests will check that you haven't added imports :)

{-# LANGUAGE NoImplicitPrelude #-}

module Set3b where

import Mooc.LimitedPrelude
import Mooc.Todo

------------------------------------------------------------------------------
-- Ex 1: given numbers start, count and end, build a list that starts
-- with count copies of start and ends with end.
--
-- Use recursion and the : operator to build the list.
--
-- Examples:
--   buildList 1 5 2 ==> [1,1,1,1,1,2]
--   buildList 7 0 3 ==> [3]

-- 재귀 문제
-- 반복되는 작업은 계속 리턴, 종료할 지점은 어떤 형태인지 따로 지정
-- 종료 지점 부터 역순으로 차례대로 실행

buildList :: Int -> Int -> Int -> [Int]
buildList _ 0 end = [end]
buildList start count end = start : buildList start (count-1) end

{- 이 코드는 에러...
buildList :: Int -> Int -> Int -> [Int]
buildList start count end = reverse(end:(buildList2 start count []))

buildList2 :: Int -> Int -> [Int] -> [Int]
buildList2 start count arr = if count > 0
    then buildList2 start (count-1) start:arr
    else arr
-}
------------------------------------------------------------------------------
-- Ex 2: given i, build the list of sums [1, 1+2, 1+2+3, .., 1+2+..+i]
--
-- Use recursion and the : operator to build the list.
--
-- Ps. you'll probably need a recursive helper function

{- 맨 앞에 0이 계속 포함됨
sums :: Int -> [Int]
sums i = sums2 0 i 1

-- j = 1~1+...i 합 , cnt = sums의 i (1~i까지 카운트)
-- j = 0, 1, 3
-- c = 1, 2, 3, 4
-- j+c = 1, 3, 6
-- j = j+c
sums2 :: Int -> Int -> Int -> [Int]
sums2 j i cnt = if cnt <= i
    then j : sums2 (j+cnt) i (cnt+1)
    else [j]
-}

sums :: Int -> [Int]
sums 0 = []
sums i = sums2 0 i

sums2 :: Int -> Int -> [Int]
sums2 x a
    | x == a    = []
    | otherwise = p b : sums2 b a where b = x + 1

p :: Int -> Int
p 1 = 1
p n = n + p (n - 1)
------------------------------------------------------------------------------
-- Ex 3: define a function mylast that returns the last value of the
-- given list. For an empty list, a provided default value is
-- returned.
--
-- Use only pattern matching and recursion (and the list constructors : and [])
--
-- Examples:
--   mylast 0 [] ==> 0
--   mylast 0 [1,2,3] ==> 3

mylast :: a -> [a] -> a
mylast def [] = def -- 리스트가 비어있는 경우 def 그대로 반환
mylast _ (x:[]) = x -- [1,2,3]일 경우 3:[] -> x=3
mylast def (_:xs) = mylast def xs

------------------------------------------------------------------------------
-- Ex 4: safe list indexing. Define a function indexDefault so that
--   indexDefault xs i def
-- gets the element at index i in the list xs. If i is not a valid
-- index, def is returned.
--
-- Use only pattern matching and recursion (and the list constructors : and [])
--
-- Examples:
--   indexDefault [True] 1 False         ==>  False
--   indexDefault [10,20,30] 0 7         ==>  10
--   indexDefault [10,20,30] 2 7         ==>  30
--   indexDefault [10,20,30] 3 7         ==>  7
--   indexDefault ["a","b","c"] (-1) "d" ==> "d"

indexDefault :: [a] -> Int -> a -> a
indexDefault [] _ def = def
indexDefault (x:xs) 0 def = x
indexDefault (_:xs) i def = indexDefault xs (i-1) def
------------------------------------------------------------------------------
-- Ex 5: define a function that checks if the given list is in
-- increasing order.
--
-- Use pattern matching and recursion to iterate through the list.
--
-- Examples:
--   sorted [1,2,3] ==> True
--   sorted []      ==> True
--   sorted [2,7,7] ==> True
--   sorted [1,3,2] ==> False
--   sorted [7,2,7] ==> False

sorted :: [Int] -> Bool
sorted [] = True
sorted (x:xs) = sorted2 x xs

sorted2 :: Int -> [Int] -> Bool
sorted2 n [] = True
sorted2 n (x:xs) = if n <= x
    then sorted2 x xs
    else False
------------------------------------------------------------------------------
-- Ex 6: compute the partial sums of the given list like this:
--
--   sumsOf [a,b,c]  ==>  [a,a+b,a+b+c]
--   sumsOf [a,b]    ==>  [a,a+b]
--   sumsOf []       ==>  []
--
-- Use pattern matching and recursion (and the list constructors : and [])

sumsOf :: [Int] -> [Int]
sumsOf [] = []
sumsOf (x:xs) = sumsOf2 x xs

sumsOf2 :: Int -> [Int] -> [Int]
sumsOf2 n [] = [n]
sumsOf2 n (x:xs) = n : sumsOf2 (n+x) xs
------------------------------------------------------------------------------
-- Ex 7: implement the function merge that merges two sorted lists of
-- Ints into a sorted list
--
-- Use only pattern matching and recursion (and the list constructors : and [])
--
-- Examples:
--   merge [1,3,5] [2,4,6] ==> [1,2,3,4,5,6]
--   merge [1,1,6] [1,2]   ==> [1,1,1,2,6]

merge :: [Int] -> [Int] -> [Int]
merge [] ys = ys -- ys는 리스트 -> [ys]가 아님!
merge xs [] = xs
merge (x:xs) (y:ys)
    | x <= y = x : merge xs (y:ys)
    | otherwise = y : merge (x:xs) ys

------------------------------------------------------------------------------
-- Ex 8: compute the biggest element, using a comparison function
-- passed as an argument.
--
-- That is, implement the function mymaximum that takes
--
-- * a function `bigger` :: a -> a -> Bool
-- * a value `initial` of type a
-- * a list `xs` of values of type a
--
-- and returns the biggest value it sees, considering both `initial`
-- and all element in `xs`.
--
-- Examples:
--   mymaximum (>) 3 [] ==> 3
--   mymaximum (>) 0 [1,3,2] ==> 3
--   mymaximum (>) 4 [1,3,2] ==> 4    -- initial value was biggest
--   mymaximum (<) 4 [1,3,2] ==> 1    -- note changed biggerThan
--   mymaximum (\xs ys -> length xs > length ys) [] [[1,2],[3]]
--     ==> [1,2]

mymaximum :: (a -> a -> Bool) -> a -> [a] -> a
mymaximum bigger initial [] = initial
-- 리스트의 첫 원소(x)가 init와 비교(bigger)해서 만족하면 init를 리스트 첫 원소로 교체
mymaximum bigger initial (x:xs) = if bigger x initial 
    then mymaximum bigger x xs
    else mymaximum bigger initial xs

------------------------------------------------------------------------------
-- Ex 9: define a version of map that takes a two-argument function
-- and two lists. Example:
--
--   map2 f [x,y,z,w] [a,b,c]  ==> [f x a, f y b, f z c]
--
-- If the lists have differing lengths, ignore the trailing elements
-- of the longer list.
--
-- Use recursion and pattern matching. Do not use any library functions.

map2 :: (a -> b -> c) -> [a] -> [b] -> [c]
map2 f [] _ = []
map2 f _ [] = []
map2 f (a:as) (b:bs) =  f a b : map2 f as bs

------------------------------------------------------------------------------
-- Ex 10: implement the function maybeMap, which works a bit like a
-- combined map & filter.
---
-- maybeMap is given a list ([a]) and a function of type a -> Maybe b.
-- This function is called for all values in the list. If the function
-- returns Just x, x will be in the result list. If the function
-- returns Nothing, no value gets added to the result list.
--
-- Examples:
--
-- let f x = if x>0 then Just (2*x) else Nothing
-- in maybeMap f [0,1,-1,4,-2,2]
--   ==> [2,8,4]
--
-- maybeMap Just [1,2,3]
--   ==> [1,2,3]
--
-- maybeMap (\x -> Nothing) [1,2,3]
--   ==> []

maybeMap :: (a -> Maybe b) -> [a] -> [b]
maybeMap _f [] = []
maybeMap f (x:xs) = addBust (f x) xs
  where
    addBust (Just a) xs = a : maybeMap f xs
    addBust Nothing xs = maybeMap f xs
