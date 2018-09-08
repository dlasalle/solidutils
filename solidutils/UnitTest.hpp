/**
 * @file UnitTest.hpp
 * @brief Top level header for UnitTest
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2015-2017, Dominique LaSalle
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2015-08-22
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */




#ifndef SOLIDUTILS_INCLUDE_UNITTEST_HPP
#define SOLIDUTILS_INCLUDE_UNITTEST_HPP


#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>
#include <sstream>

#include <cmath>


/******************************************************************************
* CLASSES AND TYPES ***********************************************************
******************************************************************************/

namespace sl
{


volatile int _unittest_numberFailed = 0;
volatile int _unittest_numberPassed = 0;


namespace
{


class TestFailed : public std::logic_error
{
  public:
    TestFailed(std::string const & str) :
        std::logic_error(str)
    {
      // do nothing
    }
};


class TestStream
{
  public:
    TestStream() :
      m_stream(),
      m_fail(false)
    {
      // do nothing
    }


    ~TestStream() noexcept(false)
    {
      if (m_fail) {
        // write new line
        std::cerr << std::endl;
        // throw our error
        throw TestFailed("Unit test failed.");
      }
    }


    std::ostream & test()
    {
      if (m_fail) {
        return std::cerr << "Test Failed: ";
      } else {
        return m_stream;
      }
    }


    std::ostream & testFail()
    {
      m_fail = true;

      return test();
    }


    std::ostream & testEqual(
        std::string const & a,
        std::string const & b)
    {
      if (!m_fail) {
        m_fail = !(a.compare(b) == 0);
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testEqual(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = !(a == b);
      }

      return test();
    }


    std::ostream & testNearEqual(
        double const a,
        double const b,
        double const ratio = 1e-6,
        double const buffer = 1e-9)
    {
      if (std::abs(a - b) <= buffer) {
        m_fail = false;
      } else if (-a == b) {
        m_fail = true;
      } else {
        m_fail = std::abs((a-b)/(a+b)) >= ratio;
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testNotEqual(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = (a == b);
      }

      return test();
    }


    std::ostream & testTrue(
        bool const pass)
    {
      if (!m_fail) {
        m_fail = !pass;
      }

      return test();
    }


    std::ostream & testFalse(
        bool const fail)
    {
      if (!m_fail) {
        m_fail = fail;
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testGreater(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = !(a > b);
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testGreaterOrEqual(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = !(a >= b);
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testLess(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = !(a < b);
      }

      return test();
    }


    template<typename A, typename B>
    std::ostream & testLessOrEqual(
        A const & a,
        B const & b)
    {
      if (!m_fail) {
        m_fail = !(a <= b);
      }

      return test();
    }



  private:
    std::ostringstream m_stream;
    bool m_fail;
};


bool UnitTest(
    char const * name,
    void (*test)(void))
{
  try {
    test();
    std::cerr << "Test " << name << " PASSED." << std::endl;
    ++_unittest_numberPassed;
    return true;
  } catch (TestFailed const & e) {
    std::cerr << "Test " << name << " FAILED." << std::endl;
    ++_unittest_numberFailed;
    return false;
  }
}

}


}


/******************************************************************************
* TESTS ***********************************************************************
******************************************************************************/


#define testFail() \
  sl::TestStream().testFail() << "testFail() called at " << __LINE__ << \
      std::endl


#define testEqual(a,b) \
  sl::TestStream().testEqual(a,b) << #a << ":'" << (a) \
      << "' != " << #b << ":'" << (b) << "' at " << __LINE__ << std::endl


#define testNotEqual(a,b) \
  sl::TestStream().testNotEqual(a,b) << #a << ":'" << (a) \
      << "' == " << #b << ":'" << (b) << "' at " << __LINE__ << std::endl


#define testTrue(a) \
  sl::TestStream().testTrue(a) << #a << "' is false at: " << __LINE__ \
      << std::endl


#define testFalse(a) \
  sl::TestStream().testFalse(a) << #a << "' is true at: " << __LINE__ \
      << std::endl


#define testGreater(a,b) \
  sl::TestStream().testGreater(a,b) << #a << ":'" << (a) << "' <= " << #b \
        << ":'" << (b) << "' at " << __LINE__ << std::endl


#define testGreaterOrEqual(a,b) \
  sl::TestStream().testGreaterOrEqual(a,b) << #a << ":'" << (a) << "' < " << \
        #b << ":'" << (b) << "' at " << __LINE__ << std::endl


#define testLess(a,b) \
  sl::TestStream().testLess(a,b) << #a << ":'" << (a) << "' >= " << #b << \
        ":'" << (b) << "' at " << __LINE__ << std::endl


#define testLessOrEqual(a,b) \
  sl::TestStream().testLessOrEqual(a,b) << #a << ":'" << (a) << "' > " << #b \
        << ":'" << (b) << "' at " << __LINE__ << std::endl


#define testNearEqual(a, b, c, d) \
  sl::TestStream().testNearEqual(a, b, c, d) << #a << ":'" << (a) \
      << "' != " << #b << ":'" << (b) << "' at " << __LINE__ << std::endl


#define UNITTEST(CLASS, TEST) \
  void _unittest_ ## CLASS ## _ ## TEST ## _func(void); \
  bool _unittest_ ## CLASS ## _ ## TEST ## _result = \
      sl::UnitTest( \
          __FILE__":"#CLASS"->"#TEST, \
          _unittest_ ## CLASS ## _ ## TEST ## _func); \
  void _unittest_ ## CLASS ## _ ## TEST ## _func(void) \




/******************************************************************************
* MAIN ************************************************************************
******************************************************************************/


int main(
    int argc,
    char ** argv)
{
  // make sure we don't have any useless arguments
  if (argc > 1) {
    for (int i=1; i<argc; ++i) {
      std::cerr << "Unused parameter: " << argv[i] << std::endl;
    }
    return 2;
  }



  if (sl::_unittest_numberPassed == 0 && \
      sl::_unittest_numberFailed == 0) {
    std::cerr << "No tests run." << std::endl;
    return 3;
  }

  std::cout << sl::_unittest_numberPassed << " tests passed." << \
      std::endl;
  std::cout << sl::_unittest_numberFailed << " tests failed." << \
      std::endl;

  if (sl::_unittest_numberFailed == 0) {
    return 0;
  } else {
    return 1;
  }
}




#endif
