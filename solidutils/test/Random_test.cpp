/**
* @file Random_test.cpp
* @brief Unit tests for the Random class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-11-01
*/


#include "Random.hpp"
#include "UnitTest.hpp"
#include <vector>


namespace sl
{

UNITTEST(Random, InRange)
{
  int min = 0;
  int max = 5;
  std::vector<bool> mask(max-min, false);

  for (size_t i = 0; i < mask.size()*10000; ++i) {
    int index = Random::inRange(min, max);
    testLess(index, static_cast<int>(mask.size()));
    testGreaterOrEqual(index, 0);
    mask[index] = true;
  }

  for (bool const & val : mask) {
    testTrue(val);
  }
}


UNITTEST(Random, fillWithRangeRaw)
{
  std::vector<int> data1(100);
  std::vector<int> data2(data1.size());

  Random::fillWithRange(data1.data(), data1.size(), 5, 10);
  Random::fillWithRange(data2.data(), data2.size(), 5, 10);

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


UNITTEST(Random, fillWithRangeContainer)
{
  std::vector<int> data1(100);
  std::vector<int> data2(data1.size());

  Random::fillWithRange(&data1, 5, 10);
  Random::fillWithRange(&data2, 5, 10);

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

  Random::fillWithPerm(data1.data(), data1.size());
  Random::fillWithPerm(data2.data(), data2.size());

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

UNITTEST(Random, fillWithPermContainer)
{
  std::vector<int> data1(1000);
  std::vector<int> data2(data1.size());
  std::vector<bool> marker(data1.size(), false);

  Random::fillWithPerm(&data1);
  Random::fillWithPerm(&data2);

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


}
