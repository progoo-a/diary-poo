#include <iostream>

class A {
    public:
    A() {
        std::cout << "A created" << std::endl;
    }
    A(const A& a) {
        std::cout << "A copied" << std::endl;
    }
    ~A() {
        std::cout << "A destroyed" << std::endl;
    }
    A& operator=(const A& a) {
        std::cout << "A assigned" << std::endl;
        this->x = a.x;
        this->y = a.y;
        return *this;
    }

    int x,y;
};

int main() {
    A a; // A created
    A b = a; // A copied
    A c(a); // A copied

    A d; // A created
    d = a; // A assigned (opérateur d'affectation =)

} // A destroyed x 4