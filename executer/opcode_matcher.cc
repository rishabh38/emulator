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

nump_string_map get_opcode_type (const string &str_opcode_t) {
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

vector<string> get_statements (const string &str_statements) {
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

inst_state get_instruction_module (const string &str_inst_module) {
  inst_state err_return_value;
  size_t module_length = str_inst_module.size();

  if (!module_length) {
    cerr << "get_instruction_module: str_instruction_module is empty"
         << endl;
    return err_return_value;
  }

  size_t pos = str_inst_module.find ('\n');

  if (pos == string::npos) {
    pos = module_length;
  }

  nump_string_map opcode_type =
              get_opcode_type (str_inst_module.substr (0, pos));
  vector<string> statements;


  if (pos >= module_length) {
    cerr << "get_instruction_module: no statements" << endl;
    return make_pair(opcode_type, statements);
  }

  statements = get_statements (str_inst_module.substr (pos, module_length - 1));
  return make_pair (opcode_type, statements);
}

bool insert_instruction_module (const string &str_inst_module) {
  inst_state inst_module = get_instruction_module (str_inst_module);
  bool success = 1;

  if (inst_module.first.empty() || inst_module.second.empty()) {
    success = 0;
  }

  instruction_list.insert (inst_module);
  return success;
}
