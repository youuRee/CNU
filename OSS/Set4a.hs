-- Exercise set 4a:
--
-- * using type classes
-- * working with lists
--
-- Type classes you'll need
--  * Eq
--  * Ord
--  * Num
--  * Fractional
--
-- Useful functions:
--  * maximum
--  * minimum
--  * sort

module Set4a where

import Mooc.Todo
import Data.List
import Data.Ord
import qualified Data.Map as Map
import Data.Array

------------------------------------------------------------------------------
-- Ex 1: implement the function allEqual which returns True if all
-- values in the list are equal.
--
-- Examples:
--   allEqual [] ==> True
--   allEqual [1,2,3] ==> False
--   allEqual [1,1,1] ==> True
--
-- PS. check out the error message you get with your implementation if
-- you remove the Eq a => constraint from the type!

allEqual :: Eq a => [a] -> Bool
allEqual [] = True
allEqual [x] = True
allEqual (x:xs) = if x /= head xs
    then False
    else allEqual xs

------------------------------------------------------------------------------
-- Ex 2: implement the function distinct which returns True if all
-- values in a list are different.
--
-- Hint: a certain function from the lecture material can make this
-- really easy for you.
--
-- Examples:
--   distinct [] ==> True
--   distinct [1,1,2] ==> False
--   distinct [1,2] ==> True

{-
ghci> filter (1 ==) [1,2,3]
[1]
-}
distinct :: Eq a => [a] -> Bool
distinct [] = True
distinct [x] = True
-- filter 결과 = [] -> x와 xs원소들이 겹치지x
distinct (x:xs) = if [] /= filter (x ==) xs
    then False
    else distinct xs

------------------------------------------------------------------------------
-- Ex 3: implement the function middle that returns the middle value
-- (not the smallest or the largest) out of its three arguments.
--
-- The function should work on all types in the Ord class. Give it a
-- suitable type signature.
--
-- Examples:
--   middle 'b' 'a' 'c'  ==> 'b'
--   middle 1 7 3        ==> 3

middle :: (Ord a) => a -> a -> a -> a
middle a b c =  head (drop 1 (sort (a:b:[c])))

------------------------------------------------------------------------------
-- Ex 4: return the range of an input list, that is, the difference
-- between the smallest and the largest element.
--
-- Your function should work on all suitable types, like Float and
-- Int. You'll need to add _class constraints_ to the type of range.
--
-- It's fine if your function doesn't work for empty inputs.
--
-- Examples:
--   rangeOf [4,2,1,3]          ==> 3
--   rangeOf [1.5,1.0,1.1,1.2]  ==> 0.5

-- rangeOf = 큰 수 - 작은 수
-- ghci> foldr max 0 [1,2,5,3] => 5

rangeOf :: (Ord a, Num a) => [a] -> a
rangeOf xs = (foldr max (head xs) (tail xs)) - (foldr min (head xs) (tail xs))

------------------------------------------------------------------------------
-- Ex 5: given a (non-empty) list of (non-empty) lists, return the longest
-- list. If there are multiple lists of the same length, return the list that
-- has the smallest _first element_.
--
-- (If multiple lists have the same length and same first element,
-- you can return any one of them.)
--
-- Give the function "longest" a suitable type.
--
-- Challenge: Can you solve this exercise without sorting the list of lists?
--
-- Examples:
--   longest [[1,2,3],[4,5],[6]] ==> [1,2,3]
--   longest ["bcd","def","ab"] ==> "bcd"

-- ghci> map length ["cd", "ef", "ghij"] => [2,2,4]

longest :: (Ord a) => [[a]] -> [a] -- 인자 : 이중 리스트
longest xs = foldr reducer (head xs) xs -- -- foldr 동작 원리 생각!
  where
    reducer cur ans
      | length cur > length ans = cur
      | length cur < length ans = ans
      | head cur < head ans = cur
      | otherwise = ans

------------------------------------------------------------------------------
-- Ex 6: Implement the function incrementKey, that takes a list of
-- (key,value) pairs, and adds 1 to all the values that have the given key.
--
-- You'll need to add _class constraints_ to the type of incrementKey
-- to make the function work!
--
-- The function needs to be generic and handle all compatible types,
-- see the examples.
--
-- Examples:
--   incrementKey True [(True,1),(False,3),(True,4)] ==> [(True,2),(False,3),(True,5)]
--   incrementKey 'a' [('a',3.4)] ==> [('a',4.4)]

-- 튜플 첫 원소 == 인자 k -> 튜플 두번째 원소 + 1
incrementKey :: (Ord k, Num v) => k -> [(k,v)] -> [(k,v)]
incrementKey d []          = []
incrementKey d ((a, b):xs)
      | d == a          = (a, b + 1) : incrementKey d xs
      | otherwise       = (a, b) : incrementKey d xs


-- 다시!!!!!!
-- incrementKey k xs = if k == head (map fst xs)
    
------------------------------------------------------------------------------
-- Ex 7: compute the average of a list of values of the Fractional
-- class.
--
-- There is no need to handle the empty list case.
--
-- Hint! since Fractional is a subclass of Num, you have all
-- arithmetic operations available
--
-- Hint! you can use the function fromIntegral to convert the list
-- length to a Fractional

average :: Fractional a => [a] -> a
average xs = sum xs / fromIntegral (length xs)

------------------------------------------------------------------------------
-- Ex 8: given a map from player name to score and two players, return
-- the name of the player with more points. If the players are tied,
-- return the name of the first player (that is, the name of the
-- player who comes first in the argument list, player1).
--
-- If a player doesn't exist in the map, you can assume they have 0 points.
--
-- Hint: Map.findWithDefault can make this simpler
--
-- Examples:
--   winner (Map.fromList [("Bob",3470),("Jane",2130),("Lisa",9448)]) "Jane" "Lisa"
--     ==> "Lisa"
--   winner (Map.fromList [("Mike",13607),("Bob",5899),("Lisa",5899)]) "Lisa" "Bob"
--     ==> "Lisa"

