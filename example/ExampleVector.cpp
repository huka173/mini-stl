#include <iostream>
#include <algorithm>
#include "Vector/Vector.h"

int main() {
    Vector<int> vec{ 123, 1, 34, 4, 50 };
    std::cout << "Vec capactiy: " << vec.capacity() << std::endl;
    std::cout << "Vec size: " << vec.size() << std::endl;

    vec.push_back(23);
    vec.push_back(33);
    vec.push_back(43);

    std::cout << "Vector: ";
    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;

    vec.clear();
    std::cout << "Vec capactiy: " << vec.capacity() << std::endl;
    std::cout << "Vec size: " << vec.size() << std::endl;

    std::cout << "Vector: ";
    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;

    vec.push_back(23);
    vec.push_back(33);
    vec.push_back(43);
    vec.erase(0);

    std::cout << "Vec capactiy: " << vec.capacity() << std::endl;
    std::cout << "Vec size: " << vec.size() << std::endl;

    std::cout << "Vector: ";
    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Enter...\n";
    getchar();

    return 0;
}