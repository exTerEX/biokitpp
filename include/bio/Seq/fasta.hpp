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

#ifndef _SEQ_FASTA_HPP
#define _SEQ_FASTA_HPP

#include <string>
#include <vector>

namespace bio::seq {

using fasta_block_t = struct FastaBlock {
  std::string m_header;
  std::string m_comment;
  std::string m_sequence;
};

using fasta_t = class Fasta {
private:
  uint m_size;
  std::vector<fasta_block_t> m_content;

protected:
public:
  // --- default constructor
  Fasta();

  // --- fill
  Fasta(const fasta_block_t& __x);
  Fasta(const std::vector<fasta_block_t>& __x);
  auto operator=(fasta_block_t& __rhs) -> Fasta&;
  auto operator=(std::vector<fasta_block_t>& __rhs) -> Fasta&;

  // --- copy
  Fasta(const Fasta& __x);
  auto operator=(const Fasta& __rhs) -> Fasta&;

  // --- move
  Fasta(Fasta&& __x) noexcept;
  auto operator=(Fasta&& __rhs) noexcept -> Fasta&;

  // --- destructor
  ~Fasta();

  // --- iterator
  auto begin() noexcept -> std::vector<fasta_block_t>::iterator;
  auto end() noexcept -> std::vector<fasta_block_t>::iterator;

  // --- capacity
  [[nodiscard]] auto size() const noexcept -> uint;
  [[nodiscard]] auto empty() const noexcept -> bool;

  // --- element access
  auto operator[](uint __n) -> fasta_block_t;
  auto at(uint __n) -> fasta_block_t;
  auto data() noexcept -> std::vector<fasta_block_t>;

  // --- modifiers
  auto insert(uint __n, const fasta_block_t& __x) -> void;
  auto insert(uint __n, const Fasta& __x) -> void;

  auto append(const fasta_block_t& __x) -> void;
  auto append(const Fasta& __x) -> void;

  auto operator+=(const Fasta& __rhs) -> Fasta&;

  auto clear() noexcept -> void;

  auto shrink_to_fit() -> void;

  // --- Operations
  auto operator==(Fasta *__rhs) const -> bool;
  auto operator!=(Fasta *__rhs) const -> bool;
};

} // namespace bio::seq

#endif
