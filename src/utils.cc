/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Summary
 */

#include "src/utils.h"
#include <iostream>
namespace utils {

std::vector<std::string> SplitStringToVector(const std::string &text, const char delimiter) {
  if (delimiter < 0) {
    std::cerr << "ERROR: SplitStringToVector(): Invalid delimiter. " << delimiter << std::endl;
    throw 1;
  } else if (text.empty()) {
    std::cerr << "ERROR: SplitStringToVector(): Input text is empty. " << std::endl;
    throw 1;
  }
  std::vector<std::string> result;
  std::string current_item;
  for (const char c : text) {
    if (c == delimiter) {
      if (!current_item.empty()) {
        result.push_back(current_item);
      }
      current_item.clear();
    } else {
      current_item += c;
    }
  }
  if (!current_item.empty()) {
    result.push_back(current_item);
  }
  return result;
}

std::vector<float> SplitStringToFloatVector(const std::string &text, const char delimiter) {
  std::vector<float> values;
  try {
    const std::vector<std::string> texts = SplitStringToVector(text, delimiter);
    for (std::string ctext : texts) {
      const float cvalue = std::stof(ctext);
      values.push_back(cvalue);
    }
  } catch (...) {
    std::cerr << "ERROR: SplitStringToFloatVector()" << std::endl;
    throw;
  }
  return values;
}

std::vector<double> SplitStringToDoubleVector(const std::string &text, const char delimiter) {
  std::vector<double> values;
  try {
    const std::vector<std::string> texts = SplitStringToVector(text, delimiter);
    for (std::string ctext : texts) {
      const double cvalue = std::stod(ctext);
      values.push_back(cvalue);
    }
  } catch (...) {
    std::cerr << "ERROR: SplitStringToDoubleVector()" << std::endl;
    throw;
  }
  return values;
}

}  // namespace utils
