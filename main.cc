#include "executer/include/executer.h"
#include "executer/include/initializer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void initialize(const string& filename) {
  bool initialize_regmem (const std::string&);
  bool initialize_operators();
  bool initialize_inst_module (const std::string&);
}


int main (int argc, char* argv[]) {
  if (argc < 3) {
    cerr << "usage: main <filename1> <filename2>" << endl;
    return 0;
  }

  initialize(argv[1]);
  execute();
}
