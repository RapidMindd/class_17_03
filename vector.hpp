#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>

namespace tarasenko
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);
    T& operator[](size_t index);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);
    void extend(size_t new_cap);
    
  private:
    T* data_;
    size_t size_;
    size_t cap_;
  };
}

template< class T >
tarasenko::Vector< T >::Vector():
data_(nullptr),
size_(0),
cap_(0)
{}

template< class T >
tarasenko::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
bool tarasenko::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t tarasenko::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t tarasenko::Vector< T >::getCapacity() const noexcept
{
  return cap_;
}

template< class T >
void tarasenko::Vector< T >::extend(size_t new_cap)
{
  if (new_cap <= cap_)
  {
    return;
  }

  T* new_data = new T[new_cap];
  try
  {
    for (size_t i = 0; i < getSize(); ++i)
    {
      new_data[i] = std::move(data_[i]);
    }
  }
  catch (...)
  {
    delete[] new_data;
    throw;
  }

  delete[] data_;
  data_ = new_data;
  cap_ = new_cap;
}

template< class T >
void tarasenko::Vector< T >::pushBack(const T& v)
{
  if (size_ == cap_)
  {
    extend(cap_ ? cap_ * 2 : 2);
  }
  data_[size_] = v;
  ++size_;
}

template< class T >
void tarasenko::Vector< T >::popBack()
{
  if (getSize()) --size_;
}

template< class T >
T& tarasenko::Vector< T >::operator[](size_t index)
{
  return data_[index];
}

#endif