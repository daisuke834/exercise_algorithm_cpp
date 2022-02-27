/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part4-4. データ構造、双方向連結リストのテスト。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

#include <iostream>
#include <sstream>

#include "src/C04_4_ALDS1_3_C_doubly_linked_list.h"

namespace ALDS1_3_C {

class Test_ALDS1_3_C : public ::testing::Test {
 protected:
  DoublyLinkedList* linked_list_;
  virtual void SetUp() { linked_list_ = new DoublyLinkedList(); }
  virtual void TearDown() { delete linked_list_; }
};

TEST_F(Test_ALDS1_3_C, Key) {
  Key key_1(1);
  Key key_2(2);
  ASSERT_FALSE(key_1.Equals(key_2));

  Key key_1_1 = key_1;
  ASSERT_TRUE(key_1.Equals(key_1_1));
  ASSERT_FALSE(key_2.Equals(key_1_1));

  Key key_1_2 = Key(1);
  ASSERT_TRUE(key_1.Equals(key_1_2));
  ASSERT_FALSE(key_2.Equals(key_1_2));

  Key key_1_3(key_1);
  ASSERT_TRUE(key_1.Equals(key_1_3));
  ASSERT_FALSE(key_2.Equals(key_1_3));

  Key key_1_4 = Key(key_1);
  ASSERT_TRUE(key_1.Equals(key_1_4));
  ASSERT_FALSE(key_2.Equals(key_1_4));

  Key key_1_5 = std::move(key_1_4);
  ASSERT_TRUE(key_1.Equals(key_1_5));
  ASSERT_FALSE(key_1_5.Equals(key_1_4));
  ASSERT_FALSE(key_2.Equals(key_1_5));
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_Insert) {
  ASSERT_EQ(0, linked_list_->FindInvalidNode());
  ASSERT_EQ(kInvalidIndex, linked_list_->top_);
  ASSERT_EQ(kInvalidIndex, linked_list_->tail_);

  const Key key1(1);
  int32_t inserted_index = 0;
  const int32_t inserted_index_1 = inserted_index;
  linked_list_->Insert(key1);
  ASSERT_EQ(inserted_index_1, linked_list_->top_);
  ASSERT_EQ(inserted_index_1, linked_list_->tail_);
  ASSERT_EQ(kTopIndex, linked_list_->nodes_[inserted_index_1].GetPrevious());
  ASSERT_EQ(kTailIndex, linked_list_->nodes_[inserted_index_1].GetNext());
  const Key stored_key_1 = linked_list_->nodes_[inserted_index_1].GetKey();
  ASSERT_TRUE(key1.Equals(stored_key_1));

  const Key key2(2);
  linked_list_->Insert(key2);
  ++inserted_index;
  const int32_t inserted_index_2 = inserted_index;
  ASSERT_EQ(inserted_index_2, linked_list_->top_);
  ASSERT_EQ(inserted_index_1, linked_list_->tail_);
  ASSERT_EQ(kTopIndex, linked_list_->nodes_[inserted_index_2].GetPrevious());
  ASSERT_EQ(inserted_index_1, linked_list_->nodes_[inserted_index_2].GetNext());
  ASSERT_EQ(inserted_index_2, linked_list_->nodes_[inserted_index_1].GetPrevious());
  ASSERT_EQ(kTailIndex, linked_list_->nodes_[inserted_index_1].GetNext());
  ASSERT_TRUE(linked_list_->nodes_[inserted_index_1].HasKey(key1));
  ASSERT_EQ(inserted_index_1, linked_list_->Search(key1));
  ASSERT_TRUE(linked_list_->nodes_[inserted_index_2].HasKey(key2));
  ASSERT_EQ(inserted_index_2, linked_list_->Search(key2));

  const Key key3(3);
  linked_list_->Insert(key3);
  ++inserted_index;
  const int32_t inserted_index_3 = inserted_index;
  ASSERT_EQ(inserted_index_2, linked_list_->nodes_[inserted_index_3].GetNext());
  ASSERT_EQ(inserted_index_1, linked_list_->nodes_[inserted_index_2].GetNext());
  ASSERT_EQ(kTailIndex, linked_list_->nodes_[inserted_index_1].GetNext());
  ASSERT_EQ(inserted_index_1, linked_list_->tail_);

  ASSERT_EQ(inserted_index_2, linked_list_->nodes_[inserted_index_1].GetPrevious());
  ASSERT_EQ(inserted_index_3, linked_list_->nodes_[inserted_index_2].GetPrevious());
  ASSERT_EQ(kTopIndex, linked_list_->nodes_[inserted_index_3].GetPrevious());
  ASSERT_EQ(inserted_index_3, linked_list_->top_);

  ASSERT_EQ(inserted_index_1, linked_list_->Search(key1));
  ASSERT_EQ(inserted_index_2, linked_list_->Search(key2));
  ASSERT_EQ(inserted_index_3, linked_list_->Search(key3));
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_Insert_full) {
  for (int32_t key_index = 0; key_index < 1000000; ++key_index) {
    const Key key(key_index);
    ASSERT_TRUE(key.IsValid());
    linked_list_->Insert(key);
  }
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_Delete_single) {
  const Key key1(1);
  const int32_t kInsertedIndex_1 = 0;
  linked_list_->Insert(key1);
  ASSERT_EQ(kInsertedIndex_1, linked_list_->Search(key1));

  linked_list_->Delete(key1);
  ASSERT_ANY_THROW(linked_list_->Search(key1));
  ASSERT_EQ(kInvalidIndex, linked_list_->top_);
  ASSERT_EQ(kInvalidIndex, linked_list_->tail_);
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_Delete_triple) {
  const Key key1(1);
  const Key key2(2);
  const Key key3(3);
  const int32_t kInsertedIndex_1 = 0;
  const int32_t kInsertedIndex_2 = 1;
  const int32_t kInsertedIndex_3 = 2;
  linked_list_->Insert(key1);
  linked_list_->Insert(key2);
  linked_list_->Insert(key3);
  ASSERT_EQ(kInsertedIndex_1, linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_2, linked_list_->Search(key2));
  ASSERT_EQ(kInsertedIndex_3, linked_list_->Search(key3));
  ASSERT_EQ(kInsertedIndex_3, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_1, linked_list_->tail_);

  linked_list_->Delete(key1);
  ASSERT_ANY_THROW(linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_2, linked_list_->Search(key2));
  ASSERT_EQ(kInsertedIndex_3, linked_list_->Search(key3));
  ASSERT_EQ(kInsertedIndex_3, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_2, linked_list_->tail_);

  linked_list_->Delete(key3);
  ASSERT_ANY_THROW(linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_2, linked_list_->Search(key2));
  ASSERT_ANY_THROW(linked_list_->Search(key3));
  ASSERT_EQ(kInsertedIndex_2, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_2, linked_list_->tail_);

  linked_list_->Insert(key1);
  // ASSERT_EQ(kInsertedIndex_1, linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_3, linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_2, linked_list_->Search(key2));
  ASSERT_ANY_THROW(linked_list_->Search(key3));
  // ASSERT_EQ(kInsertedIndex_1, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_3, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_2, linked_list_->tail_);
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_duplicated_key) {
  const Key key1(1);
  linked_list_->Insert(key1);
  linked_list_->Insert(key1);
  const int32_t kInsertedIndex_1_1 = 0;
  const int32_t kInsertedIndex_1_2 = 1;
  ASSERT_EQ(kInsertedIndex_1_2, linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_1_2, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_1_1, linked_list_->tail_);

  linked_list_->Delete(key1);
  ASSERT_EQ(kInsertedIndex_1_1, linked_list_->Search(key1));
  ASSERT_EQ(kInsertedIndex_1_1, linked_list_->top_);
  ASSERT_EQ(kInsertedIndex_1_1, linked_list_->tail_);

  linked_list_->Delete(key1);
  ASSERT_ANY_THROW(linked_list_->Search(key1));
  ASSERT_EQ(kInvalidIndex, linked_list_->top_);
  ASSERT_EQ(kInvalidIndex, linked_list_->tail_);
}

TEST_F(Test_ALDS1_3_C, DoublyLinkedList_print) {
  std::ostringstream answer;
  answer << "6 1 2" << std::endl;

  linked_list_->Insert(Key(5));
  ASSERT_EQ(5, linked_list_->nodes_[0].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[0].IsValid());
  linked_list_->Insert(Key(2));
  ASSERT_EQ(2, linked_list_->nodes_[1].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[1].IsValid());
  linked_list_->Insert(Key(3));
  linked_list_->Insert(Key(1));
  ASSERT_EQ(1, linked_list_->nodes_[3].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[3].IsValid());
  linked_list_->Delete(Key(3));
  linked_list_->Insert(Key(6));
  ASSERT_EQ(6, linked_list_->nodes_[4].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[4].IsValid());
  linked_list_->Delete(Key(5));
  ASSERT_EQ(2, linked_list_->nodes_[1].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[1].IsValid());
  ASSERT_EQ(1, linked_list_->nodes_[3].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[3].IsValid());
  ASSERT_EQ(6, linked_list_->nodes_[4].GetKey().GetKey());
  ASSERT_TRUE(linked_list_->nodes_[4].IsValid());
  testing::internal::CaptureStdout();
  linked_list_->Print();
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_C, CallDoublyLinkedList_1) {
  std::ostringstream answer;
  answer << "6 1 2" << std::endl;

  std::ostringstream input_stream;
  input_stream << "7" << std::endl;
  input_stream << "insert 5" << std::endl;
  input_stream << "insert 2" << std::endl;
  input_stream << "insert 3" << std::endl;
  input_stream << "insert 1" << std::endl;
  input_stream << "delete 3" << std::endl;
  input_stream << "insert 6" << std::endl;
  input_stream << "delete 5" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallDoublyLinkedList(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_C, CallDoublyLinkedList_2) {
  std::ostringstream answer;
  answer << "1" << std::endl;

  std::ostringstream input_stream;
  input_stream << "9" << std::endl;
  input_stream << "insert 5" << std::endl;
  input_stream << "insert 2" << std::endl;
  input_stream << "insert 3" << std::endl;
  input_stream << "insert 1" << std::endl;
  input_stream << "delete 3" << std::endl;
  input_stream << "insert 6" << std::endl;
  input_stream << "delete 5" << std::endl;
  input_stream << "deleteFirst" << std::endl;
  input_stream << "deleteLast" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallDoublyLinkedList(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

TEST_F(Test_ALDS1_3_C, CallDoublyLinkedList_3) {
  std::ostringstream answer;
  answer << "7 1234566890 999999999" << std::endl;

  std::ostringstream input_stream;
  input_stream << "8" << std::endl;
  input_stream << "insert 1000000000" << std::endl;
  input_stream << "insert 999999999" << std::endl;
  input_stream << "deleteLast" << std::endl;
  input_stream << "insert 1234566890" << std::endl;
  input_stream << "insert 5" << std::endl;
  input_stream << "deleteFirst" << std::endl;
  input_stream << "insert 7" << std::endl;
  input_stream << "delete 5" << std::endl;
  std::istringstream iss(input_stream.str());

  testing::internal::CaptureStdout();
  CallDoublyLinkedList(iss);
  const std::string captured_stdout = testing::internal::GetCapturedStdout();
  ASSERT_STREQ(answer.str().c_str(), captured_stdout.c_str());
}

}  // namespace ALDS1_3_C
