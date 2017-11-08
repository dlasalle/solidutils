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

}


#endif
