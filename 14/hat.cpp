#include <iostream>

struct Human;

struct Hat {
    int serial_number;
    Human &human;
    Hat(int serial_number, Human &human);
    std::string whoWears();
};

struct Human {
    std::string name;
    Hat *hat;
    Human(std::string name) : name{name}, hat(nullptr) {}
    int wearHat(Hat &hat) { 
        this->hat = &hat; 
        return hat.serial_number;
    }
};


Hat::Hat(int serial_number, Human &human) : serial_number{serial_number}, human(human) {}

std::string Hat::whoWears() { return human.name; }

