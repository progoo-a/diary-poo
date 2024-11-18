
#include <string>
#include <iostream>

using namespace std;
int main() {
    string foo = "foo";
    string bar = "bar";
    auto &ref = foo;

    cout << &ref << endl;
    cout << ref << endl;
    ref = bar;
    cout << &ref << endl;
    cout << ref << endl;
}