/**
* @file Array_test.cpp
* @brief Unit tests for the Array class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-06
*/


#include <cstdlib>
#include "UnitTest.hpp"
#include "Array.hpp"


namespace sl
{


UNITTEST(Array, Size)
{
  Array<int> m(1001UL);
  testEqual(m.size(), 1001UL);
}


UNITTEST(Array, Set)
{
  Array<int> m(5UL);
  m.set(3);

  for (size_t i = 0; i < m.size(); ++i) {
    testEqual(m[i], 3);
  }
}


UNITTEST(Array, Empty)
{
  Array<size_t> m(0UL);
  testEqual(m.size(), 0UL);

  m.set(10);
}




}
