/**
* @file Timer_test.cpp
* @brief Unit tests for the Timer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-07
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
