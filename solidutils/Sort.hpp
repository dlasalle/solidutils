/**
 * @file Sort.hpp
 * @brief The Sort class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018, Solid Lake LLC
 * @version 1
 * @date 2018-08-23
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


#ifndef SOLIDUTILS_SORT_HPP
#define SOLIDUTILS_SORT_HPP

#include "VectorMath.hpp"
#include "Random.hpp"

#include <memory>
#include <vector>
#include <algorithm>

namespace sl
{

class Sort
{
  public:
    /**
    * @brief Generate a permutation for a given set of keys. The range of the
    * keys must be limited to [0,n), where n is the number of keys.
    *
    * @tparam K The key type (must be integral).
    * @tparam I The index type (must be integral).
    * @param keys The set of keys to use to generate the sorted permutation.
    * @param num The number of keys.
    *
    * @return The sorted permutation array.
    */
    template<typename K, typename I>
    static std::unique_ptr<I[]> fixedKeys(
        K const * const keys,
        size_t const num)
    {
      static_assert(std::is_integral<K>::value, "Must by integral type.");
      static_assert(std::is_integral<I>::value, "Must by integral type.");

      std::vector<size_t> counts(num+1,0);
      counts.reserve(num);

      /* avoid having to do offsets in each iteration */
      for (size_t i = 0; i < num; ++i) {
        ++counts[keys[i]];
      }

      sl::VectorMath::prefixSumExclusive(counts.data(), counts.size());

      std::unique_ptr<I[]> out(new I[num]);

      for (size_t i = 0; i < num; ++i) {
        out[counts[keys[i]]++] = i;
      }

      return out;
    }

    /**
    * @brief Generate a permutation for a given set of keys. The range of the
    * keys must be limited to [0,n), where n is the number of keys.
    *
    * @tparam K The key type (must be integral).
    * @tparam I The index type (must be integral).
    * @param keys The set of keys to use to generate the sorted permutation.
    * @param num The number of keys.
    *
    * @return The sorted permutation array.
    */
    template<typename K, typename I, typename URBG>
    static std::unique_ptr<I[]> fixedKeysRandom(
        K const * const keys,
        size_t const num,
        URBG&& rng)
    {
      static_assert(std::is_integral<K>::value, "Must by integral type.");
      static_assert(std::is_integral<I>::value, "Must by integral type.");

      std::vector<size_t> counts(num+1,0);
      counts.reserve(num);

      /* avoid having to do offsets in each iteration */
      for (size_t i = 0; i < num; ++i) {
        ++counts[keys[i]];
      }

      sl::VectorMath::prefixSumExclusive(counts.data(), counts.size());

      std::unique_ptr<I[]> out(new I[num]);

      for (size_t i = 0; i < num; ++i) {
        out[counts[keys[i]]++] = i;
      }

      // randomize each bucket
      size_t start = 0;
      for (size_t i = 0; start < num; ++i) {
        sl::Random::pseudoShuffle(out.get()+start, counts[i] - start, rng);
        start = counts[i];
      }

      return out;
    }


};


}

#endif

