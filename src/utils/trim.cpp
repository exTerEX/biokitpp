#include "bio/utils/trim.hpp"
#include <algorithm>
#include <iostream>

std::string& ltrim(std::string& __s) {
  auto it = std::find_if(__s.begin(), __s.end(),
                         [](char c) { return !std::isspace<char>(c, std::locale::classic()); });

  __s.erase(__s.begin(), it);

  return __s;
}

std::string& rtrim(std::string& __s) {
  auto it = std::find_if(__s.rbegin(), __s.rend(),
                         [](char c) { return !std::isspace<char>(c, std::locale::classic()); });

  __s.erase(it.base(), __s.end());

  return __s;
}
