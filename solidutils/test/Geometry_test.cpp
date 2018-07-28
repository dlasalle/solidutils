/**
* @file GeometryTest.hpp
* @brief Unit tests for the Geometry class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-07-28
*/


#include "UnitTest.hpp"
#include "Geometry.hpp"


namespace sl
{


UNITTEST(Geometry, deg2radTest)
{
  testNearEqual(Geometry::PI / 4.0, Geometry::deg2rad(45.0), 1e-6, 0.0);
  testNearEqual(Geometry::PI / 2.0, Geometry::deg2rad(90.0), 1e-6, 0.0);
  testNearEqual(Geometry::PI, Geometry::deg2rad(180.0), 1e-6, 0.0);
  testNearEqual((3.0*Geometry::PI) / 2.0, Geometry::deg2rad(270.0), 1e-6, 0.0);
  testNearEqual(2.0*Geometry::PI, Geometry::deg2rad(360.0), 1e-6, 0.0);
}

UNITTEST(Geometry, rad2degTest)
{
  testNearEqual(45.0, Geometry::rad2deg(Geometry::PI / 4.0), 1e-6, 0.0);
  testNearEqual(90.0, Geometry::rad2deg(Geometry::PI / 2.0), 1e-6, 0.0);
  testNearEqual(180.0, Geometry::rad2deg(Geometry::PI), 1e-6, 0.0);
  testNearEqual(270.0, Geometry::rad2deg((3.0*Geometry::PI) / 2.0), 1e-6, 0.0);
  testNearEqual(360.0, Geometry::rad2deg(2.0*Geometry::PI), 1e-6, 0.0);
}




}
