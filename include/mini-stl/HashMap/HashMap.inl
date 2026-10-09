template <typename Key, typename Value>
HashMap<Key, Value>::HashMap() :
    m_size{},
    m_bucketCount{ 16 } {
    m_buckets.resize(m_bucketCount);
}

template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(const std::initializer_list<HashNode<Key, Value>> list) :
    m_size{},
    m_bucketCount{ 16 } {
    m_buckets.resize(m_bucketCount);
    for (const auto &elem : list) {
        insert(elem.key, elem.value);
    }
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::findKeyInMap(const Key &key, size_t index) const {
    for (auto it{ m_buckets[index].begin() }; it != m_buckets[index].end(); ++it) {
        if (it->key == key) {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
double HashMap<Key, Value>::loadFactor() const {
    return static_cast<double>(m_size + 1) / m_bucketCount;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::rehash(size_t newBucketCount) {
    Vector<List<HashNode<Key, Value>>> newBuckets;
    newBuckets.resize(newBucketCount);

    for (size_t i{}; i < m_buckets.size(); ++i) {
        for (auto it{ m_buckets[i].begin() }; it != m_buckets[i].end(); ++it) {
            size_t index{ hash(it->key) % newBucketCount };
            newBuckets[index].push_back(HashNode<Key, Value>{it->key, it->value});
        }
    }
    m_buckets = newBuckets;
    m_bucketCount = newBucketCount;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key &key, const Value &value) {
    size_t index{ hash(key) % m_bucketCount };

    if (findKeyInMap(key, index)) {
        for (auto it{ m_buckets[index].begin() }; it != m_buckets[index].end(); ++it) {
            if (it->key == key) {
                it->value = value;
            }
        }
    } else {
        if (loadFactor() > 0.75) {
            rehash(m_bucketCount * 2);
            index = hash(key) % m_bucketCount;
        }
        m_buckets[index].push_back(HashNode<Key, Value>{key, value});
        ++m_size;
    }
}

template <typename Key, typename Value>
size_t HashMap<Key, Value>::size() const {
    return m_size;
}

template <typename Key, typename Value>
size_t HashMap<Key, Value>::bucketCount() const {
    return m_bucketCount;
}

template <typename Key, typename Value>
HashNode<Key, Value> *HashMap<Key, Value>::find(const Key &key) {
    size_t index{ hash(key) % m_bucketCount };

    for (auto it{ m_buckets[index].begin() }; it != m_buckets[index].end(); ++it) {
        if (it->key == key) {
            return &(*it);
        }
    }

    return nullptr;
}

template <typename Key, typename Value>
const HashNode<Key, Value> *HashMap<Key, Value>::find(const Key &key) const {
    size_t index{ hash(key) % m_bucketCount };

    for (auto it{ m_buckets[index].begin() }; it != m_buckets[index].end(); ++it) {
        if (it->key == key) {
            return &(*it);
        }
    }

    return nullptr;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::erase(const Key &key) {
    size_t index{ hash(key) % m_bucketCount };
    for (auto it{ m_buckets[index].begin() }; it != m_buckets[index].end(); ++it) {
        if (it->key == key) {
            m_buckets[index].erase(it);
            --m_size;
            return;
        }
    }
}

template <typename Key, typename Value>
Value &HashMap<Key, Value>::operator[](const Key &key) {
    auto *node{ find(key) };
    if (node) {
        return node->value;
    }

    insert(key, Value{});
    return find(key)->value;
}

template <typename Key, typename Value>
HashMap<Key, Value>::Iterator HashMap<Key, Value>::begin() {
    for (auto it = m_buckets.begin(); it != m_buckets.end(); ++it) {
        if (!((*it).empty())) {
            return Iterator{ it, (*it).begin(), m_buckets.end(), (*it).end() };
        }
    }
    return end();
}

template <typename Key, typename Value>
HashMap<Key, Value>::ConstIterator HashMap<Key, Value>::begin() const {
    for (auto it = m_buckets.begin(); it != m_buckets.end(); ++it) {
        if (!((*it).empty())) {
            return ConstIterator{ it, (*it).begin(), m_buckets.end(), (*it).end() };
        }
    }
    return end();
}

template <typename Key, typename Value>
HashMap<Key, Value>::ConstIterator HashMap<Key, Value>::cbegin() const {
    for (auto it = m_buckets.begin(); it != m_buckets.end(); ++it) {
        if (!((*it).empty())) {
            return ConstIterator{ it, (*it).begin(), m_buckets.end(), (*it).end() };
        }
    }
    return end();
}

template <typename Key, typename Value>
HashMap<Key, Value>::Iterator HashMap<Key, Value>::end() {
    return Iterator{ 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::Iterator{}, 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::Iterator{} 
    };
}

template <typename Key, typename Value>
HashMap<Key, Value>::ConstIterator HashMap<Key, Value>::end() const {
    return ConstIterator{ 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::ConstIterator{}, 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::ConstIterator{} 
    };
}

template <typename Key, typename Value>
HashMap<Key, Value>::ConstIterator HashMap<Key, Value>::cend() const {
    return ConstIterator{ 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::ConstIterator{}, 
        m_buckets.end(), 
        typename List<HashNode<Key, Value>>::ConstIterator{} 
    };
}

template <typename Key, typename Value>
template <bool notConst>
HashMap<Key, Value>::BaseIterator<notConst>::BaseIterator(
    VectorIterator vectorIterator,
    ListIterator listIterator,
    VectorIterator endVectorIterator,
    ListIterator endListIterator
) :
    m_vectorIterator{ vectorIterator },
    m_listIterator{ listIterator },
    m_endVectorIterator{ endVectorIterator },
    m_endListIterator{ endListIterator } {}

template <typename Key, typename Value>
template <bool notConst>
HashMap<Key, Value>::BaseIterator<notConst>::ref_HashNode HashMap<Key, Value>::BaseIterator<notConst>::operator*() const {
    return *m_listIterator;
}

template <typename Key, typename Value>
template <bool notConst>
HashMap<Key, Value>::BaseIterator<notConst>::ptr_HashNode HashMap<Key, Value>::BaseIterator<notConst>::operator->() const {
    return &(*m_listIterator);
}

template <typename Key, typename Value>
template <bool notConst>
bool HashMap<Key, Value>::BaseIterator<notConst>::operator==(const BaseIterator &it) const {
    return m_vectorIterator == it.m_vectorIterator
        && (m_vectorIterator == m_endVectorIterator || m_listIterator == it.m_listIterator);
}

template <typename Key, typename Value>
template <bool notConst>
bool HashMap<Key, Value>::BaseIterator<notConst>::operator!=(const BaseIterator &it) const {
    return !(*this == it);
}

template <typename Key, typename Value>
template <bool notConst>
HashMap<Key, Value>::BaseIterator<notConst> &HashMap<Key, Value>::BaseIterator<notConst>::operator++() {
    if (++m_listIterator != m_endListIterator) {
        return *this;
    }

    ++m_vectorIterator;
    while ((m_vectorIterator != m_endVectorIterator) && (*m_vectorIterator).empty()) {
        ++m_vectorIterator;
    }

    if (m_vectorIterator != m_endVectorIterator) {
        m_listIterator = (*m_vectorIterator).begin();
        m_endListIterator = (*m_vectorIterator).end();
    } else {
        m_listIterator = ListIterator{};
        m_vectorIterator = m_endVectorIterator;
    }

    return *this;
}

template <typename Key, typename Value>
template <bool notConst>
HashMap<Key, Value>::BaseIterator<notConst> HashMap<Key, Value>::BaseIterator<notConst>::operator++(int) {
    BaseIterator copy{ *this };
    ++(*this);
    return copy;
}