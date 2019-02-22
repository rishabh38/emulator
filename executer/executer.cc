#include "executer/include/executer.h"

#include "executer/include/fileio.h"
#include "executer/include/statement_reader.h"
#include "executer/include/regmem_access.h"
#include "executer/include/opcode_matcher.h"

#include <fstream>
#include <iostream>

using namespace std;

bool do_all_match (const string &str, const char ch) {
  bool success = true;
  
  if (!str.size()){
    success = false;
  }

  for (auto a : str) {
    if (a != ch) {
      success = false;
      break;
    }
  }

  return success;
}
  

void execute (const string& outloc) {
  streambuf *outbuf;
  
  if (outloc.size()) {
    ofstream *file = new ofstream;
    file->open(outloc);
    outbuf = file->rdbuf();
  }
  else outbuf = cout.rdbuf();

  ostream out(outbuf);
  const string pc_alias = "PC";
  string pc_data = get_reg_value (pc_alias);
 
  while (!do_all_match (pc_data, '0')) { 
    string opcode = get_mem_value (pc_data);

    if (!opcode.size()) {
      break;
    }

    vector<string> statements = get_statements (opcode);

    if (!statements.size()) {
      break;
    }
  
    for (auto statement : statements) {
      execute_statement (statement, opcode);
    }

    pc_data = get_reg_value (pc_alias);
  }

  disp_reg_status(out);
  disp_mem_status(out);
}
