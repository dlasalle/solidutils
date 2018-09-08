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

#include <random>

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

UNITTEST(Sort, FixedKeysRandom)
{
  std::vector<int> keys{0,1,0,2,1,0};

  std::mt19937 rng(0);

  std::unique_ptr<size_t[]> perm1 = Sort::fixedKeysRandom<int, size_t>(keys.data(), \
      keys.size(), rng);
  std::unique_ptr<size_t[]> perm2 = Sort::fixedKeysRandom<int, size_t>(keys.data(), \
      keys.size(), rng);

  // check order
  testLessOrEqual(keys[perm1[0]], keys[perm1[1]]);
  testLessOrEqual(keys[perm1[1]], keys[perm1[2]]);
  testLessOrEqual(keys[perm1[2]], keys[perm1[3]]);
  testLessOrEqual(keys[perm1[3]], keys[perm1[4]]);
  testLessOrEqual(keys[perm1[4]], keys[perm1[5]]);

  testLessOrEqual(keys[perm2[0]], keys[perm2[1]]);
  testLessOrEqual(keys[perm2[1]], keys[perm2[2]]);
  testLessOrEqual(keys[perm2[2]], keys[perm2[3]]);
  testLessOrEqual(keys[perm2[3]], keys[perm2[4]]);
  testLessOrEqual(keys[perm2[4]], keys[perm2[5]]);

  // make sure orders are different
  bool different = false;
  for (size_t i = 0; i < keys.size(); ++i) {
    if (perm1[i] != perm2[i]) {
      different = true;
    }
  }
  testTrue(different);
}



}
