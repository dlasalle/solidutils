/**
* @file Debug_test.cpp
* @brief Unit tests for the Debug.hpp file.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-11-06
*/


#include "UnitTest.hpp"
#include "Debug.hpp"
#include <memory>


namespace sl
{

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
  debugMessage("start");
  debugMessage("test: %d %d %d", 1, 2, 3);
  debugMessage(std::string("end"));
}

}
