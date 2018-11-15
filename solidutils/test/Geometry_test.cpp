/**
* @file GeometryTest.hpp
* @brief Unit tests for the Geometry class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-07-28
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
