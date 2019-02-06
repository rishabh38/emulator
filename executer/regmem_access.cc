#include "executer/include/regmem_access.h"

#include "StoreLib/include/store.h"
#include "StoreLib/include/storeutil.h"

#include <cinttypes>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

#define MAX_VEC_SIZE 10000

using namespace std;

static store regster;
static store memory;

static map<string, uint16_t> reg_bitS_index_map;


/* init_reg (uint16_t total_reg, uint16_t width):
 * takes width and total no. of registers to make
 * and inititalizes them.
 * returns true if successful else returns false.
 */
bool init_reg (uint16_t total_reg, uint16_t width) {
  regster = initializeStore (total_reg, width);
  return isStoreUsable (regster);
}

/* init_mem (uint32_t size, uint16_t width):
 * takes width and size of memory to make
 * and inititalizes it.
 * returns true if successful else returns false.
 */
bool init_mem (uint32_t size, uint16_t width) {
  memory = initializeStore (size, width);
  return isStoreUsable (memory);
}

/* insert_reg_bitS (string bitS, uint16_t index):
 * takes a bitstring and intended index, and insert
 * bitstring and index in a map.
 * if index > total no. of defined registers,
 * then makes index = index % total registers,
 * and returns false, else returns true
 */
bool insert_reg_bitS (string bitS, uint16_t index) {
  bool success_code = 1;
  cout << "sizeofregister: " << totalElements (regster) << endl;
  if (index >= totalElements (regster)) {
    index = index % totalElements (regster);
    success_code = 0;
  }

  reg_bitS_index_map[bitS] = index;
  
  return success_code;
}

/* boolAtobitS (bool *boolA, size_t length):
 * converts array of bool to bitstring.
 * takes boolean array and length of the array,
 * and returns equivalent bitstring.
 * if length is 0, then returns space string
 */
string boolAtobitS (bool *boolA, size_t length) {
  if (!length) {
    cerr << "length of bool array is 0" << endl;
    return " ";
  }

  string bitS;
  for ( size_t i = 0; i < length; i++) {
    bitS.push_back (boolA[i] + '0');
  }

  return bitS;
}

/* get_regmem_value (store regmem, uint64_t index):
 * takes a store type object (intended for either
 * regster or memory), and unsigned type index,
 * returns the value stored in that index of
 * the store object.
 * if index >= total elements of the store, then
 * returns " ",
 * else returns store value at that index.
 */
string get_regmem_value (store regmem, uint64_t index) {
  if (index >= totalElements (regmem)) {
    cerr << "get_regmem_value: register/memory address " << index
         << " doesn't exist" << endl;
    return " ";
  }
  
  uint16_t regmem_width = storeWidth (regmem);
  bool *boolA = readMultiBitsfromStore (regmem, index, 0, regmem_width);
  string regmem_value = boolAtobitS (boolA, regmem_width);

  if (regmem_value == " "){
    cerr << "get_regmem_value: register/memory " << index 
         << " is empty" << endl;
  }

  return regmem_value;
}

/* get_reg_value (string reg_bitS):
 * takes bitstring mapped to one of the regster
 * index, and returns the value stored in that index,
 * if unable to find the mapped index, then returns
 * " ",
 * else returns regster's stored value.
 */
string get_reg_value (string reg_bitS) {
  if (!reg_bitS_index_map.count (reg_bitS)) {
    cerr << "get_reg_value: invalid register_bitString" << endl;
    return " ";
  }

  uint16_t reg_index = reg_bitS_index_map[reg_bitS];
  string reg_value = get_regmem_value (regster, reg_index);

  return reg_value;
}

/* bitS_to_num (string bitS):
 * takes a bitstring, and returns
 * equivalent unsigned decimal number.
 * treats elements at lowest index as
 * MSB and elements at higher index
 * as LSB.
 * returns 0 if bitstring is empty.
 */
uint64_t bitS_to_num (string bitS) {
  if (bitS.empty()) {
    cerr << "bitS_to_num: bitstring is empty" << endl;
    return 0;
  }

  uint64_t number = 0;
  size_t string_length = bitS.length();

  for (size_t i = 0; i < string_length; i++ ) {
    number += pow (2,string_length - 1 - i) * (bitS[i] - '0');
  }

  return number;
}

/* get_mem_value (string reg_bitS):
 * takes bitstring representing memory
 * address and returns value stored in
 * that address of memory if the address
 * exist, else returns " ".
 */
string get_mem_value (string reg_bitS) {
  uint64_t mem_index = bitS_to_num (reg_bitS);
  string mem_value = get_regmem_value (memory, mem_index);

  return mem_value;
}


/*test function:
void show_memreg (string bitS) {
  cout << bitS << " : " << reg_bitS[bitS] << endl;
}
*/
