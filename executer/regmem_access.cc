#include "executer/include/regmem_access.h"

#include "StoreLib/include/store.h"
#include "StoreLib/include/storeutil.h"

#include <cinttypes>
#include <iostream>
#include <map>
#include <string>

#define MAX_VEC_SIZE 10000

using namespace std;

static store regster;
static store memory;

static map<string, uint16_t> reg_bitS;

bool init_reg (uint16_t total_reg, uint16_t width) {
  regster = initializeStore (total_reg, width);
  return isStoreUsable (regster);
}

bool init_mem (uint32_t size, uint16_t width) {
  memory = initializeStore (size, width);
  return isStoreUsable (memory);
}

bool insert_reg_bitS (string bitS, uint16_t index) {
  bool success_code = 1;
  cout << "sizeofregister: " << totalElements (regster) << endl;
  if (index >= totalElements (regster)) {
    index = index % totalElements (regster);
    success_code = 0;
  }

  reg_bitS[bitS] = index;
  
  return success_code;
}

/*test function:
void show_memreg (string bitS) {
  cout << bitS << " : " << reg_bitS[bitS] << endl;
}
*/
