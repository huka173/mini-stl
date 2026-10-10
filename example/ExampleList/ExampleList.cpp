#include <iostream>
#include "List/List.h"
#include "List/Node.h"

int main() {
    List<int> a{ 1, 2, 3 };
    
    List<int> b{ a };
    for (const auto &elem : b) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Size a: " << a.size() << std::endl;
    std::cout << "Size b: " << b.size() << std::endl;

    return 0;
}