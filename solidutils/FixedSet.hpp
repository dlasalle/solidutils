/**
 * @file FixedSet.hpp
 * @brief The FixedSet class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2017-10-19
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



#ifndef SOLIDUTILS_INCLUDE_FIXEDSET_HPP
#define SOLIDUTILS_INCLUDE_FIXEDSET_HPP


#include "Array.hpp"


namespace sl
{


/**
* @brief The FixedSet class provides a set implementation which allows for
* insertion, querying, and deletion in constant time. While std::unordered_set
* may give constant time complexity of these operations through a hash table,
* this does so through fixed size dense vector (no hashing).
*
* @tparam T The type of element to store.
*/
template <typename T>
class FixedSet
{
  public:
    static constexpr T const NULL_INDEX = static_cast<T>(-1);

    /**
    * @brief Create a new empty fixed set.
    *
    * @param size The size of the set.
    */
    FixedSet(
        size_t const size) :
      m_size(0),
      m_data(size),
      m_index(size, NULL_INDEX)
    {
      // do nothing
    }


    /**
    * @brief Check if an element exists in this set.
    *
    * @param element The element.
    *
    * @return The element.
    */
    bool has(
        T const element) const noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());

      return m_index[index] != NULL_INDEX;
    }

    /**
    * @brief Add an element to this set.
    *
    * @param element The element to add.
    */
    void add(
        T const element) noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());
      ASSERT_EQUAL(m_index[index], NULL_INDEX);

      m_data[m_size] = element;
      m_index[index] = m_size;

      ++m_size;
    }


    /**
    * @brief Remove an element from this set.
    *
    * @param element The element to remove.
    */
    void remove(
        T const element) noexcept
    {
      size_t const index = static_cast<size_t>(element);

      ASSERT_LESS(index, m_index.size());
      ASSERT_NOTEQUAL(m_index[index], NULL_INDEX);

      --m_size;
      T const swap = m_data[m_size];
      size_t const place = m_index[index];
      m_data[place] = swap;
      m_index[swap] = place;
      m_index[index] = NULL_INDEX;
    }


    /**
    * @brief Get the underlying array.
    *
    * @return The data.
    */
    T * data() noexcept
    {
      return m_data.data();
    }


    /**
    * @brief Get the underlying array.
    *
    * @return The data.
    */
    T const * data() const noexcept
    {
      return m_data.data();
    }


    /**
    * @brief Get the number of elements in the set.
    *
    * @return The number of elements.
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
      return m_data.begin();
    }


    /**
    * @brief Get the end iterator.
    *
    * @return The iterator/pointer.
    */
    T const * end() const noexcept
    {
      // we want to return the set's size, and not the array's.
      return m_data.begin() + m_size;
    }


    /**
    * @brief Get the beginning iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * begin() noexcept
    {
      return m_data.begin();
    }


    /**
    * @brief Get the end iterator (mutable).
    *
    * @return The iterator/pointer.
    */
    T * end() noexcept
    {
      // we want to return the set's size, and not the array's.
      return m_data.begin() + m_size;
    }


  private:
    size_t m_size;
    Array<T> m_data;
    Array<T> m_index;
};

}

#endif
