#ifndef EXECUTER_INCLUDE_OPCODE_MATCHER
#define EXECUTER_INCLUDE_OPCODE_MATCHER

#include <cinttypes>
#include <map>
#include <string>
#include <vector>

using num_pair = std::pair<uint64_t, uint64_t>;
using nump_string_map = std::map<num_pair, std::string>;
using string_vec = std::vector<std::string>;
using inst_rule = std::pair<nump_string_map, string_vec>;

bool insert_instruction_module (const std::string&);
bool is_bitS (const std::string &the_string);
#endif
