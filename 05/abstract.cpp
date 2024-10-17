

struct Foo {
    Foo() {}
    virtual void a();
    void b() {};
};

void Foo::a() {}

int main () {
    Foo foo;
}

