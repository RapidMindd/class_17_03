#include <iostream>
#include <iomanip>
#include "vector.hpp"

bool testEmptyVector()
{
  // std::cout << __func__ << "\n";
  tarasenko::Vector< int > v;
  return v.isEmpty();
}

bool testAccessOperator()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  return v[0] == 0 && v[9] == 9;
}

bool testAccessOperatorConst()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  const tarasenko::Vector< int >& rv = v;
  return rv[0] == 0 && rv[9] == 9;
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

bool testGetSize()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  return v.getSize() == 10;
}

bool testGetCapacity()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  return v.getCapacity() == 16;
}

bool testExtend()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  v.extend(100);
  return v[0] == 0 && v[9] == 9 && v.getCapacity() == 100 && v.getSize() == 10;
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
    const int& val = rv.at(0);
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
    const int& val = rv.at(0);
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

bool testComparisonOperator()
{
  tarasenko::Vector< int > v(4, 5);
  tarasenko::Vector< int > same_v(4, 5);
  tarasenko::Vector< int > d(4, 5);
  tarasenko::Vector< int > almost_same_d(5, 5);
  return v == same_v && !(d == almost_same_d);
}

bool testCopyConstructorEmpty()
{
  tarasenko::Vector< int > v;
  tarasenko::Vector< int > another = v;
  return v == another;
}

bool testCopyConstructorNonEmpty()
{
  tarasenko::Vector< int > v;
  v.pushBack(1);
  tarasenko::Vector< int > another = v;
  return v == another;
}

bool testMoveConstructorEmpty()
{
  tarasenko::Vector< int > v;
  tarasenko::Vector< int > copy = v;
  tarasenko::Vector< int > another = std::move(v);
  return another == copy;
}

bool testMoveConstructorNonEmpty()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  tarasenko::Vector< int > copy = v;
  tarasenko::Vector< int > another = std::move(v);
  return another == copy;
}

bool testInitConstructor()
{
  tarasenko::Vector< int > v(2, 5);
  return v.getSize() == 2 && v[0] == 5 && v[1] == 5;
}

bool testCopyAssignmentEmpty()
{
  tarasenko::Vector< int > v;
  tarasenko::Vector< int > another(2, 5);
  another = v;
  return another == v;
}

bool testCopyAssignmentNonEmpty()
{
  tarasenko::Vector< int > v(4, 1);
  tarasenko::Vector< int > another(2, 5);
  another = v;
  return another == v;
}

bool testMoveAssignmentEmpty()
{
  tarasenko::Vector< int > v;
  tarasenko::Vector< int > copy = v;
  tarasenko::Vector< int > another(2, 5);
  another = std::move(v);
  return another == copy;
}

bool testMoveAssignmentNonEmpty()
{
  tarasenko::Vector< int > v(4, 1);
  tarasenko::Vector< int > copy = v;
  tarasenko::Vector< int > another(2, 5);
  another = std::move(v);
  return another == copy;
}

bool testSwap()
{
  tarasenko::Vector< int > v(5, 6);
  tarasenko::Vector< int > another(7, 8);
  tarasenko::Vector< int > v_copy = v;
  tarasenko::Vector< int > another_copy = another;
  v.swap(another);
  return v == another_copy && another == v_copy;
}

bool testSelfCopyAssignment()
{
  tarasenko::Vector< int > v(5, 6);
  tarasenko::Vector< int > copy = v;
  v = v;
  return v == copy;
}

bool testSelfMoveAssignment()
{
  tarasenko::Vector< int > v(5, 6);
  tarasenko::Vector< int > copy = v;
  v = std::move(v);
  return v == copy;
}

bool testInsertOneElem()
{
  tarasenko::Vector< int > v(5, 6);
  v.insert(3, 4);
  return v.getSize() == 6 && v[3] == 4;
}

bool testInsertSeveralElems()
{
  tarasenko::Vector< int > v(5, 6);
  tarasenko::Vector< int > another;
  for (size_t i = 0; i < 10; ++i)
  {
    another.pushBack(i);
  }
  v.insert(3, another, 2, 5);
  return v.getSize() == 8 && v[0] == 6 && v[5] == 4 && v[7] == 6;
}

bool testEraseOneElem()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  v.erase(5);
  return v.getSize() == 9 && v[4] == 4 && v[5] == 6;
}

bool testEraseSeveralElems()
{
  tarasenko::Vector< int > v;
  for (size_t i = 0; i < 10; ++i)
  {
    v.pushBack(i);
  }
  v.erase(2, 5);
  return v.getSize() == 7 && v[1] == 1 && v[2] == 5;
}

bool testInitializerList()
{
  tarasenko::Vector< int > v({1, 2, 3});
  return v[0] == 1 && v[1] == 2 && v[2] == 3 && v.getSize() == 3;
}


int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] =
  {
    {"Empty vector", testEmptyVector},
    {"Access operator", testAccessOperator},
    {"Access operator const", testAccessOperatorConst},
    {"Push back", testPushBack},
    {"Pop back", testPopBack},
    {"Get size", testGetSize},
    {"Get capacity", testGetCapacity},
    {"Extend", testExtend},
    {"In bound access", testElemAccess},
    {"Out of bounds access", testElemOutOfBoundAccess},
    {"In bound access const", testElemAccessConst},
    {"Out of bounds access const", testElemOutOfBoundAccessConst},
    {"Comparison operator", testComparisonOperator},
    {"Copy empty vector", testCopyConstructorEmpty},
    {"Copy non-empty vector", testCopyConstructorNonEmpty},
    {"Init constructor", testInitConstructor},
    {"Copy assignment empty", testCopyAssignmentEmpty},
    {"Copy assignment non-empty", testCopyAssignmentNonEmpty},
    {"Move assignment empty", testMoveAssignmentEmpty},
    {"Move assignment non-empty", testMoveAssignmentNonEmpty},
    {"Swap", testSwap},
    {"Copy assignment to itself", testSelfCopyAssignment},
    {"Move assignment to itself", testSelfMoveAssignment},
    {"Insert one elem", testInsertOneElem},
    {"Insert several elems", testInsertSeveralElems},
    {"Erase one elem", testEraseOneElem},
    {"Erase several elems", testEraseSeveralElems},
    {"Initializer list", testInitializerList}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
  // количество пройденных/непройденных
  // только не прошедшие выводить
}
