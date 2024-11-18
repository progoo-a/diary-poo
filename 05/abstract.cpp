

struct Foo {
    Foo() {}
    virtual void a() = 0;
    void b() {};
};

struct Bar : public Foo {
    void a() override {}
    void b() {}
};

// void Foo::a() {}

int main () {
    Bar bar;
    bar.b(); // b de bar
    Foo *p = &bar;
    p->b(); // b de foo sans le virtual ou, b de bar avec le virtual
}

