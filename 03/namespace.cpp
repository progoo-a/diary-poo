#include <iostream>

namespace mymath {
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
}

namespace debug {
int add(int a, int b) {
    std::cerr << "DEBUG: add(" << a << ", " << b << ")" << std::endl;
    return a + b;

}

int subtract(int a, int b) {
    std::cerr << "DEBUG: subtract(" << a << ", " << b << ")" << std::endl;
    return a - b;
}
}

#ifdef DEBUG
using namespace debug;
#else
using namespace mymath;
#endif 

int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << subtract(1, 2) << std::endl;
}