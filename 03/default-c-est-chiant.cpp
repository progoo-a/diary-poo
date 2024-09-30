#include <iostream>

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

int main() {
    Point p = {3,4};
    Point q = p;
    Point r;
    q = p;
}