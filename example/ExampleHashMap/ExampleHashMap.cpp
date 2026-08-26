#include <iostream>
#include "HashMap/HashNode.h"
#include <string>

int main() {
    HashNode<int, std::string> hashNode{ 123, "Hello World" };
    std::cout << "Key: " << hashNode.key << std::endl;
    std::cout << "Value: " << hashNode.value << std::endl;

    return 0;
}