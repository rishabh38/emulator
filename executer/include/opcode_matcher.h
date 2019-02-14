#ifndef EXECUTER_INCLUDE_OPCODE_MATCHER
#define EXECUTER_INCLUDE_OPCODE_MATCHER

#include <cinttypes>
#include <map>
#include <string>
#include <vector>

bool insert_instruction_module (const std::string&);
std::vector<std::string> get_statements (const std::string&);

#endif
