#include <iostream>

using namespace std;
struct Base {
    int value;
    Base() { value = rand() % 42; cout << "Base()\n"; }
    ~Base() { cout << "~Base()\n"; }
};

struct A: public virtual Base {
    A() { cout << "A()\n"; }
    ~A() { cout << "~A()\n"; }

    auto aget() { return value; }
};
struct B: public virtual Base {
    B() { cout << "B()\n"; }
    ~B() { cout << "~B()\n"; }

    auto bget() { return value; }
};

// Multiple Inheritence
struct C: public A, public B {
    C() { cout << "C()\n"; }
    ~C() { cout << "~C()\n"; }
};

int main() {
    C c;
    cout << c.aget() << "\n";
    cout << c.bget() << "\n";
}