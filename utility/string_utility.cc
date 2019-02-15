#include "executer/include/string_utility.h"

#include <iostream>
#include <string>

using namespace std;

string get_bitS (const string &str, size_t &index) {
  size_t init_index = index;
  size_t str_length = str.size();
  string bitS;

  while (index < str_length) {
    if ((unsigned)(str[index] ^ '0') > 1) {
      break;
    }

    bitS.push_back (str[index]);
    index++;
  }

  return bitS;
}

bool skip_char (const string &str, char skipchar, size_t &index) {
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

pair<uint64_t, uint64_t> get_rangei (const string &range_string, size_t &i) {
  pair<uint64_t, uint64_t> error_return_value = make_pair (0,0);
  size_t range_string_length = range_string.size();

  if (!range_string_length) {
    cerr << "get_rangei: empty range_string" << endl;
    return error_return_value;
  }

  bool success = 1;
  success = skip_char (range_string, '[', i);

  if (!success) {
    cerr << "get_rangei: invalid range string" << endl;
    return error_return_value;
  }

  size_t processed_chars;
  unsigned num1 = stoul (range_string.substr (i), &processed_chars);
  i += processed_chars;
  success = skip_char (range_string, '-', i);

  if (!success) {
    cerr << "get_rangei: invalid range string" << endl;
    return error_return_value;
  }

  unsigned num2 = stoul (range_string.substr (i), &processed_chars);
  i += processed_chars;
  success = skip_char (range_string, ']', i);

  if (!success) {
    cerr << "get_rangei: invalid range string" << endl;
    return error_return_value;
  }

  return make_pair (num1, num2);
}

pair<uint64_t, uint64_t> get_range (const string &str) {
  size_t index = 0;
  return get_rangei (str, index);
}


string get_procedure (const string &statement, size_t& index) {
  size_t statement_length = statement.size();

  if (!statement_length) {
    cerr << "separate_subprocedure: empty statement" << endl;
    return "";
  }

  while (index < statement_length && isspace (statement[index])) {
    index++;
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

void  trim_str (string &str) {
  size_t beg = str.find_first_not_of (" \n\t\r");
  size_t end = str.find_last_not_of (" \n\t\r") + 1;

  if (beg == string::npos) {
    beg = 0;
    end = 0;
  }

  str = str.substr (beg, end);
}
