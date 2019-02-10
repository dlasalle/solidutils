/**
* @file FastIntDistribution.hpp
* @brief The FastIntDistribution class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2019
* @version 1
* @date 2019-02-09
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/


#ifndef SOLIDUTILS_INCLUDE_FASTINTDISTRIBUTION_HPP
#define SOLIDUTILS_INCLUDE_FASTINTDISTRIBUTION_HPP


namespace sl
{

/**
* @brief This distribution is designed to be fast and consistent across
* platforms. However, it will not be uniform.
*
* @tparam T
*/
template<typename T>
class FastIntDistribution
{
  public:
  /**
  * @brief Create a new FastIntDistribution which will result in numbers
  * [min,max].
  *
  * @param min The minimum number.
  * @param max The maximum number.
  */
  FastIntDistribution(
      T const min,
      T const max) :
    m_min(min),
    m_range(max-min+1)
  {
    // do nothing
  }

  /**
  * @brief Generate a number in the range of [min, max]. The distribution may
  * not be uniform, particularily for larger ranges.
  *
  * @tparam RNG The random engine type.
  * @param rng The random engine.
  *
  * @return A number in the range of [min, max].
  */
  template<class RNG>
  T operator()(RNG& rng)
  {
    constexpr auto RNG_RANGE = RNG::max() - RNG::min() + 1;

    size_t const width = m_range / RNG_RANGE;

    uint64_t num = 0;
    for (size_t i = 0; i <= width; ++i) {
      num *= static_cast<uint64_t>(RNG_RANGE);
      num += static_cast<uint64_t>(rng() - RNG::min());
    }
    num = num % m_range;
    
    return static_cast<T>(num) + m_min;
  }

  private:
  T m_min;
  T m_range;

};


}

#endif


