template <typename T>
List<T>::List() :
    m_head{ nullptr },
    m_tail{ nullptr },
    m_size{} {}

template <typename T>
List<T>::List(const std::initializer_list<T> list) {    
    if (list.size() == 1) {
        m_head = new Node<T>{ *(list.begin()), nullptr, nullptr };
        m_tail = nullptr;
    } else if (list.size() == 2) {
        m_head = new Node<T>{ *(list.begin()), nullptr, nullptr };
        m_tail = new Node<T>{ *(list.end() - 1), nullptr, nullptr };
        m_head->next = m_tail;
        m_tail->prev = m_head;
    } else {
        m_head = new Node<T>{ *(list.begin()), nullptr, nullptr };
        Node<T> *current{ m_head };

        for (auto it{ list.begin() + 1 }; it != list.end(); ++it) {
            if (it == list.end() - 1) {
                m_tail = new Node<T>{ *it, nullptr, nullptr };
                m_tail->prev = current;
                current->next = m_tail;
                break;
            }

            Node<T> *node{ new Node<T>{ *it, nullptr, nullptr } };
            current->next = node;
            node->prev = current;
            current = node;
        }
    }

    m_size = list.size();
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