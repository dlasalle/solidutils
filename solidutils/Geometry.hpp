/**
* @file Geometry.hpp
* @brief Geometry utility functions.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-07-28
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
