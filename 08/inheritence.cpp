#include <iostream>

struct Animal {
    int age;
    virtual void speak() { std::cout << "(barely audible)\n"; }
};

struct Dog : public Animal {
    void speak() override { std::cout << "Woof\n"; }
};

struct Cat : public Animal {
    void speak() override { std::cout << "Meow\n"; }
};

int main() {
    Animal *p;
    if (rand() % 2) 
        p = new Cat;
    else 
        p = new Dog;
    p->speak();

    // Animal a;
    // Dog d;
    // Cat c;

    // a.speak(); // Animal
    // d.speak(); // Woof
    // c.speak(); // Meow


}
