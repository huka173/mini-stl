template <typename Key, typename Value>
HashMap<Key, Value>::HashMap() :
    m_size{},
    m_bucketCount{ 16 } {
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
double HashMap<Key, Value>::loadFactor() const {
    return static_cast<double>(m_size + 1) / m_bucketCount;
}

template <typename Key, typename Value>
void HashMap<Key, Value>::rehash(size_t newBucketCount) {
    Vector<List<HashNode<Key, Value>>> newBuckets;
    newBuckets.resize(newBucketCount);

    for (size_t i{}; i < m_buckets.size(); ++i) {
        for (auto it{ m_buckets[i].begin() }; it != nullptr; it = it->next) {
            size_t index{ hash(it->value.key) % newBucketCount };
            newBuckets[index].push_back(HashNode<Key, Value>{it->value.key, it->value.value});
        }
    }
    m_buckets = newBuckets;
    m_bucketCount = newBucketCount;
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