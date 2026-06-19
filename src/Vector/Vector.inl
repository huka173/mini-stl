template <typename T>
Vector<T>::Vector(size_t size) :
    m_size{ size },
    m_data{ new T[size]{} },
    m_capacity{ size } {
}

template <typename T>
Vector<T>::Vector(size_t size, const T &value) {

}

template <typename T>
const T &Vector<T>::operator[](size_t index) const {

}