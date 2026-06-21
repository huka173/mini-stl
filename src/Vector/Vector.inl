#include <cassert>
#include <utility>
#include <stdexcept>

template <typename T>
Vector<T>::Vector(size_t size) :
    m_size{ size },
    m_data{ new T[size]{} },
    m_capacity{ size } {}

template <typename T>
Vector<T>::Vector(size_t size, const T &value) :
    m_size{ size },
    m_capacity{ size },
    m_data{ new T[size] } {
    for (size_t i{}; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list) :
    m_size{ list.size() },
    m_capacity{ list.size() },
    m_data{ new T[list.size()] } {

    size_t index{};
    for (const auto &elem : list) {
        m_data[index] = elem;
        ++index;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &another) :
    m_data{ new T[another.capacity()] },
    m_size{ another.size() },
    m_capacity{ another.capacity() } {

    for (size_t i{}; i < m_size; ++i) {
        m_data[i] = another.m_data[i];
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] m_data;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &another) & {
    Vector<T> copy{ another };
    swap(copy);
    return *this;
}

template <typename T>
void Vector<T>::swap(Vector<T> &another) noexcept {
    std::swap(m_data, another.m_data);
    std::swap(m_size, another.m_size);
    std::swap(m_capacity, another.m_capacity);
}

template <typename T>
const T &Vector<T>::operator[](size_t index) const {
    assert(index < m_size);
    return m_data[index];
}

template <typename T>
T &Vector<T>::operator[](size_t index) {
    assert(index < m_size);
    return m_data[index];
}

template <typename T>
size_t Vector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
size_t Vector<T>::size() const {
    return m_size;
}

template <typename T>
T &Vector<T>::at(size_t index) {
    if (index >= m_size) {
        throw std::out_of_range("Out of range");
    }

    return m_data[index];
}

template <typename T>
const T &Vector<T>::at(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range("Out of range");
    }

    return m_data[index];
}

template <typename T>
bool Vector<T>::empty() const {
    return m_size == 0;
}

template <typename T>
void Vector<T>::clear() noexcept {
    m_size = 0;
}

template <typename T>
void Vector<T>::push_back(const T &elem) {
    if (m_size == m_capacity) {
        if (m_capacity == 0) {
            m_capacity = 1;
        } else {
            m_capacity = m_size * 2;
        }

        T *copy{ new T[m_capacity] };
        for (size_t i{}; i < m_size; ++i) {
            copy[i] = m_data[i];
        }
        copy[m_size] = elem;
        ++m_size;

        delete[] m_data;
        m_data = copy;
    } else {
        m_data[m_size] = elem;
        ++m_size;
    }
}

template <typename T>
void Vector<T>::pop_back() {
    if (m_size != 0) {
        --m_size;
    }
}

template <typename T>
T *Vector<T>::data() noexcept {
    return m_data;
}

template <typename T>
const T *Vector<T>::data() const noexcept {
    return m_data;
}

template <typename T>
void Vector<T>::reserve(size_t n) {
    if (n > m_capacity) {
        m_capacity = n;
        T *copy{ new T[m_capacity] };
        for (size_t i{}; i < m_size; ++i) {
            copy[i] = m_data[i];
        }

        delete[] m_data;
        m_data = copy;
    }
}

template <typename T>
T &Vector<T>::front() {
    return *m_data;
}

template <typename T>
const T &Vector<T>::front() const {
    return *m_data;
}

template <typename T>
T &Vector<T>::back() {
    return *(m_data + (m_size - 1));
}

template <typename T>
const T &Vector<T>::back() const {
    return *(m_data + (m_size - 1));
}