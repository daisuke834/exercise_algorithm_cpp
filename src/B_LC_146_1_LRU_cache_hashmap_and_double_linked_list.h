/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode Problem #146. Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put. Time complexities of both operations should be O(1).
 * Implemented by hashmap and Doubly-linked-list.
 */

#ifndef SRC_B_LC_146_1_LRU_CACHE_HASHMAP_AND_DOUBLE_LINKED_LIST_H_
#define SRC_B_LC_146_1_LRU_CACHE_HASHMAP_AND_DOUBLE_LINKED_LIST_H_

#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace LC_146_1 {

constexpr int32_t kInvalidValue = INT32_MAX;
constexpr int32_t kNotFound = -1;
constexpr int32_t kInvalidIndex = -1;
constexpr int32_t kInvalidKey = INT32_MAX;

struct Element {
  int32_t key{kInvalidKey};
  int32_t value{kInvalidValue};
  int32_t index{kInvalidIndex};
  Element *newer{nullptr};
  Element *older{nullptr};
};

class LRUCache {
 public:
  LRUCache(int capacity);
  int get(int key);
  void put(int key, int value);

 private:
  void MoveTop(Element *target);

 private:
  const int32_t size_;
  std::vector<Element> cache_;
  std::unordered_map<int32_t, int32_t> cache_indices_;
  const int32_t top_index_;
  const int32_t bottom_index_;
};

}  // namespace LC_146_1

#endif  // SRC_B_LC_146_1_LRU_CACHE_HASHMAP_AND_DOUBLE_LINKED_LIST_H_
