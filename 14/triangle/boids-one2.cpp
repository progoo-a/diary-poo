/**
 * Afficher des boids qui rebondissent
 * Un boid montre ses voisins
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>

using vec2 = sf::Vector2f;

sf::Color blue(50, 129, 168);

auto boidShape(vec2 center, float rotation) {
    float height = 20.f;
    float width = 3.f * height / 4; 
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

    float getSpeed() {
        return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    }

    void setSpeed(float magnitude) {
        float speed = getSpeed();
        velocity.x *= magnitude / speed;
        velocity.y *= magnitude / speed;
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
    for(int i = 0; i < 20; i++) {
        boids.push_back(Particle(randPosition(), randVelocity()));
    }
    boids[0].shape.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // Find neighbors for boids[0]
        float radius = 100;
        sf::CircleShape circle(radius);
        vec2 pos = boids[0].shape.getPosition();
        circle.setPosition(pos.x - radius, pos.y - radius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::Yellow);
        circle.setOutlineThickness(1);
        window.draw(circle);

        vec2 separation_factor;
        vec2 cohesion_factor;
        vec2 alignment_factor;
        int count = 0;
        for(auto& boid : boids) {
            float dist2 = std::pow(boid.shape.getPosition().x - pos.x, 2) + std::pow(boid.shape.getPosition().y - pos.y, 2);
            if (dist2 < radius*radius && &boid != &boids[0]) {
                boid.shape.setFillColor(sf::Color::Yellow);
                // Separation, Cohesion, Alignment
                separation_factor += (pos - boid.shape.getPosition()) / dist2;
                cohesion_factor += boid.shape.getPosition();
                alignment_factor += boid.velocity;
                count++;
            } else {
                boid.shape.setFillColor(blue);
            }
        }
        if (count > 0) {
            separation_factor.x /= count;
            separation_factor.y /= count;
            cohesion_factor.x /= count;
            cohesion_factor.y /= count;
            alignment_factor.x /= count;
            alignment_factor.y /= count;
        }
        boids[0].velocity += separation_factor * 0.001f;
        boids[0].velocity += (cohesion_factor - pos) * 0.001f;
        boids[0].velocity += alignment_factor * 0.001f;
        
        if (boids[0].getSpeed() > 1.5) {
            boids[0].setSpeed(1.5);
        }

        for(auto& boid : boids) {
            boid.update();
            window.draw(boid.shape);
        }
        window.display();
    }
}