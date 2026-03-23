#include <iostream>
#include <iomanip>
#include "vector.hpp"

bool testEmptyVector()
{
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

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = 
  {
    {"Empty vector", testEmptyVector},
    {"Push back", testPushBack},
    {"Pop back", testPopBack}
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
}
