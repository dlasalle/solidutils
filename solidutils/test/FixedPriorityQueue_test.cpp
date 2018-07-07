/**
 * @file FixedPriorityQueue_test.cpp
 * @brief Unit tests for the FixedPriorityQueue class.
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2017, Solid Lake LLC
 * @version 1
 * @date 2017-10-20
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
    pq.add(i, i);
  }

  for (int i = 0; i < 10; ++i) {
    if (i % 3 == 0) {
      pq.updateByDelta(i, i);
    }
  }

  // verify top element
  testEqual(pq.max(), 18);
  testEqual(pq.peek(), 9);

  float lastPriority = pq.max();
  for (int i = 0; i < 10; ++i) {
    float const newPriority = pq.max();
    int const x = pq.pop();

    // verify we're getting them in order
    testLessOrEqual(newPriority, lastPriority);

    // verify we have the right priority
    if (x % 3 == 0) {
      testEqual(newPriority, static_cast<float>(x*2));
    } else {
      testEqual(newPriority, static_cast<float>(x));
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
