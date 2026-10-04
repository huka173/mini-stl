#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <type_traits>
#include "Node.h"

template <typename T>
class List {
    Node<T> *m_node;
    size_t m_size;

    template <bool notConst>
    class BaseIterator {
        friend class List;
    public:
        using node_ptr_type = std::conditional_t<notConst, Node<T> *, const Node<T> *>;
        using ref_type = std::conditional_t<notConst, T &, const T &>;
        using ptr_type = std::conditional_t<notConst, T *, const T *>;

    private:
        node_ptr_type m_ptr;

    public:
        BaseIterator(node_ptr_type ptr);
        BaseIterator(const BaseIterator &) = default;
        BaseIterator &operator=(const BaseIterator &) = default;

        ref_type operator*() const;
        ptr_type operator->() const;

        BaseIterator &operator++();
        BaseIterator operator++(int);

        BaseIterator &operator--();
        BaseIterator operator--(int);

        bool operator==(const BaseIterator &it) const;
        bool operator!=(const BaseIterator &it) const;
    };

public:
    using Iterator = BaseIterator<true>;
    using ConstIterator = BaseIterator<false>;

    List();
    List(const std::initializer_list<T> list);
    List(const List<T> &copy);

    List<T> &operator=(const List<T> &copy);

    void push_back(const T &value);
    void push_front(const T &value);
    size_t size() const;
    bool empty() const;

    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;

    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;

    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    void pop_back();
    void pop_front();
    void clear();
    void remove(const T &val);
    Iterator erase(Iterator it);

    void swap(List<T> &another) noexcept;

    ~List();
};

#include "List.inl"

#endif // !LIST_H
