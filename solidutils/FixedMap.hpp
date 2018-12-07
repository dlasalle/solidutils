/**
 * @file FixedMap.hpp
 * @brief The FixedMap class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2018
 * @version 1
 * @date 2018-12-05
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


#ifndef SOLIDUTILS_INCLUDE_FIXEDMAP_HPP
#define SOLIDUTILS_INCLUDE_FIXEDMAP_HPP


#include "Array.hpp"
#include "ConstArray.hpp"

namespace sl
{

/**
* @brief The FixedMap class provides a map implementation which allows for
* insertion, querying, and deletion in constant time. While std::unordered_set
* may give constant time complexity of these operations through a hash table,
* this does so through fixed size dense vector (no hashing), and store the data
* in a contiguous chunk of memory.
*
* @tparam K The key type, must an integer.
* @tparam V The value type, must be trivial.
*/
template <typename K, typename V>
class FixedMap
{
  public:
    static constexpr K const NULL_INDEX = static_cast<K>(-1);

    /**
    * @brief Create a new empty fixed set.
    *
    * @param size The size of the set.
    */
    FixedMap(
        size_t const size) :
      m_size(0),
      m_keys(size),
      m_values(size),
      m_index(size, NULL_INDEX)
    {
      // do nothing
    }


    /**
    * @brief Check if an key exists in this set.
    *
    * @param key The key.
    *
    * @return True if the key is in the map.
    */
    bool has(
        K const key) const noexcept
    {
      size_t const index = static_cast<size_t>(key);

      ASSERT_LESS(index, m_index.size());

      return m_index[index] != NULL_INDEX;
    }


    /**
    * @brief Get the value associated with a given key.
    *
    * @param key The key.
    *
    * @return The value.
    */
    V get(
        K const key) const noexcept
    {
      size_t const index = static_cast<size_t>(key);

      ASSERT_LESS(index, m_index.size());

      return m_values[m_index[index]];
    }

    /**
    * @brief Add an key-value pair to this set.
    *
    * @param key The key.
    * @param value The value.
    */
    void add(
        K const key,
        V const value) noexcept
    {
      size_t const index = static_cast<size_t>(key);

      ASSERT_LESS(index, m_index.size());
      ASSERT_EQUAL(m_index[index], NULL_INDEX);

      m_keys[m_size] = key;
      m_values[m_size] = value;

      m_index[index] = m_size;

      ++m_size;
    }


    /**
    * @brief Remove an key-value pair from this set.
    *
    * @param key The key to remove.
    */
    void remove(
        K const key) noexcept
    {
      size_t const index = static_cast<size_t>(key);

      ASSERT_LESS(index, m_index.size());
      ASSERT_NOTEQUAL(m_index[index], NULL_INDEX);

      --m_size;
      K const swapKey = m_keys[m_size];
      V const swapValue = m_values[m_size];
      size_t const place = m_index[index];
      m_keys[place] = swapKey;
      m_values[place] = swapValue;
      m_index[static_cast<size_t>(swapKey)] = place;
      m_index[index] = NULL_INDEX;
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
    * @brief Get the keys in this map.
    *
    * @return The keys.
    */
    ConstArray<K> keys() const noexcept
    {
      return ConstArray<K>(m_keys.data(), m_size);
    }

    /**
    * @brief Get the values in this map.
    *
    * @return The values.
    */
    ConstArray<V> values() const noexcept
    {
      return ConstArray<V>(m_values.data(), m_size);
    }


  private:
    size_t m_size;
    Array<K> m_keys;
    Array<V> m_values;
    Array<K> m_index;
};

}


#endif
