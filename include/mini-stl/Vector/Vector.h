#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

template <typename T>
class Vector {
    T *m_data{ nullptr };
    size_t m_size{};
    size_t m_capacity{};

public:
    Vector() = default;
    explicit Vector(size_t size);
    Vector(size_t size, const T &value);
    Vector(const std::initializer_list<T> list);
    Vector(const Vector<T> &another);
    ~Vector();

    const T &operator[](size_t index) const;
    T &operator[](size_t index);
    Vector<T> &operator=(const Vector<T> &another) &;
    bool operator==(const Vector<T> &another) const;

    size_t capacity() const;
    size_t size() const;
    void swap(Vector<T> &another) noexcept;
    bool empty() const;
    void clear() noexcept;
    void erase(size_t index);
    void erase(size_t start, size_t end);

    T &at(size_t index);
    const T &at(size_t index) const;

    void push_back(const T &elem);
    void pop_back();

    T *data() noexcept;
    const T *data() const noexcept;

    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const T &val);
    void shrink_to_fit();

    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
};

#include "Vector.inl";

#endif // VECTOR_H
