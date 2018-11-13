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
