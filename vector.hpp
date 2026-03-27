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
    Vector(Vector&&) noexcept;
    Vector(size_t size, const T& init);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t index) noexcept;
    const T& operator[](size_t index) const noexcept;
    T& at(size_t index);
    const T& at(size_t index) const;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& elem);
    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t i);
    void erase(size_t start, size_t end);
    void extend(size_t new_cap);

    void swap(Vector< T >& rhs) noexcept;
    
  private:
    T* data_;
    size_t size_;
    size_t cap_;

    explicit Vector(size_t size);
  };

  template< class T >
  bool operator==(const Vector< T >& rhs, const Vector< T >& lhs);
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
T& tarasenko::Vector< T >::operator[](size_t index) noexcept
{
  const Vector< T >* cthis = this;
  return const_cast< T& >((*cthis)[index]);
}

template< class T >
const T& tarasenko::Vector< T >::operator[](size_t index) const noexcept
{
  return data_[index];
}

template< class T >
T& tarasenko::Vector< T >::at(size_t index)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(index));
}

template< class T >
const T& tarasenko::Vector< T >::at(size_t index) const
{
  if (index < getSize())
  {
    return (*this)[index];
  }
  throw std::out_of_range("bad index");
}

template< class T >
tarasenko::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
tarasenko::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  cap_(size)
{}

template< class T >
tarasenko::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
bool tarasenko::operator==(const Vector< T >& rhs, const Vector< T >& lhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

template< class T >
tarasenko::Vector< T >& tarasenko::Vector< T >::operator=(const Vector< T >& rhs)
{
  Vector< T > copy = rhs;
  swap(copy);
  return *this;
}

template< class T >
void tarasenko::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(cap_, rhs.cap_);
}

template< class T >
tarasenko::Vector< T >::Vector(Vector&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  cap_(rhs.cap_)
{
  rhs.data_ = nullptr;
}

template< class T >
tarasenko::Vector< T >& tarasenko::Vector< T >::operator=(Vector&& rhs) noexcept
{
  Vector< T > copy = std::move(rhs);
  swap(copy);
  return *this;
}

template< class T >
void tarasenko::Vector< T >::insert(size_t i, const T& elem)
{
  Vector< T > copy{size_ + 1};
  for (size_t k = 0; k < i; ++k)
  {
    copy[k] = (*this)[k];
  }
  copy[i] = elem;
  for (size_t k = i; k < size_; ++k)
  {
    copy[k + 1] = (*this)[k];
  }
  swap(copy);
}

template< class T >
void tarasenko::Vector< T >::insert(size_t i, const Vector< T >& rhs, size_t start, size_t end)
{
  size_t quantity = end - start;
  Vector< T > copy{size_ + quantity};
  for (size_t k = 0; k < i; ++k)
  {
    copy[k] = (*this)[k];
  }
  for (size_t k = i; k < i + quantity; ++k)
  {
    copy[k] = rhs[start + k - i];
  }
  for (size_t k = i + quantity; k < copy.getSize(); ++k)
  {
    copy[k] = (*this)[k - quantity];
  }
  swap(copy);
}

template< class T >
void tarasenko::Vector< T >::erase(size_t i)
{
  Vector< T > copy{size_ - 1};
  for (size_t k = 0; k < i; ++k)
  {
    copy[k] = (*this)[k];
  }
  for (size_t k = i; k < copy.getSize(); ++k)
  {
    copy[k] = (*this)[k + 1];
  }
  swap(copy);
}

template< class T >
void tarasenko::Vector< T >::erase(size_t start, size_t end)
{
  size_t quantity = end - start;
  Vector< T > copy{size_ - quantity};
  for (size_t i = 0; i < start; ++i)
  {
    copy[i] = (*this)[i];
  }
  for (size_t i = start; i < copy.getSize(); ++i)
  {
    copy[i] = (*this)[i + quantity];
  }
  swap(copy);
}

// строгая гарантия 2 инсерта + 2 эрейза
// + тесты для всего предыдущего
// + дз: итераторы для вектора
// придумать несколько инсертов и эрейзов с итераторами (тоже строгая гарантия (copy and swap))
// например с итераторами из списка
// по 3 штуки
// + тесты этого

#endif
