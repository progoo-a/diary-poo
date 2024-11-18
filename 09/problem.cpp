#include <iostream>

template <typename T>
struct Base {
    T value;
    Base(T value) : value{value} {}

    auto addOne() {
        return Base<T>(value + 1);
    }
};

struct BaseInt : public Base<int> {
};

int main() {
    Base<int> b{42};
    Base<int> c = b.addOne();

    BaseInt bi{42};
    BaseInt di = bi.addOne();
}

