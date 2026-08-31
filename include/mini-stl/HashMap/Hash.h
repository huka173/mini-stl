#ifndef HASH_H
#define HASH_H

#include <string>
#include <type_traits>

// Easy implementation hash function

template <typename T>
constexpr size_t hash(const T& value) {
    if constexpr (std::is_same_v<T, int>) {
        return static_cast<size_t>(value);
    } else if constexpr (std::is_array_v<T>) {
        std::string str{ value };

        size_t result{};
        for (char ch : str) {
            result = result * 31 + static_cast<size_t>(ch);
        }

        return result;
    }

    return 0;
}

#endif // !HASH_H
