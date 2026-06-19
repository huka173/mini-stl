#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
    T *m_data{ nullptr };
    size_t m_size{};
    size_t m_capacity{};

public:
    Vector() = default;
    Vector(size_t size);
    Vector(size_t size, const T &value);

    const T &operator[](size_t index) const;
};

#include "Vector.inl";

#endif // VECTOR_H
