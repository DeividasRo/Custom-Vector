#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <stdexcept>
#include <memory>

template <class T>
class Vector
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;

    Vector() { Create(); }
    explicit Vector(size_t n, const T &val = T{}) { Create(n, val); }
    Vector(std::initializer_list<T> v_list) { Create(v_list.begin(), v_list.end()); }
    Vector(iterator begin, iterator end) { Create(begin, end); }
    // rule of 3
    Vector(const Vector &v) { Create(v.begin(), v.end()); }
    Vector &operator=(const Vector &other)
    {
        if (&other != this)
        {
            Uncreate();
            Create(other.begin(), other.end());
        }
        return *this;
    }
    Vector &operator=(Vector &other)
    {
        if (&other == this)
        {
            return *this;
        }
        Uncreate();
        Create(other.begin(), other.end());
        return *this;
    }
    ~Vector() { Uncreate(); }

    T &
    operator[](size_t i)
    {
        if (i < 0 || i > size())
            throw std::out_of_range("Index out of range.");
        return data[i];
    }
    const T &operator[](size_t i) const
    {
        if (i < 0 || i > size())
            throw std::out_of_range("Index out of range.");
        return data[i];
    }
    T &at(size_t pos) { return data[pos]; }
    T back() { return *(avail - 1); }
    T front() { return data[0]; }

    bool operator>(const Vector<T> &v) const;
    bool operator<(const Vector<T> &v) const;
    bool operator>=(const Vector<T> &v) const;
    bool operator<=(const Vector<T> &v) const;
    bool operator==(const Vector<T> &v) const;
    bool operator!=(const Vector<T> &v) const;

    void push_back(const T &);
    void pop_back();
    void assign(size_t n, const T &val);
    void assign(std::initializer_list<T> list);
    void assign(const_iterator i, const_iterator j);
    void erase(const_iterator position);
    void erase(const_iterator first, const_iterator last);
    void resize(size_t n, const T &val);
    void resize(size_t n);
    void swap(Vector<T> &v);
    void clear();
    void shrink_to_fit();
    void reserve(size_t n);
    bool empty();

    size_t size() const { return avail - data; }
    size_t capacity() const { return limit - data; }
    iterator begin() { return data; }
    const_iterator begin() const { return data; }
    iterator end() { return avail; }
    const_iterator end() const { return avail; }

private:
    iterator data;  // ant pirmo el.
    iterator avail; // po paskutinio el.
    iterator limit; // po paskutines uzrezervuotos vietos

    std::allocator<T> alloc;

    void Create();
    void Create(size_t, const T &);
    void Create(const_iterator, const_iterator);
    void Uncreate();
    void Grow();
    void Unchecked_append(const T &);
};

// private funkcijos

template <typename T>
void Vector<T>::Create()
{
    data = avail = limit = nullptr;
}

template <typename T>
void Vector<T>::Create(size_t n, const T &val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template <typename T>
void Vector<T>::Create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <typename T>
void Vector<T>::Uncreate()
{
    if (data)
    {
        while (avail != data)
            alloc.destroy(--avail);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}

template <typename T>
void Vector<T>::Grow()
{
    size_t new_size = std::max(2 * (limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    Uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T>
void Vector<T>::Unchecked_append(const T &value)
{
    alloc.construct(avail++, value);
}

// operatoriai

template <typename T>
bool Vector<T>::operator>(const Vector<T> &v) const
{
    return !operator<=(v);
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T> &v) const
{
    return !operator<(v);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T> &v) const
{
    if (operator==(v))
        return false;
    else
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            if (data[i] > v.data[i])
                return false;
        }
        return true;
    }
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T> &v) const
{

    if (operator==(v))
        return true;
    else
        return operator<(v);
}

template <typename T>
bool Vector<T>::operator==(const Vector<T> &v) const
{
    if (v.size() != this->size())
        return false;
    else
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            if (data[i] != v.data[i])
                return false;
        }
        return true;
    }
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T> &v) const
{
    if (v.size() != this->size())
        return true;
    else
    {
        for (size_t i = 0; i < v.size; i++)
        {
            if (data[i] != v.data[i])
                return true;
        }
        return false;
    }
}

// public member funkcijos

template <typename T>
void Vector<T>::push_back(const T &val)
{
    if (avail == limit)
        Grow();
    Unchecked_append(val);
}

template <typename T>
void Vector<T>::pop_back()
{
    alloc.destroy(--avail); // -- -> destroy
}

template <typename T>
void Vector<T>::assign(const_iterator i, const_iterator j)
{
    Uncreate();
    Create(i, j);
}

template <typename T>
void Vector<T>::assign(size_t n, const T &value)
{
    Uncreate();
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, value);
}
template <typename T>
void Vector<T>::assign(std::initializer_list<T> v_list)
{
    assign(v_list.begin(), v_list.end());
}

template <typename T>
void Vector<T>::erase(Vector<T>::const_iterator position)
{
    if (position < data || position > avail)
        throw std::out_of_range{"Out of bounds."};
    iterator new_avail = std::move(position + 1, avail, position);
    alloc.destroy(new_avail);
    avail = new_avail;
}

template <typename T>
void Vector<T>::erase(Vector<T>::const_iterator first, const_iterator last)
{
    if (first < data || last > avail)
        throw std::out_of_range{"Out of bounds."};
    avail = std::move(last, avail, first);
    ;
}

template <typename T>
void Vector<T>::resize(size_t n, const T &value)
{
    if (n > capacity())
    {
        Grow();
        resize(n, value);
    }
    else if (n > size())
    {
        avail += (n - size());

        for (size_t i = size(); i < n; i++)
        {
            data[i] = value;
        }
    }
    else
        resize(n);
}

template <typename T>
void Vector<T>::resize(size_t n)
{
    if (n < size())
    {
        while (avail != begin() + n)
        {
            alloc.destroy(--avail);
        }
        avail = begin() + n;
    }
    else if (n > capacity())
    {
        Grow();
        resize(n);
    }
    else if (n > size())
    {
        avail += (n - size());
    }
}

template <typename T>
void Vector<T>::swap(Vector<T> &v)
{
    iterator data_t = data, avail_t = avail, limit_t = limit;
    data = v.data;
    limit = v.limit;
    avail = v.avail;

    v.data = data_t;
    v.avail = avail_t;
    v.limit = limit_t;
}

template <typename T>
void Vector<T>::clear()
{
    while (avail != data)
    {
        alloc.destroy(--avail);
    }
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (avail < limit)
        limit = avail;
}

template <typename T>
void Vector<T>::reserve(size_t n)
{
    if (n > capacity())
    {
        Uncreate();
        data = alloc.allocate(n);
        avail = std::uninitialized_copy(data, avail, data);
        limit = data + n;
    }
}

template <typename T>
bool Vector<T>::empty()
{
    return begin() == end();
}

#endif