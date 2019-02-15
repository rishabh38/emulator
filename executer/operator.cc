#include "executer/include/operator.h"

#include "executer/include/regmem_access.h"
#include "utility/include/bitS_utility.h"

#include <iostream>
#include <map>
#include <string>

using namespace std; 

static map<string, string (*)(vector<string>)> operator_function_map;

opfunc *match_operator (string operator_name) {
  if (!operator_function_map.count (operator_name)) {
    cerr << "match_operator: operator " << operator_name 
         << " not found" << endl;
    return NULL;
  }

  return operator_function_map [operator_name];
}

string uadd (vector<string> operands) {
  if (operands.empty()) {
    return "err";
  }

  uint64_t result = bitS_to_unum (operands[0]) +
                    bitS_to_unum (operands[1]);

  return unum_to_bitS (result);
}


void init_opfuncmap () {
  operator_function_map.insert (make_pair ("uadd", uadd));
}
