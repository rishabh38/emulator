#include "executer/include/operator.h"

#include "executer/include/regmem_access.h"
#include "utility/include/bitS_utility.h"

#include <iostream>
#include <map>
#include <string>

using namespace std; 

string uadd (vector<string> operands);
string regstore (vector<string> operands);

static map<string, string (*)(vector<string>)> operator_function_map = 
  {
    {"uadd", uadd},
    {"regstore", regstore},
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

  
