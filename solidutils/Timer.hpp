/**
* @file Timer.hpp
* @brief The Timer class.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017, Solid Lake LLC
* @version 1
* @date 2018-01-07
*/




#ifndef SOLIDUTILS_INCLUDE_TIMER_HPP
#define SOLIDUTILS_INCLUDE_TIMER_HPP


#include <chrono>
#include <memory>
#include "Exception.hpp"


namespace sl
{

/**
* @brief This class is used to perform wall timings of varius tasks. It
* provides means to meanually start and stop a timer:
*
* ```
* Timer t;
*
* t.start();
* // perform task 1
* t.stop();
*
* t.start();
* // perform task 2
* t.stop();
*
* double duration = t.poll();
* ```
*
* It also provides a means to time a scoped environment:
* ```
* Timer t;
*
* {
*   Timer::Scope scope = t.scope();
*   // perform task 1
* }
*
* {
*   Timer::Scope scope = t.scope();
*   // perform task 2
* }
*
* double duration = t.poll();
* ```
*/
class Timer
{
  public:
    /**
    * @brief Get a double representing the current time in seconds. This is an
    * arbitrary value by itself, but the relation between return values of two
    * calls is the duration in seconds elapsed.
    *
    * @return The current time in seconds.
    */
    static double now()
    {
      std::chrono::high_resolution_clock::time_point time =
          std::chrono::high_resolution_clock::now();
			size_t const ticks = time.time_since_epoch().count();
			double constexpr SECONDS_PER_TICK = \
					static_cast<double>(std::chrono::system_clock::period::num) / \
					static_cast<double>(std::chrono::system_clock::period::den);
 			double const seconds = ticks * SECONDS_PER_TICK;
			return seconds;
    }

    /**
    * @brief This class provides a means of timing a scoped region. It begins
    * timing when it is created, and adds its duration to the parent timer when
    * it is destroyed.
    */
    class Scope
    {
      public:
        /**
        * @brief Create a new Scope from the given timer.
        *
        * @param parent The parent timer.
        */
        Scope(
            Timer * const parent) :
          m_parent(parent),
          m_start(now())
        {
          // do nothing
        }

        /**
        * @brief Move once Scope to this Scope.
        *
        * @param scope The Scope to move.
        */
        Scope(
            Scope&& scope) :
          m_parent(scope.m_parent),
          m_start(scope.m_start)
        {
          scope.m_parent = nullptr;
          scope.m_start = 0;
        }

        /**
        * @brief Deleted copy constructor.
        *
        * @param other The Scope to copy.
        */
        Scope(
            Scope const & other) = delete;

        /**
        * @brief Deleted assignment operator.
        *
        * @param other The Scope to assign from.
        *
        * @return The newly assigned Scope.
        */
        Scope& operator=(
            Scope const & other) = delete;

        /**
        * @brief Destroy this timer Scope.
        */
        ~Scope()
        {
          double const stop = now();

          if (m_parent != nullptr) {
            m_parent->add(stop - m_start);
          }
        }

      private:
        Timer * m_parent;
        double m_start;
    };

    /**
    * @brief Creat a new timer.
    */
    Timer() :
      m_duration(0),
      m_scope(nullptr)
		{
      // do nothing
    }

    /**
    * @brief Start a new timed scope. The duration from when the Scope object
    * is created
    *
    * @return 
    */
    Scope scope()
    {
      if (m_scope.get() != nullptr) {
        throw InvalidStateException(
            "Cannot start scope for already running timer."); 
      }

      return Scope(this);
    }

    /**
    * @brief Start or continue the timer.
    */
    void start()
    {
      if (m_scope.get() != nullptr) {
        throw InvalidStateException("Cannot start already running timer."); 
      }

      m_scope.reset(new Scope(this));
    }

    /**
    * @brief Stop the timer.
    */
    void stop()
    {
      if (m_scope.get() == nullptr) {
        throw InvalidStateException("Cannot stop non-running timer."); 
      }

      // destroy scope (adding durationg).
      m_scope.reset(nullptr);
    }

    /**
    * @brief Get the elapsed number of seconds on the timer.
    *
    * @return The amount of elapsed time.
    */
    double poll() const
    {
      if (m_scope.get() != nullptr) {
        throw InvalidStateException("Cannot poll running timer."); 
      }

      return m_duration;
    }

    /**
    * @brief Add some amount of time to the timer.
    *
    * @param duration The time to add.
    */
    void add(
      double duration)
    {
      m_duration += duration;
    }

  private:
    double m_duration;
    std::unique_ptr<Scope> m_scope;
};

}

#endif
