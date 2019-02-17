#ifndef EXECUTER_INCLUDE_FILEIO_H
#define EXECUTER_INCLUDE_FILEIO_H

#include <cinttypes>
#include <string>
#include <vector>
#include <utility>

using num_pair = std::pair<uint64_t, uint64_t>;
using str_pair = std::pair<std::string, std::string>;

std::pair<num_pair, num_pair> read_regmem_size(const std::string&);
std::vector<std::vector<std::string>> read_reg_alias (const std::string&);
std::vector<str_pair> read_reg_values (const std::string&);
std::vector<std::string> read_inst_modules (const std::string&);
#endif
