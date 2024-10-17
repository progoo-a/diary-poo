
struct Bar {
    Bar(int a, int b) {}
};

class Foo {
    const int a, b;
    Bar bar;
public:
    Foo(int a, int b) : a(a), b(b), bar(a,b) {
    }
};

int main() {
    int a(42);
}