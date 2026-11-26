#include "calc.h"
#include <cstdlib>
#include <iostream>

void check(bool condition) {
    if (!condition) {
        std::cerr << "Calculator test failed\n";
        std::exit(1);
    }
}

template <class T>
void test_type() {
    num_node left, right;
    left.number = T(-7);
    right.number = T(2);
    calculator calc;
    visitor *base = &calc;
    add_node add;
    sub_node sub;
    mul_node mul;
    div_node div;
    add.lnode = sub.lnode = mul.lnode = div.lnode = &left;
    add.rnode = sub.rnode = mul.rnode = div.rnode = &right;
    check(std::any_cast<T>(base->visit(&left)) == T(-7));
    check(std::any_cast<T>(base->visit(&add)) == T(-5));
    check(std::any_cast<T>(base->visit(&sub)) == T(-9));
    check(std::any_cast<T>(base->visit(&mul)) == T(-14));
    check(std::any_cast<T>(base->visit(&div)) == T(-7) / T(2));
    mul.lnode = &add;
    mul.rnode = &sub;
    div.lnode = &mul;
    for (int i = 0; i < 3; ++i) {
        check(std::any_cast<T>(base->visit(&div)) == T(45) / T(2));
    }
    check(std::any_cast<T>(left.number) == T(-7));
    check(std::any_cast<T>(right.number) == T(2));
    check(mul.lnode == &add && mul.rnode == &sub);
}

int main() {
    test_type<long long>();
    test_type<double>();
    num_node large;
    large.number = 9007199254740993LL;
    calculator calc;
    check(std::any_cast<long long>(calc.visit(&large)) == 9007199254740993LL);
    std::cout << "All calculator tests passed\n";
}
