/**
* @file Timer_test.cpp
* @brief Unit tests for the Timer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-07
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




#include "Timer.hpp"
#include <thread>
#include <chrono>
#include "UnitTest.hpp"


namespace sl
{

UNITTEST(Timer, StartStop)
{
  Timer timer;

  timer.start();

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  timer.stop();

  double duration = timer.poll();

  testGreater(duration, 0.01);

  // allow for a lot of buffer in case unit test server is under heavy load
  testLess(duration, 1.0);
}

UNITTEST(Timer, Scope)
{
  Timer timer;

  {
    Timer::Scope scope = timer.scope();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  double duration = timer.poll();

  testGreater(duration, 0.01);

  // allow for a lot of buffer in case unit test server is under heavy load
  testLess(duration, 1.0);
}

UNITTEST(Timer, Add)
{
  Timer timer;

  timer.add(1.0);
  double duration = timer.poll();

  testEqual(duration, 1.0);
}

}
