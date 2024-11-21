#include <iostream>
#include <cmath>

struct Vector {
    double x,y;
    Vector(double x, double y) : x(x), y(y) {}
    double length() const {
        return sqrt(x*x + y*y);
    }

    operator double () const {
        return length();
    }
    // operator int () const {
    //     return x;
    // }
    // operator long() const {
    //     return y;
    // }
};

int main() {
    Vector v{3,4};
    if (v > 23.2) {
        std::cout << "Vector is longer than 23.2" << std::endl;
    }
}