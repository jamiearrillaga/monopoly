#include "MonopolyUtility.h"

unsigned long Monopoly::Utility::max(const unsigned long a, const unsigned long b) {
  return a > b ? a : b;
}

unsigned long Monopoly::Utility::get_max_string_length(const std::vector<std::string>& strings) {
  unsigned long max_len = 0;
  for (const auto& string : strings) {
    max_len = max(max_len, string.size());
  }
  return max_len;
}

int Monopoly::Utility::vector_sum(const std::vector<int>& numbers) {
  int sum = 0;
  for (const auto& num : numbers) {
    sum += num;
  }
  return sum;
}

