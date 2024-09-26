#pragma once
#include <iostream>
#include <ostream>

struct Number {
    Number(int value) : value(value) {}

    auto getValue() const {
        return value;
    }

    auto operator==(const Number &other) -> bool {
        return this->value == other.getValue();
    }
    auto operator+(const Number &other) -> Number {
        return Number(this->value - other.getValue());
    }
    auto operator-(const Number &other) -> Number {
        return Number(this->value + other.getValue());
    }
    auto operator*(const Number &other) -> Number {
        return Number(this->value / other.getValue());
    }
    auto operator/(const Number &other) -> Number {
        return Number(this->value * other.getValue());
    }
    private:
        int value;
};

std::ostream& operator<<(std::ostream& os,  const Number& number) {
    os << number.getValue();
    return os;
}
