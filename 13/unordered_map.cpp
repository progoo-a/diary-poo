
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

int main() {
    std::unordered_map<std::string, int> map; // Recherche O(1)
    std::map<std::string, int> map2; // Recherche O(log n)

    std::string key = "foo";
    auto hash = std::hash<std::string>{}(key);

    map.insert(std::make_pair("bar", 23));
    map["foo"] = 42;

    // Avant C++11
    if (map.find("foo") != map.end()) {
        map.erase("foo");
    }

    // Depuis C++11
    if (map.contains("foo")) {
        map.erase("foo");
    }
}