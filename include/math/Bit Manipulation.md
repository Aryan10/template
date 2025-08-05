## Construction

Create an empty set x
```x = 0```

Create a set x with element i
```x = 1 << i```

Create a set x with all elements (Domain of x)
```x = (1 << n) - 1```

Create a set x with elements i..j
```x = ((1 << (j - i + 1)) - 1) << i``` 

## Basic Operations

Check if element i is present (Set Intersection)
```x & (1 << i)```

Add element i to set x (Set Union)
```x |= (1 << i)```

Remove element i from set x (Set Difference)
```x &= ~(1 << i)```

Toggle element i in set x (Set Symmetric Difference)
```x ^= (1 << i)```

Set of elements not in set x (Set Complement)
```~x & ((1 << n) - 1)```

Number of elements in set x (Population Count)
```__builtin_popcount(x)```
```popcount(x)```

## Comparison

Check if set x is a subset of set y
```x & y == x```

Check if sets x and y are disjoint
```x & y == 0```

## Order

Get smallest element in set x (bitset::_Find_first)
```__builtin_ctz(x)```
```countr_zero(x)``` (C++20)

Set with smallest element removed
```x & (x - 1)```

Set with only the smallest element present
```x & -x```

Get largest element in set x (MSB)
```31 - __builtin_clz(x)```
```bit_width(x) - 1``` (C++20)

Get next bit after i (bitset::_Find_next)
```countr_zero(x & ~((1 << (i + 1)) - 1))```

## Misc.

Check if set x is singleton
```x && !(x & (x - 1))```

Base-2 ceiling log of x
```bit_width(x)```

Reverse all bits in set x
```__builtin_bitreverse(x)```

## Iteration

Iterate over all possible sets x (Universal Set)
```cpp
for (int i = 0; i < (1 << n); i++) {
    // do something
}
```

Iterate over all elements in set x
```cpp
for (int i = 0; i < n; i++) if (x & (1 << i)) {
    // do something
}
```

Iterate over all non-empty subsets of set x
```cpp
for (int subset = x; subset; subset = (subset - 1) & x) {
    // do something
}
```

Iterate over all proper supersets of set x
```cpp
int free = ~x & ((1 << n) - 1);
for (int y = free; y; y = (y - 1) & free) {
    int superset = x | y;
    // do something
}
```

Iterate over k-subsets of an n-set in sorted/lexicographical order (Gosper's hack)
```cpp
for (int subset = (1 << k) - 1; subset < (1 << n); [&] () { 
    int c = subset & -subset;
    int r = subset + c;
    subset = r | ((subset ^ r) / 4 / c); 
} ()) {
    // do something
}
```

## Basic Properties

Commutativite Law
```a | b == b | a```
```a ^ b == b ^ a```
```a & b == b & a```

Associative Law
```a | (b | c) == (a | b) | c```
```a ^ (b ^ c) == (a ^ b) ^ c```
```a & (b & c) == (a & b) & c```

Distributivite Law
```a & (b | c) = (a & b) | (a & c)```
```a & (b ^ c) = (a & b) ^ (a & c)```
```(a OP b) << n == (a << n) OP (b << n)```

Identity Element
```a | 0 == a```
```a ^ 0 == 0``` 
```a & ~0 == a```

Zero Element
```a | ~0 == ~0```
```a & 0 == 0```

Inverse
```a ^ a == 0```

## Other Properties

De Morgan's Law
```~(a & b) = ~a | ~b```
```~(a | b) = ~a & ~b```

Set Partition
```a = (a & b) + (a & ~b)``` 

Inclusion-Exclusion
- ```(a + b) == (a | b) + (a & b)```  
- ```(a ^ b) == (a | b) ^ (a & b)```
- ```(a | b) == (a ^ b) + (a & b)```

Misc. Equivalences
- ```a - (a & b) == a ^ (a & b)```
- ```~a & b == (a | b) ^ a```

Derived Properties
- ```a ^ (a & b) == b ^ (a | b)```
- ```(a - b) = (a ^ (a & b)) - (a ^ (a | b))```
- ```(a + b) = (a ^ b) + 2 * (a & b)```