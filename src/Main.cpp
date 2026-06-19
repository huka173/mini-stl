#include <iostream>
#include "Vector/Vector.h"

int main() {
    Vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Vector<int> newVec;
    newVec = vec;
    for (size_t i{}; i < newVec.size(); ++i) {
        std::cout << newVec.at(i) << " ";
    }

    return 0;
}