#include <iostream>
#include <numeric>
#include <vector>
#include <functional>
#include <typeinfo>

void f2(int x) {
    std::cout << "lol from f2\n";
}

void exec(std::function<int(int)>& f) {
    f(1);
}
template<typename x, typename y>
class lmao {
public:
    void lmao3() {
        std::cout << "lmao3\n";
        std::cout << typeid(x).name() << ", " << typeid(y).name() << std::endl;
    }
};
template<typename x, typename y>
class lmao<x(y), y> {
public:
    void lmao2() {
        std::cout << "lmao2\n";
        std::cout << typeid(x).name() << ", " << typeid(y).name() << std::endl;
    }
};
int main() {
    lmao<int(int), double> x;
    lmao<int(double), double> x2;
    x.lmao3();
    x2.lmao2();
}