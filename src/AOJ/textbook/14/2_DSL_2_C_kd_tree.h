/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-2. 高度なデータ構造、kD Tree (kd木, k-dimensional tree)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#ifndef SRC_C14_2_DSL_2_C_KD_TREE_H_
#define SRC_C14_2_DSL_2_C_KD_TREE_H_

#include <gtest/gtest_prod.h>  // Needed for FRIEND_TEST. Should be removed from production code

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace DSL_2_C {

constexpr int32_t kMaxNumberOfPoints = 500000;
constexpr int32_t kMaxNumberOfQueries = 20000;
constexpr int32_t kMaxNumberOfNodes = kMaxNumberOfPoints;
constexpr int32_t kInvalidPointIndex = -1;
constexpr int32_t kInvalidNodeIndex = -1;
constexpr int32_t kLeaf = -2;
constexpr int32_t kMaxLoopCount = 2000000;
constexpr int32_t kInvalidKey = -1;

// ****************************************************
void CallKdTree(std::istream& input_stream);

// ****************************************************
struct Point2D {
  int32_t x{INT32_MAX};
  int32_t y{INT32_MAX};
  int32_t key{kInvalidKey};
};

struct Range1D {
  int32_t min{INT32_MAX};
  int32_t max{INT32_MIN};
};

struct Range2D {
  Range1D x{};
  Range1D y{};
};

struct Node {
  int32_t point_index{kInvalidPointIndex};
  int32_t left_node_index{kInvalidNodeIndex};
  int32_t right_node_index{kInvalidNodeIndex};
};

enum class Axis : int32_t { kX = 0, kY };

Point2D CreatePoint2D(const int32_t x, const int32_t y, const int32_t key) noexcept;
bool P1xIsLessThanP2x(const Point2D& p1, const Point2D& p2) noexcept;
bool P1yIsLessThanP2y(const Point2D& p1, const Point2D& p2) noexcept;

// ****************************************************
class KdTree {
 public:
  KdTree() noexcept;
  ~KdTree() noexcept;
  void AddPoint(const Point2D& point);
  void BuildKdTree();
  void FindPointsWithinRange(const Range2D& range);

 private:
  int32_t BuildKdTreeRecursively(const int32_t start_point_index, const int32_t end_point_index, const int32_t depth);
  void FindPointsWithinRangeRecursively(const Range2D& range, const int32_t node_index, const int32_t depth);
  static bool PointIsWithinRange(const Point2D& point, const Range2D& range) noexcept;
  bool InvalidPointIndex(const int32_t point_index) const noexcept;
  bool InvalidNodeIndex(const int32_t node_index) const noexcept;
  static Axis GetAxisByDepth(const int32_t depth) noexcept;

  KdTree(const KdTree& obj) = delete;
  KdTree& operator=(const KdTree& obj) = delete;
  KdTree(KdTree&& obj) = delete;
  KdTree& operator=(KdTree&& obj) = delete;

 private:
  int32_t number_of_points_;
  int32_t number_of_nodes_;
  Point2D points_[kMaxNumberOfPoints];
  Node nodes_[kMaxNumberOfNodes];
  std::vector<int32_t> found_points_;

 private:
  FRIEND_TEST(Test_DSL_2_C, AddPoint);  // Should be removed from production code
};

}  // namespace DSL_2_C

#endif  // SRC_C14_2_DSL_2_C_KD_TREE_H_
