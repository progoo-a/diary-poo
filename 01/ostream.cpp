#include <ostream>
#include <iostream>
#include <string> 

struct Person {
    std::string name;
    Person(const std::string& name, int age) {
        this->name = name;
        this->age = age;
    }

    int age;
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person(name: " << p.name << ", age: " << p.age << ")";
    return os;
}

int main() {
    Person bob("Bob", 42);

    std::cout << bob;
}

