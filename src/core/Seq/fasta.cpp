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

Fasta::Fasta(fasta_block_t __x) {
  this->m_size = 1;
  this->m_content.push_back(__x);
}

Fasta::Fasta(std::vector<fasta_block_t> __x) {
  this->m_size = __x.size();
  this->m_content = __x;
}

Fasta& Fasta::operator=(fasta_block_t& __rhs) {
  this->m_size = 1;

  // Remove content if present
  if (!this->m_content.empty()) {
    this->m_content.clear();
  }

  this->m_content.push_back(__rhs);

  return *this;
}

Fasta& Fasta::operator=(std::vector<fasta_block_t>& __rhs) {
  this->m_size = __rhs.size();

  this->m_content = __rhs;

  return *this;
}

Fasta::Fasta(const Fasta&) = default;

// TODO: Define
Fasta& Fasta::operator=(const Fasta& __rhs) { return *this; };

Fasta::Fasta(Fasta&&) = default;

// TODO: Define
Fasta& Fasta::operator=(Fasta&&) { return *this; }

Fasta::~Fasta() = default;

// TODO: Define
std::vector<fasta_block_t>::iterator Fasta::begin() noexcept {
  return std::vector<fasta_block_t>::iterator();
}

// TODO: Define
std::vector<fasta_block_t>::iterator Fasta::end() noexcept {
  return std::vector<fasta_block_t>::iterator();
}

uint Fasta::size() const noexcept { return this->m_size; }

bool Fasta::empty() const noexcept {
  if (this->m_size == 0) {
    return true;
  }

  return false;
}

fasta_block_t Fasta::operator[](uint __n) { return this->at(__n); }

fasta_block_t Fasta::at(uint __n) { return this->m_content[__n]; }

std::vector<fasta_block_t> Fasta::data() noexcept { return this->m_content; }

void Fasta::insert(uint __n, const fasta_block_t& __x) {
  this->m_size += 1;
  this->m_content.assign(__n, __x);
}

void Fasta::insert(uint __n, const Fasta& __x) {
  for (const auto& element : __x.m_content) {
    this->m_content.assign(__n, element);
    __n++;
  }
}

void Fasta::append(const fasta_block_t& __x) {
  this->m_size += 1;
  this->m_content.push_back(__x);
}

void Fasta::append(const Fasta& __x) {
  for (const auto& element : __x.m_content) {
    this->m_content.push_back(element);
  }
}

Fasta& Fasta::operator+=(const Fasta& __rhs) {
  this->append(__rhs);
  return *this;
}

void Fasta::clear() noexcept { this->m_content.clear(); }

bool Fasta::operator==(Fasta *__rhs) const {
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

bool Fasta::operator!=(Fasta *__rhs) const { return !(this == __rhs); }

void Fasta::shrink_to_fit() { this->m_content.shrink_to_fit(); }

} // namespace bio::seq
