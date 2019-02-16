#ifndef EXECUTER_INCLUDE_FILEIO_H
#define EXECUTER_INCLUDE_FILEIO_H

#include <cinttypes>
#include <string>
#include <vector>
#include <utility>

using num_pair = std::pair<uint64_t, uint64_t>;

std::pair<num_pair, num_pair> read_regmem_size(const std::string&);
std::vector<std::vector<std::string>> read_reg_alias (const std::string&);

#endif
