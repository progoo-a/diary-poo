/**
 * Afficher des boids qui rebondissent
 * Un boid montre ses voisins
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <climits>
#include <random>

using vec2 = sf::Vector2f;

sf::Color blue(50, 129, 168);

auto boidShape(vec2 center, float rotation)
{
    float height = 12.f;
    float width = 3.f * height / 4;
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, vec2(0, -height));
    triangle.setPoint(1, vec2(-width, height));
    triangle.setPoint(2, vec2(+width, height));
    triangle.setOrigin(0, height / 3);
    triangle.setPosition(center);
    triangle.setRotation(rotation);
    triangle.setFillColor(blue);
    return triangle;
}

struct Particle
{
    sf::ConvexShape shape;
    vec2 velocity;

    Particle(vec2 position, vec2 velocity) : velocity(velocity)
    {
        shape = boidShape(position, 0);
        shape.setRotation(angle());
    }
    void update()
    {
        auto pos = shape.getPosition();
        pos += velocity;

        if (pos.x < 0 || pos.x > 800)
            velocity.x = -velocity.x;
        if (pos.y < 0 || pos.y > 600)
            velocity.y = -velocity.y;

        shape.setPosition(pos);
        shape.setRotation(angle());
    }
    float angle()
    {
        return std::atan2(velocity.y, velocity.x) * 180 / M_PI + 90;
    }

    float getSpeed()
    {
        return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    }

    void setSpeed(float magnitude)
    {
        float speed = getSpeed();
        if (speed < 1e-5f) return;
        velocity.x *= magnitude / speed;
        velocity.y *= magnitude / speed;
    }
};

vec2 randPosition() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> distX(0, 800);
    static std::uniform_real_distribution<float> distY(0, 600);
    return {distX(gen), distY(gen)};
}

vec2 randVelocity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dist(-1.f, 1.f);
    return {dist(gen), dist(gen)};
}

const float SEPARATION_WEIGHT = 0.0035f;
const float COHESION_WEIGHT = 0.0035f;
const float ALIGNMENT_WEIGHT = 0.002f;
const float MAX_SPEED = 1.0f;
const float NEIGHBOR_RADIUS = 70.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Triangle");

    std::vector<Particle> boids;
    for (int i = 0; i < 100; i++)
    {
        boids.push_back(Particle(randPosition(), randVelocity()));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        float radius = NEIGHBOR_RADIUS ;
        for (auto &boid : boids)
        {
            vec2 pos = boid.shape.getPosition();
            std::vector<Particle*> neighbors;

            for (auto &other : boids) {
                float dx = other.shape.getPosition().x - pos.x;
                float dy = other.shape.getPosition().y - pos.y;
                float dist2 = dx * dx + dy * dy;
                if (dist2 < radius * radius && &other != &boid)
                    neighbors.push_back(&other);
            }

            vec2 separation_factor(0, 0);
            vec2 cohesion_factor(0, 0);
            vec2 alignment_factor(0, 0);
            for (auto &neighbor : neighbors)
            {
                separation_factor += (pos - neighbor->shape.getPosition());
                cohesion_factor += neighbor->shape.getPosition();
                alignment_factor += neighbor->velocity;
            }

            const int count = neighbors.size();
            if (count > 0)
            {
                separation_factor.x /= count;
                separation_factor.y /= count;
                cohesion_factor.x /= count;
                cohesion_factor.y /= count;
                alignment_factor.x /= count;
                alignment_factor.y /= count;

                boid.velocity += separation_factor * SEPARATION_WEIGHT ;
                boid.velocity += (cohesion_factor - pos) * COHESION_WEIGHT ;
                boid.velocity += alignment_factor * ALIGNMENT_WEIGHT ;
            }

            if (boid.getSpeed() > MAX_SPEED) boid.setSpeed(MAX_SPEED);
        }

        for (auto &boid : boids) {
            boid.update();
            window.draw(boid.shape);
        }
        window.display();
    }
}
