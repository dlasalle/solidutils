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
#include <algorithm>
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
    * @param max The maximum value (exclusive).
    */
    template <typename T>
    inline static T inRange(
        T const min,
        T const max) noexcept
    {
      ASSERT_LESS(min, max);

      T const range = max - min;
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
    * @param min The minimum number (inclusive).
    * @param max The maximum number (exclusive).
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


    /**
    * @brief Fill a container with random numbers. If min and max are
    * the same, an optimization is used where random is never called. If min is
    * greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of container.
    * @tparam U The type of number to fill with.
    * @param container The container to fill.
    * @param min The minimum number (inclusive).
    * @param max The maximum number (exclusive).
    */
    template <typename T, typename U>
    inline static void fillWithRange(
        T * const container,
        U const min,
        U const max) noexcept
    {
      if (min == max) {
        for (size_t i = 0; i < container->size(); ++i) {
          (*container)[i] = min;
        }
      } else {
        for (size_t i = 0; i < container->size(); ++i) {
          (*container)[i] = inRange(min, max);
        }
      }
    }


    /**
    * @brief Fill a memory location with a permutation vector.
    *
    * @tparam T The type of index.
    * @param data The memory location.
    * @param start The starting index.
    * @param end The ending index (exclusive).
    */
    template <typename T>
    inline static void fillWithPerm(
        T * const data,
        T const begin,
        T const end) noexcept
    {
      size_t const num = end - begin;

      for (size_t i = 0; i < num; ++i) {
        data[i] = begin + static_cast<T>(i);
      }

      std::random_shuffle(data, data+num);
    }


    /**
    * @brief Fill a memory location with a permutation vector.
    *
    * @tparam T The type of container.
    * @tparam U The type of item.
    * @param container The container.
    * @param offset The starting offset.
    */
    template <typename T, typename U>
    inline static void fillWithPerm(
        T * const container,
        U const offset) noexcept
    {
      for (size_t i = 0; i < container->size(); ++i) {
        (*container)[i] = offset + static_cast<U>(i);
      }

      std::random_shuffle(container->begin(), container->end());
    }
};


}


#endif
