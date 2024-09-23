#include <math.h>

struct Vector {
    double x, y;
    double length() {
        return sqrt(x*x + y*y)
    }
    Vector operator+(const Vector &other) {
        Vector v = {x + other.x, y + other.y};
    }

    bool isSame(const Vector &other) {
        return x == other.x && y == other.y;
    }
};

int main() {
    Vector u = {3,6}, v = { 7, 12};
    Vector w = u + v;
    printf("Est-ce que les deux vecteurs sont les mêmes : %d", u.isSame(v));
}