/**
 * @file Random.hpp
 * @brief The Random class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2017-10-10
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


#ifndef SOLIDUTILS_INCLUDE_RANDOM_HPP
#define SOLIDUTILS_INCLUDE_RANDOM_HPP


#include "Debug.hpp"
#include "FastIntDistribution.hpp"

#include <cstddef>
#include <algorithm>
#include <type_traits>



namespace sl
{

/**
* @brief The Random class provides wrappers around base 'random' functionality,
* such as getting a number within a given range, shuffling elements, or filling
* an array with large amounts of random data. This class assumes
* psuedo-randomness is sufficient and that performance is more important, and
* thus should not be used where unpredictability or uniform distribution is
* desired.
*/
class Random
{
  public:
    /**
    * @brief Get a random number within the given range. The distribution may
    * not be uniform.
    *
    * @tparam T The type of random source.
    * @tparam URBG The random source.
    * @param min The lower bound (inclusive).
    * @param max The upper bound (exclusive).
    * @param rng The random source.
    */
    template<typename T, typename URBG>
    static T inRange(
        T const min,
        T const max,
        URBG&& rng) noexcept
    {
      T const range = max - min;
      return min + static_cast<T>(static_cast<uint64_t>(rng()) % range);
    }


    /**
    * @brief Fill a container with random numbers. If min and max are
    * the same, an optimization is used where random is never called. If min is
    * greater than max, the behavior is undefined (very bad).
    *
    * @tparam T The type of iterator.
    * @tparam URBG The type of random source.
    * @param range The range of elements to fill.
    * @param min The minimum number (inclusive).
    * @param max The maximum number (exclusive).
    * @param rng The random source.
    */
    template <typename T, typename URBG>
    static void fillWithRange(
        T * const data,
        size_t const num,
        T const min,
        T const max,
        URBG&& rng) noexcept
    {
      if (min == max) {
        for (size_t i = 0; i < num; ++i) {
          data[i] = min;
        }
      } else {
        for (size_t i = 0; i < num; ++i) {
          data[i] = inRange(min, max, rng);
        }
      }
    }


    /**
    * @brief Fill a memory location with a permutation vector.
    *
    * @tparam T The type of data.
    * @tparam URBG The type of random source.
    * @param data The range of elements to fill.
    * @param begin The starting index.
    */
    template <typename T, typename URBG>
    static void fillWithPerm(
        T * const data,
        size_t const num,
        T const offset,
        URBG&& rng) noexcept
    {
      for (size_t i = 0; i < num; ++i) {
        data[i] = static_cast<T>(i)+offset;
      }

      pseudoShuffle(data, num, rng);
    }

    /**
    * @brief Re-order the elements in array in a randomly. This is
    * less random than std::shuffle, but is significantly faster for large
    * arrays.
    *
    * @tparam T The type of elements.
    * @tparam URBG The type of random source.
    * @param data The data to shuffle.
    * @param num The number of elements.
    * @param rng The random source.
    */
    template <typename T, typename URBG>
    static void pseudoShuffle(
        T * const data,
        size_t const num,
        URBG&& rng) noexcept
    {
      constexpr size_t swapSize = 8;
      constexpr size_t minSize = 64;

      if (num < minSize) {
        // for small arrays, resort to std::shuffle
        std::shuffle(data, data+num, rng);
      } else {
        FastIntDistribution<size_t> indexDist(0, num-swapSize);
        FastIntDistribution<int> swapDist(0, 4);

        // The below swapping is originally based on the algorithm used in
        // `randArrayPermute()` function in George Karypis's GKLib.

        // perform several network swaps
        for (size_t swap = 0; swap < num/swapSize; ++swap) {
          size_t const start = indexDist(rng);
          size_t const end = indexDist(rng);
          int const swapSet = swapDist(rng);
          switch (swapSet) {
            case 0:
              std::swap(data[start], data[end+1]);
              std::swap(data[start+1], data[end+4]);
              std::swap(data[start+2], data[end+7]);
              std::swap(data[start+3], data[end+3]);
              std::swap(data[start+4], data[end+2]);
              std::swap(data[start+5], data[end+6]);
              std::swap(data[start+6], data[end]);
              std::swap(data[start+7], data[end+5]);
              break;
            case 1:
              std::swap(data[start], data[end+5]);
              std::swap(data[start+1], data[end+3]);
              std::swap(data[start+2], data[end+1]);
              std::swap(data[start+3], data[end+6]);
              std::swap(data[start+4], data[end]);
              std::swap(data[start+5], data[end+7]);
              std::swap(data[start+6], data[end+2]);
              std::swap(data[start+7], data[end+4]);
              break;
            case 2:
              std::swap(data[start], data[end+3]);
              std::swap(data[start+1], data[end+5]);
              std::swap(data[start+2], data[end+6]);
              std::swap(data[start+3], data[end+1]);
              std::swap(data[start+4], data[end+2]);
              std::swap(data[start+5], data[end]);
              std::swap(data[start+6], data[end+4]);
              std::swap(data[start+7], data[end+7]);
              break;
            case 3:
              std::swap(data[start], data[end+7]);
              std::swap(data[start+1], data[end]);
              std::swap(data[start+2], data[end+2]);
              std::swap(data[start+3], data[end+3]);
              std::swap(data[start+4], data[end+4]);
              std::swap(data[start+5], data[end+1]);
              std::swap(data[start+6], data[end+6]);
              std::swap(data[start+7], data[end+5]);
              break;
          }
        }
      }
    }




};


}


#endif
