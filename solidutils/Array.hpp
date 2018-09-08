/**
* @file Array.hpp
* @brief A mutable array structure for storing self-allocated or externally
* allocated memory.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2017-2018, Solid Lake LLC
* @version 1
* @date 2017-10-06
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


#ifndef SOLIDUTILS_INCLUDE_ARRAY_HPP
#define SOLIDUTILS_INCLUDE_ARRAY_HPP


#include <cstring>
#include "Alloc.hpp"
#include "Debug.hpp"


namespace sl
{

/**
* @brief The Array class provides functionality similar to std::vector, except
* that it does not construct or destruct elements, and does not allow
* insertions or append. This is for performance reasons when initialization
* is not required. However, this makes it unsuitable for anything other than
* primitive datatypes or other structures movemable with a simple memcpy().
*
* @tparam T The type of element.
*/
template<typename T>
class Array
{
  public:
    /**
    * @brief Create a new mutable array.
    *
    * @param size The size of the array.
    */
    Array(
        size_t const size) :
      m_size(size),
      m_data(Alloc::uninitialized<T>(size))
    {
      // do nothing
    }


    /**
    * @brief Create a new mutable array with a default value for each element.
    *
    * @param size The size of the array.
    */
    Array(
        size_t const size,
        T const value) :
      m_size(size),
      m_data(Alloc::initialized<T>(size, value))
    {
      // do nothing
    }


    /**
    * @brief Copy a memory location into a new array.
    *
    * @param ptr The memory location.
    * @param size The number of elements.
    */
    Array(
        T const * const ptr,
        size_t const size) :
      m_size(size),
      m_data(Alloc::duplicate(ptr, size))
    {
      // do nothing
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The array to move.
    */
    Array(
        Array && lhs) noexcept :
      m_size(lhs.m_size),
      m_data(lhs.m_data)
    {
      lhs.m_size = 0;
      lhs.m_data = nullptr;
    }


    /**
    * @brief The destructor.
    */
    ~Array()
    {
      Alloc::free(m_data);
    }


    /**
    * @brief Assignment operator (move).
    *
    * @param lhs The array to assign (and destroy) to this one.
    *
    * @return This array.
    */
    Array & operator=(
        Array && lhs)
    {
      m_size = lhs.m_size;
      m_data = lhs.m_data;

      lhs.m_size = 0;
      lhs.m_data = nullptr;

      return *this;
    }


    /**
    * @brief Resize the array.
    *
    * @param size The new size.
    *
    * @throw std::bad_alloc If there is not enough memory.
    */
    void resize(
        size_t const size)
    {
      if (m_size > 0) {
        // actually resize
        m_size = size;
        Alloc::resize<T>(&m_data, size);
      } else {
        // initialize allocation
        m_size = size;
        m_data = Alloc::uninitialized<T>(size);
      }
    }


    /**
    * @brief Set all entries in the array to the given value.
    *
    * @param val The value to set.
    */
    void set(
        T const val) noexcept
    {
      for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = val;
      }
    }


    /**
    * @brief Get the element at the given index.
    *
    * @param index The index of the element.
    *
    * @return A reference to the element.
    */
    T & operator[](
        size_t const index) noexcept
    {
      ASSERT_LESS(index, m_size);
      return m_data[index];
    }


    /**
    * @brief Get the element at the given index.
    *
    * @param index The index of the element.
    *
    * @return A reference to the element.
    */
    T const & operator[](
        size_t const index) const noexcept
    {
      ASSERT_LESS(index, m_size);
      return m_data[index];
    }


    /**
    * @brief Get the underlying memory.
    *
    * @return The underlying memory.
    */
    T * data() noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the underlying memory.
    *
    * @return The underlying memory.
    */
    T const * data() const noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the size of the underlying memory allocation.
    *
    * @return The size of the memory allocation.
    */
    size_t size() const noexcept
    {
      return m_size;
    }


    /**
    * @brief Get the beginning iterator.
    *
    * @return The iterator/pointer.
    */
    T const * begin() const noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the end iterator.
    *
    * @return The iterator/pointer.
    */
    T const * end() const noexcept
    {
      return m_data + m_size;
    }


    /**
    * @brief Get the beginning iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * begin() noexcept
    {
      return m_data;
    }


    /**
    * @brief Get the end iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * end() noexcept
    {
      return m_data + m_size;
    }

    /**
    * @brief Get the front of the array.
    *
    * @return The first element.
    */
    T const & front() const noexcept
    {
      return (*this)[0];
    }

    /**
    * @brief Get the front of the array.
    *
    * @return The first element.
    */
    T & front() noexcept
    {
      return (*this)[0];
    }

    /**
    * @brief Get the back of the array.
    *
    * @return The last element.
    */
    T const & back() const noexcept
    {
      return (*this)[m_size-1];
    }

    /**
    * @brief Get the back of the array.
    *
    * @return The last element.
    */
    T & back() noexcept
    {
      return (*this)[m_size-1];
    }



  private:
    size_t m_size;
    T * m_data;

    // disable copying
    Array(
        Array const & lhs);
    Array & operator=(
        Array const & lhs);


};


}



#endif
