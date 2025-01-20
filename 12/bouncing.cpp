#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Ball
{
    float mass;       // In kg
    float elasticity; // Coefficient of restitution
public:
    Ball(sf::Vector2f position) : position{position}, radius{16 + rand() % 9}
    {
        velocity = {(rand() % 201 - 100) * 0.5f, (rand() % 201 - 100) * 0.5f};
    }
    Ball(float radius, sf::Vector2f position, sf::Vector2f velocity)
        : radius(radius), position(position), velocity(velocity),
          mass(4.0f / 3.0f * 3.14159f * radius * radius * radius),
          elasticity(0.9f)
    {
        {
            circle.setRadius(radius);
            circle.setFillColor(getRandomColor());
            circle.setOrigin(radius, radius); // Centrer le cercle
            circle.setPosition(position);
        }

        void update(float dt)
        {
            position += velocity * dt;
            circle.setPosition(position);
        }

        void draw(sf::RenderWindow & window)
        {
            window.draw(circle);
        }

        void bounce(Ball & other)
        {
            sf::Vector2f delta = position - other.position;
            float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            if (distance == 0.f)
                return; // Éviter la division par zéro

            float overlap = radius + other.radius - distance;
            if (overlap > 0)
            {
                // Résolution de chevauchement
                sf::Vector2f direction = delta / distance;
                position += direction * overlap / 2.0f;
                other.position -= direction * overlap / 2.0f;

                // Résolution des vitesses (conservation du moment)
                float m1 = mass;
                float m2 = other.mass;

                sf::Vector2f relativeVelocity = velocity - other.velocity;
                float dot = relativeVelocity.x * direction.x + relativeVelocity.y * direction.y;

                if (dot > 0)
                {
                    sf::Vector2f impulse = direction * (2 * dot) / (m1 + m2);

                    velocity -= impulse * (m2 / (m1 + m2));
                    other.velocity += impulse * (m1 / (m1 + m2));
                }
            }
        }

        void bounce(const sf::Vector2f &normal)
        {
            float dot = velocity.x * normal.x + velocity.y * normal.y;
            velocity -= (1 + elasticity) * normal * dot;
        }

        void applyGravity(float dt)
        {
            velocity.y += 9.81f * dt;
        }

        sf::CircleShape circle;
        float radius;
        sf::Vector2f position;
        sf::Vector2f velocity;

    private:
        // Générer une couleur aléatoire pour chaque balle
        sf::Color getRandomColor()
        {
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            return sf::Color(r, g, b);
        }
    };

    int main()
    {
        srand(static_cast<unsigned>(time(0)));

        sf::RenderWindow window(sf::VideoMode(1000, 800), "Bouncing Balls");
        window.setFramerateLimit(60);

        std::vector<Ball> balls;
        for (int i = 0; i < 10; ++i)
        {
            balls.emplace_back(sf::Vector2f(rand() % 1000, rand() % 800));
        }

        bool gravity = false;
        bool mousePressed = false;

        while (window.isOpen())
        {
            sf::Time dt = sf::seconds(1.0f / 60.0f);
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::G)
                    {
                        gravity = !gravity;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        mousePressed = true;
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        mousePressed = false;
                    }
                }
            }

            if (mousePressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                balls.push_back(createRandomBall(sf::Vector2f(static_cast<float>(mousePosition.x),
                                                              static_cast<float>(mousePosition.y))));
            }

            for (Ball &ball : balls)
            {
                if (gravity)
                {
                    ball.applyGravity(dt.asSeconds());
                }
                ball.update(dt.asSeconds());
            }

            for (size_t i = 0; i < balls.size(); i++)
            {
                for (size_t j = i + 1; j < balls.size(); j++)
                {
                    balls[i].bounce(balls[j]);
                }
            }

            for (Ball &ball : balls)
            {
                if (ball.position.x < ball.radius)
                {
                    ball.position.x = ball.radius;
                    ball.bounce(sf::Vector2f(1, 0));
                }
                if (ball.position.x > 800 - ball.radius)
                {
                    ball.position.x = 800 - ball.radius;
                    ball.bounce(sf::Vector2f(-1, 0));
                }
                if (ball.position.y < ball.radius)
                {
                    ball.position.y = ball.radius;
                    ball.bounce(sf::Vector2f(0, 1));
                }
                if (ball.position.y > 600 - ball.radius)
                {
                    ball.position.y = 600 - ball.radius;
                    ball.bounce(sf::Vector2f(0, -1));
                }
            }

            window.clear();

            for (Ball &ball : balls)
            {
                ball.draw(window);
            }

            window.display();
        }
    }
