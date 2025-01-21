#include <iostream>
using namespace std;
struct A
{
    A() { cout << 0; }
    virtual void foo() const
    {
        cout << 1;
    }
    void bar() const { cout << 2; }
    virtual ~A() { cout << 3; }
};
struct B : public A
{
    B() { cout << 4; }
    void foo() const override { cout << 5; }
    void bar() const { cout << 7; }
    virtual ~B() override { cout << 6; }
};
int main()
{
    A *ptr = new B;
    ptr->foo();
    ptr->bar();
    delete ptr;
}