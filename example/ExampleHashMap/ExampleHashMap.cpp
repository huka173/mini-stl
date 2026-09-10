#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<std::string, int> map;

    map["one"] = 1;
    map["two"] = 2;
    map["three"] = 3;

    map.erase("one");

    std::cout << "Size: " << map.size() << std::endl;
    if (map.find("one") == nullptr) {
        std::cout << "NOT FOUND\n";
    }
    std::cout << map["three"] << std::endl;
    std::cout << map["two"] << std::endl;


    return 0;
}