

struct Foo {
    Foo() {
        p = new int(42);
    }
    Foo(const Foo& foo) = default;
    int *p; 
    int a; 
};

int main() {
    Foo foo1;
    foo1.a = 42;
    
    Foo foo2 = foo1; // Constructeur par copie (copie de surface)
    *(foo2.p) = 23; // foo1.p et foo2.p pointent vers la même adresse mémoire
}
