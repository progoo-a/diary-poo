/**
 * Afficher un triangle avec SFML
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using vec2 = sf::Vector2f;

auto boidShape(vec2 center, float rotation) {
    float height = 20.f;
    float width = 3.f * height / 4; 
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

struct Particle {
    sf::ConvexShape shape;
    vec2 velocity;

    Particle(sf::ConvexShape shape, vec2 velocity) : shape(shape), velocity(velocity) {}
    void update() {
        auto pos = shape.getPosition();
        pos += velocity;

        if (pos.x < 0 || pos.x > 800) velocity.x = -velocity.x;
        if (pos.y < 0 || pos.y > 600) velocity.y = -velocity.y;
    
        shape.setPosition(pos);

        // Rotate along the velocity vector
        float angle = std::atan2(velocity.y, velocity.x) * 180 / M_PI + 90;
        shape.setRotation(angle);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle");
    Particle boid(boidShape({400, 300}, 45), {1, 1});
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        boid.update();
        window.draw(boid.shape);
        window.display();
    }
}