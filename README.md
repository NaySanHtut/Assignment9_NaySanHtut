# Assignment9_NaySanHtut

# GenericArray: A Templated Dynamic Array Class

## Overview

`GenericArray<T>` is a C++ class template that mimics some of the behavior of `std::vector`. It manages a dynamically allocated array of any basic numerical type (`int`, `float`, `double`, etc.) using `new` and `delete`.

Every time an element is added, a new array one element larger is allocated, the old contents are copied over along with the new element, and the old array is deleted.

## Build and Run

Requires a C++11 (or newer) compiler, for example `g++`:

```bash
g++ -Wall -std=c++11 main.cpp -o main
./main
```

## Functions

| Function | Description |
|----------|-------------|
| `GenericArray()` | Creates an empty array |
| `void addElement(T value)` | Appends `value` to the end. Allocates a new array of size + 1, copies the old elements and the new value into it, then deletes the old array |
| `T at(int index) const` | Returns the element at `index`. Throws `std::out_of_range` if `index < 0` or `index >= size()` |
| `int size() const` | Returns the number of elements |
| `T sum() const` | Returns the sum of all elements (0 for an empty array) |
| `T max() const` | Returns the largest element. Throws `std::out_of_range` if the array is empty |
| `T min() const` | Returns the smallest element. Throws `std::out_of_range` if the array is empty |
| `T *slice(int begin, int end) const` | Returns a pointer to a **new** array containing elements `begin` through `end`, inclusive (see below) |

### `slice(begin, end)`

- Returns a copy, not a pointer into the underlying data.
- Example: for the array `[0,2,4,6,8]`, `slice(2,4)` returns `[4,6,8]`.
- The number of elements in the result is `end - begin + 1`.
- Throws `std::out_of_range` if `begin < 0`, `end >= size()`, or `begin > end`.
- The caller owns the returned array and must free it with `delete[]`.

## Memory Management

- Storage is allocated with `new[]` and released with `delete[]`.
- The destructor frees the array when the object goes out of scope.
- A copy constructor and assignment operator perform deep copies, so two `GenericArray` objects never share the same memory.
- Arrays returned by `slice()` must be deleted by the caller.

## Example

```cpp
GenericArray<int> arr;
for (int i = 0; i < 15; i++)
    arr.addElement(i * 2);              // 0, 2, 4, ..., 28

std::cout << arr.size() << std::endl;   // 15
std::cout << arr.sum() << std::endl;    // 210
std::cout << arr.max() << " " << arr.min() << std::endl;   // 28 0

int *s = arr.slice(5, 10);              // 10 12 14 16 18 20
for (int i = 0; i < 6; i++)
    std::cout << s[i] << " ";
delete[] s;
```

## Expected Output

```
size of array is 15
sum of the array is 210
maximum and minimum of array is 28	0
element at index 3 is 6
slice(5,10) = 10 12 14 16 18 20
caught: slice(): invalid bounds
double sum = 3.25, max = 4, min = -2.25
```
