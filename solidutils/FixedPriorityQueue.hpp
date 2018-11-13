/**
 * @file FixedPriorityQueue.hpp
 * @brief The FixedPriorityQueue class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017-2018, Solid Lake LLC
 * @version 1
 * @date 2017-10-20
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




#ifndef SOLIDUTILS_INCLUDE_FIXEDPRIORITYQUEUE_HPP
#define SOLIDUTILS_INCLUDE_FIXEDPRIORITYQUEUE_HPP

#include "Array.hpp"

namespace sl
{


/**
* @brief The FixedPriorityQueue class provides a priority queue implementation
* with the standard O(log n) insertion, deletion, pop, and update operations,
* but in addition can perform non-modifying queries in O(1) time.
*
* @tparam K The key type.
* @tparam V The value type.
*/
template<typename K, typename V>
class FixedPriorityQueue
{
  public:
    static constexpr size_t const NULL_INDEX = static_cast<size_t>(-1);

    class ValueSet
    {
      public:
      class Iterator
      {
        public:
        /**
        * @brief Create a new forward iterator.
        *
        * @param index The index of the iterator.
        * @param q The priority queue being iterated.
        */
        Iterator(
            size_t const index,
            FixedPriorityQueue<K,V> const * const q) :
          m_index(index),
          m_q(q)
        {
          // do nothing
        }

        /**
        * @brief Get the value of the iterator.
        *
        * @return The value.
        */
        inline V operator*() const noexcept
        {
          size_t const pos = m_q->m_index[m_index];
          return m_q->m_data[pos].value;
        }

        /**
        * @brief Move the iterator forward.
        *
        * @return This iterator.
        */
        inline Iterator & operator++()
        {
          do {
            ++m_index;
          } while (m_index < m_q->m_index.size() && \
              m_q->m_index[m_index] == NULL_INDEX);

          return *this;
        }

        /**
        * @brief Check if this iterator is the same as another.
        *
        * @param other The other iterator.
        *
        * @return True if they are at the same position.
        */
        inline bool operator==(
            Iterator const & other) const
        {
          return m_index == other.m_index;
        }

        /**
        * @brief Check if this iterator is different from another iterator.
        *
        * @param other The other iterator.
        *
        * @return True if the iterators are not equal.
        */
        inline bool operator!=(
            Iterator const & other) const
        {
          return !(*this == other);
        }

        private:
        size_t m_index;
        FixedPriorityQueue<K,V> const * m_q;
      };

      /**
      * @brief Create a new value set.
      *
      * @param q The priority queue.
      */
      ValueSet(
          FixedPriorityQueue<K,V> const * const q) :
        m_q(q)
      {
        // do nothing
      }

      /**
      * @brief Get the forward iterator to the start of the set.
      *
      * @return The forward iterator.
      */
      inline Iterator begin() const noexcept
      {
        // find first valid index
        size_t index = 0;
        while (index < m_q->m_index.size() && \
            m_q->m_index[index] == NULL_INDEX) {
          ++index;
        }

        return Iterator(index, m_q);
      }

      /**
      * @brief Get the forward iterator to the end of the set.
      *
      * @return The end iterator.
      */
      inline Iterator end() const noexcept
      {
        return Iterator(m_q->m_index.size(), m_q);
      }

      private:
      FixedPriorityQueue<K,V> const * m_q;
    };

    /**
    * @brief Create a new priority queue that can hold element 0 through max.
    *
    * @param max The max value in the priority queue (exclusive).
    */
    FixedPriorityQueue(
        V const max) :
      m_data(max),
      m_index(max, NULL_INDEX),
      m_size(0)
    {
      // do nothing
    }


    /**
    * @brief Remove an element from the queue.
    *
    * @param elem The element to remove
    */
    void remove(
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      // remove item from heap and sort up
      size_t const index = m_index[value];
      fill(index);
    }


    /**
    * @brief Add an value to the queue.
    *
    * @param key The key/priority of the value to add.
    * @param value The value to add.
    */
    void add(
        K const key,
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_EQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_size++;
      m_index[value] = index;
      m_data[index].key = key;
      m_data[index].value = value;

      siftUp(index);
    }


    /**
    * @brief Update the key associated with a given value.
    *
    * @param key The new key for the value.
    * @param value The value.
    */
    void update(
        K const key,
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_index[value];
      m_data[index].key = key;

      // update position
      if (index > 0 && key > m_data[parentIndex(index)].key) {
        siftUp(index);
      } else {
        siftDown(index);
      }
    }


    /**
    * @brief Update the key associated with a given value by modifying the key.
    *
    * @param delta The change in priority.
    * @param value The value.
    */
    void updateByDelta(
        K const delta,
        V const value) noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      size_t const index = m_index[value];
      V const key = m_data[index].key + delta;

