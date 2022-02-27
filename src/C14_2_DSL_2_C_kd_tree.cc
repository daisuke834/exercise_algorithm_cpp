/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part14-2. 高度なデータ構造、kD Tree (kd木, k-dimensional tree)
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C14_2_DSL_2_C_kd_tree.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace DSL_2_C {

void CallKdTree(std::istream& input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  KdTree* kd_tree = new KdTree();
  try {
    int32_t number_of_points;
    input_stream >> number_of_points;
    for (int32_t i = 0; i < number_of_points; ++i) {
      Point2D point;
      input_stream >> point.x >> point.y;
      point.key = i;
      kd_tree->AddPoint(point);
    }
    kd_tree->BuildKdTree();
    int32_t number_of_queries;
    input_stream >> number_of_queries;
    for (int32_t i = 0; i < number_of_queries; ++i) {
      Range2D range;
      input_stream >> range.x.min >> range.x.max >> range.y.min >> range.y.max;
      kd_tree->FindPointsWithinRange(range);
    }
  } catch (...) {
    std::cerr << "ERROR: CallKdTree()" << std::endl;
    throw;
  }
  delete kd_tree;
}

// ****************************************************

KdTree::KdTree() noexcept : number_of_points_(0), number_of_nodes_(0) {}

KdTree::~KdTree() noexcept {}

void KdTree::AddPoint(const Point2D& point) {
  if (number_of_points_ >= kMaxNumberOfPoints) {
    std::cerr << "ERROR: AddPoint(): Number of points exceeded a limit : " << kMaxNumberOfPoints << std::endl;
    throw 1;
  }
  const int32_t index_store = number_of_points_;
  ++number_of_points_;
  points_[index_store] = point;
}

void KdTree::BuildKdTree() {
  constexpr int32_t kInitialDepth = 0;
  try {
    const int32_t start_point_index = 0;
    const int32_t end_point_index = number_of_points_ - 1;
    BuildKdTreeRecursively(start_point_index, end_point_index, kInitialDepth);
  } catch (...) {
    std::cerr << "ERROR: BuildKdTree()" << std::endl;
    throw;
  }
}

int32_t KdTree::BuildKdTreeRecursively(const int32_t start_point_index, const int32_t end_point_index,
                                       const int32_t depth) {
  int32_t node_index_store;
  const int32_t length = end_point_index - start_point_index + 1;
  if (InvalidPointIndex(start_point_index)) {
    node_index_store = kLeaf;
  } else if (InvalidPointIndex(end_point_index)) {
    node_index_store = kLeaf;
  } else if (length <= 0) {
    node_index_store = kLeaf;
  } else {
    try {
      const Axis axis = GetAxisByDepth(depth);
      if (axis == Axis::kX) {
        std::sort(&points_[start_point_index], &points_[end_point_index] + 1, P1xIsLessThanP2x);
      } else {
        std::sort(&points_[start_point_index], &points_[end_point_index] + 1, P1yIsLessThanP2y);
      }
      const int32_t median_point_index = (start_point_index + end_point_index) / 2;
      node_index_store = number_of_nodes_;
      ++number_of_nodes_;
      const int32_t next_depth = depth + 1;
      nodes_[node_index_store].point_index = median_point_index;
      nodes_[node_index_store].left_node_index =
          BuildKdTreeRecursively(start_point_index, median_point_index - 1, next_depth);
      nodes_[node_index_store].right_node_index =
          BuildKdTreeRecursively(median_point_index + 1, end_point_index, next_depth);
    } catch (...) {
      std::cerr << "ERROR: BuildKdTreeRecursively()" << std::endl;
      throw;
    }
  }
  return node_index_store;
}

void KdTree::FindPointsWithinRange(const Range2D& range) {
  constexpr int32_t kInitialDepth = 0;
  try {
    found_points_.clear();
    constexpr int32_t kRootNodeIndex = 0;
    FindPointsWithinRangeRecursively(range, kRootNodeIndex, kInitialDepth);
    std::sort(found_points_.begin(), found_points_.end());
    for (int32_t point_index : found_points_) {
      printf("%d\n", point_index);
    }
    printf("\n");
  } catch (...) {
    std::cerr << "ERROR: FindPointsWithinRange()" << std::endl;
    throw;
  }
}

void KdTree::FindPointsWithinRangeRecursively(const Range2D& range, const int32_t node_index, const int32_t depth) {
  if (node_index == kLeaf) {
    // DO NOTHING
  } else if (InvalidNodeIndex(node_index)) {
    std::cerr << "ERROR: FindPointsWithinRangeRecursively(): Invalid arg node_index=" << node_index << std::endl;
    throw 1;
  } else {
    try {
      const Node& node = nodes_[node_index];
      const Point2D& point = points_[node.point_index];
      if (PointIsWithinRange(point, range)) {
        found_points_.push_back(point.key);
      }
      const int32_t next_depth = depth + 1;
      const Axis axis = GetAxisByDepth(depth);
      if (axis == Axis::kX) {
        // X axis
        if (point.x >= range.x.min) {
          FindPointsWithinRangeRecursively(range, node.left_node_index, next_depth);
        }
        if (point.x <= range.x.max) {
          FindPointsWithinRangeRecursively(range, node.right_node_index, next_depth);
        }
      } else {
        // Y axis
        if (point.y >= range.y.min) {
          FindPointsWithinRangeRecursively(range, node.left_node_index, next_depth);
        }
        if (point.y <= range.y.max) {
          FindPointsWithinRangeRecursively(range, node.right_node_index, next_depth);
        }
      }
    } catch (...) {
      std::cerr << "ERROR: FindPointsWithinRangeRecursively()" << std::endl;
      throw;
    }
  }
}

bool KdTree::PointIsWithinRange(const Point2D& point, const Range2D& range) noexcept {
  const bool x_is_within_range = (range.x.min <= point.x) && (point.x <= range.x.max);
  const bool y_is_within_range = (range.y.min <= point.y) && (point.y <= range.y.max);
  return (x_is_within_range && y_is_within_range);
}

Axis KdTree::GetAxisByDepth(const int32_t depth) noexcept { return (((depth % 2) == 0) ? Axis::kX : Axis::kY); }

bool KdTree::InvalidPointIndex(const int32_t point_index) const noexcept {
  return ((point_index < 0) || (point_index >= number_of_points_));
}

bool KdTree::InvalidNodeIndex(const int32_t node_index) const noexcept {
  return ((node_index < 0) || (node_index >= number_of_nodes_));
}

// **********************************************************************

Point2D CreatePoint2D(const int32_t x, const int32_t y, const int32_t key) noexcept {
  Point2D point;
  point.x = x;
  point.y = y;
  point.key = key;
  return point;
}

bool P1xIsLessThanP2x(const Point2D& p1, const Point2D& p2) noexcept { return (p1.x < p2.x); }

bool P1yIsLessThanP2y(const Point2D& p1, const Point2D& p2) noexcept { return (p1.y < p2.y); }

// **********************************************************************
}  // namespace DSL_2_C
