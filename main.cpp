#include <iostream>
#include <iomanip>
#include "vector.hpp"

bool testEmptyVector()
{
  // std::cout << __func__ << "\n";
  tarasenko::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack()
{
  tarasenko::Vector< int > v;
  v.pushBack(5);
  return v[0] == 5 && v.getSize() == 1;
}

bool testPopBack()
{
  tarasenko::Vector< int > v;
  v.pushBack(5);
  v.pushBack(3);
  v.popBack();
  return v[v.getSize() - 1] == 5 && v.getSize() == 1;
}

bool testElemAccess()
{
  tarasenko::Vector< int > v;
  v.pushBack(5);
  try
  {
    int& val = v.at(0);
    return val == 5;
  }
  catch (...)
  {
    return false;
  }
}

bool testElemOutOfBoundAccess()
{
  tarasenko::Vector< int > v;
  try
  {
    int& val = v.at(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElemAccessConst()
{
  tarasenko::Vector< int > v;
  const tarasenko::Vector< int >& rv = v;
  v.pushBack(5);
  try
  {
    const int& val = v.at(0);
    return val == 5;
  }
  catch (...)
  {
    return false;
  }
}

bool testElemOutOfBoundAccessConst()
{
  tarasenko::Vector< int > v;
  const tarasenko::Vector< int >& rv = v;
  try
  {
    const int& val = v.at(0);
    return false;
  }
  catch (const std::out_of_range &)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = 
  {
    {"Empty vector", testEmptyVector},
    {"Push back", testPushBack},
    {"Pop back", testPopBack},
    {"In bound access", testElemAccess},
    {"Out of bounds access", testElemOutOfBoundAccess},
    {"In bound access const", testElemAccessConst},
    {"Out of bounds access const", testElemOutOfBoundAccessConst}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << tests[i].second() << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
  // количество пройденных/непройденных
  // только не прошедшие выводить
}
