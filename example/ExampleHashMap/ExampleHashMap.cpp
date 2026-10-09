#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<int, int> map {
        {100, 1},
        {200, 2},
        {300, 3}
    };

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << it->key << " : " << it->value << std::endl;
    }

    return 0;
}