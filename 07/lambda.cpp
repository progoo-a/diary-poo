#include <functional> 
#include <vector>
#include <iostream>
using namespace std;

int square(int value) { return value * value; }

void traverse(vector<int>&data, function<int(int)>func) {
    for (auto &v : data) {
        v = func(v);
    }
}

int main() {
    vector<int> data(10);
    int count = 0;
    traverse(data, [&count](int v){ return v + count++; });
    traverse(data, [](int v){ return v * v; });
    traverse(data, [](int v){ cout << v << endl; return v; });
}