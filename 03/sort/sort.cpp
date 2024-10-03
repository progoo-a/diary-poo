#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    double x;
    vector<decltype(x)> data;
    while (cin >> x) data.push_back(x);
    sort(data.begin(), data.end());

    //for (int i = 0; i < data.size(); i++) cout << data[i] << " ";
    //for (auto it = data.begin(); it != data.end(); it++) cout << *it << " ";
    for (auto x : data) cout << x << " ";
    cout << endl;
}