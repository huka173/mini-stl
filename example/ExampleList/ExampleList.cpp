#include <iostream>
#include "List/List.h"
#include "List/Node.h"

int main() {
    List<int> list{ 1, 2 };

    Node<int> *ptr{ list.m_tail };
    while (ptr != nullptr) {
        std::cout << ptr->value << " ";
        ptr = ptr->prev;
    }

    return 0;
}