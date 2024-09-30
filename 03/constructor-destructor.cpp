#include <iostream>

struct Golem {
    // Constructeur
    Golem(int level = 1) {
        std::cout << "Golem created (" << level << ")" << std::endl;    
    }
    // Destructeur
    ~Golem() {
        std::cout << "Golem destroyed" << std::endl;
    }
};

int main() {
    std::cout << "World created" << std::endl;
    {
        Golem golem(32);
    } // golem is destroyed here
    std::cout << "World destroyed" << std::endl;
}