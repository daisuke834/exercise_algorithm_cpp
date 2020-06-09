/**
 * @copyright (c) 2020 Daisuke Hashimoto
 * @brief Summary
 */

#include "src/utils.h"
#include <algorithm>
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

int64_t CalculatePower(const int64_t x, const int64_t n) noexcept {
  // log(n) order
  if (n == 0LL) {
    return 1LL;
  } else if (n == 1LL) {
    return x;
  } else if (x == 1LL) {
    return 1LL;
  }
  constexpr int64_t kPrime = 1000000007LL;
  int64_t result = CalculatePower((x * x) % kPrime, n / 2LL);
  if (n % 2LL == 1LL) {
    result = (result * x) % kPrime;
  }
  return result;
}

bool IsPrime(const int64_t N) {
  // root N order
  if (N <= 0LL || N == 1LL) {
    return false;
  }
  bool result = true;
  for (int64_t i = 2LL; i * i <= N; ++i) {
    if (N % i == 0LL) {
      result = false;
      break;
    }
  }
  return result;
}

std::vector<std::pair<int64_t, int64_t>> FactorizeIntoPrimeFactors(const int64_t N) {
  std::vector<std::pair<int64_t, int64_t>> result;
  if (N <= 0LL || N == 1LL) {
    return result;
  }
  int64_t remaining = N;
  for (int64_t i = 2LL; i * i <= remaining; ++i) {
    int64_t count = 0LL;
    while (remaining % i == 0LL) {
      ++count;
      remaining /= i;
    }
    if (count > 0LL) {
      result.push_back(std::pair<int64_t, int64_t>(i, count));
    }
  }
  if (remaining > 1) {
    result.push_back(std::pair<int64_t, int64_t>(remaining, 1));
  }
  return result;
}

int64_t GreatestCommonDivisor(const int64_t a, const int64_t b) {
  // GCD. O(log(min(a, b))). 最大公約数.
  int64_t result = -1LL;
  if (a < 0) {
    std::cerr << "ERROR: GreatestCommonDivisor(): a is out of range: " << a << std::endl;
    throw 1;
  } else if (b < 0LL) {
    std::cerr << "ERROR: GreatestCommonDivisor(): b is out of range: " << b << std::endl;
    throw 1;
  } else if (a == 0LL) {
    result = b;
  } else if (b == 0LL) {
    result = a;
  } else {
    const int64_t new_a = std::min(a, b);
    const int64_t new_b = std::max(a, b) % new_a;  // Euclidean Algorithm
    result = GreatestCommonDivisor(new_a, new_b);
  }
  return result;
}

int64_t LeastCommonMultiple(const int64_t a, const int64_t b) {
  // LCM. O(log(min(a, b))). 最小公倍数.
  int64_t result;
  if (a == 0 || b == 0) {
    return 0;
  } else if (a == 1) {
    return b;
  } else if (b == 1) {
    return a;
  } else if (a < 0 || b < 0) {
    std::cerr << "ERROR: LeastCommonMultiple(): Invalid arg. a=" << a << ", b=" << b << std::endl;
    throw 1;
  }
  try {
    result = (a / GreatestCommonDivisor(a, b) * b);
  } catch (...) {
    std::cerr << "ERROR: LeastCommonMultiple()" << std::endl;
  }
  return result;
}

int64_t GetNumberOfDigits(const int64_t N) {
  // 桁数の取得
  constexpr int64_t kBase = 10;
  int64_t result;
  if (N == 0) {
    result = 1;
  } else {
    result = 0;
    int64_t temp = N;
    while (temp != 0) {
      ++result;
      temp /= kBase;
    }
  }
  return result;
}

}  // namespace utils
