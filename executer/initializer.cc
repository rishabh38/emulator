#include "executer/include/initializer.h"

#include "utility/include/bitS_utility.h"
#include "executer/include/fileio.h"
#include "executer/include/operator.h"
#include "executer/include/opcode_matcher.h"
#include "executer/include/regmem_access.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using num_pair = pair<uint64_t, uint64_t>;

bool set_regmem_size (pair<num_pair, num_pair> regmem_size) {
  bool success;
  success = init_reg (regmem_size.first.first, regmem_size.first.second);
  success = init_mem (regmem_size.second.first, regmem_size.second.second);
  return success;
}

bool init_reg_aliases (vector<vector<string>> reg_aliases) {
  bool success;

  for (auto reg_alias : reg_aliases) {
    if (reg_alias.size() < 2) {
      success = 0;
      cerr << "init_reg_aliases: missing index/bitsIndex" << endl;
      break;
    }

    success = insert_reg_bitS (reg_alias[1], stoull (reg_alias[0]));

    if (reg_alias.size() >= 3) {
      success = add_reg_alias (reg_alias[2], reg_alias[1]);
    }
  }

  return success;
}

bool set_reg_values (const vector<pair<string, string>> &reg_vals) {
  bool success = 1;

  for (auto reg_val : reg_vals) {
    success &= insert_reg_value (reg_val.first, reg_val.second);
  }

  return success;
}

bool initialize_regmem(const string &filename) {
  bool success;
  auto regmem_size = read_regmem_size (filename);
  success = set_regmem_size (regmem_size);

  auto reg_aliases = read_reg_alias (filename);
  success = init_reg_aliases (reg_aliases); 

  auto reg_val = read_reg_values (filename);
  success = set_reg_values (reg_val);  
  return success;
}

bool initialize_operators(){
  init_opfuncmap ();
}

bool initialize_inst_module (const string& filename) {
  bool success = 0;
  vector<string> inst_modules = read_inst_modules (filename);
  for (auto inst_module : inst_modules) {
    success = insert_instruction_module (inst_module);
  }
  
  return success;
}

bool write_opcodes_to_mem (vector<string> opcode_list) {
  bool success = 1;
  uint64_t index = 1;

  for (auto opcode : opcode_list) {

    string index_bits = unum_to_bitS (index);
    success &= insert_mem_value (index_bits, opcode);
    index++;
  }

  return success;
}

bool load_opcodes_to_mem (const string& filename) {
  bool success = 0;
  auto opcode_list = read_opcodes (filename);
  success = write_opcodes_to_mem (opcode_list);
  return success;
}
