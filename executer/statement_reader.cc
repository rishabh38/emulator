#include "executer/include/statement_reader.h"

#include "executer/include/bitS_utility.h"
#include "executer/include/operator.h"
#include "executer/include/regmem_access.h"
#include "executer/include/string_utility.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
      operands.push_back (get_procedure (statement, i));
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
