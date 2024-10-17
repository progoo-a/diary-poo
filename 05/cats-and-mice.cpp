#include <iostream>
#include <vector>

// Interface 
// Une interface est une classe dont toutes les méthodes
// sont virtuelles pures.
class Animal {
    protected:
    std::string name;
    public:
    Animal(std::string name) : name{name} {}
    virtual void eat() = 0; // Méthode virtuelle pure 
    virtual void speak() = 0;
    virtual void sleep() = 0;
};

struct Cat : public Animal {
    int griffes = 10;

    Cat(std::string name) : Animal(name) { std::cout << "New 🐈\n"; }
    void sleep() override { std::cout << name << "🐈 Sleep\n"; }
    void eat() override { std::cout << name << "🐈 Eat\n"; }
    void speak() override { std::cout << name << "🐈 Speak\n"; }
};

struct Mouse : public Animal {
    Mouse(std::string name) : Animal(name)  { std::cout << "New 🐁\n"; }
    void sleep() override { std::cout << name << "🐁 Sleep\n"; }
    void eat() override { std::cout << name << "🐁 Eat\n"; }
    void speak() override { std::cout << name << "🐁 Speak\n"; }    
};

void happyLife(Animal *animal) {
    animal->eat();
    animal->speak();
    animal->sleep();
}

std::string names[] = {"A", "B", "C", "D", "E"};

int main() {
    Cat cat("Felix");
    Mouse mouse("Mickey");

    std::vector<Animal *> zoo;
    for (int i = 0; i < 5; i++) {
        if (rand() % 2)
            zoo.push_back(new Cat(names[i]));
        else
            zoo.push_back(new Mouse(names[i]));
    }

    for (auto &animal : zoo) {
        animal->eat();
    }
}
/**
 * Class A : public B
 * A hérite de tout B, ce qui est public reste public, ce qui est protégé
 * reste protégé et ce qui est privé reste privé.
 * 
 * Class A : protected B
 * A hérite de tout B, ce qui est public devient protégé, ce qui est protégé
 * reste protégé et ce qui est privé reste privé.
 * 
 * Class A : private B
 * A hérite de tout B
 *   public -> privé
 *   protected -> privé
 *   privé -> privé (pas accès)
 * 
 * ------
 * 
 * public : accessible à tout le monde 
 * protégé : accessible uniquement de l'intérieur ou des classes dérivées
 * privé: accessible uniquement de l'intérieur de la classe
 */