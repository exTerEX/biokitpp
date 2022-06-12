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

#include "bio/SeqIO/fasta.hpp"
#include "trim.hpp"
#include <regex>

namespace bio::io {

auto read_fasta(std::stringstream& __ss) -> bio::seq::fasta_t {
  bio::seq::fasta_t fasta_object;
  bio::seq::fasta_block_t fasta_block_object;

  bool sequence_reached = true;

  for (std::string line; std::getline(__ss, line);) {
    // Remove trailing whitespace
    line = rtrim(line);

    if ((line[0] == '>' || line[0] == ';') && sequence_reached) {
      // Flush previous block
      if (!fasta_block_object.m_header.empty()) {
        fasta_object.append(fasta_block_object);

        // Erase each element in structure
        fasta_block_object.m_header.erase();
        fasta_block_object.m_comment.erase();
        fasta_block_object.m_sequence.erase();
      }

      // Remove '>' in header line
      line.erase(0, 1);

      // Remove leading whitespaces
      line = ltrim(line);

      // Add fasta_block_object line to fasta_block_object header
      fasta_block_object.m_header = line;
      sequence_reached = false;
    } else if (line[0] == ';' && !sequence_reached) {
      // Remove '>' in header line
      line.erase(0, 1);

      // Remove leading whitespaces
      line = ltrim(line);

      fasta_block_object.m_comment = line;
    } else if (!line.empty()) {
      fasta_block_object.m_sequence += line;
      sequence_reached = true;
    } else {
      continue;
    }
  }

  fasta_object.append(fasta_block_object);

  // Erase each element in structure
  fasta_block_object.m_header.erase();
  fasta_block_object.m_comment.erase();
  fasta_block_object.m_sequence.erase();

  fasta_object.shrink_to_fit();

  return fasta_object;
}

auto read_fasta(std::fstream& __file) -> bio::seq::fasta_t {
  std::stringstream stream;

  // Move data to stringstream
  stream << __file.rdbuf();

  // Read stringstream data into object
  __file.close();

  return read_fasta(stream);
}

auto read_fasta(const std::string __fp) -> bio::seq::fasta_t {
  std::fstream file(__fp, std::ios::in);
  std::stringstream stream;

  // Move data to stringstream
  stream << file.rdbuf();

  // Read stringstream data into object
  file.close();

  return read_fasta(stream);
}

auto encode_fasta(bio::seq::fasta_t& __fas, const char __eol = '\n') -> std::stringstream {
  std::stringstream file_content;

  for (const auto& block : __fas) {
    // Add header
    std::string header = "> " + block.m_header + __eol;
    file_content.write(header.c_str(), header.size());

    // Add comment
    if (block.m_comment != "") {
      std::string comment = "; ";

      for (size_t index = 0; index < block.m_comment.size(); index++) {
        comment += block.m_comment[index];

        // Newline if 80 characters long line
        if (!index % 77) {
          comment += __eol;
          file_content.write(comment.c_str(), comment.size());
          comment = "; ";
        }
      }

      comment += __eol;
      file_content.write(comment.c_str(), comment.size());
    }

    // Add sequence
    std::string sequence;

    for (size_t index = 0; index < block.m_sequence.size(); index++) {
      sequence += block.m_sequence[index];

      // Newline if 80 characters long line
      if (!index % 79) {
        sequence += __eol;
        file_content.write(sequence.c_str(), sequence.size());
      }

      sequence += __eol;
      file_content.write(sequence.c_str(), sequence.size());
    }

    file_content.put(__eol);
  }

  return file_content;
}

auto write_fasta(const std::string __fn, bio::seq::fasta_t __fas, const char __eol = '\n') -> void {
  std::stringstream file_content = encode_fasta(__fas, __eol);

  std::ofstream file(__fn);
  file << file_content.rdbuf();
  file.close();
}

} // namespace bio::io
