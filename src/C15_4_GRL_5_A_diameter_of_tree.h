/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part15-4. 木の直径(Diameter of a Tree)。
 */

#ifndef SRC_C15_5_GRL_5_A_MST_PRIM_H_
#define SRC_C15_5_GRL_5_A_MST_PRIM_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace GRL_5_A {

constexpr int32_t kMaxNumberOfNodes = 100000;
constexpr int32_t kInvalidIndex = -1;

void CallTreeDiameter(std::istream &input_stream);

class TreeDiameter {
 public:
  TreeDiameter() noexcept;
  ~TreeDiameter() noexcept;

 private:
};

}  // namespace GRL_5_A

#endif  // SRC_C15_5_GRL_5_A_MST_PRIM_H_
