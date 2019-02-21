#include "executer/include/executer.h"
#include "executer/include/initializer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void initialize(const string& inst_file, const string& opc_file) {
  initialize_regmem (inst_file);
  initialize_inst_module (inst_file);
  load_opcodes_to_mem (opc_file);
}

int main (int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "usage: main <filename1> <filename2>" << endl;
    return 1;
  }

  initialize(argv[1], argv[2]);
  execute();
}
