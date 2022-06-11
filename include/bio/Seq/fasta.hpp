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
  Fasta(fasta_block_t);
  Fasta(std::vector<fasta_block_t>);
  auto operator=(fasta_block_t&) -> Fasta&;
  auto operator=(std::vector<fasta_block_t>&) -> Fasta&;

  // --- copy
  Fasta(const Fasta&);
  auto operator=(const Fasta&) -> Fasta&;

  // --- move
  Fasta(Fasta&&);
  auto operator=(Fasta&&) -> Fasta&;

  // --- destructor
  ~Fasta();

  // --- iterator
  auto begin() noexcept -> std::vector<fasta_block_t>::iterator;
  auto end() noexcept -> std::vector<fasta_block_t>::iterator;

  // --- capacity
  auto size() const noexcept -> uint;
  auto empty() const noexcept -> bool;

  // --- element access
  auto operator[](uint) -> fasta_block_t;
  auto at(uint) -> fasta_block_t;
  auto data() noexcept -> std::vector<fasta_block_t>;

  // --- modifiers
  auto insert(uint, const fasta_block_t&) -> void;
  auto insert(uint, const Fasta&) -> void;

  auto append(const fasta_block_t&) -> void;
  auto append(const Fasta&) -> void;

  auto operator+=(const Fasta&) -> Fasta&;

  auto clear() noexcept -> void;

  auto shrink_to_fit() -> void;

  // --- Operations
  auto operator==(Fasta *) const -> bool;
  auto operator!=(Fasta *) const -> bool;
};

} // namespace bio::seq

#endif
