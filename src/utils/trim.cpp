#include "trim.hpp"
#include <algorithm>
#include <iostream>

auto ltrim(std::string& __s) -> std::string& {
  auto iterator = std::find_if(__s.begin(), __s.end(), [](char __c) {
    return !std::isspace<char>(__c, std::locale::classic());
  });

  __s.erase(__s.begin(), iterator);

  return __s;
}

auto rtrim(std::string& __s) -> std::string& {
  auto iterator = std::find_if(__s.rbegin(), __s.rend(), [](char __c) {
    return !std::isspace<char>(__c, std::locale::classic());
  });

  __s.erase(iterator.base(), __s.end());

  return __s;
}