      update(key, value);
    }

    /**
    * @brief Check if a value in present in the priority queue.
    *
    * @param value The value to check for.
    *
    * @return Whether or not the value is present.
    */
    bool contains(
        V const value) const noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());

      return m_index[value] != NULL_INDEX;
    }


    /**
    * @brief Get the key associated with the given value.
    *
    * @param value The value.
    *
    * @return The key.
    */
    K get(
        V const value) const noexcept
    {
      ASSERT_LESS(static_cast<size_t>(value), m_index.size());
      ASSERT_NOTEQUAL(m_index[value], NULL_INDEX);

      return m_data[m_index[value]].key;
    }


    /**
    * @brief Pop the top value from the queue.
    *
    * @return The top value.
    */
    V pop() noexcept
    {
      ASSERT_GREATER(m_size, 0);

      V const value = m_data[0].value;
      fill(0);

      return value;
    }


    /**
    * @brief Get get the top of the priority queue's value.
    *
    * @return The value.
    */
    V const & peek() const noexcept
    {
      return m_data[0].value;
    }


    /**
    * @brief Get get the top of the priority queue's value.
    *
    * @return The value.
    */
    K const & max() const noexcept
    {
      return m_data[0].key;
    }


    /**
    * @brief Get the number of elements in the queue.
    *
    * @return The number of elements.
    */
    size_t size() const noexcept
    {
      return m_size;
    }


    /**
    * @brief Clear entries from the priority queue.
    */
    void clear() noexcept
    {
      for (size_t i = 0; i < m_size; ++i) {
        m_index[m_data[i].value] = NULL_INDEX;
      }
      m_size = 0;
    }


    /**
    * @brief Get the set of remaining items in the priority. The order of the
    * values is arbitrary.
    *
    * @return The set of values.
    */
    ValueSet remaining() const noexcept
    {
      return ValueSet(this);
    }


  private:
    struct kv_pair_struct
    {
      K key;
      V value;
    };

    Array<kv_pair_struct> m_data;
    Array<size_t> m_index;
    size_t m_size;


    /**
    * @brief Get the index of the parent.
    *
    * @param index The index of the current element.
    *
    * @return The index of the parent element.
    */
    size_t parentIndex(
        size_t const index) const noexcept
    {
      return index / 2;
    }


    /**
    * @brief Get the index of the left child node.
    *
    * @param index The current index.
    *
    * @return The left child index.
    */
    size_t leftChildIndex(
        size_t const index) const noexcept
    {
      return (index * 2)+1;
    }


    /**
    * @brief Get the index of the right child node.
    *
    * @param index The current index.
    *
    * @return The right child index.
    */
    size_t rightChildIndex(
        size_t const index) const noexcept
    {
      return leftChildIndex(index) + 1;
    }


    /**
    * @brief Swap two items within the priority queue.
    *
    * @param indexA The first value.
    * @param indexB The second value.
    */
    void swap(
        size_t const indexA,
        size_t const indexB) noexcept
    {
      V const valueA = m_data[indexA].value;
      V const valueB = m_data[indexB].value;

      std::swap(m_index[valueA], m_index[valueB]);
      std::swap(m_data[indexA], m_data[indexB]);
    }


    /**
    * @brief Fill a whole created in the heap.
    *
    * @param index The index of the hole to fill.
    */
    void fill(
        size_t const index) noexcept
    {
      ASSERT_LESS(index, m_size);

      --m_size;
      V const deletedValue = m_data[index].value;

      if (m_size > 0) {
        // what we'll do is move the bottom node to this position
        m_data[index] = m_data[m_size];

        V const value = m_data[index].value;
        m_index[value] = index;

        siftDown(index);
      }

      m_index[deletedValue] = NULL_INDEX;
    }


    /**
    * @brief Correctly float an item up into the heap.
    *
    * @param index The index of the value to place.
    */
    void siftUp(
        size_t index) noexcept
    {
      while (index > 0) {
        size_t const parent = parentIndex(index);
        if (m_data[parent].key >= m_data[index].key) {
          // reached a valid state
          break;
        }
        swap(index, parent);
        index = parent;
      }
    }


    /**
    * @brief Correctly sink an item up into the heap.
    *
    * @param index The index of the value to place.
    */
    void siftDown(
        size_t index) noexcept
    {
      K const key = m_data[index].key;
      while (true) {
        size_t const leftIndex = leftChildIndex(index);
        size_t const rightIndex = rightChildIndex(index);
        if (rightIndex < m_size && key < m_data[rightIndex].key) {
          if (m_data[rightIndex].key >= m_data[leftIndex].key) {
            swap(index, rightIndex);
            index = rightIndex;
          } else {
            swap(index, leftIndex);
            index = leftIndex;
          }
        } else if (leftIndex < m_size && key < m_data[leftIndex].key) {
          swap(index, leftIndex);
          index = leftIndex;
        } else {
          // life is good -- exit
          break;
        }
      }
    }
};


}

#endif
