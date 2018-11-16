/**
* @file Array.hpp
* @brief A mutable array structure for storing self-allocated memory.
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


#include "Debug.hpp"

#include <memory>


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
      m_data(new T[size])
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
      Array(size)
    {
      std::fill(m_data.get(), m_data.get()+m_size, value);
    }


    /**
    * @brief Move constructor.
    *
    * @param lhs The array to move.
    */
    Array(
        Array && lhs) noexcept :
      m_size(lhs.m_size),
      m_data(std::move(lhs.m_data))
    {
      lhs.m_size = 0;
    }


    /**
    * @brief Deleted copy-assignment operator.
    *
    * @param rhs The Array to copy.
    */
    Array(
        Array const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param lhs The Array to copy.
    *
    * @return This array.
    */
    Array & operator=(
        Array const & rhs) = delete;


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
      m_data = std::move(lhs.m_data);

      lhs.m_size = 0;

      return *this;
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
      return m_data.get();
    }


    /**
    * @brief Get the underlying memory.
    *
    * @return The underlying memory.
    */
    T const * data() const noexcept
    {
      return m_data.get();
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
      return m_data.get();
    }


    /**
    * @brief Get the end iterator.
    *
    * @return The iterator/pointer.
    */
    T const * end() const noexcept
    {
      return m_data.get() + m_size;
    }


    /**
    * @brief Get the beginning iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * begin() noexcept
    {
      return m_data.get();
    }


    /**
    * @brief Get the end iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * end() noexcept
    {
      return m_data.get() + m_size;
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


    /**
    * @brief Shrink the size of the array. This does not gaurantee the memory
    * allocation will be decreased, but only that the local size of the array
    * will shrink. Calling this method with a `smallerSize` greater than the
    * size of the array will have no effect.
    *
    * @param smallerSize The size to shrink the array to.
    */
    void shrink(
        size_t smallerSize)
    {
      if (smallerSize < m_size) {
        m_size = smallerSize;
      }
    }


    /**
    * @brief Pull out the heap memory from this Array, leaving it empty.
    *
    * @return The unique pointer to the heap memory.
    */
    std::unique_ptr<T[]> steal() noexcept
    {
      m_size = 0;
      return std::unique_ptr<T[]>(std::move(m_data));
    }


  private:
    size_t m_size;
    std::unique_ptr<T[]> m_data;

};


}



#endif
