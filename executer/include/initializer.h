#ifndef EXECUTER_INCLUDE_INITIALIZER
#define EXECUTER_INCLUDE_INITIALIZER

#include <cinttypes>
#include <string>
#include <utility>
#include <vector>

using num_pair = std::pair <uint64_t, uint64_t>;

bool initialize_regmem (const std::string&);
bool initialize_inst_module (const std::string&);
bool load_opcodes_to_mem (const std::string&);

#endif
