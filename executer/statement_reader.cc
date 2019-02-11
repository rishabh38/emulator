#include "executer/include/statement_reader.h"

#include "executer/include/operator.h"
#include "executer/include/regmem_access.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string separate_subprocedure (const string statement, size_t& index) {
  size_t statement_length = statement.size(); 
  
  if (!statement.size()) {
    cerr << "separate_subprocedure: empty statement" << endl;
    return "";
  }

  if (statement[index] != '(') {
    cerr << "separate_subprocedure: indicated position in "
         << "statement doesn't represent subprocedure" 
         << endl;
    return "";
  }

  size_t index_beg = index;
  int level = 0;
  
  for (; index < statement_length; index++) {
    if (statement[index] == '(') {
      level++;
    }
    else if (statement[index] == ')') {
      level--;
    }
    
    if (level <= 0) {
      break;
    }
  }

  string subprocedure = statement.substr (index_beg, 
                                          index - index_beg + 1);
  return subprocedure;
}

vector<string> separate_operands (string statement) {
  vector<string> operands;
 
  if (!statement.size()) {
    cerr << "separate_operands: empty statement" << endl;
    return operands;
  }
  
  if (statement[0] != '(' || statement[statement.size() - 1] != ')') {
    cerr << "separate_operands: invalid statement format" << endl;
    return operands;
  }

  statement.pop_back();
  statement.erase (statement.begin());
  size_t statement_length = statement.size();
  string temp;
  
  for (size_t i = 0; i < statement_length; i++) {
    if (!temp.size() && statement[i] == '(') {
      operands.push_back (separate_subprocedure (statement, i));
    } 
 
    else if (statement[i] != ' ') {
      temp.push_back (statement[i]);
    }
    else if (isspace (statement[i]) && temp.size()){
      operands.push_back (temp);
      temp.clear();
    }
  
  }

  if (temp.size()) {
    operands.push_back (temp);
  }
  return operands;
}

pair<string, vector<string>> get_statement_operands (string statement) {
  vector<string> operands;
  
  if (!statement.size()) {
    cerr << "get_statement_operands: empty statement" << endl;
    return make_pair ("", operands);
  }

  vector<string> all_operands = separate_operands (statement);
  
  if (!all_operands.size()) {
    cerr << "get_statement_operands: no operands found" << endl;
    return make_pair ("", operands);
  } 

  string operator_str = all_operands[0];
  operands.assign (all_operands.begin() + 1, all_operands.end());

  return make_pair (operator_str, operands);
}

bool skip_char (string str, char skipchar, size_t &index) {
  size_t str_length = str.size();
  bool success = 1; 
  
  if (!str_length) {
    return 0;
  }
 
  for (; index < str_length; index++) {
    if (!isspace (str[index])) {
      if (str[index] == skipchar) {
        index++;
        break;
      }

      success = 0;
      break;
    }
  }

  return success;
}

pair<unsigned, unsigned> get_range (string rnge_string) {
  pair<unsigned, unsigned> error_return_value = make_pair (0,0);
  size_t rnge_string_length = rnge_string.size();
 
  //tests
  if (!rnge_string.size()) {
    cerr << "get_range: empty range_string" << endl;
    return error_return_value;
  }
  //end tests
  
  bool success = 1;
  size_t i = 0; 
  success = skip_char (rnge_string, '[', i);
  
  if (!success) {
    cerr << "get_range: invalid range string" << endl;
    return error_return_value;
  }
  
  size_t processed_chars;
  unsigned num1 = stoul (rnge_string.substr (i), &processed_chars);
  i += processed_chars;
  success = skip_char (rnge_string, '-', i);
  
  if (!success) {
    cerr << "get_range: invalid range string" << endl;
    return error_return_value;
  }

  unsigned num2 = stoul (rnge_string.substr (i), &processed_chars);
  i += processed_chars;
  success = skip_char (rnge_string, ']', i);
  
  if (!success) {
    cerr << "get_range: invalid range string" << endl;
    return error_return_value;
  }
  
  return make_pair (num1, num2);
}

bool is_bitS (string the_string) {
  bool success = 1;
  size_t str_length = the_string.length();
  
  if (!str_length) {
    success = 0;
  }
  
  for (size_t i = 0; i < str_length; i++) {
    if (the_string[i] != '0' || the_string[i] == '1') {
      success = 0;
      break;
    }
  }

  return success;
}

string get_bitS_equivalent (string operand, string opcode) {
  if (!operand.size()) {
    cerr << "get_bitS_equivalent: empty operand" << endl;
    return "";
  }
  if (!opcode.size()) {
    cerr << "get_bitS_equivalent: empty  opcode" << endl;
  }

  string bitS;

  if (is_bitS (operand)) {
    bitS = operand;
  }
  else if (operand[0] == '(') {
    bitS = execute_statement (operand, opcode);
  }
  else if (operand[0] == '[') {
    auto range = get_range (operand);
    if (range.first > opcode.size()) {
      cerr << "get_bitS_equivalent: invalid requested range" 
           << endl;
      return ""; 
    }
    
    bitS = opcode.substr (range.first, range.second - range.first + 1);
  }
  else {
    bitS = alias_to_reg_bitS (operand);
  }
  
  return bitS;
}

vector<string> get_bitS_equivalent (vector<string> operand_list,
                                    string opcode) {
  for (size_t i = 0; i < operand_list.size(); i++) { 
    operand_list[i] = get_bitS_equivalent (operand_list[i], opcode);
  }

  return operand_list;
} 

string execute_statement (string statement, string opcode) {
  if (!statement.size()) {
    cerr << "execute_statement: statement empty" << endl;
    return "err";
  }
  if (!opcode.size()) {
    cerr << "execute_statement: opcode empty" << endl;
    return "err";
  }

  pair<string, vector<string>> statement_operands;
  statement_operands = get_statement_operands (statement);
  statement_operands.second = get_bitS_equivalent (statement_operands.second, opcode);
  auto operator_function = match_operator (statement_operands.first);
  
  if (!operator_function) {
    cerr << "execute_statement: unable to perform operation "
         << statement_operands.first << endl;
    return "";
  }  

  return operator_function (statement_operands.second);
}
