#include <iostream>
#include <utility>

template <typename T>
List<T>::List() :
    m_node{ new Node<T>{} },
    m_size{} {
    m_node->next = m_node;
    m_node->prev = m_node;
}

template <typename T>
List<T>::List(const std::initializer_list<T> list) :
    m_node{ new Node<T>{} },
    m_size{} {
    m_node->next = m_node;
    m_node->prev = m_node;
    for (const auto &elem : list) {
        push_back(elem);
    }
}

template <typename T>
List<T>::~List() {
    Node<T> *current{ m_node->next };
    while (current != m_node) {
        Node<T> *nextNode{ current->next };
        delete current;
        current = nextNode;
    }
    delete m_node;
}

template <typename T>
void List<T>::push_back(const T &value) {
    Node<T> *node{ new Node<T>{value, nullptr, nullptr} };
    auto tail{ m_node->prev };
    tail->next = node;
    node->prev = tail;
    node->next = m_node;
    m_node->prev = node;

    ++m_size;
}

template <typename T>
void List<T>::push_front(const T &value) {
    Node<T> *node{ new Node<T>{value, nullptr, nullptr} };
    auto head{ m_node->next };
    head->prev = node;
    node->next = head;
    node->prev = m_node;
    m_node->next = node;

    ++m_size;
}

template <typename T>
size_t List<T>::size() const {
    return m_size;
}

template <typename T>
bool List<T>::empty() const {
    return m_size == 0;
}

template <typename T>
T &List<T>::front() noexcept {
    return m_node->next->value;
}

template <typename T>
const T &List<T>::front() const noexcept {
    return m_node->next->value;
}

template <typename T>
T &List<T>::back() noexcept {
    return m_node->prev->value;
}

template <typename T>
const T &List<T>::back() const noexcept {
    return m_node->prev->value;
}

template <typename T>
List<T>::Iterator List<T>::begin() noexcept {
    return Iterator{ m_node->next };
}

template <typename T>
List<T>::ConstIterator List<T>::begin() const noexcept {
    return ConstIterator{ m_node->next };
}

template <typename T>
List<T>::ConstIterator List<T>::cbegin() const noexcept {
    return ConstIterator{ m_node->next };
}

template <typename T>
List<T>::Iterator List<T>::end() noexcept {
    return Iterator{ m_node };
}

template <typename T>
List<T>::ConstIterator List<T>::end() const noexcept {
    return ConstIterator{ m_node };
}

template <typename T>
List<T>::ConstIterator List<T>::cend() const noexcept {
    return ConstIterator{ m_node };
}

template <typename T>
void List<T>::pop_back() {
    if (m_size > 0) {
        Node<T> *lastElem{ m_node->prev };
        m_node->prev = lastElem->prev;
        m_node->prev->next = m_node;
        delete lastElem;
        --m_size;
    }
}

template <typename T>
void List<T>::pop_front() {
    if (m_size > 0) {
        Node<T> *firstElem{ m_node->next };
        m_node->next = firstElem->next;
        m_node->next->prev = m_node;
        delete firstElem;
        --m_size;
    }
}

template <typename T>
void List<T>::clear() {
    Node<T> *current{ m_node->next };
    while (current != m_node) {
        Node<T> *nextNode{ current->next };
        delete current;
        current = nextNode;
    }
    m_node->next = m_node;
    m_node->prev = m_node;
    m_size = 0;
}

template <typename T>
void List<T>::remove(const T &val) {
    if (empty()) {
        return;
    }

    while (!empty() && m_node->next->value == val) {
        pop_front();
    }

    while (!empty() && m_node->prev->value == val) {
        pop_back();
    }

    Node<T> *current{ m_node->next };
    while (current != m_node) {
        Node<T> *nextNode{ current->next };
        Node<T> *prevNode{ current->prev };
        if (current->value == val) {
            delete current;
            --m_size;
            current = nextNode;
            current->prev = prevNode;
            prevNode->next = current;
        } else {
            current = nextNode;
        }
    }
}

template <typename T>
List<T>::Iterator List<T>::erase(Iterator it) {
    Node<T> *node{ it.m_ptr };
    if (node == m_node) {
        return end();
    }

    Node<T> *next{ node->next };
    node->prev->next = next;
    next->prev = node->prev;
    delete node;
    --m_size;

    return Iterator{ next };
}

template <typename T>
List<T>::List(const List<T> &copy) : m_node{ new Node<T>{} }, m_size{} {
    m_node->next = m_node;
    m_node->prev = m_node;
    try {
        for (auto it{ copy.begin() }; it != copy.end(); ++it) {
            push_back(*it);
        }
    } catch (...) {
        auto *current{ m_node->next };
        while (current != m_node) {
            auto nextNode{ current->next };
            delete current;
            current = nextNode;
        }

        delete m_node;
        throw;
    }
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &copy) {
    List<T> temp{ copy };
    swap(temp);
    return *this;
}

template <typename T>
void List<T>::swap(List<T> &another) noexcept {
    std::swap(m_node, another.m_node);
    std::swap(m_size, another.m_size);
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst>::BaseIterator(node_ptr_type ptr) : m_ptr{ ptr } {}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst>::ref_type List<T>::BaseIterator<notConst>::operator*() const {
    return m_ptr->value;
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst>::ptr_type List<T>::BaseIterator<notConst>::operator->() const {
    return &(m_ptr->value);
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst> &List<T>::BaseIterator<notConst>::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst> List<T>::BaseIterator<notConst>::operator++(int) {
    BaseIterator copy{ *this };
    m_ptr = m_ptr->next;
    return copy;
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst> &List<T>::BaseIterator<notConst>::operator--() {
    m_ptr = m_ptr->prev;
    return *this;
}

template <typename T>
template <bool notConst>
List<T>::BaseIterator<notConst> List<T>::BaseIterator<notConst>::operator--(int) {
    BaseIterator copy{ *this };
    m_ptr = m_ptr->prev;
    return copy;
}

template <typename T>
template <bool notConst>
bool List<T>::BaseIterator<notConst>::operator==(const BaseIterator &it) const {
    return m_ptr == it.m_ptr;
}

template <typename T>
template <bool notConst>
bool List<T>::BaseIterator<notConst>::operator!=(const BaseIterator &it) const {
    return !(*this == it);
}