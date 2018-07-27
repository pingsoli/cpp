# Effective STL

## Containers
#### Item 1: Choose your containers with care.
#### Item 2: Beware the illusion of container-independent code.
#### Item 3: Make copying cheap and correct for objects in containers.
#### Item 4: Call empty instead of chekcing size() against zero.
#### Item 5: Prefer range member functions to their single-element counterparts.
#### Item 6: Be alert for C++'s most vexing parse.
widget w(); // it's a function, not a instance.  

#### Item 7: When using containers of newed pointers, remember to delete the pointer before the container is destroyed.
#### Item 8: Never create containers of auto_ptrs.

#### Item 9: Choose carefully among erasing options.
```
// remove the duplicate value from vector
std::vector<int> vi;
vi.erase(std::remove(vi.begin(), vi.end(), value), vi.end);

// if we use map, set, use erase() member function.
```
#### Item 10: Be aware of allocator conventions and restrictions.
#### Item 11: Understand the legitimate uses of custom allocates.
#### Item 12: Have realistic expectations about the thread safety of STL containers.


## vector and string
##### Item 13: Prefer vector and string to dynamically allocated arrays.
##### Item 14: Use reserve to avoid unnecessary reallocations.
reserve() and shrink_to_fit() functions.  

#### Item 15: Be aware of variations in string implementations.
refcounted string implementation, but on c++11, all string is implemented with
non-refcounted.  

#### Item 16: Know how to pass vector and string data to legacy APIs.
```
std::vector<int> vi;
std::string s;
&vi[0] === pointer to the first int value of the vector
&s[0]  === pointer to the first char of the string

std::vector<char> vc;
```

#### Item 17: Use "the swap trick" to trim excess capacity.
1. swap trick
2. shrink_to_fit(), since c++11

#### Item 18: Avoid using vector<bool>


## Associative containers
#### Item 19: Understand the difference between equality and equivalence.
operator()== and operator< in associative containers.  

#### Item 20: Specify comparison types for associative containers of pointers.
ftor class is a good idea.  

#### Item 21: Always have comparison functions return false for equal values.
```
std::set<std::string, std::less> // equal values return false
10 < 10 ===> false
std::set<std::string, std::less_equal> // equal values return true
10 <= 10 ===> true

associative container sort according to the comparison function, so use `std::less_equal`
will destory associative container.
```
#### Item 22: Avoid in-place key modification in set and multiset.
#### Item 23: Consider replacing associative containers with sorted vectors.
#### Item 24: Choose carefully between map::operator[] and map-insert when efficiency is important.
#### Item 25: Familiarize yourself with the nonstandard hashed containers.


## Iterators
#### Item 26: Prefer iterator to const_iterator, reverse_iterator to const_reverse_iterator.
Don't mix iterator and const_iterator, reverse_iterator and const_reverse_iterator.

#### Item 27: Use distance and advance to convert a container's const_iterators to iterators.
#### Item 28: Understand how to use a reverse_iterator's base iterator.
#### Item 29: Consider istreambuf_iterator for character-by-character input.


## Algorithms
#### Item 30: Make sure destination ranges are big enough.
#### Item 31: Know your sorting options.
sort, stable_sort, partition_sort, nth_element  

#### Item 32: Follow remove-like algorithms by erase if you really want to remove something.
```
std::vector<int> vi{1, 2, 3, 2, 5};
vi.erase(std::remove(vi.begin(), vi.end(), 2), vi.end());
```
#### Item 33: Be wary of remove-like algorithms on containers of pointers.
precaute the memory leak.

#### Item 34: Note which algorithm expect sorted ranges.
binary_search, lower_bound, upper_bound, equal_range, set_union, set_intersection, 
set_difference, set_symmetic_difference, merge, implace_merge, includes.

#### Item 35: Implement simple case-insensitive string comparisons via mismatch or lexicographical compare.
#### Item 36: Understand the proper implementation of copy_if.
#### Item 37: Use accumulate or for_each to summarize ranges.


## Functors, Functor class, Function, etc
#### Item 38: Design functor classes for pass-by-value.
#### Item 39: Make predicates pure functions.
Q: what is pure functions ?  
A: const restriction.  
#### Item 40: Make functor classes adaptable.
#### Item 41: Understand the reason for ptr_fun, mem_fun and mem_fun_ref.
#### Item 42: Make sure less<T> means operator<.


## Programming with STL
#### Item 43: Prefer algorithm calls to hand-written loops.
#### Item 44: Prefer member functions to algorithms with the same names.
#### Item 45: Distinguish among count, find, binary_sarch, lower_bound, upper_bound and equal_bound.
#### Item 46: Consider function objects instead of functions as algorithm paramters.
#### Item 47: Avoid producing write-only code.
#### Item 48: Always #include the proper headers.
#### Item 49: Learn to decipher STL-related compiler diagnostics.
#### Item 50: Familiarize yourself with STL-related web sites.
