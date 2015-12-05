create table parents as
  select "abraham" as parent, "barack" as child union
  select "abraham"          , "clinton"         union
  select "delano"           , "herbert"         union
  select "fillmore"         , "abraham"         union
  select "fillmore"         , "delano"          union
  select "fillmore"         , "grover"          union
  select "eisenhower"       , "fillmore";

create table dogs as
  select "abraham" as name, "long" as fur, 26 as height union
  select "barack"         , "short"      , 52           union
  select "clinton"        , "long"       , 47           union
  select "delano"         , "long"       , 46           union
  select "eisenhower"     , "short"      , 35           union
  select "fillmore"       , "curly"      , 32           union
  select "grover"         , "short"      , 28           union
  select "herbert"        , "curly"      , 31;

create table sizes as
  select "toy" as size, 24 as min, 28 as max union
  select "mini",        28,        35        union
  select "medium",      35,        45        union
  select "standard",    45,        60;

-------------------------------------------------------------
-- PLEASE DO NOT CHANGE ANY SQL STATEMENTS ABOVE THIS LINE --
-------------------------------------------------------------

-- The size of each dog
create table size_of_dogs as
  select dogs.name, sizes.size from 
  dogs join sizes on dogs.height > sizes.min and dogs.height <= sizes.max;


-- All dogs with parents ordered by decreasing height of their parent
create table by_height as
select dogs.name from
dogs join parents on dogs.name = parents.child
order by height desc;


-- Sentences about siblings that are the same size
create table sentences as
with lookup(child, size, parent) as (
     select size_of_dogs.name, size_of_dogs.size, parents.parent from 
     size_of_dogs join parents on size_of_dogs.name = parents.child
     )
select x.child || ' and ' || y.child || ' are ' || x.size || ' siblings'
from lookup as x, lookup as y
where x.parent = y.parent and x.child < y.child and x.size = y.size;


-- Ways to stack 4 dogs to a height of at least 170, ordered by total height
create table stacks as
with four_tuple(fst, snd, thd, fth, total) as (
     select one.name, two.name, three.name, four.name, one.height+two.height+three.height+four.height from
     dogs as one, dogs as two, dogs as three, dogs as four
     where one.height < two.height and two.height < three.height and three.height < four.height
     )
select fst || ", " || snd || ", " || thd || ", " || fth, total from four_tuple
where total >= 170; 


create table tallest as
select "REPLACE THIS LINE WITH YOUR SOLUTION";


-- All non-parent relations ordered by height difference
create table non_parents as
select "REPLACE THIS LINE WITH YOUR SOLUTION";


