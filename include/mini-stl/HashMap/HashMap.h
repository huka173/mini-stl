#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <type_traits>
#include <initializer_list>
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
    double loadFactor() const;
    void rehash(size_t newBucketCount);

    template <bool notConst>
    class BaseIterator {
    public:
        using VectorIterator = std::conditional_t<
            notConst,
            typename Vector<List<HashNode<Key, Value>>>::Iterator,
            typename Vector<List<HashNode<Key, Value>>>::ConstIterator
        >;

        using ListIterator = std::conditional_t<
            notConst,
            typename List<HashNode<Key, Value>>::Iterator,
            typename List<HashNode<Key, Value>>::ConstIterator
        >;

        using ref_HashNode = std::conditional_t<notConst, HashNode<Key, Value> &, const HashNode<Key, Value> &>;
        using ptr_HashNode = std::conditional_t<notConst, HashNode<Key, Value> *, const HashNode<Key, Value> *>;

    private:
        VectorIterator m_vectorIterator;
        ListIterator m_listIterator;

        VectorIterator m_endVectorIterator;
        ListIterator m_endListIterator;
        
    public:
        BaseIterator(VectorIterator vectorIterator, ListIterator listIterator, VectorIterator endVectorIterator, ListIterator endListIterator);
        BaseIterator(const BaseIterator &) = default;
        BaseIterator &operator=(const BaseIterator &) = default;

        ref_HashNode operator*() const;
        ptr_HashNode operator->() const;

        BaseIterator &operator++();
        BaseIterator operator++(int);

        bool operator==(const BaseIterator &it) const;
        bool operator!=(const BaseIterator &it) const;
    };


public:
    using Iterator = BaseIterator<true>;
    using ConstIterator = BaseIterator<false>;

    HashMap();
    HashMap(const std::initializer_list<HashNode<Key, Value>> list);
    void insert(const Key &key, const Value &value);

    HashNode<Key, Value> *find(const Key &key);
    const HashNode<Key, Value> *find(const Key &key) const;

    size_t size() const;
    size_t bucketCount() const;

    void erase(const Key &key);

    Value &operator[](const Key &key);

    Iterator begin();
    ConstIterator begin() const;
    ConstIterator cbegin() const;

    Iterator end();
    ConstIterator end() const;
    ConstIterator cend() const;
};

#include "HashMap.inl"

#endif // !HASH_MAP_H
