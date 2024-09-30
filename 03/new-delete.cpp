#include <iostream>

struct Weapon {
    Weapon() {
        std::cout << "Weapon created" << std::endl;
    }
    ~Weapon() {
        std::cout << "Weapon destroyed" << std::endl;
    }
};

struct Golem {
    // Constructeur
    Golem(int level = 1) {
        std::cout << "Golem created (" << level << ")" << std::endl;    
        weapon = new Weapon();
    }
    // Destructeur
    ~Golem() {
        std::cout << "Golem destroyed" << std::endl;
    }
private:
    Weapon *weapon;
};

int main() {
    std::cout << "World created" << std::endl;
    {
        Golem *golem = new Golem(32);
        delete golem;
    } 
    std::cout << "World destroyed" << std::endl;
}

// int main() {
//     std::cout << "World created" << std::endl;
//     {
//         Golem *golem = new Golem(32);
//     } // golem is NOT destroyed here
//     std::cout << "World destroyed" << std::endl;
// }