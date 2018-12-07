/**
* @file FixedMap_test.cpp
* @brief Unit tests for the FixedMap class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-12-05
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




#include "FixedMap.hpp"
#include "UnitTest.hpp"

#include <vector>
#include <algorithm>


namespace sl
{

UNITTEST(FixedMap, SizeAddRemove)
{
  FixedMap<int, float> map(10);

  testEqual(map.size(), 0u);

  map.add(2, 1.0);
  map.add(6, 3.0);

  testEqual(map.size(), 2u);

  map.remove(6);

  testEqual(map.size(), 1u);

  map.remove(2);

  testEqual(map.size(), 0u);
}

UNITTEST(FixedMap, Get)
{
  FixedMap<int, float> map(10);

  map.add(0, 1.0);
  map.add(2, 2.0);
  map.add(5, 0.0);

  testEqual(map.get(0), 1.0);
  testEqual(map.get(2), 2.0);
  testEqual(map.get(5), 0.0);
}

UNITTEST(FixedMap, Has)
{
  FixedMap<int, float> map(10);

  testFalse(map.has(0));
  testFalse(map.has(1));
  testFalse(map.has(2));
  testFalse(map.has(3));
  testFalse(map.has(4));
  testFalse(map.has(5));
  testFalse(map.has(6));
  testFalse(map.has(7));
  testFalse(map.has(8));
  testFalse(map.has(9));

  map.add(0, 1.0);
  map.add(2, 2.0);
  map.add(5, 0.0);

  testTrue(map.has(0));
  testFalse(map.has(1));
  testTrue(map.has(2));
  testFalse(map.has(3));
  testFalse(map.has(4));
  testTrue(map.has(5));
  testFalse(map.has(6));
  testFalse(map.has(7));
  testFalse(map.has(8));
  testFalse(map.has(9));
}

UNITTEST(FixedMap, Remove)
{
  FixedMap<int, float> map(10);

  map.add(0, 1.0);
  map.add(2, 2.0);
  map.add(5, 0.0);

  map.remove(2);

  testTrue(map.has(0));
  testFalse(map.has(1));
  testFalse(map.has(2));
  testFalse(map.has(3));
  testFalse(map.has(4));
  testTrue(map.has(5));
  testFalse(map.has(6));
  testFalse(map.has(7));
  testFalse(map.has(8));
  testFalse(map.has(9));

  map.remove(0);

  testFalse(map.has(0));
  testFalse(map.has(0));
  testFalse(map.has(1));
  testFalse(map.has(2));
  testFalse(map.has(3));
  testFalse(map.has(4));
  testTrue(map.has(5));
  testFalse(map.has(6));
  testFalse(map.has(7));
  testFalse(map.has(8));
  testFalse(map.has(9));
}

UNITTEST(FixedMap, Keys)
{
  FixedMap<int, float> map(10);

  map.add(0, 1.0);
  map.add(2, 2.0);
  map.add(5, 0.0);

  std::vector<bool> mask(map.size(), false);

  testEqual(map.keys().size(), 3ULL);
  for (int const key : map.keys()) {
    mask[key] = true;
  }

  testTrue(mask[0]);
  testTrue(mask[2]);
  testTrue(mask[5]);
}


UNITTEST(FixedMap, Values)
{
  FixedMap<int, float> map(10);

  map.add(0, 1.0);
  map.add(2, 2.0);
  map.add(5, 0.0);

  testEqual(map.values().size(), 3ULL);
  float sum = 0;
  for (float const value : map.values()) {
    sum += value;
  }

  testNearEqual(sum, 3.0, 1e-9, 1e-9);
}


}

