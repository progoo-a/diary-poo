#include <iostream>
#include <string>
int main() {


    // const char s[] = "Salut";

    // for (auto c: s) { std::cout << c << std::endl; }
    // for (auto c: "Salut") { std::cout << c << std::endl; }

    std::string s = "Salut";
    std::string::iterator it = s.begin();
    while (it != s.end()) {
        std::cout << *it << std::endl;
        ++it;
    }

    for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
        char c = *it;
        std::cout << c << std::endl;
    }

    for (const char &c : s) {
        std::cout << c << std::endl;
    }
}