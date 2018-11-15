/**
 * @file FixedPriorityQueue_test.cpp
 * @brief Unit tests for the FixedPriorityQueue class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017, Solid Lake LLC
 * @version 1
 * @date 2017-10-20
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




#include "UnitTest.hpp"
#include "FixedPriorityQueue.hpp"


namespace sl
{


UNITTEST(FixedPriortyQueue, AddPopInOrder)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  for (int i = 0; i < 10; ++i) {
    int const num = pq.pop();
    testEqual(num, i);
  }
}


UNITTEST(FixedPriortyQueue, AddPeek)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  testEqual(pq.peek(), 0);
}


UNITTEST(FixedPriortyQueue, AddMax)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  testEqual(pq.max(), 1.0);
}


UNITTEST(FixedPriortyQueue, AddContains)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      pq.add(1.0/(i+1), i);
    }
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      testTrue(pq.contains(i));
    } else {
      testFalse(pq.contains(i));
    }
  }

}


UNITTEST(FixedPriortyQueue, AddUpdate)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      pq.update(i, i);
    }
  }

  // verify top element
  testEqual(pq.max(), 9);
  testEqual(pq.peek(), 9);

  float lastPriority = pq.max();
  for (int i = 0; i < 10; ++i) {
    float const newPriority = pq.max();
    int const x = pq.pop();

    // verify we're getting them in order
    testLessOrEqual(newPriority, lastPriority);

    // verify we have the right priority
    if (x % 3 == 0) {
      testEqual(newPriority, x);
    } else {
      testEqual(newPriority, static_cast<float>(1.0/(x+1)));
    }

    lastPriority = newPriority;
  }
}

UNITTEST(FixedPriortyQueue, UpdateByDelta)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(-i, i);
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      pq.updateByDelta(2*i, i);
    }
  }

  // verify top element
  testEqual(pq.max(), 9);
  testEqual(pq.peek(), 9);

  float lastPriority = pq.max();
  for (int i = 0; i < 10; ++i) {
    float const newPriority = pq.max();
    int const x = pq.pop();

    // verify we're getting them in order
    testLessOrEqual(newPriority, lastPriority);

    // verify we have the right priority
    if (x % 3 == 0) {
      testEqual(newPriority, static_cast<float>(x));
    } else {
      testEqual(newPriority, static_cast<float>(-x));
    }

    lastPriority = newPriority;
  }
}




UNITTEST(FixedPriortyQueue, AddPopReverseOrder)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(i/10.0, i);
  }

  for (int i = 10; i > 0;) {
    --i;
    int const num = pq.pop();
    testEqual(num, i);
  }
}


UNITTEST(FixedPriortyQueue, AddRemoveContains)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      pq.remove(i);
    }
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      testFalse(pq.contains(i));
    } else {
      testTrue(pq.contains(i));
    }
  }
}


UNITTEST(FixedPriortyQueue, Clear)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  // remove a couple
  pq.pop();
  pq.pop();

  pq.clear();
  testEqual(0u, pq.size());

  // verify that it is empty
  for (int i = 0; i < 10; ++i) {
    testFalse(pq.contains(i));
  }

  // test that we can re-use the priorty queue again
  for (int i = 0; i < 10; ++i) {
    pq.add(i/10.0, i);
  }

  for (int i = 10; i > 0;) {
    --i;
    int const num = pq.pop();
    testEqual(num, i);
  }
}


UNITTEST(FixedPriorityQueue, RemainingAll)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 10; ++i) {
    pq.add(1.0/(i+1), i);
  }

  size_t count = 0;
  for (int const i : pq.remaining()) {
    ++count;
    testTrue(pq.contains(i));
  }

  testEqual(count, pq.size());
}

UNITTEST(FixedPriorityQueue, RemainingHalf)
{
  FixedPriorityQueue<float, int> pq(10);

  for (int i = 0; i < 7; ++i) {
    pq.add(1.0/(i+1), i);
  }

  pq.pop();
  pq.pop();

  size_t count = 0;
  for (int const i : pq.remaining()) {
    ++count;
    testTrue(pq.contains(i));
  }

  testEqual(count, pq.size());
}

}
