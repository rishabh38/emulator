#ifndef EXECUTER_INCLUDE_INITIALIZER
#define EXECUTER_INCLUDE_INITIALIZER

#include <cinttypes>
#include <string>
#include <utility>
#include <vector>

using num_pair = std::pair <uint64_t, uint64_t>;

bool initialize_regmem (const std::string&);
bool initialize_operators();
bool initialize_inst_module ();

bool set_regmem_size (std::pair <num_pair, num_pair>);
bool init_reg_aliases (std::vector<std::vector<std::string>>);
#endif
