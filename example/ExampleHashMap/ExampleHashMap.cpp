#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<int, int> map {
        {100, 1},
        {200, 2},
        {300, 3}
    };

    for (const auto &[key, value] : map) {
        std::cout << key << ":" << value << std::endl;
    }

    return 0;
}