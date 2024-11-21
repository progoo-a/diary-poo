#include <iostream>

// CRTP (Curiously Reccuring Template Pattern)
template <typename T, typename Derived>
struct Base {
    T value;
    Base(T value) : value{value} {}

    auto addOne() {
        return Derived(value + 1);
    }
};

struct BaseInt : public Base<int, BaseInt> {
};

int main() {
    // Base b{42};
    // Base c = b.addOne();

    BaseInt bi{42};
    BaseInt di = bi.addOne(); // Erreur
}

