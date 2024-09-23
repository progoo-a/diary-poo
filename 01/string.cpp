#include <iostream>
#include <string>

using namespace std;

int main() {
    string s("abcdef\n");
    s.pop_back();
    s = s + "les biscuits";

    cout << s;
    
}