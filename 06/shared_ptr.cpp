#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> p(new int(42));
    std::shared_ptr<int> q = p;
    std::cout << *p << std::endl;
    std::cout << *q << std::endl;
    std::cout << p.use_count() << std::endl;
    std::cout << q.use_count() << std::endl;
}