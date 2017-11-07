/**
 * @file Debug.hpp
 * @brief Debugging functions.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017, Solid Lake LLC
 * @version 1
 * @date 2017-10-03
 */


#ifndef SOLIDUTILS_INCLUDE_DEBUG_HPP
#define SOLIDUTILS_INCLUDE_DEBUG_HPP

/******************************************************************************
* MACROS **********************************************************************
******************************************************************************/

#ifndef NDEBUG
#include <cassert>  // assert
#include <cstdio>   // vprintf
#include <cstdarg>  // va_start, va_end
#include <iostream> // std::cerr, std::cout

namespace sl
{

namespace
{

// NOTE: there is no stream based debugging, as expression in the '<<' would
// still be evaluated even if not printed.

/**
* @brief Print a debugging message
*
* @param fmt The format of the message (printf style).
* @param ... The message arguments.
*/
void debugMessage(
    char const * const fmt,
    ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    fprintf(stdout, "DEBUG: ");
    vfprintf(stdout, fmt, argptr);
    fprintf(stdout, "\n");
    va_end(argptr);
    fflush(stdout);
}

/**
* @brief Print a debugging message.
*
* @param msg The message.
*/
void debugMessage(
    std::string const & msg)
{
  fprintf(stdout, "DEBUG: %s\n", msg.c_str());
}

}

}

#define ASSERT_TRUE(a) \
  do { \
    if (!(a)) { \
      std::cerr << "("#a" = " << (a) << ")" << std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_FALSE(a) \
  do { \
    if (a) { \
      std::cerr << "("#a" = " << (a) << ")" << std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_EQUAL(a,b) \
  do { \
    if (a != b) { \
      std::cerr << "("#a" = " << (a) << ") != ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_NOTEQUAL(a,b) \
  do { \
    if (a == b) { \
      std::cerr << "("#a" = " << (a) << ") == ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_NULL(a) \
  do { \
    if (a != nullptr) { \
      std::cerr << "("#a" = " << (a) << ") != nullptr" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_NOTNULL(a) \
  do { \
    if (a == nullptr) { \
      std::cerr << #a" is  null" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_LESS(a,b) \
  do { \
    if (a >= b) { \
      std::cerr << "("#a" = " << (a) << ") !< ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_LESSEQUAL(a,b) \
  do { \
    if (a > b) { \
      std::cerr << "("#a" = " << (a) << ") !<= ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_GREATER(a,b) \
  do { \
    if (a <= b) { \
      std::cerr << "("#a" = " << (a) << ") !> ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define ASSERT_GREATEREQUAL(a,b) \
  do { \
    if (a < b) { \
      std::cerr << "("#a" = " << (a) << ") !>= ("#b" = " << (b) << ")" << \
          std::endl; \
      assert(false); \
    } \
  } while (false)
#define DEBUG_MESSAGE( ...) \
    sl::debugMessage( __VA_ARGS__ )

#else
#define ASSERT_TRUE(a)
#define ASSERT_FALSE(a)
#define ASSERT_EQUAL(a,b)
#define ASSERT_NOTEQUAL(a,b)
#define ASSERT_NULL(a)
#define ASSERT_NOTNULL(a)
#define ASSERT_LESS(a,b)
#define ASSERT_LESSEQUAL(a,b)
#define ASSERT_GREATER(a,b)
#define ASSERT_GREATEREQUAL(a,b)
#define DEBUG_MESSAGE( ...)

#endif

#endif

