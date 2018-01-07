/**
* @file Exception.hpp
* @brief Some base exception classes.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017
* @version 1
* @date 2017-11-08
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
