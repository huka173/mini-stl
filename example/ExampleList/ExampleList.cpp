#include <iostream>
#include "List/List.h"
#include "List/Node.h"

int main() {
    List<int> list{ 1, 2 };
    list.pop_front();
    std::cout << list.end()->value;

    return 0;
}