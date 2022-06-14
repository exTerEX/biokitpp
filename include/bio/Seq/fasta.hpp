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

  /**
   * @brief Returns an iterator pointing to the first block in the fasta file.
   *
   * @return std::vector<fasta_block_t>::iterator Iterator to beginning
   */
  auto begin() noexcept -> std::vector<fasta_block_t>::iterator;

  /**
   * @brief Returns an iterator pointing to the last block in the fasta file.
   *
   * @return std::vector<fasta_block_t>::iterator Iterator to end
   */
  auto end() noexcept -> std::vector<fasta_block_t>::iterator;

  // --- capacity

  /**
   * @brief Returns the number of elements in the fasta object.
   *
   * @return uint Number of blocks
   */
  [[nodiscard]] auto size() const noexcept -> uint;

  /**
   * @brief Returns whether the vector is empty (i.e. whether its size is 0).
   *
   * @return true Amount of elements is zero
   * @return false Amount of elements is bigger then zero
   */
  [[nodiscard]] auto empty() const noexcept -> bool;

  // --- element access

  auto operator[](uint __n) -> fasta_block_t;

  /**
   * @brief Returns a the element at position n in the vector.
   *
   * @param __n The index for the element to be accessed.
   *
   * @return fasta_block_t The accessed element
   */
  auto at(uint __n) -> fasta_block_t;

  /**
   * @brief Returns a direct pointer to the memory array used internally by the fasta object to
   * store its owned blocks.
   *
   * @return std::vector<fasta_block_t> A pointer to the first block in the array used internally
   * by the fasta object.
   */
  auto data() noexcept -> std::vector<fasta_block_t>;

  // --- modifiers

  /**
   * @brief Insert a fasta block into the fasta object at index.
   *
   * @param __n Index to where to put fasta block
   * @param __x Fasta block to insert at index
   */
  auto insert(uint __n, const fasta_block_t& __x) -> void;

  /**
   * @brief Insert a fasta object into anther fasta object at index.
   *
   * @param __n Index to where to put the fasta object
   * @param __x Fasta object to insert at index
   */
  auto insert(uint __n, const Fasta& __x) -> void;

  /**
   * @brief Insert a fasta block into the fasta object after existing blocks.
   *
   * @param __x Fasta block to append
   */
  auto append(const fasta_block_t& __x) -> void;

  /**
   * @brief Insert a fasta object into the fasta object after existing blocks.
   *
   * @param __x Fasta object to append
   */
  auto append(const Fasta& __x) -> void;

  auto operator+=(const Fasta& __rhs) -> Fasta&;

  /**
   * @brief Erases all elements from the container.
   */
  auto clear() noexcept -> void;

  /**
   * @brief Requests the removal of unused capacity.
   */
  auto shrink_to_fit() -> void;

  // --- Operations
  auto operator==(Fasta *__rhs) const -> bool;
  auto operator!=(Fasta *__rhs) const -> bool;
};

} // namespace bio::seq

#endif
