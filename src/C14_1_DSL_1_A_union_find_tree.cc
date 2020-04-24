/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-1. 高度なデータ構造、Union Find Tree
 * (素集合データ構造, Union Find木, 互いに素な集合, Disjoint Sets Forest)
 * 計算量=O(log(N))
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C14_1_DSL_1_A_union_find_tree.h"
#include <iostream>
#include <string>

namespace DSL_1_A {

enum Command : int32_t { kCommandUnite = 0, kCommandSame = 1 };

void CallUnionFindTree(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  UnionFindTree *union_find_tree = new UnionFindTree();
  try {
    int32_t number_of_elements;
    input_stream >> number_of_elements;
    union_find_tree->Initialize(number_of_elements);
    int32_t number_of_queries;
    input_stream >> number_of_queries;
    for (int32_t i = 0; i < number_of_queries; ++i) {
      int32_t command;
      int32_t x, y;
      input_stream >> command >> x >> y;
      bool is_same;
      switch (command) {
        case kCommandUnite:
          union_find_tree->UniteSets(x, y);
          break;
        case kCommandSame:
          is_same = union_find_tree->IsSameSet(x, y);
          if (is_same) {
            std::cout << 1 << std::endl;
          } else {
            std::cout << 0 << std::endl;
          }
          break;
        default:
          std::cerr << "CallUnionFindTree(): Invalid command = " << command << std::endl;
          throw 1;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: CallUnionFindTree()" << std::endl;
    throw;
  }
  delete union_find_tree;
}

// ****************************************************

UnionFindTree::UnionFindTree() noexcept : number_of_elements_(0) {}

UnionFindTree::~UnionFindTree() noexcept {}

void UnionFindTree::Initialize(const int32_t number_of_elements) {
  if ((number_of_elements < 0) || (number_of_elements > kMaxNumberOfElements)) {
    std::cerr << "ERROR: Initialize(): Invalid arg: number_of_elements = " << number_of_elements << std::endl;
    throw 1;
  }
  number_of_elements_ = number_of_elements;
  for (int32_t index = 0; index < number_of_elements; ++index) {
    SetRoot(index, index);
  }
}

bool UnionFindTree::IsSameSet(const int32_t element_1, const int32_t element_2) const {
  bool is_same_set;
  if (InvalidIndex(element_1)) {
    std::cerr << "ERROR: IsSameSet(): Invalid arg: element_1 = " << element_1 << std::endl;
    throw 1;
  } else if (InvalidIndex(element_2)) {
    std::cerr << "ERROR: IsSameSet(): Invalid arg: element_2 = " << element_2 << std::endl;
    throw 1;
  } else {
    try {
      const int32_t root_1 = GetRoot(element_1);
      const int32_t root_2 = GetRoot(element_2);
      is_same_set = (root_1 == root_2);
    } catch (...) {
      std::cerr << "ERROR: IsSameSet()" << std::endl;
      throw;
    }
  }
  return is_same_set;
}

void UnionFindTree::UniteSets(const int32_t element_1, const int32_t element_2) {
  if (InvalidIndex(element_1)) {
    std::cerr << "ERROR: UniteSets(): Invalid arg: element_1 = " << element_1 << std::endl;
    throw 1;
  } else if (InvalidIndex(element_2)) {
    std::cerr << "ERROR: UniteSets(): Invalid arg: element_2 = " << element_2 << std::endl;
    throw 1;
  } else {
    try {
      if (IsSameSet(element_1, element_2)) {
        // DO NOTHING
      } else {
        const int32_t depth_1 = GetDepth(element_1);
        const int32_t depth_2 = GetDepth(element_2);
        if (depth_1 > depth_2) {
          const int32_t root = element_2;
          SetRootRecursively(element_1, root);
        } else {
          const int32_t root = element_1;
          SetRootRecursively(element_2, root);
        }
      }
    } catch (...) {
      std::cerr << "ERROR: UniteSets(): element_1=" << element_1 << ", element_2=" << element_2 << std::endl;
      throw;
    }
  }
}

void UnionFindTree::SetRootRecursively(const int32_t element_index, const int32_t root_index) {
  if (InvalidIndex(element_index)) {
    std::cerr << "ERROR: SetRootRecursively(): Invalid arg: element_index = " << element_index << std::endl;
    throw 1;
  } else if (InvalidIndex(root_index)) {
    std::cerr << "ERROR: SetRootRecursively(): Invalid arg: root_index = " << root_index << std::endl;
    throw 1;
  } else {
    // DO NOTHING
  }
  bool root_found = false;
  try {
    int32_t current_index = element_index;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      const int32_t previous_parent = GetParentIndex(current_index);
      const bool is_root = IsRoot(current_index);
      SetRoot(current_index, root_index);
      if (is_root) {
        root_found = true;
        break;
      } else {
        current_index = previous_parent;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: SetRootRecursively()" << std::endl;
    throw;
  }
  if (!root_found) {
    std::cerr << "ERROR: SetRootRecursively(): Root of element_index was not found." << std::endl;
    throw 1;
  }
}

int32_t UnionFindTree::GetRoot(const int32_t element_index) const {
  int32_t root_index = kInvalidIndex;
  try {
    int32_t current_index = element_index;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      if (IsRoot(current_index)) {
        root_index = current_index;
        break;
      } else {
        current_index = GetParentIndex(current_index);
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetRoot(): element_index=" << element_index << std::endl;
    throw;
  }
  if (root_index == kInvalidIndex) {
    std::cerr << "ERROR: GetRoot(): Root was not found. element_index=" << element_index << std::endl;
    throw 1;
  }
  return root_index;
}

void UnionFindTree::SetRoot(const int32_t element_index, const int32_t root_index) {
  if (InvalidIndex(element_index)) {
    std::cerr << "ERROR: IsSameSet(): Invalid arg: element_index = " << element_index << std::endl;
    throw 1;
  } else if (InvalidIndex(root_index)) {
    std::cerr << "ERROR: IsSameSet(): Invalid arg: root_index = " << root_index << std::endl;
    throw 1;
  } else {
    elements_[element_index].parent = root_index;
  }
}

bool UnionFindTree::IsRoot(const int32_t element_index) const {
  if (InvalidIndex(element_index)) {
    std::cerr << "ERROR: IsRoot(): Invalid arg: element_index = " << element_index << std::endl;
    throw 1;
  }
  bool is_root;
  try {
    is_root = (GetParentIndex(element_index) == element_index);
  } catch (...) {
    std::cerr << "ERROR: IsRoot()" << std::endl;
    throw;
  }
  return is_root;
}

int32_t UnionFindTree::GetDepth(const int32_t element_index) const {
  int32_t depth = 0;
  bool root_found = false;
  try {
    int32_t current_index = element_index;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      if (IsRoot(current_index)) {
        root_found = true;
        break;
      } else {
        current_index = GetParentIndex(current_index);
        ++depth;
      }
    }
  } catch (...) {
    std::cerr << "ERROR: GetDepth()" << std::endl;
    throw;
  }
  if (!root_found) {
    std::cerr << "ERROR: GetDepth(): Root was not found." << std::endl;
    throw 1;
  }
  return depth;
}

int32_t UnionFindTree::GetParentIndex(const int32_t element_index) const {
  if (InvalidIndex(element_index)) {
    std::cerr << "ERROR: IsRoot(): Invalid arg: element_index = " << element_index << std::endl;
    throw 1;
  }
  return elements_[element_index].parent;
}

bool UnionFindTree::InvalidIndex(const int32_t element_index) const noexcept {
  return ((element_index < 0) || (element_index >= number_of_elements_));
}

void UnionFindTree::Debug() const noexcept {
  for (int32_t index = 0; index < number_of_elements_; ++index) {
    int32_t current_index = index;
    for (int32_t i = 0; i < kMaxLoopCount; ++i) {
      if (i != 0) {
        std::cerr << " -> ";
      }
      std::cerr << current_index;
      if (IsRoot(current_index)) {
        std::cerr << std::endl;
        break;
      }
      current_index = elements_[current_index].parent;
    }
  }
}

// **********************************************************************

}  // namespace DSL_1_A
