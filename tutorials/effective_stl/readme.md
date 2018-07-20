# Table of Content

## Containers
### Item 1: Choose your containers with care.
### Item 2: Beware the illusion of container-independent code.
### Item 3: Make copying cheap and correct for objects in containers.
### Item 4: Call empty instead of chekcing size() against zero.

### Item 6: Be alert for C++'s most vexing parse.
widget w(); // it's a function, not a instance.  

### Item 7: When using containers of newed pointers, remember to delete the pointer before the container is destroyed.
### Item 8: Never create containers of auto_ptrs.

### Item 9: Choose carefully among erasing options.
```
// remove the duplicate value from vector
std::vector<int> vi;
vi.erase(std::remove(vi.begin(), vi.end(), value), vi.end);

// if we use map, set, use erase() member function.
```


## vector and string
### Item 13: Prefer vector and string to dynamically allocated arrays.
### Item 14: Use reserve to avoid unnecessary reallocations.
reserve() and shrink_to_fit() functions.  

### Item 15: Be aware of variations in string implementations.
refcounted string implementation, but on c++11, all string is implemented with
non-refcounted.  

### Item 16: Know how to pass vector and string data to legacy APIs.
```
std::vector<int> vi;
std::string s;
&vi[0] === pointer to the first int value of the vector
&s[0]  === pointer to the first char of the string

std::vector<char> vc;
```

### Item 17: Use "the swap trick" to trim excess capacity.
1. swap trick
2. shrink_to_fit(), since c++11

### Item 18: Avoid using vector<bool>


## Associative containers
### Item 19: Understand the difference between equality and equivalence.
operator()== and operator< in associative containers.  

### Item 20: Specify comparison types for associative containers of pointers.
ftor class is a good idea.  

### Item 21: Always have comparison functions return false for equal values.
```
std::set<std::string, std::less> // equal values return false
10 < 10 ===> false
std::set<std::string, std::less_equal> // equal values return true
10 <= 10 ===> true

associative container sort according to the comparison function, so use `std::less_equal`
will destory associative container.
```


## Iterators
Item 26: Prefer iterator to const_iterator, reverse_iterator to const_reverse_iterator.
Don't mix iterator and const_iterator, reverse_iterator and const_reverse_iterator.

Item 27: Use distance and advance to convert a container's const_iterators to iterators.
Item 28: Understand how to use a reverse_iterator's base iterator.
Item 29: Consider istreambuf_iterator for character-by-character input.


## Algorithms
### Item 31: Know your sorting options.
