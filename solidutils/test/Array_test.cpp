/**
* @file Array_test.cpp
* @brief Unit tests for the Array class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018, Solid Lake LLC
* @version 1
* @date 2017-10-06
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
#include "Array.hpp"

#include <cstdlib>


namespace sl
{


UNITTEST(Array, Size)
{
  Array<int> m(1001UL);
  testEqual(m.size(), 1001UL);
}


UNITTEST(Array, Set)
{
  Array<int> m(5UL);
  m.set(3);

  for (size_t i = 0; i < m.size(); ++i) {
    testEqual(m[i], 3);
  }
}


UNITTEST(Array, Empty)
{
  Array<size_t> m(0UL);
  testEqual(m.size(), 0UL);

  m.set(10);
}


UNITTEST(Array, Front)
{
  Array<size_t> m(10UL);
  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = i;
  }

  testEqual(m.front(), 0UL);

  m.front() = 5UL;

  testEqual(m.front(), 5UL);
  testEqual(m[0], 5UL);
}


UNITTEST(Array, Back)
{
  Array<size_t> m(10UL);
  for (size_t i = 0; i < m.size(); ++i) {
    m[i] = i;
  }

  testEqual(m.back(), m.size()-1);

  m.back() = 5UL;

  testEqual(m.back(), 5UL);
  testEqual(m[m.size()-1], 5UL);
}


}
