/**
 * @file Exception.hpp
 * @brief Some base exception classes.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018
 * @version 1
 * @date 2017-11-08
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


#ifndef SOLIDUTILS_INCLUDE_EXCEPTION_HPP
#define SOLIDUTILS_INCLUDE_EXCEPTION_HPP


#include <stdexcept>


namespace sl
{


/**
* @brief The InvalidInputException indicates that the input given to a function
* or class was not valid.
*/
class InvalidInputException :
    public std::runtime_error
{
  public:
    /**
    * @brief Create a new InvalidInputException.
    *
    * @param msg The message about what input was invalid.
    */
    InvalidInputException(
        std::string const & msg) :
      std::runtime_error("Invalid input: " + msg)
    {
      // do nothing
    }

    /**
    * @brief Virtual destructor.
    */
    virtual ~InvalidInputException()
    {
      // do nothing
    }
};


/**
* @brief The InvalidInputException indicates that an operation was attempted
* that is not valid for an objects current state.
*/
class InvalidStateException :
    public std::runtime_error
{
  public:
    /**
    * @brief Create a new InvalidStateException.
    *
    * @param msg The message about what state was invalid.
    */
    InvalidStateException(
        std::string const & msg) :
      std::runtime_error("Invalid state: " + msg)
    {
      // do nothing
    }

    /**
    * @brief Virtual destructor.
    */
    virtual ~InvalidStateException()
    {
      // do nothing
    }
};



}


#endif
