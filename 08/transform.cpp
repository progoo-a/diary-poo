/*
    C++23 transform exemple on vector
*/
#include <iostream>

#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    // Double each element
    auto doubled = v | std::views::transform([](int i) { return i * 2; });

    // Count each access
    int sum = 0;
    auto sub = doubled | std::views::transform([&sum](int i) {
        sum++;
        return i;
    });

    std::cout << "Sum is: " << sum << std::endl;

    // Display
    for (auto i : sub) {
        std::cout << i << " ";
    }

    std::cout << "Sum is: " << sum << std::endl;
}