#include <vector> 
#include <iostream>
using namespace std;

int main() {
    vector<int> foo;
    for(int i = 0; i < 10; ++i) foo.push_back(i);

    for(int prout: foo) {
        cout << prout << ", ";
    }
    cout << "\n";
}