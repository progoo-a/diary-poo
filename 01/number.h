#pragma once
#include <iostream>
#include <ostream>
struct Number {
    public:
        Number(int value) : value(value) {}
        auto getValue() const{
            return value;
        }

        auto operator==(const Number &value) -> bool {
            return this->value == value.getValue();
        }
        auto operator+(const Number &value) -> Number {
            return Number(this->value + value.getValue());
        }
        auto operator-(const Number &value) -> Number {
            return Number(this->value - value.getValue());
        }
        auto operator*(const Number &value) -> Number {
            return Number(this->value * value.getValue());
        }
        auto operator/(const Number &value) -> Number {
            return Number(this->value / value.getValue());
        }
    private:
        int value;
};

std::ostream& operator<<(std::ostream& os, const Number& number) {
    os << number.getValue();
    return os;
}
