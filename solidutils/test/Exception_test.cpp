/**
* @file Exception_test.cpp
* @brief Unit tests for the base exceptions.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-11-08
*/


#include "UnitTest.hpp"
#include "Exception.hpp"


namespace sl
{


UNITTEST(Exception, InvalidInputException)
{
  try {
    throw InvalidInputException("test-input");
  } catch (InvalidInputException const & ex) {
    std::string msg = ex.what();
    testEqual(msg, "Invalid input: test-input");
  } catch (...) {
    testFail() << "Unknown exception thrown.";
  }
}


}
