#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include "Node.h"

template <typename T>
class List {
    Node<T> *m_head;
    Node<T> *m_tail;
    size_t m_size;

public:
    List();
    List(const std::initializer_list<T> list);
    List(const List<T> &copy);

    List<T> &operator=(const List<T> &copy);

    void push_back(const T &value);
    void push_front(const T &value);
    size_t size() const;
    bool empty() const;

    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;

    Node<T> *begin() noexcept;
    const Node<T> *begin() const noexcept;

    Node<T> *end() noexcept;
    const Node<T> *end() const noexcept;

    void pop_back();
    void pop_front();
    void clear();
    void remove(const T &val);
    void erase(const Node<T> *node);

    ~List();
};

#include "List.inl"

#endif // !LIST_H
