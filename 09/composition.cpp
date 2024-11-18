#include <iostream>
#include <string>

struct IFlyer {
    virtual void fly() const = 0;
};

struct ISwimmer { virtual void swim() const = 0;
};

// Trait : Interface pour tirer
struct IShooter {
    virtual void shoot() const = 0; // Méthode purement virtuelle
};

// Classe de base pour les personnages
struct Character {
public:
    Character(const std::string& name) : name(name) {}
    virtual ~Character() = default;

    void introduce() const {
        std::cout << "Hi, I am " << name << "!" << std::endl;
    }

private:
    std::string name;
};

// Un personnage qui peut voler et tirer
struct FlyingShooter : public Character, public IFlyer, public IShooter {
public:
    FlyingShooter(const std::string& name) : Character(name) {}

    // Implémentation des traits
    void fly() const override {
        std::cout << "I am flying like a bird!" << std::endl;
    }

    void shoot() const override {
        std::cout << "I am shooting lasers!" << std::endl;
    }
};

// Un personnage qui peut nager
struct SwimmingCharacter : public Character, public ISwimmer {
public:
    SwimmingCharacter(const std::string& name) : Character(name) {}

    // Implémentation du trait
    void swim() const override {
        std::cout << "I am swimming like a fish!" << std::endl;
    }
};

int main() {
    // Créons un personnage qui vole et tire
    FlyingShooter eagle("Eagle");
    eagle.introduce();
    eagle.fly();
    eagle.shoot();

    std::cout << std::endl;

    // Créons un personnage qui nage
    SwimmingCharacter fish("Fish");
    fish.introduce();
    fish.swim();

    return 0;
}
