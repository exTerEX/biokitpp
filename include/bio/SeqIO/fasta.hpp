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

#ifndef _IO_FASTA_HPP
#define _IO_FASTA_HPP

#include "bio/Seq/fasta.hpp"
#include <fstream>
#include <sstream>

namespace bio::io {

auto read_fasta(std::stringstream&) -> bio::seq::fasta_t;
auto read_fasta(std::fstream&) -> bio::seq::fasta_t;
auto read_fasta(std::string) -> bio::seq::fasta_t;

auto encode_fasta(bio::seq::fasta_t, char) -> std::stringstream;
auto write_fasta(std::string, bio::seq::fasta_t, char) -> void;

} // namespace bio::io

#endif
