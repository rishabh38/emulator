#include "executer/include/executer.h"
#include "executer/include/initializer.h"

#include <gflags/gflags.h>
#include <iostream>
#include <string>
#include <vector>

DEFINE_string(opcode,"opcode","file to read opcodes from");
DEFINE_string(init,"init","file to read initial states from");

using namespace std;

void initialize(const string& inst_file, const string& opc_file) {
  initialize_regmem (inst_file);
  initialize_inst_module (inst_file);
  load_opcodes_to_mem (opc_file);
}

int main (int argc, char* argv[]) {
  gflags::ParseCommandLineFlags (&argc, &argv, true);

  initialize(FLAGS_init, FLAGS_opcode);
  execute();
}
