/**
* @file ConstArray_test.cpp
* @brief Unit tests for the ConstArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-11-14
*/


#include "UnitTest.hpp"
#include "ConstArray.hpp"
#include "Array.hpp"

#include <cstdlib>
#include <vector>


namespace sl
{


UNITTEST(ConstArray, Size)
{
  ConstArray<int> m(1001UL);
  testEqual(m.size(), 1001UL);
}

UNITTEST(ConstArray, FromArray)
{
  ConstArray<int> m(Array<int>(5, 1));
  testEqual(m.size(), 5UL);

  for (int const v : m) {
    testEqual(v, 1);
  }
}

UNITTEST(ConstArray, FromExternalMemory)
{
  std::vector<int> a(5, 1);
  {
    // make sure the const array is free'd before vector
    ConstArray<int> m(a.data(), a.size());
    testEqual(m.size(), 5UL);

    for (int const v : m) {
      testEqual(v, 1);
    }
  }
}

UNITTEST(ConstArray, Front)
{
  Array<size_t> a(10UL);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = i;
  }
  ConstArray<size_t> m(std::move(a));

  testEqual(m.front(), 0UL);
}


UNITTEST(ConstArray, Back)
{
  Array<size_t> a(10UL);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = i;
  }
  ConstArray<size_t> m(std::move(a));

  testEqual(m.back(), m.size()-1);
}


}
