#include <iostream>
#include "List/List.h"
#include "List/Node.h"

int main() {
    List<int> a{ 1,2,3 };
    List<int> b;

    a = b;

    for (auto *it{ a.begin() }; it != nullptr; it = it->next) {
        std::cout << it->value << " ";
    }

    return 0;
}