-- fromList == reverse
-- lookup "키" "배열" => 배열 안에 키에 해당하는 값 리턴
winner :: Map.Map String Int -> String -> String -> String
winner scores player1 player2 = if v1 >= v2 then player1 else player2
    where v1 = Map.lookup player1 scores
          v2 = Map.lookup player2 scores

------------------------------------------------------------------------------
-- Ex 9: compute how many times each value in the list occurs. Return
-- the frequencies as a Map from value to Int.
--
-- Challenge 1: try using Map.alter for this
--
-- Challenge 2: use foldr to process the list
--
-- Example:
--   freqs [False,False,False,True]
--     ==> Map.fromList [(False,3),(True,1)]


-- a = Map.empty -> a = []
{-
findWithDefault : 키(인자2)의 값을 반환하거나 키가 Map에 없으면 인자1을 반환
 findWithDefault 'x' 1 (fromList [(5,'a'), (3,'b')]) == 'x'
 findWithDefault 'x' 5 (fromList [(5,'a'), (3,'b')]) == 'a'

alter : 인자2가 fromList 안에 없으면 새로 추가, 있으면 변경
 let f _ = Just "c"
 alter f 7 (fromList [(5,"a"), (3,"b")]) == fromList [(3, "b"), (5, "a"), (7, "c")]
 alter f 5 (fromList [(5,"a"), (3,"b")]) == fromList [(3, "b"), (5, "c")]
-}

freqs :: (Eq a, Ord a) => [a] -> Map.Map a Int
freqs xs = foldr addToMap Map.empty xs
  where
    addToMap val cur = Map.alter (\_ -> Just ((Map.findWithDefault 0 val cur) + 1)) val cur

------------------------------------------------------------------------------
-- Ex 10: recall the withdraw example from the course material. Write a
-- similar function, transfer, that transfers money from one account
-- to another.
--
-- However, the function should not perform the transfer if
-- * the from account doesn't exist,
-- * the to account doesn't exist,
-- * the sum is negative,
-- * or the from account doesn't have enough money.
--
-- Hint: there are many ways to implement this logic. Map.member or
-- Map.notMember might help.
--
-- Examples:
--   let bank = Map.fromList [("Bob",100),("Mike",50)]
--   transfer "Bob" "Mike" 20 bank              --> Bob이 Mike에게 20을 줘라
--     ==> fromList [("Bob",80),("Mike",70)]
--   transfer "Bob" "Mike" 120 bank             --> 120 > 100 => 그대로
--     ==> fromList [("Bob",100),("Mike",50)]
--   transfer "Bob" "Lisa" 20 bank              --> Lisa x => 그대로 
--     ==> fromList [("Bob",100),("Mike",50)]
--   transfer "Lisa" "Mike" 20 bank
--     ==> fromList [("Bob",100),("Mike",50)]

{-
notMember : fromList 안에 인자2 없으면 = True
 notMember 5 (fromList [(5,'a'), (3,'b')]) == False
 notMember 1 (fromList [(5,'a'), (3,'b')]) == True

union (fromList [(5, "a"), (3, "b")]) (fromList [(5, "A"), (7, "C")])
 => fromList [(3, "b"), (5, "a"), (7, "C")]
-}
transfer :: String -> String -> Int -> Map.Map String Int -> Map.Map String Int
transfer from to amount bank
  | Map.notMember from bank = bank
  | Map.notMember to bank = bank
  | amount < 0 = bank
  | newFrom < 0 = bank
  | otherwise = Map.union (Map.fromList [(from, newFrom), (to, newTo)]) bank
  where
    newFrom = Map.findWithDefault 0 from bank - amount -- from의 값(돈) amount만큼 제거
    newTo = Map.findWithDefault 0 to bank + amount     -- 해당하는 from 없으면 fWD = 0 --> new = 음수
------------------------------------------------------------------------------
-- Ex 11: given an Array and two indices, swap the elements in the indices.
--
-- Example:
--   swap 2 3 (array (1,4) [(1,"one"),(2,"two"),(3,"three"),(4,"four")])
--         ==> array (1,4) [(1,"one"),(2,"three"),(3,"two"),(4,"four")]

swap :: Ix i => i -> i -> Array i a -> Array i a
swap i j arr = arr // [(i, n2), (j, n1)]
  where n1 = arr ! i -- ! : arr의 원소들 중 fst가 i에 해당되는 것
        n2 = arr ! j

------------------------------------------------------------------------------
-- Ex 12: given an Array, find the index of the largest element. You
-- can assume the Array isn't empty.
--
-- You may assume that the largest element is unique.
--
-- Hint: check out Data.Array.indices or Data.Array.assocs

{- 
Input: assocs (array (0,3) [(1,"A"),(2,"B"),(3,"D"),(0,"QQQ")])
Output: [(0,"QQQ"),(1,"A"),(2,"B"),(3,"D")]

assos : array idx 범위까지 정렬(fst 기준으로)하여 출력
-}

maxIndex :: (Ix i, Ord a) => Array i a -> i
maxIndex arr = fst (foldr comparer (head arrList) arrList)
  where
    arrList = Data.Array.assocs arr
    comparer v c = if snd v > snd c then v else c 

{-
maxIndex :: (Ix i, Ord a) => Array i a -> i
maxIndex xs = fst (head(drop ((length arr)-1) arr)) -- max : 맨 뒤 -> 앞에거 drop
  where arr = Data.Array.assocs xs -- snd 기준으로 정렬
-}
