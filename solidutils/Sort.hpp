/**
* @file Sort.hpp
* @brief The Sort class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018
* @version 1
* @date 2018-08-23
*/


#ifndef SOLIDUTILS_SORT_HPP
#define SOLIDUTILS_SORT_HPP

#include "VectorMath.hpp"

#include <memory>
#include <vector>

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

};


}

#endif

