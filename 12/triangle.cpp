// Triangle with sfml
#include <SFML/Graphics.hpp>
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle");
    sf::CircleShape triangle(100, 3);
    triangle.setFillColor(sf::Color::Green);
    triangle.setPosition(400, 300);
    while (window.isOpen()) {
        window.clear();
        window.draw(triangle);
        window.display();
    }
}