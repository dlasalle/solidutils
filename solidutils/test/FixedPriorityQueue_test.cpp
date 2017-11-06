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
  testEqual(0, pq.size());

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


}
