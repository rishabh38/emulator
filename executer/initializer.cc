#include "executer/include/initializer.h"

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

    if (reg_alias.size() >= 2) {
      success = add_reg_alias (reg_alias[2], reg_alias[1]);
    }
  }

  return success;
}

bool initialize_regmem(const string &filename) {
  bool success;
  pair<num_pair,num_pair> regmem_size = read_regmem_size (filename);
  success = set_regmem_size (regmem_size);

  vector<vector<string>> reg_aliases = read_reg_alias (filename);
  success = init_reg_aliases (reg_aliases); 
  return success;
}

bool initialize_operators(){
  init_opfuncmap ();
}

bool initialize_opcode_statement_map (/*UPDATE IT*/){}
