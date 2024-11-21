#include <concepts>

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T>
auto add(T a, T b) {

    return a + b;
}

struct Foo {
};

int main() {
    Foo a, b;

    Foo c = add(a, b);
}