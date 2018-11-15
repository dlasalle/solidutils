/**
* @file Random_test.cpp
* @brief Unit tests for the Random class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018, Solid Lake LLC
* @version 1
* @date 2017-11-01
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




#include "Random.hpp"
#include "UnitTest.hpp"

#include <vector>
#include <random>


namespace sl
{

UNITTEST(Random, fillWithRange)
{
  std::vector<int> data1(100);
  std::vector<int> data2(data1.size());

  std::mt19937 rng(0);

  Random::fillWithRange(data1.data(), data1.size(), 5, 10, rng);
  Random::fillWithRange(data2.data(), data2.size(), 5, 10, rng);

  // check range
  for (int const & num : data1) {
    testGreaterOrEqual(num, 5);
    testLess(num, 10);
  }

  // make sure two are not the same
  bool same = true;
  for (size_t i = 0; i < data1.size(); ++i) {
    if (data1[i] != data2[i]) {
      same = false;
    }
  }
  testFalse(same);
}


UNITTEST(Random, fillWithPermRaw)
{
  std::vector<int> data1(1000);
  std::vector<int> data2(data1.size());
  std::vector<bool> marker(data1.size(), false);

  std::mt19937 rng(0);

  Random::fillWithPerm(data1.data(), data1.size(), 0, rng);
  Random::fillWithPerm(data2.data(), data2.size(), 0, rng);

  // make sure all parts are covered
  for (int const & num : data1) {
    testFalse(marker[num]);
    marker[num] = true;
  }
  for (bool const & mark : marker) {
    testTrue(mark);
  }

  // make sure two permutations are not the same
  bool same = true;
  for (size_t i = 0; i < data1.size(); ++i) {
    if (data1[i] != data2[i]) {
      same = false;
    }
  }
  testFalse(same);
}


UNITTEST(Random, pseudoShuffleSane)
{
  std::vector<int> data(1000);
  std::vector<bool> marker(data.size(), false);

  std::mt19937 rng(0);

  Random::pseudoShuffle(data.data(), data.size(), rng);

  for (size_t i = 0; i < data.size(); ++i) {
    testFalse(marker[i]);
    marker[i] = true;
  }

  for (bool const mark : marker) {
    testTrue(mark);
  }
}

UNITTEST(Random, pseudoShuffleDifferent)
{
  std::vector<int> data1(1000);
  std::vector<int> data2(1000);

  for (size_t i = 0; i < data1.size(); ++i) {
    data1[i] = static_cast<int>(i);
    data2[i] = static_cast<int>(i);
  }

  std::mt19937 rng(0);

  Random::pseudoShuffle(data1.data(), data1.size(), rng);
  Random::pseudoShuffle(data2.data(), data2.size(), rng);

  // expect many differences
  size_t difference = 0;
  for (size_t i = 0; i < data1.size(); ++i) {
    if (data1[i] != data2[i]) {
      ++difference;
    }
  }

  testGreater(difference, 900UL);
}



}
