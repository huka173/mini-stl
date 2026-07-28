#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "Node.h"

template <typename T>
class List {
public:
    Node<T> *m_head;
    Node<T> *m_tail;
    size_t m_size;

public:
    List();
    List(const std::initializer_list<T> list);

    ~List();
};

#include "List.inl"

#endif // !LIST_H
