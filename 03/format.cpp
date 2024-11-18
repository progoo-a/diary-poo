#include <iomanip>
#include <iostream>
#include <sstream>
#include <functional>

std::ostream& custom_format(std::ostream& os) {
    return os << std::setw(10) << std::setfill('0');
}

std::ostream& bold_red(std::ostream& os) {
    return os << "\033[1;31m";
}

// std::ostream& operator<< (std::ostream& os, 
//                           std::function<std::ostream&(std::ostream&)> f) {
//     return f(os);
// }

int main() {
    //std::stringstream ss;
    //ss << std::setw(10) << std::setfill('0');
    std::cout << std::setw(10) << std::setfill('0') 
        << 3.141592 
        << "  "
        << bold_red << custom_format
        << 6.283185 
        << std::endl;
}