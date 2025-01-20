#include <iostream>

class Foo;
class Bar;

class IVisitor {
public:
    virtual void visitFoo(Foo* foo) = 0;
    virtual void visitBar(Bar* bar) = 0;
};

class IElement {
    virtual void accept(IVisitor& visitor) = 0;
};

class Foo : public IElement {
public:
    int data = 42;
    void accept(IVisitor& visitor) override {
        visitor.visitFoo(this);
    }
};

class Bar : public IElement {
public:
    int data = 23;
    void accept(IVisitor& visitor) override {
        visitor.visitBar(this);
    }
};

class VisitorVerbose : public IVisitor {
public:
    void visitFoo(Foo* foo) override {
        std::cout << "Visiting Foo (data = " << foo->data << ")" << std::endl;
    }

    void visitBar(Bar* bar) override {
        std::cout << "Visiting Bar (date = " << bar->data << ")" << std::endl;
    }
};

class VisitorQuiet : public IVisitor {
public:
    void visitFoo(Foo* foo) override {
        std::cout << foo->data << std::endl;
    }

    void visitBar(Bar* bar) override {
        std::cout << bar->data << std::endl;
    }
};



int main() {
    Foo foo;
    Bar bar;

    VisitorVerbose verbose;
    VisitorQuiet quiet;

    foo.accept(verbose);
    bar.accept(verbose);

    foo.accept(quiet);
    bar.accept(quiet);
}
