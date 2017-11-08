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


class InvalidInputException :
    public std::runtime_error
{
  public:
    InvalidInputException(
        std::string const & msg) :
      std::runtime_error("Invalid input: " + msg)
    {
      // do nothing
    }
};

}


#endif
