#include "executer/include/executer.h"
#include "executer/include/initializer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void initialize(const string& filename) {
  initialize_regmem (filename);
  initialize_operators();
  initialize_inst_module (filename);
}


int main (int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "usage: main <filename1> <filename2>" << endl;
    return 1;
  }

  initialize(argv[1]);
  execute();
}
