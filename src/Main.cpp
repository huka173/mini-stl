#include <iostream>
#include "Vector/Vector.h"

int main() {
    Vector<int> vec;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;
    
    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.push_back(1);
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.push_back(2);
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.push_back(4);
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.push_back(5);
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.push_back(6);
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;

    for (size_t i{}; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }

    return 0;
}