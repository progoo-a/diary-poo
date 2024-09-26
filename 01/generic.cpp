
#include <iostream>
using namespace std;

template <class T>
T find(T *data, int size, T search) {
    for (int i = 0; i < size; i++) {
        if (data[i] == (int)search)
           return i;
    }
    return -1;
}

int main() {
    int data[1024];
    data[42] = 666;
    cout << find<int>(data, sizeof(data) / sizeof(data[0]), 666.0);
}