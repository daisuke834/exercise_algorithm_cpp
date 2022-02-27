/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief AtCoder Beginner Contest(ABC) 167-D. Doubling.
 */

#ifndef SRC_D_ABC_167_D_2_TELEPORTER_DOUBLING_H_
#define SRC_D_ABC_167_D_2_TELEPORTER_DOUBLING_H_

#include <cstdint>
#include <iostream>
#include <string>

namespace ABC_167_D_2 {

constexpr int64_t kMaxNumberOfTowns = 200000L;
constexpr int64_t kMaxLog = 60L;  // > log2(K)

void CallTeleporter(std::istream& input_stream) noexcept;

class Doubling {
 public:
  Doubling() noexcept;
  ~Doubling() noexcept;
  void SetNumberOfTowns(const int64_t number_of_towns) noexcept;
  void SetMapping(const int64_t from, const int64_t to) noexcept;
  void CreateTable() noexcept;
  int64_t SearchFinalTown(const int64_t start_town, const int64_t number_of_teleportations) noexcept;

 private:
  int64_t number_of_towns_;
  int64_t ported_to_[kMaxLog][kMaxNumberOfTowns];
};

}  // namespace ABC_167_D_2

#endif  // SRC_D_ABC_167_D_2_TELEPORTER_DOUBLING_H_
