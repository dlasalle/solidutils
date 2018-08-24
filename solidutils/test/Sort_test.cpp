/**
* @file Sort_test.cpp
* @brief Unit tests for the Sort class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/


#include "Sort.hpp"
#include "UnitTest.hpp"

namespace sl
{

UNITTEST(Sort, FixedKeys)
{
  std::vector<int> keys{0,5,2,3,4,1,1,3};

  std::unique_ptr<size_t[]> perm = Sort::fixedKeys<int, size_t>(keys.data(), \
      keys.size());
  
  testEqual(perm[0], 0UL);
  testEqual(perm[1], 5UL);
  testEqual(perm[2], 6UL);
  testEqual(perm[3], 2UL);
  testEqual(perm[4], 3UL);
  testEqual(perm[5], 7UL);
  testEqual(perm[6], 4UL);
}

}
