# Semaine 10/16

## Vector v.s. Array

```cpp
#include <vector>
#include <array>
#include <iostream>

class Foo {
    std::vector<int> data = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
};

class Bar {
    std::array<int, 16> data = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
};

int main() {
    Foo foo;
    Bar bar;
    std::cout << sizeof(foo) << "\n" << sizeof(bar) << "\n";
}
```

La sortie est 24 et 64. 

## Danger des vecteurs

Rappelez-vous un vecteur est un tableau dynamique. 

```cpp
std::vector<int> v;
v.append(1);
int *p = &v[0];
for (int i = 0; i < 1000000; i++) v.append(1);
std::cout << *p << "\n";
```