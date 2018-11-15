/**
* @file Debug_test.cpp
* @brief Unit tests for the Debug.hpp file.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-11-06
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
#include "Debug.hpp"
#include <memory>


UNITTEST(Debug, Asserts)
{
  std::unique_ptr<int> mem(new int[1]);

  // we can't actually unit test assert-ness, but just that things compile and
  // do not fail
  ASSERT_TRUE(true);
  ASSERT_FALSE(false);
  ASSERT_EQUAL(3, 3);
  ASSERT_NOTEQUAL(2, 3);
  ASSERT_NULL(static_cast<int*>(nullptr));
  ASSERT_NOTNULL(mem.get());
  ASSERT_LESS(1, 2);
  ASSERT_LESSEQUAL(2, 2);
  ASSERT_LESSEQUAL(2, 3);
  ASSERT_GREATER(10, 5);
  ASSERT_GREATEREQUAL(10, 10);
  ASSERT_GREATEREQUAL(10, 5);
}


UNITTEST(Debug, DebugMessage)
{
  DEBUG_MESSAGE("start");
  DEBUG_MESSAGE("test: %d %d %d", 1, 2, 3);
  DEBUG_MESSAGE(std::string("end"));
}
