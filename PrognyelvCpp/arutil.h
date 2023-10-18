#ifndef ARRAY_UTIL
#define ARRAY_UTIL

#include <cstdlib>
#include <vector>
#include <algorithm>

template <typename T>
class array_util {
public:
    array_util ();
    explicit array_util (std::vector<T>&);
    array_util(T*, size_t);

    [[nodiscard]] const T& operator[] (int index) const;

    bool operator== (const array_util<T>&) const;
    bool equals (const array_util<T>&) const;

    void copy (const array_util<T>&);
    array_util<T>& operator= (const array_util<T>&);

    bool permutation (const array_util<T>&) const;

    size_t size() const;

private:
    bool _equal(const array_util<T>&) const;
    void _copy (const array_util<T>&);

    size_t  _size;
    T *_arr;
};




template<typename T>
array_util<T>::array_util () {
    _size = 0;
    _arr = nullptr;
}

template<typename T>
array_util<T>::array_util (std::vector<T> &vector) {
    _size = vector.size();
    _arr = &vector[0];
    //_arr = new T[vector.size()];
    //std::copy(vector.begin(), vector.end(), _arr);
}

template<typename T>
array_util<T>::array_util (T *arr, size_t size) {
    _size = size;
    _arr = arr;
    /*_arr = new T[_size];
    for (size_t i = 0; i < _size; ++i) {
        _arr[i] = arr[i];
    }*/
}


template<typename T>
size_t array_util<T>::size() const {
    return _size;
}



template<typename T>
bool array_util<T>::_equal (const array_util<T> &arr) const {
    if (this->_size == arr._size) {
        for (size_t i = 0; i < _size; ++i) {
            if (_arr[i] != arr[i]) return false;
        }
    } else return false;
    return true;
}

template<typename T>
bool array_util<T>::equals (const array_util<T> &rhs) const {
    return _equal(rhs);
}

template<typename T>
bool array_util<T>::operator== (const array_util<T> &rhs) const {
    return _equal(rhs);
}



template<typename T>
const T &array_util<T>::operator[] (int index) const {
    if (index > (int)_size) throw std::out_of_range("Index was out of bounds of array_util");
    return _arr[index];
}



template<typename T>
void array_util<T>::_copy (const array_util<T> &source) {
    for (size_t i = 0; (i < _size) && (i < source.size()); ++i) {
        _arr[i] = source[i];
    }
}

template<typename T>
void array_util<T>::copy (const array_util<T> &source) {
    _copy(source);
}

template<typename T>
array_util<T>& array_util<T>::operator= (const array_util<T> &source) {
    if (this == &source) return *this;
    _copy(source);
    return *this;
}

template<typename T>
bool array_util<T>::permutation(const array_util<T> &other) const {
    bool result = true;
    for (size_t i = 0; i < _size; ++i) {
        bool has_elem = false;
        for (size_t j = 0; j < other.size(); ++j) {
            has_elem = has_elem || _arr[i] == other[j];
        }
        result = result && has_elem;
        if (!result) return false;
    }
    return result;
}


#endif