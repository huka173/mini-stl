template <typename Key, typename Value>
HashMap<Key, Value>::HashMap() :
    m_size{ 5 }, 
    m_bucketCount{ 8 } {
    m_buckets.reserve(m_size);
    m_buckets.resize(m_size);
}