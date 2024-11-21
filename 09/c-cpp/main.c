#include "mul.h"
#include "sub.h"

int main() {
    int a = 5;
    int b = 3;
    int c = 2;

    int result = mul(a, b);
    result = sub(result, c);

    return result;
}