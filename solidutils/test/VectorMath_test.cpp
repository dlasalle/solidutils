/**
* @file VectorMath_test.cpp
* @brief Unit tests for the VectorMath class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-11
*/



#include "VectorMath.hpp"
#include "UnitTest.hpp"
#include <vector>



namespace sl
{


UNITTEST(VectorMath, Sum)
{
  std::vector<int> m{2, 3, 1, -2, 4, 9};

  int const sum = VectorMath::sum(m.data(), m.size());

  int val = 0;
  for (size_t i = 0; i < m.size(); ++i) {
    val += m[i];
  }
  testEqual(sum, val);
}


UNITTEST(VectorMath, Increment)
{
  std::vector<int> m(5UL);

  VectorMath::increment(m.data(), m.size(), 1, 2);

  int val = 1;
  for (size_t i = 0; i < m.size(); ++i) {
    testEqual(m[i], val);
    val += 2;
  }
}


UNITTEST(Array, PrefixSumExclusive)
{
  std::vector<size_t> m(3UL);

  m[0] = 3;
  m[1] = 1;
  m[2] = 2;

  VectorMath::prefixSumExclusive(m.data(), m.size());

  testEqual(m[0], 0);
  testEqual(m[1], 3);
  testEqual(m[2], 4);
}





}
