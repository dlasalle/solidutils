/**
* @file ConstArray_test.cpp
* @brief Unit tests for the ConstArray class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-11-14
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
#include "ConstArray.hpp"
#include "Array.hpp"

#include <cstdlib>
#include <vector>


namespace sl
{


UNITTEST(ConstArray, Size)
{
  ConstArray<int> m(1001UL);
  testEqual(m.size(), 1001UL);
}

UNITTEST(ConstArray, FromArray)
{
  ConstArray<int> m(Array<int>(5, 1));
  testEqual(m.size(), 5UL);

  for (int const v : m) {
    testEqual(v, 1);
  }
}

UNITTEST(ConstArray, FromExternalMemory)
{
  std::vector<int> a(5, 1);
  {
    // make sure the const array is free'd before vector
    ConstArray<int> m(a.data(), a.size());
    testEqual(m.size(), 5UL);

    for (int const v : m) {
      testEqual(v, 1);
    }
  }
}

UNITTEST(ConstArray, Front)
{
  Array<size_t> a(10UL);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = i;
  }
  ConstArray<size_t> m(std::move(a));

  testEqual(m.front(), 0UL);
}


UNITTEST(ConstArray, Back)
{
  Array<size_t> a(10UL);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = i;
  }
  ConstArray<size_t> m(std::move(a));

  testEqual(m.back(), m.size()-1);
}


}
