/**
 * @file VectorMath.hpp
 * @brief The VectorMath class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2017-10-11
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



#ifndef SOLIDUTILS_INCLUDE_VECTORMATH_HPP
#define SOLIDUTILS_INCLUDE_VECTORMATH_HPP


#include "Array.hpp"


namespace sl
{


/**
* @brief The VectorMath class contains static functions for manipulating
* numerical data in vectors. This includes operations for summation, scaling,
* dot products, cross products, prefix sums, etc..
*/
class VectorMath
{
  public:
    /**
    * @brief Sum the elements of an array.
    *
    * @tparam T The type element.
    * @param data The starting memory location.
    * @param size The number of elements.
    *
    * @return The sum.
    */
    template <typename T>
    static T sum(
        T * const data,
        size_t const size) noexcept
    {
      T sum = 0;
      for (size_t i = 0; i < size; ++i) {
        sum += data[i];
      }
      return sum;
    }


    /**
    * @brief Set all entries int the array to the given sequence.
    *
    * @tparam The type of elements in the array.
    * @param data The starting location of memory.
    * @param size The number of lements.
    * @param start The starting value of the sequence.
    * @param inc The increment of the sequence.
    */
    template <typename T>
    static void increment(
        T * const data,
        size_t const size,
        T const start = 0,
        T const inc = 1) noexcept
    {
      T val = start;
      for (size_t i = 0; i < size; ++i) {
        data[i] = val;
        val += inc;
      }
    }


    /**
    * @brief Perform a prefix sum on an array.
    *
    * @tparam T The type of elements in the array.
    * @param data The starting location of memory.
    * @param size The number of elements in the array.
    */
    template <typename T>
    static void prefixSumExclusive(
        T * const data,
        size_t const size) noexcept
    {
      T sum = 0;
      for (size_t i = 0; i < size; ++i) {
        T const val = data[i];
        data[i] = sum;
        sum += val;
      }
    }


};


}



#endif
