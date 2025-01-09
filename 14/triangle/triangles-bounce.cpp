/**
 * Afficher un triangle avec SFML
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

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

    Particle(vec2 position, vec2 velocity) : velocity(velocity) {
        shape = boidShape(position, 0);
        shape.setRotation(angle());
    }
    void update() {
        auto pos = shape.getPosition();
        pos += velocity;

        if (pos.x < 0 || pos.x > 800) velocity.x = -velocity.x;
        if (pos.y < 0 || pos.y > 600) velocity.y = -velocity.y;
    
        shape.setPosition(pos);

        // Rotate along the velocity vector
        shape.setRotation(angle());
    }
    float angle() {
        return std::atan2(velocity.y, velocity.x) * 180 / M_PI + 90;
    }
};

vec2 randPosition() {
    return {(float)(rand() % 800 - 1), (float)(rand() % 600 - 1)};
}
vec2 randVelocity() {
    return {(float)rand() / (float)INT_MAX - 1.f, (float)rand() / (float)INT_MAX - 1.f};
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle");
    std::vector<Particle> boids;
    for(int i = 0; i < 10; i++) {
        boids.push_back(Particle(randPosition(), randVelocity()));
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for(auto& boid : boids) {
            boid.update();
            window.draw(boid.shape);
        }
        window.display();
    }
}