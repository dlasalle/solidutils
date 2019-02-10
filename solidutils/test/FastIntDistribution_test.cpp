/**
* @file FastIntDistribution_test.cpp
* @brief Unit tests for the FastIntDistribution class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2019-02-09
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/



#include "UnitTest.hpp"
#include "FastIntDistribution.hpp"

#include <random>
#include <limits>


namespace sl
{


UNITTEST(FastIntDistribution, Int1To10)
{
  std::mt19937 rng(0);

  std::vector<bool> hits(10);

  FastIntDistribution<int> dist(1, 10);

  for (size_t i = 0; i < hits.size()*hits.size()*hits.size(); ++i) {
    int const num = dist(rng);

    testGreaterOrEqual(num, 1);
    testLessOrEqual(num, 10);

    hits[num-1] = true;
  }

  for (size_t i = 0; i < hits.size(); ++i) {
    testTrue(hits[i]) << "i = " << i;
  }
}


UNITTEST(FastIntDistribution, Int5To5)
{
  std::mt19937 rng(0);

  std::vector<bool> hits(11);

  FastIntDistribution<int> dist(-5, 5);

  for (size_t i = 0; i < hits.size()*hits.size()*hits.size(); ++i) {
    int const num = dist(rng);

    testGreaterOrEqual(num, -5);
    testLessOrEqual(num, 5);

    hits[num+5] = true;
  }

  for (size_t i = 0; i < hits.size(); ++i) {
    testTrue(hits[i]) << "i = " << i;
  }
}

UNITTEST(FastIntDistribution, Int641To2_40)
{
  std::mt19937 rng(0);

  FastIntDistribution<int64_t> dist(0, 1LL<<40);

  bool aboveMax;
  for (size_t i = 0; i < 10000; ++i) {
    int64_t const num = dist(rng);

    testGreaterOrEqual(num, 0);
    testLessOrEqual(num, 1LL<<40);

    if (num > static_cast<int64_t>(std::numeric_limits<uint32_t>::max())) {
      aboveMax = true;
    }
  }

  testTrue(aboveMax);
}

}
