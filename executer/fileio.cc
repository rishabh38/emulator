#include "executer/include/fileio.h"

#include "utility/include/string_utility.h"

#include <unistd.h>
#include <fstream>
#include <cinttypes>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

using num_pair = pair<uint64_t, uint64_t>;

bool isfileok(const string& filename) {
  return !access (filename.c_str(), F_OK); 
}

uint64_t find_tag (const string& filename, const string& tag) {
  if (!isfileok(filename)) {
    cerr << "find_tag: unable to access file" << endl; 
    return 0;
  }

  ifstream file (filename);
  string search_string = "[" + tag + "]";
  uint64_t match_pos = 0;
  string buffer;
  
  while (file >> buffer) {
    if (buffer == search_string) {
      match_pos = file.tellg();
      break;
    }
  }

  return match_pos;
}

pair<num_pair, num_pair> read_regmem_size (const string &filename) {
  pair<num_pair, num_pair> err_return;
  pair<num_pair, num_pair> size_vals;

  if (!isfileok (filename)) {
    cerr << "read_regmem_size: uable to access file " << filename << endl;
    return err_return;
  }

  uint64_t size_pos = 0;

  if (!(size_pos = find_tag (filename, "size"))) {
    cerr << "read_regmem_size: unable to locate \"size\" tag" << endl;
    return err_return;
  }

  string buffer;
  ifstream file (filename);
  file.seekg (size_pos);
  uint64_t reg_count, reg_width;
  uint64_t mem_count, mem_width;
  reg_count = reg_width = mem_count = mem_width = 0;
 
   while (getline (file, buffer, ';')) {
    stringstream stream_buffer (buffer);
    string word;
    stream_buffer >> word;

    if (word == "--") {
      break;
    }

    if (word == "count") {
      stream_buffer >> word;
      
      if (word == "register") {
        stream_buffer >> word >> word;
        reg_count = stoull (word);
      }
      else if (word == "memory") {
        stream_buffer >> word >> word;
        mem_count = stoull (word);
      }
      else cerr << "read_regmem_size: invalid input1" << endl;
    }
    else if (word == "width") {
      stream_buffer >> word;

      if (word == "register") {
        stream_buffer >> word >> word;
        reg_width = stoull (word);
      }
      else if (word == "memory") {
        stream_buffer >> word >> word;
        mem_width = stoull (word);
      }
      else cerr << "read_regmem_size: invalid input2" << endl;
    }
    else cerr << "read_regmem_size: invalid input3: " << word << endl;
  }

  return make_pair (make_pair(reg_count, reg_width), make_pair (mem_count, mem_width));
}

vector<vector<string>> read_reg_alias (const string &filename){
  vector<vector<string>> err_return_value;
 
  if (!isfileok (filename)) {
    cerr << "read_reg_alias: unable to access file " << filename << endl;
    return err_return_value;
  }

  uint64_t pos = 0;

  if (!(pos = find_tag (filename, "register-alias"))) {
    cerr << "read_reg_alias: unable to find tag \"register-alias\"" << endl;
    return err_return_value;
  }

  ifstream file (filename);
  file.seekg (pos);
  vector<vector<string>> alias_list;
  string str_buffer;

  while (getline (file, str_buffer, ';')) {
    string aliases, word;
    stringstream stream_buffer (str_buffer);
    vector<string> line;
    stream_buffer >> word;
    unsigned count = 0;

    if (word == "--") {
      break;
    }

    if (word.size() > 1 && word[0] == 'r') {
      line.push_back (word.substr (1));
      count++;
    }
    else {
      cerr << "read_reg_alias: invalid input " << word << endl;
      continue;
    }

    stream_buffer >> word;

    if (!word.find ("bits")) {
      size_t bits_beg = word.find_first_of ("01");
      size_t bits_end = word.find_last_of ("01");

      if (bits_beg == 0) {
        cerr << "read_reg_alias: invalid input " << word << endl;
        continue;
      }

      line.push_back (word.substr (bits_beg, bits_end - bits_beg + 1));
      count++;
    }
    else {
      cerr << "read_reg_alias: invalid input " << word << endl;
      continue;
    }

    if (!stream_buffer.eof()) {
      stream_buffer >> word;
      line.push_back (word);
    }

    alias_list.push_back (line);
  }

  return alias_list;
}

vector<string> read_inst_modules (const string& filename) {
  vector<string> err_return_value;
  if (!isfileok (filename)) {
    cerr << "read_inst_modules: unable to access file " << filename << endl;
    return err_return_value;
  }

  uint64_t pos = 0;

  if (!(pos = find_tag (filename, "instruction-module"))) {
    cerr << "read_reg_alias: unable to find tag \"register-alias\"" << endl;
    return err_return_value;
  }

  ifstream file (filename);
  file.seekg (pos);
  string str_buffer;
  vector<string> inst_modules; 
  
  while (getline (file, str_buffer, ';')) {
    stringstream stream_buffer (str_buffer);
    string word;
    stream_buffer >> word;

    if (word == "--") {
      break;
    }

    if (str_buffer.size()) {
      trim_str (str_buffer);      
      inst_modules.push_back (str_buffer);
    }
  }

  return inst_modules;
}
