/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Part7-6. 高等的整列、反転数(The Number of Inversions)。
 * 「アルゴリズムとデータ構造」(渡部有隆(著))のアルゴリズムのスクラッチ実装。
 */

#include "src/C07_6_ALDS1_5_D_number_of_inversions.h"
#include <iostream>
#include <string>

namespace ALDS1_5_D {

void CallNumberOfInversions(std::istream &input_stream) {
  input_stream.tie(0);
  std::ios::sync_with_stdio(false);
  NumberOfInversions *number_of_inversions = new NumberOfInversions();
  try {
    int32_t count;
    input_stream >> count;
    for (int32_t index = 0; index < count; ++index) {
      int32_t cvalue;
      input_stream >> cvalue;
      number_of_inversions->AddData(cvalue);
    }
    number_of_inversions->CalculateNumberOfInversions();
    number_of_inversions->Print();
  } catch (...) {
    std::cerr << "ERROR: CallNumberOfInversions()" << std::endl;
    throw;
  }
  delete number_of_inversions;
}

// ****************************************************

NumberOfInversions::NumberOfInversions() noexcept : size_(0), values_{}, number_of_inversions_{0} {}
NumberOfInversions::~NumberOfInversions() noexcept {}

void NumberOfInversions::AddData(const int32_t value) {
  if (size_ >= kMaxArraySize) {
    std::cerr << "ERROR: AddData(): Data size exceeded a limit = " << kMaxArraySize << std::endl;
    throw 1;
  }
  values_[size_] = value;
  size_++;
}

int64_t NumberOfInversions::GetNumberOfInversions() const noexcept {
  return number_of_inversions_;
}

void NumberOfInversions::CalculateNumberOfInversions() noexcept {
  try {
    ComputeMergeSort(0, size_);
  } catch (...) {
    std::cerr << "ERROR: CalculateNumberOfInversions()" << std::endl;
    throw;
  }
}

void NumberOfInversions::Print() const noexcept {
  std::cout << GetNumberOfInversions() << std::endl;
}

void NumberOfInversions::ResetData() noexcept {
  size_ = 0;
  number_of_inversions_ = 0;
}

void NumberOfInversions::ComputeMergeSort(const int32_t left_end, const int32_t right_end) {
  if ((right_end < left_end) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: ComputeMergeSort: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  try {
    if (left_end + 1 < right_end) {
      const int32_t center = GetCenterIndex(left_end, right_end);
      ComputeMergeSort(left_end, center);
      ComputeMergeSort(center, right_end);
      MergeLeftAndRight(left_end, center, right_end);
    } else {
      // DO NOTHING
    }
  } catch (...) {
    std::cerr << "ERROR: ComputeMergeSort()" << std::endl;
    throw;
  }
}

void NumberOfInversions::MergeLeftAndRight(const int32_t left_end, const int32_t center, const int32_t right_end) {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if (((left_end < 0) || (right_end > size_) || (center <= left_end) || (right_end <= center))) {
    std::cerr << "ERROR: MergeLeftAndRight: invalid args. left_end=" << left_end << ", center=" << center
              << ", right_end=" << right_end << std::endl;
    throw 1;
  }
  const int32_t left_size = center - left_end;
  const int32_t right_size = right_end - center;
  if (left_size > kMaxArraySize / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid left_size. left_size=" << left_size << std::endl;
    throw 1;
  } else if (right_size > kMaxArraySize / 2) {
    std::cerr << "ERROR: MergeLeftAndRight: Invalid right_size. right_size=" << right_size << std::endl;
    throw 1;
  }
  try {
    for (int32_t index_left = 0; index_left < left_size; ++index_left) {
      left_values_[index_left] = values_[left_end + index_left];
    }
    left_values_[left_size] = INT32_MAX;
    for (int32_t index_right = 0; index_right < right_size; ++index_right) {
      right_values_[index_right] = values_[center + index_right];
    }
    right_values_[right_size] = INT32_MAX;

    int32_t index_left = 0;
    int32_t index_right = 0;
    for (int32_t index_target = left_end; index_target < right_end; ++index_target) {
      if (left_values_[index_left] <= right_values_[index_right]) {
        values_[index_target] = left_values_[index_left];
        ++index_left;
      } else {
        values_[index_target] = right_values_[index_right];
        ++index_right;
        if (right_values_[index_left] != INT32_MAX) {
          number_of_inversions_ += (left_size - index_left);
        }
      }
    }
  } catch (...) {
    std::cerr << "ERROR: MergeLeftAndRight()" << std::endl;
    throw;
  }
}

int32_t NumberOfInversions::GetCenterIndex(const int32_t left_end, const int32_t right_end) const {
  // endは右端indexの右一つ隣のindex (無効領域の先頭)left_end(有効) < center(有効) < right_end(無効)
  if ((right_end <= left_end + 1) || ((left_end < 0) || (right_end > size_))) {
    std::cerr << "ERROR: GetCenterIndex: invalid args. left_end=" << left_end << ", right_end=" << right_end
              << std::endl;
    throw 1;
  }
  return (left_end + right_end) / 2;
}

}  // namespace ALDS1_5_D
