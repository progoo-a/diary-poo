/**
 * Draw a circle with different vertex color using triangle fan
 */
#include <SFML/Graphics.hpp>
#include <cmath>

#define N 16
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle Fan");
    sf::VertexArray circle(sf::TriangleFan, N);
    circle[0].position = sf::Vector2f(400, 300);
    circle[0].color = sf::Color::White;
    for (int i = 1; i < N; i++) {
        float angle = i * 2 * 3.14159f / N;
        circle[i].position = sf::Vector2f(
            400 + std::cos(angle) * 100, 300 + std::sin(angle) * 100);
        circle[i].color = sf::Color(255, 255, 255, 128);
    }
    while (window.isOpen()) {
        window.clear();
        window.draw(circle);
        window.display();
    }
}