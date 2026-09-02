#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "HashNode.h"
#include "List/List.h"
#include "Vector/Vector.h"
#include "Hash.h"

template <typename Key, typename Value>
class HashMap {
public:
    Vector<List<HashNode<Key, Value>>> m_buckets;
    size_t m_size;
    size_t m_bucketCount;

public:
    HashMap();

};

#include "HashMap.inl"

#endif // !HASH_MAP_H
