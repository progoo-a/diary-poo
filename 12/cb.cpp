#include <iostream>
#include <vector>
#include <functional>
class Container {
    std::vector<int> data;
public:
    Container(std::vector<int> data) : data(data) {}
    void bubbleSort(
        std::function<void(std::vector<int> &data, 
            int ia, int ib)> cb = [](std::vector<int> &data, int ia, int ib) {}) {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.size() - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                    cb(data, j, j + 1);
                }
            }
        }
    }
};

int main() {
    Container container({5, 3, 2});
    container.bubbleSort([](std::vector<int> &data, int ia, int ib) {
        std::cout << "Swapping " << data[ia] << " and " << data[ib] << "\t(";
        for (auto &i : data) { std::cout << i << " "; }
        std::cout << ")" << std::endl;
    });
}

