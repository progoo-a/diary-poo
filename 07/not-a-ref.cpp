
#include <iostream>
struct Foo {
    int x,y;
    Foo() { std::cout << "Default constructor" << std::endl; }
    Foo(const Foo&) { std::cout << "Copy constructor" << std::endl; }
    ~Foo() { std::cout << "Destructor" << std::endl; }
};

Foo factory() {
    return Foo{};
}

int main() {
    Foo f = factory();
}