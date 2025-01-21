#include <iostream>

class Animal {
public:
    virtual ~Animal() {}
};

class Dog : public Animal {};
class Cat : public Animal {};

int main() {
    // RTTI Demo
    Animal* a = new Dog();

    // Using dynamic cast
    if (dynamic_cast<Dog*>(a)) {
        std::cout << "It's a dog!" << std::endl;
    } else {
        std::cout << "It's not a dog!" << std::endl;
    }
    // Using typeid
    if (typeid(*a) == typeid(Dog)) {
        std::cout << "It's a dog!" << std::endl;
    } else {
        std::cout << "It's not a dog!" << std::endl;
    }
}