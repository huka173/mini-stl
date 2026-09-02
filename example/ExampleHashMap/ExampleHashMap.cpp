#include <iostream>
#include "HashMap/HashMap.h"
#include <string>

int main() {
    HashMap<std::string, int> map{};
    std::cout << "Bucket count: " << map.m_bucketCount << std::endl;
    std::cout << "Size: " << map.m_size << std::endl;
    std::cout << "Buckets size: " << map.m_buckets.size() << std::endl;
    std::cout << "Buckets capacity: " << map.m_buckets.capacity() << std::endl;

    return 0;
}