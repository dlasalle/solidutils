/**
* @file Random.hpp
* @brief The Random class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2017-10-10
*/


#ifndef SOLIDUTILS_INCLUDE_RANDOM_HPP
#define SOLIDUTILS_INCLUDE_RANDOM_HPP


#include <cstdlib>
#include "Debug.hpp"


namespace sl
{

/**
* @brief The Random class provides wrappers around base 'random' functionality,
* such as getting a number within a given range, shuffling elements, or filling
* an array with large amounts of random data. The functions contained here in
* make no effort to provide random numbers with any particular distribution,
* but rather focus on generating random numbers as fast as possible. Any
* application which needs high quality random numbers should not use this
* class.
*/
class Random
{
  public:
    /**
    * @brief Get a single random number in a specified range (inclusive). If
    * min is greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of number to get.
    * @param min The minimum value (inclusive).
    * @param max The maximum value (inclusive).
    */
    template <typename T>
    inline static T inRange(
        T const min,
        T const max) noexcept
    {
      ASSERT_LESSEQUAL(min, max);

      T const range = (max+1) - min;
      T const entropy = std::rand() % range;

      return entropy + min;
    }

    /**
    * @brief Fill a location in memory with random numbers. If min and max are
    * the same, an optimization is used where random is never called. If min is
    * greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of number to fill with.
    * @param data The memory location.
    * @param num The number of elements to insert.
    * @param min The minimum number.
    * @param max The maximum number.
    */
    template <typename T>
    inline static void fillWithRange(
        T * const data,
        size_t const num,
        T const min,
        T const max) noexcept
    {
      if (min == max) {
        for (size_t i = 0; i < num; ++i) {
          data[i] = min;
        }
      } else {
        for (size_t i = 0; i < num; ++i) {
          data[i] = inRange(min, max);
        }
      }
    }



};


}


#endif