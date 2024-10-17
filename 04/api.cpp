#include <iostream>

#include "api.hpp"
#include <stdio.h>

Foo::Foo() {
    std::cout << "Foo created" << std::endl;
}

void Foo::toto() {
    std::cout << "toto" << std::endl;
}

Foo::~Foo() {
    std::cout << "Foo destroyed" << std::endl;
}