#include <memory>
#include <iostream>
#include <vector>

struct Golem {
    int health;
    Golem(int health) : health(health) {}
    virtual void attack() = 0;

    virtual ~Golem() {
        std::cout << "Golem destroyed" << std::endl;
    }
};

struct GolemIce : public Golem {
    GolemIce(int health) : Golem(health) {}
    void attack() override {
        std::cout << "Ice attack" << std::endl;
    }
};

struct GolemFire : public Golem {
    GolemFire(int health) : Golem(health) {}
    void attack() override {
        std::cout << "Fire attack" << std::endl;
    }
    void specialFireAttack() {
        std::cout << "Special fire attack" << std::endl;
    }
};

int main() {
    std::shared_ptr<Golem> g;
    {
        std::vector<std::shared_ptr<Golem>> golems;
        golems.push_back(std::make_shared<GolemIce>(100));
        golems.push_back(std::make_shared<GolemFire>(200));
        g = golems[1];
    }

    std::cout << "----" << std::endl;

}