/**
 * @file VectorMath_test.cpp
 * @brief Unit tests for the VectorMath class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2017-10-11
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
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


UNITTEST(Array, PrefixSumExclusivePointer)
{
  std::vector<size_t> m(3UL);

  m[0] = 3;
  m[1] = 1;
  m[2] = 2;

  VectorMath::prefixSumExclusive(m.data(), m.size());

  testEqual(m[0], 0u);
  testEqual(m[1], 3u);
  testEqual(m[2], 4u);
}


UNITTEST(Array, PrefixSumExclusiveIterator)
{
  std::vector<size_t> m(3UL);

  m[0] = 3;
  m[1] = 1;
  m[2] = 2;

  VectorMath::prefixSumExclusive(m.data(), m.data() + m.size());

  testEqual(m[0], 0u);
  testEqual(m[1], 3u);
  testEqual(m[2], 4u);
}




}
