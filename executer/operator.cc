#include "executer/include/operator.h"

#include "executer/include/regmem_access.h"
#include "utility/include/bitS_utility.h"

#include <iostream>
#include <map>
#include <string>

using namespace std; 

string uadd (vector<string> operands);
string regstore (vector<string> operands);
string regload (vector<string> operands);
string memstore (vector<string> operands);
string memload (vector<string> operands);

static map<string, string (*)(vector<string>)> operator_function_map = 
  {
    {"uadd", uadd},
    {"regstore", regstore},
    {"regload", regload},
    {"memstore", memstore},
    {"memload", memload},
  };

opfunc *match_operator (string operator_name) {
  if (!operator_function_map.count (operator_name)) {
    cerr << "match_operator: operator " << operator_name 
         << " not found" << endl;
    return NULL;
  }

  return operator_function_map [operator_name];
}

string uadd (vector<string> operands) {
  if (operands.size() < 2) {
    return "err";
  }
  uint64_t result = bitS_to_unum (operands[0]) +
                    bitS_to_unum (operands[1]);

  return unum_to_bitS (result);
}

string regstore (vector<string> operands) {
  if (operands.size() < 2) {
    cerr << "regstore err" << endl;
    return "";
  }

  insert_reg_value (operands[0], operands[1]);
  return "";
} 

string regload (vector<string> operands) {
  if (operands.size() < 1) {
    cerr << "regload error" << endl;
    return "";
  }

  return get_reg_value (operands[0]);
}

string memstore (vector<string> operands) {
  if (operands.size() < 2) {
    cerr << "memstore error" << endl; 
    return "";
  }

  insert_mem_valuea (operands[0], operands[1]);
  return "";
}

string memload (vector<string> operands) {
  if (operands.size() < 2) {
    cerr << "memload erro" << endl;
    return "";
  }

  return get_mem_valuea (operands[0], operands[1]);
}
