#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<std::string, int> map;
    map.insert("Hello", 1);
    map.insert("World", 2);
    map.insert("Mir", 3);

    std::cout << map.find("Mir")->value << std::endl;

    map.find("Mir")->value = 12;

    std::cout << map.find("Mir")->value;

    return 0;
}