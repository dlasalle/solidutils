/**
* @file ConstArray.hpp
* @brief A constant array structure for storing self-allocated or externally
* allocated memory.
* @author Dominique LaSalle <dominique@solidlake.com>
* Copyright 2018, Solid Lake LLC
* @version 1
* @date 2018-10-14
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


#ifndef SOLIDUTILS_INCLUDE_CONSTARRAY_HPP
#define SOLIDUTILS_INCLUDE_CONSTARRAY_HPP


#include "Debug.hpp"
#include "Array.hpp"

#include <memory>


namespace sl
{

/**
* @brief The ConstArray class provides functionality similar to std::vector,
* except that it does not construct or destruct elements, does not allow
* insertions or appending, and can use memory it does not own for storage.
* This is for performance reasons when initialization
* is not required. However, this makes it unsuitable for anything other than
* primitive datatypes or other structures movemable with a simple memcpy().
*
* @tparam T The type of element.
*/
template<typename T>
class ConstArray
{
  public:
    /**
    * @brief Create an empty non mutable array.
    */
    ConstArray() :
      m_size(0),
      m_data(nullptr),
      m_isOwner(true)
    {
      // do nothing
    }

    /**
    * @brief Create a new non-mutable array with a default
    * value for each element.
    *
    * @param size The size of the array.
    */
    ConstArray(
        Array<T> array) :
      m_size(array.size()), // must come before call to steal()
      m_data(array.steal()),
      m_isOwner(true)
    {
      // do nothing
    }


    /**
    * @brief Create a new non-owning array. If the pointer is null, then
    * size must 0.
    *
    * @param ptr The pointer.
    * @param size The number of elements in the array.
    */
    ConstArray(
        T const * const ptr,
        size_t const size) :
      m_size(size),
      m_data(ptr),
      m_isOwner(false)
    {
      ASSERT_TRUE(ptr != nullptr || size == 0);
    }

    /**
    * @brief Create a new constant array.
    *
    * @param ptr The data to move into the array.
    * @param size The size of the array.
    */
    ConstArray(
        std::unique_ptr<T[]>&& ptr,
        size_t const size) :
      m_size(size),
      m_data(std::move(ptr)),
      m_isOwner(true)
    {
      // do nothing
    }


    /**
    * @brief Move constructor.
    *
    * @param rhs The array to move.
    */
    ConstArray(
        ConstArray && rhs) noexcept :
      m_size(rhs.m_size),
      m_data(std::move(rhs.m_data)),
      m_isOwner(rhs.m_isOwner)
    {
      rhs.m_size = 0;
    }


    /**
    * @brief Deleted copy-assignment operator.
    *
    * @param rhs The ConstArray to copy.
    */
    ConstArray(
        ConstArray const & rhs) = delete;


    /**
    * @brief Deleted assignment operator.
    *
    * @param lhs The ConstArray to copy.
    *
    * @return This array.
    */
    ConstArray & operator=(
        ConstArray const & rhs) = delete;


    /**
    * @brief Assignment operator (move).
    *
    * @param lhs The array to assign (and destroy) to this one.
    *
    * @return This array.
    */
    ConstArray & operator=(
        ConstArray && lhs)
    {
      m_size = lhs.m_size;
      m_data = std::move(lhs.m_data);

      lhs.m_size = 0;

      return *this;
    }

    /**
    * @brief Destructor.
    */
    ~ConstArray()
    {
      if (!m_isOwner) {
        // disown the unique pointer before this object is destroyed.
        m_data.release();
      }
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
    * @brief Get the front of the array.
    *
    * @return The first element.
    */
    T const & front() const noexcept
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
    * @brief Free the memory associated with this array.
    */
    void clear()
    {
      m_size = 0;
      m_data.reset();
    }


  private:
    size_t m_size;
    std::unique_ptr<T const []> m_data;
    bool m_isOwner;

};


}



#endif
