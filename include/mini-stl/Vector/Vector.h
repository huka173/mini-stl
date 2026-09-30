#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <type_traits>

template <typename T>
class Vector {
    T *m_data{ nullptr };
    size_t m_size{};
    size_t m_capacity{};

    template <bool notConst>
    class BaseIterator {
    public:
        using ptr_type = std::conditional_t<notConst, T *, const T *>;
        using ref_type = std::conditional_t<notConst, T &, const T &>;

    private:
        ptr_type m_ptr;

    public:
        BaseIterator(ptr_type ptr);
        BaseIterator(const BaseIterator &) = default;
        BaseIterator &operator=(const BaseIterator &) = default;

        ref_type operator*() const;
        ptr_type operator->() const;

        BaseIterator &operator++();
        BaseIterator operator++(int);

        BaseIterator &operator--();
        BaseIterator operator--(int);

        BaseIterator operator+(int number) const;
        friend BaseIterator operator+(int number, const BaseIterator &it) {
            return it + number;
        }

        BaseIterator operator-(int number) const;
        int operator-(const BaseIterator &it) const;

        BaseIterator &operator+=(int number);
        BaseIterator &operator-=(int number);

        ref_type operator[](size_t index) const;

        bool operator!=(const BaseIterator &it) const;
        bool operator<(const BaseIterator &it) const;
        bool operator>(const BaseIterator &it) const;
        bool operator>=(const BaseIterator &it) const;
        bool operator<=(const BaseIterator &it) const;
        bool operator==(const BaseIterator &it) const;
    };

public:
    using Iterator = BaseIterator<true>;
    using ConstIterator = BaseIterator<false>;
    
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

    Iterator begin();
    ConstIterator begin() const;
    ConstIterator cbegin() const;

    Iterator end();
    ConstIterator end() const;
    ConstIterator cend() const;
};

#include "Vector.inl";

#endif // VECTOR_H
