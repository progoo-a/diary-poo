/**
 * Afficher un triangle avec SFML
 */
#include <SFML/Graphics.hpp>
#include <iostream>

using vec2 = sf::Vector2f;

auto boidShape(vec2 center, float rotation) {
    int height = 100;
    int width = 3 * height / 4; 
    sf::Color blue(50, 129, 168);
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, vec2(0, -height));
    triangle.setPoint(1, vec2(-width, height));
    triangle.setPoint(2, vec2(+width, height));
    triangle.setOrigin(0, height/3);
    triangle.setPosition(center);
    triangle.setRotation(rotation);
    triangle.setFillColor(blue);
    return triangle;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle");
    auto boid = boidShape({400, 300}, 45);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        boid.setRotation(boid.getRotation() + 1);
        window.draw(boid);
        window.display();
    }
}