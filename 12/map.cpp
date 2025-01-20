#include <unordered_map>
#include <iostream>
#include <functional>

static const std::unordered_map<char, std::function<double(double, double) >> 
    operations = {
    {'+', [](double a, double b) { return a + b; }},
    {'-', [](double a, double b) { return a - b; }},
    {'*', [](double a, double b) { return a * b; }},
    {'/', [](double a, double b) { return a / b; }}
};

int main() {

    double a, b;
    char op;
    std::cin >> a >> b >> op;
    if (operations.find(op) == operations.end()) {
        std::cout << "Invalid operation" << std::endl;
        return 1;
    }
    std::cout << operations[op](a, b) << std::endl;
}