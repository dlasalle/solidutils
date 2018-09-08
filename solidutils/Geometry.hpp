/**
 * @file Geometry.hpp
 * @brief Geometry utility functions.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018, Solid Lake LLC
 * @version 1
 * @date 2018-07-28
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


#ifndef SOLIDUTILS_INCLUDE_GEOMETRY_HPP
#define SOLIDUTILS_INCLUDE_GEOMETRY_HPP

namespace sl
{

class Geometry
{
  public:
  static constexpr double const PI = 3.141592653589793;

  /**
  * @brief Convert degrees to radians.
  *
  * @param deg The degrees.
  *
  * @return The radians.
  */
  static constexpr double deg2rad(
      double const deg)
  {
    return (deg * PI) / 180.0;
  }

  /**
  * @brief Convert radians to degrees.
  *
  * @param rad The radians.
  *
  * @return The degrees.
  */
  static constexpr double rad2deg(
      double const rad)
  {
    return rad * 180.0 / PI;
  }


};

}

#endif
