/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-4. データ構造、双方向連結リスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C04_4_ALDS1_3_C_DOUBLY_LINKED_LIST_H_
#define SRC_C04_4_ALDS1_3_C_DOUBLY_LINKED_LIST_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code
#include <cstdint>
#include <iostream>
#include <string>

namespace ALDS1_3_C {

constexpr int32_t kMaxNumberOfActiveNodes = 1000000;
constexpr int32_t kMaxNumberOfDeletedNodes = 20;
constexpr int32_t kMaxNumberOfNodes = kMaxNumberOfActiveNodes + kMaxNumberOfDeletedNodes;
constexpr int32_t kInvalidIndex = -1;
constexpr int32_t kTopIndex = -2;
constexpr int32_t kTailIndex = -3;

void CallDoublyLinkedList(std::istream &input_stream);

class Key {
 public:
  Key() noexcept;
  explicit Key(const int32_t key) noexcept;
  ~Key() noexcept;
  Key(const Key &obj) noexcept;
  Key &operator=(const Key &rhs) noexcept;
  Key(Key &&obj) noexcept;
  Key &operator=(Key &&rhs) noexcept;
  bool Equals(const Key &obj) const noexcept;
  int32_t GetKey() const noexcept;
  bool IsValid() const noexcept;

 private:
  int32_t key_;
};

class Node {
 public:
  Node() noexcept;
  ~Node() noexcept;
  void SetKey(const Key &key) noexcept;
  void UpdateNext(int32_t next) noexcept;
  void UpdatePrevious(int32_t previous) noexcept;
  bool IsValid() const noexcept;
  Key GetKey() const noexcept;
  bool HasKey(const Key &key) const noexcept;
  int32_t GetNext() const noexcept;
  int32_t GetPrevious() const noexcept;

 private:
  Node(const Node &obj) = delete;
  Node &operator=(const Node &rhs) = delete;
  Node(Node &&obj) = delete;
  Node &operator=(Node &&rhs) = delete;

 private:
  int32_t next_;
  int32_t previous_;
  Key key_;
};

class DoublyLinkedList {
 public:
  DoublyLinkedList() noexcept;
  ~DoublyLinkedList() noexcept;
  void Insert(const Key &key);
  void Delete(const Key &key);
  void DeleteFirst();
  void DeleteLast();
  void Print() const;

 private:
  DoublyLinkedList(const DoublyLinkedList &obj) = delete;
  DoublyLinkedList &operator=(const DoublyLinkedList &obj) = delete;
  DoublyLinkedList(DoublyLinkedList &&obj) = delete;
  DoublyLinkedList &operator=(DoublyLinkedList &&obj) = delete;

  int32_t FindInvalidNode();
  int32_t Search(const Key &key);

 private:
  int32_t top_;
  int32_t tail_;
  Node nodes_[kMaxNumberOfNodes];

 private:
  FRIEND_TEST(Test_ALDS1_3_C, DoublyLinkedList_Insert);          // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_C, DoublyLinkedList_Delete_single);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_C, DoublyLinkedList_Delete_triple);   // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_C, DoublyLinkedList_duplicated_key);  // Should be removed from production code
  FRIEND_TEST(Test_ALDS1_3_C, DoublyLinkedList_print);           // Should be removed from production code
};

}  // namespace ALDS1_3_C
#endif  // SRC_C04_4_ALDS1_3_C_DOUBLY_LINKED_LIST_H_
