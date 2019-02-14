#include "executer/include/opcode_matcher.h"
#include "executer/include/string_utility.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

using num_pair = pair<uint64_t, uint64_t>;
using nump_string_map = map<num_pair, string>;
using string_vec = vector<string>;
using inst_state = pair<nump_string_map, string_vec>;

static map<nump_string_map, string_vec> instruction_list;

nump_string_map parse_opcode_type (const string &str_opcode_t) {
  size_t str_opcode_length = str_opcode_t.size();
  nump_string_map bitS_range_spec;

  for (size_t i = 0; i < str_opcode_length; i++) {
    num_pair range = get_rangei (str_opcode_t, i);

    skip_char (str_opcode_t, ':', i);
    string bitS = get_bitS (str_opcode_t, i);
    bitS_range_spec.insert (make_pair (range, bitS));
  }

  return bitS_range_spec;
}

vector<string> parse_statements (const string &str_statements) {
  vector<string> vec_statement;
  size_t str_statements_length = str_statements.size();

  for (size_t i = 0; i < str_statements_length; i++) {
      string statement = get_procedure (str_statements, i);

      if (!statement.empty()) {
        vec_statement.push_back (statement);
      }
  }

  return vec_statement;
}

inst_state parse_instruction_module (const string &str_inst_module) {
  inst_state err_return_value;
  size_t module_length = str_inst_module.size();

  if (!module_length) {
    cerr << "parse_instruction_module: str_instruction_module is empty"
         << endl;
    return err_return_value;
  }

  size_t pos = str_inst_module.find ('\n');

  if (pos == string::npos) {
    pos = module_length;
  }

  string str_opcode_type = str_inst_module.substr (0, pos);
  trim_str (str_opcode_type);
  nump_string_map opcode_type = parse_opcode_type (str_opcode_type);
  vector<string> statements;

  if (pos >= module_length) {
    cerr << "parse_instruction_module: no statements" << endl;
    return make_pair(opcode_type, statements);
  }

  statements = parse_statements (str_inst_module.substr (pos, module_length - 1));
  return make_pair (opcode_type, statements);
}

bool insert_instruction_module (const string &str_inst_module) {
  inst_state inst_module = parse_instruction_module (str_inst_module);
  bool success = 1;

  if (inst_module.first.empty() || inst_module.second.empty()) {
    success = 0;
  }

  instruction_list.insert (inst_module);
  return success;
}

bool is_substr (const string& str, pair<num_pair, string> range_string) {
  num_pair range = range_string.first;
  string string_to_match = range_string.second;
  size_t str_length = str.size();

  if (range.first >= str_length) {
    return 0;
  }

  if (str.substr (range.first, range.second - range.first) != string_to_match) {
    return 0;
  }

  return 1;
}

string_vec get_statements (const string &opcode) {
  string_vec statements;
  for (auto inst_module : instruction_list) {
    bool match = true;
    
    for (auto range_str : inst_module.first) {
      if (!is_substr (opcode, range_str)) {
        match = false;
        break;
      }
    }
     
    if (match) {
      statements = inst_module.second;
      break;
    } 
  }

  return statements;
}
