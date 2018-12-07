/**
* @file FixedSet_test.cpp
* @brief Unit tests for the FixedSet class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018, Solid Lake LLC
* @version 1
* @date 2017-10-19
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




#include "FixedSet.hpp"
#include "UnitTest.hpp"

#include <vector>
#include <algorithm>


namespace sl
{

UNITTEST(FixedSet, SizeAddRemove)
{
  FixedSet<int> set(10);

  testEqual(set.size(), 0u);

  set.add(2);
  set.add(6);

  testEqual(set.size(), 2u);

  set.remove(6);

  testEqual(set.size(), 1u);

  set.remove(2);

  testEqual(set.size(), 0u);
}

UNITTEST(FixedSet, HasAddRemove)
{
  FixedSet<int> set(10);

  testFalse(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(5));

  set.add(0);
  set.add(2);
  set.add(5);

  testTrue(set.has(0));
  testTrue(set.has(2));
  testTrue(set.has(5));

  set.remove(2);
  set.remove(5);

  testTrue(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(5));

  set.add(3);
  set.add(2);

  testTrue(set.has(0));
  testTrue(set.has(2));
  testTrue(set.has(3));

  set.remove(3);
  set.remove(0);
  set.remove(2);

  testFalse(set.has(0));
  testFalse(set.has(2));
  testFalse(set.has(3));
}

UNITTEST(FixedSet, Iterator)
{
  std::vector<int> base{1, 5, 3, 6};
  FixedSet<int> set(10);

  for (int const & v : base) {
    set.add(v);
  }

  for (int const v : set) {
    testTrue(std::find(base.begin(), base.end(), v) != base.end());
  }
}


}
