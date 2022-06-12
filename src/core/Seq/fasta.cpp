// Copyright 2022 Andreas Sagen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bio/Seq/fasta.hpp"

namespace bio::seq {

Fasta::Fasta() = default;

Fasta::Fasta(const fasta_block_t& __x) {
  this->m_size = 1;
  this->m_content.push_back(__x);
}

Fasta::Fasta(const std::vector<fasta_block_t>& __x) {
  this->m_size = __x.size();
  this->m_content = __x;
}

auto Fasta::operator=(fasta_block_t& __rhs) -> Fasta& {
  this->m_size = 1;

  // Remove content if present
  if (!this->m_content.empty()) {
    this->m_content.clear();
  }

  this->m_content.push_back(__rhs);

  return *this;
}

auto Fasta::operator=(std::vector<fasta_block_t>& __rhs) -> Fasta& {
  this->m_size = __rhs.size();

  this->m_content = __rhs;

  return *this;
}

Fasta::Fasta(const Fasta& __x) = default;

auto Fasta::operator=(const Fasta& __rhs) -> Fasta& = default;

Fasta::Fasta(Fasta&& __x) noexcept = default;

auto Fasta::operator=(Fasta&& __rhs) noexcept -> Fasta& = default;

Fasta::~Fasta() = default;

auto Fasta::begin() noexcept -> std::vector<fasta_block_t>::iterator {
  return this->m_content.begin();
}

auto Fasta::end() noexcept -> std::vector<fasta_block_t>::iterator { return this->m_content.end(); }

auto Fasta::size() const noexcept -> uint { return this->m_size; }

auto Fasta::empty() const noexcept -> bool { return this->m_size == 0; }

auto Fasta::operator[](uint __n) -> fasta_block_t { return this->at(__n); }

auto Fasta::at(uint __n) -> fasta_block_t { return this->m_content[__n]; }

auto Fasta::data() noexcept -> std::vector<fasta_block_t> { return this->m_content; }

auto Fasta::insert(uint __n, const fasta_block_t& __x) -> void {
  this->m_size += 1;
  this->m_content.assign(__n, __x);
}

auto Fasta::insert(uint __n, const Fasta& __x) -> void {
  for (const auto& element : __x.m_content) {
    this->m_content.assign(__n, element);
    __n++;
  }
}

auto Fasta::append(const fasta_block_t& __x) -> void {
  this->m_size += 1;
  this->m_content.push_back(__x);
}

auto Fasta::append(const Fasta& __x) -> void {
  for (const auto& element : __x.m_content) {
    this->m_content.push_back(element);
  }
}

auto Fasta::operator+=(const Fasta& __rhs) -> Fasta& {
  this->append(__rhs);
  return *this;
}

auto Fasta::clear() noexcept -> void { this->m_content.clear(); }

auto Fasta::operator==(Fasta *__rhs) const -> bool {
  if (this->m_content.size() != __rhs->m_content.size()) {
    return false;
  }

  for (size_t index = 0; index < this->m_content.size(); index++) {
    if (this->m_content[index].m_header != __rhs->m_content[index].m_header) {
      return false;
    }

    if (this->m_content[index].m_comment != __rhs->m_content[index].m_comment) {
      return false;
    }

    if (this->m_content[index].m_sequence != __rhs->m_content[index].m_sequence) {
      return false;
    }
  }
  return true;
}

auto Fasta::operator!=(Fasta *__rhs) const -> bool { return !(this == __rhs); }

auto Fasta::shrink_to_fit() -> void { this->m_content.shrink_to_fit(); }

} // namespace bio::seq
