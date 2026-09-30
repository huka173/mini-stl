#include <cassert>
#include <utility>
#include <stdexcept>

template <typename T>
Vector<T>::Vector(size_t size) :
    m_size{ size },
    m_data{ reinterpret_cast<T *>(new char[size * sizeof(T)]) },
    m_capacity{ size } {
    size_t i{};
    try {
        for (; i < size; ++i) {
            new (m_data + i) T{};
        }
    } catch (...) {
        for (size_t j{}; j < i; ++j) {
            m_data[j].~T();
        }
        delete[] reinterpret_cast<char *>(m_data);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(size_t size, const T &value) :
    m_size{ size },
    m_capacity{ size },
    m_data{ reinterpret_cast<T *>(new char[size * sizeof(T)]) } {

    size_t i{};
    try {
        for (; i < size; ++i) {
            new (m_data + i) T{ value };
        }
    } catch (...) {
        for (size_t j{}; j < i; ++j) {
            m_data[j].~T();
        }

        delete[] reinterpret_cast<char *>(m_data);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list) :
    m_size{ list.size() },
    m_capacity{ list.size() },
    m_data{ reinterpret_cast<T *>(new char[list.size() * sizeof(T)]) } {

    size_t index{};
    try {
        for (const auto &elem : list) {
            new (m_data + index) T{ elem };
            ++index;
        }
    } catch (...) {
        for (size_t i{}; i < index; ++i) {
            m_data[i].~T();
        }

        delete[] reinterpret_cast<char *>(m_data);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &another) :
    m_data{ reinterpret_cast<T *>(new char[another.capacity() * sizeof(T)]) },
    m_size{ another.size() },
    m_capacity{ another.capacity() } {

    size_t index{};
    try {
        for (; index < m_size; ++index) {
            new (m_data + index) T{ another.m_data[index] };
        }
    } catch (...) {
        for (size_t i{}; i < index; ++i) {
            m_data[i].~T();
        }
        delete[] reinterpret_cast<char *>(m_data);
        throw;
    }
}

template <typename T>
Vector<T>::~Vector() {
    for (size_t i{}; i < m_size; ++i) {
        m_data[i].~T();
    }

    delete[] reinterpret_cast<char *>(m_data);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &another) & {
    Vector<T> copy{ another };
    swap(copy);
    return *this;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T> &another) const {
    if (size() != another.size()) {
        return false;
    }

    for (size_t i{}; i < size(); ++i) {
        if (another[i] != m_data[i]) {
            return false;
        }
    }

    return true;
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
    for (size_t i{}; i < m_size; ++i) {
        m_data[i].~T();
    }
    m_size = 0;
}

template <typename T>
void Vector<T>::erase(size_t index) {
    erase(index, index + 1);
}

template <typename T>
void Vector<T>::erase(size_t start, size_t end) {
    assert(start <= end);
    assert(end <= m_size);

    size_t diff{ end - start };
    T *copy{ reinterpret_cast<T *>(new char[m_capacity * sizeof(T)]) };

    size_t i{}, k{};
    try {
        for (; i < m_size; ++i) {
            if ((i < start) || (i >= end)) {
                new (copy + k) T{ m_data[i] };
                ++k;
            }
        }
    } catch (...) {
        for (size_t j{}; j < k; ++j) {
            copy[j].~T();
        }

        delete[] reinterpret_cast<char *>(copy);
        throw;
    }

    for (size_t i{}; i < m_size; ++i) {
        m_data[i].~T();
    }

    delete[] reinterpret_cast<char *>(m_data);
    m_data = copy;
    m_size -= diff;
}

template <typename T>
void Vector<T>::push_back(const T &elem) {
    if (m_size == m_capacity) {
        size_t newCapacity{};
        if (m_capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = m_size * 2;
        }

        T *copy{ reinterpret_cast<T *>(new char[newCapacity * sizeof(T)]) };
        size_t index{};
        try {
            for (; index < m_size; ++index) {
                new (copy + index) T{ m_data[index] };
            }
            new (copy + index) T{ elem };
        } catch (...) {
            for (size_t i{}; i < index; ++i) {
                copy[i].~T();
            }

            delete[] reinterpret_cast<char *>(copy);
            throw;
        }
        ++m_size;

        for (size_t i{}; i < m_size; ++i) {
            m_data[i].~T();
        }
        delete[] reinterpret_cast<char *>(m_data);
        m_capacity = newCapacity;
        m_data = copy;
    } else {
        new (m_data + m_size) T{ elem };
        ++m_size;
    }
}

template <typename T>
void Vector<T>::pop_back() {
    if (m_size != 0) {
        m_data[m_size - 1].~T();
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
        T *copy{ reinterpret_cast<T *>(new char[n * sizeof(T)]) };

        size_t index{};
        try {
            for (; index < m_size; ++index) {
                new (copy + index) T{ m_data[index] };
            }
        } catch (...) {
            for (size_t j{}; j < index; ++j) {
                copy[j].~T();
            }
            delete[] reinterpret_cast<char *>(copy);
            throw;
        }

        for (size_t i{}; i < m_size; ++i) {
            m_data[i].~T();
        }

        delete[] reinterpret_cast<char *>(m_data);
        m_capacity = n;
        m_data = copy;
    }
}

template <typename T>
void Vector<T>::resize(size_t n, const T &val) {
    if (n > m_size) {
        size_t diff{ n - m_size };
        size_t newCapacity{ n > m_capacity ? n * 2 : m_capacity };

        T *copy{ reinterpret_cast<T *>(new char[newCapacity * sizeof(T)]) };

        size_t index{};
        try {
            for (; index < n; ++index) {
                if (index < (n - diff)) {
                    new (copy + index) T{ m_data[index] };
                } else {
                    new (copy + index) T{ val };
                }
            }
        } catch (...) {
            for (size_t i{}; i < index; ++i) {
                copy[i].~T();
            }

            delete[] reinterpret_cast<char *>(copy);
            throw;
        }

        for (size_t i{}; i < m_size; ++i) {
            m_data[i].~T();
        }
        delete[] reinterpret_cast<char *>(m_data);
        m_size = n;
        m_capacity = newCapacity;
        m_data = copy;
    } else {
        for (size_t i{ n }; i < m_size; ++i) {
            m_data[i].~T();
        }
        m_size = n;
    }
}

template <typename T>
void Vector<T>::resize(size_t n) {
    resize(n, T{});
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (m_capacity > m_size) {
        T *copy{ reinterpret_cast<T *>(new char[m_size * sizeof(T)]) };
        size_t index{};
        try {
            for (; index < m_size; ++index) {
                new (copy + index) T{ m_data[index] };
            }
        } catch (...) {
            for (size_t i{}; i < index; ++i) {
                copy[i].~T();
            }

            delete[] reinterpret_cast<char *>(copy);
            throw;
        }

        for (size_t i{}; i < m_size; ++i) {
            m_data[i].~T();
        }
        delete[] reinterpret_cast<char *>(m_data);
        m_capacity = m_size;
        m_data = copy;
    }
}

template <typename T>
T &Vector<T>::front() {
    assert(!empty());
    return *m_data;
}

template <typename T>
const T &Vector<T>::front() const {
    assert(!empty());
    return *m_data;
}

template <typename T>
T &Vector<T>::back() {
    assert(!empty());
    return *(m_data + (m_size - 1));
}

template <typename T>
const T &Vector<T>::back() const {
    assert(!empty());
    return *(m_data + (m_size - 1));
}

template <typename T>
Vector<T>::Iterator Vector<T>::begin() {
    return Iterator{ m_data };
}

template <typename T>
Vector<T>::Iterator Vector<T>::end() {
    return Iterator{ m_data + m_size };
}

template <typename T>
Vector<T>::ConstIterator Vector<T>::begin() const {
    return ConstIterator{ m_data };
}

template <typename T>
Vector<T>::ConstIterator Vector<T>::end() const {
    return ConstIterator{ m_data + m_size };
}

template <typename T>
Vector<T>::ConstIterator Vector<T>::cbegin() const {
    return ConstIterator{ m_data };
}

template <typename T>
Vector<T>::ConstIterator Vector<T>::cend() const {
    return ConstIterator{ m_data + m_size };
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst>::BaseIterator(ptr_type ptr) : m_ptr{ ptr } {}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst>::ref_type Vector<T>::BaseIterator<notConst>::operator*() const {
    return *m_ptr;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> &Vector<T>::BaseIterator<notConst>::operator++() {
    ++m_ptr;
    return *this;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> Vector<T>::BaseIterator<notConst>::operator++(int) {
    BaseIterator copy{ *this };
    ++m_ptr;
    return copy;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst>::ptr_type Vector<T>::BaseIterator<notConst>::operator->() const {
    return m_ptr;
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator==(const BaseIterator &it) const {
    return m_ptr == it.m_ptr;
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator!=(const BaseIterator &it) const {
    return !(m_ptr == (it.m_ptr));
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> &Vector<T>::BaseIterator<notConst>::operator--() {
    --m_ptr;
    return *this;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> Vector<T>::BaseIterator<notConst>::operator--(int) {
    BaseIterator copy{ *this };
    --m_ptr;
    return copy;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> &Vector<T>::BaseIterator<notConst>::operator+=(int number) {
    m_ptr = m_ptr + number;
    return *this;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> Vector<T>::BaseIterator<notConst>::operator+(int number) const {
    return BaseIterator<notConst>{ m_ptr + number };
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> &Vector<T>::BaseIterator<notConst>::operator-=(int number) {
    m_ptr = m_ptr - number;
    return *this;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst> Vector<T>::BaseIterator<notConst>::operator-(int number) const {
    return BaseIterator<notConst>{ m_ptr - number };
}

template <typename T>
template <bool notConst>
int Vector<T>::BaseIterator<notConst>::operator-(const BaseIterator &it) const {
    return m_ptr - it.m_ptr;
}

template <typename T>
template <bool notConst>
Vector<T>::BaseIterator<notConst>::ref_type Vector<T>::BaseIterator<notConst>::operator[](size_t index) const {
    return *(m_ptr + index);
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator<(const BaseIterator &it) const {
    return (it.m_ptr - m_ptr) > 0;
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator>(const BaseIterator &it) const {
    return it < *this;
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator>=(const BaseIterator &it) const {
    return !(*this < it);
}

template <typename T>
template <bool notConst>
bool Vector<T>::BaseIterator<notConst>::operator<=(const BaseIterator &it) const {
    return !(*this > it);
}