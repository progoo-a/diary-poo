/**
 * Afficher des boids qui rebondissent
 * Un boid montre ses voisins
 */
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
using vec2 = sf::Vector2f;

const float WIDTH = 1200;
const float HEIGHT = 800;
const float SEPARATION_WEIGHT = 0.02f;
const float COHESION_WEIGHT = 0.02f;
const float ALIGNMENT_WEIGHT = 0.01f;
const float MAX_SPEED = 5.0f;
const float NEIGHBOR_RADIUS = 50.0f;


vec2 operator/(const vec2 &v, float scalar) {
  return vec2(v.x / scalar, v.y / scalar);
}
auto operator/=(vec2 &v, float scalar) {
  v.x /= scalar;
  v.y /= scalar;
  return v;
}

sf::Color blue(50, 129, 168);

auto boidShape(vec2 center, float rotation) {
  float height = 8.f;
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

float toroidalDistance(vec2 a, vec2 b) {
  float dx = std::abs(a.x - b.x);
  float dy = std::abs(a.y - b.y);
  float width = WIDTH;
  float height = HEIGHT;
  dx = std::min(dx, width - dx);
  dy = std::min(dy, height - dy);
  return std::sqrt(dx * dx + dy * dy);
}

float distance(vec2 a, vec2 b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}

void toroidalWrap(vec2 &pos) {
  pos.x = std::fmod(pos.x + WIDTH, WIDTH);
  pos.y = std::fmod(pos.y + HEIGHT, HEIGHT);
}

vec2 repulsiveForce(vec2 pos) {
  float left = pos.x, right = WIDTH - pos.x;
  float top = pos.y, bottom = HEIGHT - pos.y;
  float d = 50.0f;

  vec2 repulsiveForce(0, 0);
  repulsiveForce.x += 1.0f / std::pow(std::max(left - d, 1.0f), 2);
  repulsiveForce.x -= 1.0f / std::pow(std::max(right - d, 1.0f), 2);
  repulsiveForce.y += 1.0f / std::pow(std::max(top - d, 1.0f), 2);
  repulsiveForce.y -= 1.0f / std::pow(std::max(bottom - d, 1.0f), 2);

  return 0.5f * repulsiveForce;
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
    shape.setPosition(pos);
    shape.setRotation(angle());
  }

  float angle() { return std::atan2(velocity.y, velocity.x) * 180 / M_PI + 90; }

  float getSpeed() {
    return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
  }

  void setSpeed(float magnitude) {
    float speed = getSpeed();
    if (speed < 1e-5f)
      return;
    velocity.x *= magnitude / speed;
    velocity.y *= magnitude / speed;
  }
};

vec2 randPosition() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> distX(0, WIDTH);
  static std::uniform_real_distribution<float> distY(0, HEIGHT);
  return {distX(gen), distY(gen)};
}

vec2 randVelocity() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dist(-MAX_SPEED, MAX_SPEED);
  return {dist(gen), dist(gen)};
}


int main() {
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids");
  sf::Clock clock;
  const float frameTime = 1.0f / 60.0f;
  float elapsed = 0;

  std::vector<Particle> boids;
  for (int i = 0; i < 200; i++) {
    boids.emplace_back(randPosition(), randVelocity());
  }

  bool wrap = false;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
          window.close();
        if (event.key.code == sf::Keyboard::Space) {
          wrap = !wrap;
        }
      }
    }
    window.clear();

    elapsed += clock.restart().asSeconds();
    while (elapsed >= frameTime) {
      elapsed -= frameTime;

      for (auto &boid : boids) {
        vec2 pos = boid.shape.getPosition();

        // Find neighbors
        std::vector<Particle *> neighbors;
        for (auto &other : boids) {
          auto func = wrap ? toroidalDistance : distance;
          if (func(pos, other.shape.getPosition()) < NEIGHBOR_RADIUS && &other != &boid)
            neighbors.push_back(&other);
        }

        // Apply rules
        vec2 separation_factor, cohesion_factor, alignment_factor;
        for (auto &neighbor : neighbors) {
          separation_factor += (pos - neighbor->shape.getPosition());
          cohesion_factor += neighbor->shape.getPosition();
          alignment_factor += neighbor->velocity;
        }
        const int count = neighbors.size();
        if (count > 0) {
          separation_factor /= count;
          cohesion_factor /= count;
          alignment_factor /= count;

          boid.velocity += separation_factor * SEPARATION_WEIGHT;
          boid.velocity += (cohesion_factor - pos) * COHESION_WEIGHT;
          boid.velocity += alignment_factor * ALIGNMENT_WEIGHT;
        }

        // Boundaries
        if (!wrap) {
          auto force = repulsiveForce(pos);
          boid.velocity += force;
        } else {
            toroidalWrap(pos);
            boid.shape.setPosition(pos);
        }

        // Limit speed
        if (boid.getSpeed() > MAX_SPEED)
          boid.setSpeed(MAX_SPEED);

        // Update boid
        boid.update();
        window.draw(boid.shape);
      }
      window.display();
    }
  }
}
