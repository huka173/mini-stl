template <typename Key, typename Value>
HashMap<Key, Value>::HashMap() :
    m_size{},
    m_bucketCount{ 8 } {
    m_buckets.resize(m_bucketCount);
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::findKeyInMap(const Key &key, size_t index) const {
    for (auto it{ m_buckets[index].begin() }; it != nullptr; it = it->next) {
        if ((it->value).key == key) {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::insert(const Key &key, const Value &value) {
    size_t index{ hash(key) % m_bucketCount };

    if (findKeyInMap(key, index)) {
        for (auto it{ m_buckets[index].begin() }; it != nullptr; it = it->next) {
            if ((it->value).key == key) {
                (it->value).value = value;
            }
        }
    } else {
        m_buckets[index].push_back(HashNode<Key, Value>{key, value});
        ++m_size;
    }
}

template <typename Key, typename Value>
size_t HashMap<Key, Value>::size() const {
    return m_size;
}

template <typename Key, typename Value>
HashNode<Key, Value> *HashMap<Key, Value>::find(const Key &key) {
    size_t index{ hash(key) % m_bucketCount };

    for (auto it{ m_buckets[index].begin() }; it != nullptr; it = it->next) {
        if (it->value.key == key) {
            return &it->value;
        }
    }

    return nullptr;
}

template <typename Key, typename Value>
const HashNode<Key, Value> *HashMap<Key, Value>::find(const Key &key) const {
    size_t index{ hash(key) % m_bucketCount };

    for (auto it{ m_buckets[index].begin() }; it != nullptr; it = it->next) {
        if (it->value.key == key) {
            return &it->value;
        }
    }

    return nullptr;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::erase(const Key &key) {
    size_t index{ hash(key) % m_bucketCount };
    for (auto it{ m_buckets[index].begin() }; it != nullptr; it = it->next) {
        if (it->value.key == key) {
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