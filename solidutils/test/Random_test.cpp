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
  std::vector<bool> mask(max-min+1, false);

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

}
