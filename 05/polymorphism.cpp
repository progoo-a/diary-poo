#include <iostream> 
#include <vector>

struct Shape {
    float area;
    int corners;

    void draw() {
        std::cout << "Shape" << std::endl;
    }
};

struct Triangle : public Shape {
    void draw() {
        std::cout << "Triangle" << std::endl;
    }
};
struct Square : public Shape {
    void draw() {
        std::cout << "Square" << std::endl;
    }
};
struct Pentagon : public Shape {
    void draw() {
        std::cout << "Pentagon" << std::endl;
    }
};
struct Hexagon : public Shape {
    void draw() {
        std::cout << "Hexagon" << std::endl;
    }
};

Shape* shapeFactory(int corners, float area) {
    switch (corners) {
        case 3:
            return new Triangle();
        case 4:
            return new Square();
        case 5:
            return new Pentagon();
        case 6:
            return new Hexagon();
        default:
            throw std::invalid_argument("Invalid number of corners");
    }
}

int main() {
    std::vector<Shape*> shapes;
    for (int i = 0; i < 10; ++i) {
        // Random value between 3 and 6
        int corners = 3 + rand() % 4;
        shapes.push_back(shapeFactory(corners, 10.0));
    }

    for (auto shape : shapes) {
        shape->draw();
    }
}
