template <typename T>
List<T>::List() :
    m_head{ nullptr },
    m_tail{ nullptr },
    m_size{} {}

template <typename T>
List<T>::List(const std::initializer_list<T> list) :
    m_head{ nullptr },
    m_tail{ nullptr },
    m_size{} {
    for (const auto &elem : list) {
        push_back(elem);
    }
}

template <typename T>
List<T>::~List() {
    Node<T> *current{ m_head };
    while (current != nullptr) {
        Node<T> *nextNode{ current->next };
        delete current;
        current = nextNode;
    }
}

template <typename T>
void List<T>::push_back(const T &value) {
    Node<T> *node{ new Node<T>{value, nullptr, nullptr} };
    if (m_head == nullptr) {
        m_head = node;
        m_tail = node;
    } else {
        m_tail->next = node;
        node->prev = m_tail;
        m_tail = node;
    }

    ++m_size;
}

template <typename T>
void List<T>::push_front(const T &value) {
    Node<T> *node{ new Node<T>{value, nullptr, nullptr} };
    if (m_head == nullptr) {
        m_head = node;
        m_tail = node;
    } else {
        m_head->prev = node;
        node->next = m_head;
        m_head = node;
    }

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
    return m_head->value;
}

template <typename T>
const T &List<T>::front() const noexcept {
    return m_head->value;
}

template <typename T>
T &List<T>::back() noexcept {
    return m_tail->value;
}

template <typename T>
const T &List<T>::back() const noexcept {
    return m_tail->value;
}

template <typename T>
Node<T> *List<T>::begin() noexcept {
    return m_head;
}

template <typename T>
const Node<T> *List<T>::begin() const noexcept {
    return m_head;
}

template <typename T>
Node<T> *List<T>::end() noexcept {
    return m_tail;
}

template <typename T>
const Node<T> *List<T>::end() const noexcept {
    return m_tail;
}