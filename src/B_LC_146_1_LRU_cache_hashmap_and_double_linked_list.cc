/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief LeetCode Problem #146. Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put. Time complexities of both operations should be O(1).
 * Implemented by hashmap and Doubly-linked-list.
 */

#include "src/B_LC_146_1_LRU_cache_hashmap_and_double_linked_list.h"

namespace LC_146_1 {

LRUCache::LRUCache(int capacity) : size_(capacity + 2), top_index_(size_ - 1), bottom_index_(0) {
  cache_ = std::vector<Element>(size_);
  for (int32_t i = 0; i < size_; ++i) {
    cache_[i].index = i;
    if (i != size_ - 1) {
      cache_[i].newer = &cache_[i + 1];
    }
    if (i != 0) {
      cache_[i].older = &cache_[i - 1];
    }
  }
}

int LRUCache::get(int key) {
  int value;
  if (cache_indices_.find(key) == cache_indices_.end()) {
    value = kNotFound;
  } else {
    const int32_t index = cache_indices_[key];
    value = cache_[index].value;
    MoveTop(&cache_[index]);
  }
  return value;
}

void LRUCache::put(int key, int value) {
  if (cache_indices_.find(key) == cache_indices_.end()) {
    Element* assigned = cache_[bottom_index_].newer;
    if (assigned->key != kInvalidKey) {
      cache_indices_.erase(cache_indices_.find(assigned->key));
    }
    cache_indices_[key] = assigned->index;
    assigned->key = key;
    assigned->value = value;
    MoveTop(assigned);
  } else {
    const int32_t index = cache_indices_[key];
    cache_[index].value = value;
    MoveTop(&cache_[index]);
  }
}

void LRUCache::MoveTop(Element* target) {
  target->newer->older = target->older;
  target->older->newer = target->newer;
  target->newer = &cache_[top_index_];
  cache_[top_index_].older->newer = target;
  target->older = cache_[top_index_].older;
  cache_[top_index_].older = target;
}

}  // namespace LC_146_1
