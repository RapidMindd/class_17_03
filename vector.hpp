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

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);
    
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
bool tarasenko::Vector< T >::empty() const noexcept
{
  return !size_;
}

template< class T >
void tarasenko::Vector< T >::pushBack(const T& v)
{

}

#endif