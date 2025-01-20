#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

class Player;
class SmallBall;
class EntityVisitor;

class Entity {
   public:
    virtual void accept(EntityVisitor& visitor, std::shared_ptr<Entity> self) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::CircleShape& getShape() = 0;
    virtual ~Entity() = default;
};

class EntityVisitor {
   public:
    virtual void visit(Player& player, std::shared_ptr<Entity> self) = 0;
    virtual void visit(SmallBall& ball, std::shared_ptr<Entity> self) = 0;
};

class Player : public Entity {
    sf::CircleShape shape;
    float speed;

   public:
    Player(float x, float y) : speed(200.0f) {
        shape.setRadius(20.0f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(x, y);
        shape.setOrigin(20.0f, 20.0f);  // origin au centre
    }

    void accept(EntityVisitor& visitor, std::shared_ptr<Entity> self) override {
        visitor.visit(*this, self);
    }

    void update(float deltaTime) override {
        sf::Vector2f movement(0.0f, 0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * deltaTime;

        // Contrôler les bords de l'écran
        sf::Vector2f newPos = shape.getPosition() + movement;
        if (newPos.x - shape.getRadius() < 0) newPos.x = shape.getRadius();
        if (newPos.y - shape.getRadius() < 0) newPos.y = shape.getRadius();
        if (newPos.x + shape.getRadius() > 800) newPos.x = 800 - shape.getRadius();
        if (newPos.y + shape.getRadius() > 600) newPos.y = 600 - shape.getRadius();

        shape.setPosition(newPos);
    }

    void draw(sf::RenderWindow& window) override { window.draw(shape); }

    sf::CircleShape& getShape() override { return shape; }

    void grow(float radiusIncrease) {
        float newRadius = shape.getRadius() + radiusIncrease;
        shape.setRadius(newRadius);
        shape.setOrigin(newRadius, newRadius);  // Mettre à jour l'origine
    }
};

class SmallBall : public Entity {
    sf::CircleShape shape;

   public:
    SmallBall(float x, float y) {
        shape.setRadius(10.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        shape.setOrigin(10.0f, 10.0f);  // origin au centre
    }

    void accept(EntityVisitor& visitor, std::shared_ptr<Entity> self) override {
        visitor.visit(*this, self);
    }

    void update(float deltaTime) override {}
    void draw(sf::RenderWindow& window) override { window.draw(shape); }
    sf::CircleShape& getShape() override { return shape; }
    float getRadius() const { return shape.getRadius(); }
};

class CollisionVisitor : public EntityVisitor {
    Player* player;
    std::vector<std::shared_ptr<Entity>>& entities;
    std::vector<std::shared_ptr<Entity>> toRemove;

   public:
    CollisionVisitor(Player* player, std::vector<std::shared_ptr<Entity>>& entities)
        : player(player), entities(entities) {}

    void visit(Player& /*player*/, std::shared_ptr<Entity> /*self*/) override {
        // No special collision behavior for the player
    }

    void visit(SmallBall& ball, std::shared_ptr<Entity> self) override {
        if (player->getShape().getGlobalBounds().intersects(ball.getShape().getGlobalBounds())) {
            float ballRadius = ball.getRadius();
            float ballArea = M_PI * ballRadius * ballRadius;
            float radiusIncrease = std::sqrt(ballArea / M_PI);
            player->grow(radiusIncrease);
            toRemove.push_back(self);
        }
    }

    void applyCollisions() {
        for (auto& entity : toRemove) {
            auto it = std::find(entities.begin(), entities.end(), entity);
            if (it != entities.end()) entities.erase(it);
        }
        toRemove.clear();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visitor Pattern Game");
    window.setFramerateLimit(60);

    std::vector<std::shared_ptr<Entity>> entities;

    auto player = std::make_shared<Player>(400.0f, 300.0f);
    entities.push_back(player);

    for (int i = 0; i < 10; ++i) {
        float x = static_cast<float>(rand() % 800);
        float y = static_cast<float>(rand() % 600);
        entities.push_back(std::make_shared<SmallBall>(x, y));
    }

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed) window.close();

        for (auto& entity : entities) entity->update(deltaTime);

        CollisionVisitor collisionVisitor(player.get(), entities);

        for (auto& entity : entities) entity->accept(collisionVisitor, entity);

        collisionVisitor.applyCollisions();

        // Rendu
        window.clear();
        for (auto& entity : entities) {
            entity->draw(window);
        }
        window.display();
    }
}
