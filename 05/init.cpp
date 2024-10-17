#include <iostream>

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {
        std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }
    Point(const Point& p) : x(p.x), y(p.y) {
        std::cout << "Point(" << p.x << ", " << p.y << ")" << std::endl;
    }
};

struct Circle {
    Point center;
    Circle(): center{42,23} {
        std::cout << "Circle()" << std::endl;
        //center = Point(42, 23);
    }
};

int main() {
    Point p{1, 2};
    Circle c;
}