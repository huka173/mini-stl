#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<std::string, std::string> map;

    map["one"] = "1";

    map["two"] = "2";

    std::cout << map["two"];

    return 0;
}