/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode Problem #146. Design and implement a data structure for Least Recently Used (LRU) cache.
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <iostream>
#include <sstream>
#include "src/B_LC_146_1_LRU_cache_hashmap_and_double_linked_list.h"

namespace LC_146_1 {

class Test_LC_146_1 : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(Test_LC_146_1, test_1) {
  LRUCache *cache = new LRUCache(2);

  cache->put(1, 1);
  cache->put(2, 2);
  ASSERT_EQ(1, cache->get(1));
  cache->put(3, 3);
  ASSERT_EQ(kNotFound, cache->get(2));
  cache->put(4, 4);
  ASSERT_EQ(kNotFound, cache->get(1));
  ASSERT_EQ(3, cache->get(3));
  ASSERT_EQ(4, cache->get(4));

  delete cache;
}

}  // namespace LC_146_1
