#ifndef EXECUTER_INCLUDE_STRING_UTILITY_H
#define EXECUTER_INCLUDE_STRING_UTILITY_H

#include <string>
#include <utility>

bool skip_char (const std::string&, char, size_t&);
std::pair<uint64_t, uint64_t> get_range (const std::string&);
std::pair<uint64_t, uint64_t> get_rangei (const std::string&, size_t&);
std::string get_bitS (const std::string&, size_t&);
std::string get_procedure (const std::string&, size_t&);
void trim_str (std::string&);
#endif
