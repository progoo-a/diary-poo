#include <string>
#include <iostream>

std::string digit2name[] = {
    "Un", "Deux", "Trois", "Quatre", "Cinq", "Six", "Sept", "Huit", "Neuf"
};

int name2digit[] = {
   1, 2, 3, 4, 5, 6, 7, 8, 9
};


int hash(std::string name) {
    int hash = 0x42accef7;
    int i = 0;
    for (char c : name) {
        hash ^= c << i++;
    }
    return hash % 100;
}

int main() {
    int name2digitMap[100];  // Initialiser un tableau de 100 éléments

    name2digitMap[10] = 1;
    name2digitMap[81] = 2;
    name2digitMap[47] = 3;
    name2digitMap[24] = 4;
    name2digitMap[58] = 5;
    name2digitMap[90] = 6;
    name2digitMap[86] = 7;
    name2digitMap[53] = 8;
    name2digitMap[23] = 9;

    int i = 3;
    std::cout << digit2name[i-1] << std::endl;

    for (auto name : digit2name) {
        std::cout << name << " -> " << hash(name) << std::endl;
    }

    std::string name = "Quatre"; 
    // for (int i = 0; i < 9; i++) {
    //     if (name == digit2name[i]) {
    //         std::cout << name2digit[i] << std::endl;
    //         break;
    //     }
    // }
    std::cout << name2digit[hash(name)] << std::endl;
}
