#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "HashNode.h"
#include "List/List.h"
#include "Vector/Vector.h"
#include "Hash.h"

template <typename Key, typename Value>
class HashMap {
    Vector<List<HashNode<Key, Value>>> m_buckets;
    size_t m_size;
    size_t m_bucketCount;

    bool findKeyInMap(const Key &key, size_t index) const;

public:
    HashMap();
    void insert(const Key &key, const Value &value);

    HashNode<Key, Value> *find(const Key &key);
    const HashNode<Key, Value> *find(const Key &key) const;

    size_t size() const;

    Value &operator[](const Key &key);
};

#include "HashMap.inl"

#endif // !HASH_MAP_H
