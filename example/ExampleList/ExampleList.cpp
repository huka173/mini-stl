#include <iostream>
#include "List/List.h"
#include "List/Node.h"

int main() {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    std::cout << list.back() << std::endl;


    return 0;
}