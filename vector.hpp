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
    bool empty() const noexcept;
  private:
    T* data_;
    size_t size_;
    size_t cap_;
  };
}

template< class T >
tarasenko::Vector< T >::Vector():
data_(),
size_(),
cap_()
{}

template< class T >
tarasenko::Vector< T >::~Vector()
{}

template< class T >
bool tarasenko::Vector< T >::empty() const noexcept
{
  return false;
}

#endif