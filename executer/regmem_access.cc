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
static map<string, string> alias_reg_bitS_map;

/* add_reg_alias (string alias, string bitS): 
 * takes alias string and bitstring, maps alias
 * string with bitstring in alias_reg_bitS_map.
 * gives WARNING when alias overwritten.
 * always returns true :_>
 */
bool add_reg_alias (string alias, string bitS) {
  if (alias_reg_bitS_map.count (alias)) {
    cerr << "WARNING: overwriting mapped register alias" << endl;
  }

  alias_reg_bitS_map.insert (make_pair (alias, bitS));
  return 1;
}

/* string alias_to_reg_bitS (string alias)
 * takes an alias string and retrieves equivalent bitstring
 * from alias_reg_bitS_map.Returns empty string if 
 * alias not found in the structure
 */
string alias_to_reg_bitS (string alias) {
  string bitS = "";

  if (!alias_reg_bitS_map.count(alias)) {
    cerr << "alias_to_reg_bitS: alias " << alias << " not found"
         << endl; }
  else bitS = alias_reg_bitS_map[alias];

  return bitS;
}



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
    return "";
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
 * returns "",
 * else returns store value at that index.
 */
string get_regmem_value (store regmem, uint64_t index) {
  if (index >= totalElements (regmem)) {
    cerr << "get_regmem_value: register/memory address " << index
         << " doesn't exist" << endl;
    return "";
  }
  
  uint16_t regmem_width = storeWidth (regmem);
  bool *boolA = readMultiBitsfromStore (regmem, index, 0, regmem_width);
  string regmem_value = boolAtobitS (boolA, regmem_width);

  if (regmem_value == ""){
    cerr << "get_regmem_value: register/memory " << index 
         << " is empty" << endl;
  }

  return regmem_value;
}

/* get_reg_value (string reg):
 * takes bitstring/alias mapped to one of the regster
 * index, and returns the value stored in that index,
 * if unable to find the mapped index, then returns
 * "",
 * else returns regster's stored value.
 */
string get_reg_value (string reg) {
  string reg_bitS = "";

  if (alias_reg_bitS_map.count (reg)) {
    reg_bitS = alias_to_reg_bitS (reg);
  }
  else if (reg_bitS_index_map.count (reg)) {
    reg_bitS = reg;
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
 * exist, else returns "".
 */
string get_mem_value (string reg_bitS) {
  uint64_t mem_index = bitS_to_num (reg_bitS);
  string mem_value = get_regmem_value (memory, mem_index);

  return mem_value;
}

/* bitStoboolA (string bitS):
 * converts a bitstring to array of boolean 
 * elements.
 * returns NULL if bitstring is empty,
 * else return boolean array such that ith 
 * index of boolean array represents
 * same value as ith index of bitstring.
 */
bool* bitStoboolA (string bitS) {
  if (!bitS.length()) {
    cerr << "string is empty" << endl;
    return NULL;
  }
 
  size_t bitS_length = bitS.size(); 
  bool *boolA = new bool[bitS_length];

  for (size_t i = 0; i < bitS_length; i++) {
    boolA[i] = bitS[i] - '0';
  }

  return boolA; 
} 

/* insert_regmem_value (store, uint64_t, string):
 * takes a store object, index representing location
 * of store that needs to be written, and the bitString
 * that will be inserted.
 * returns 0 if failed else returns 1.
 */
bool insert_regmem_value (store regmem, uint64_t index, string bitS) {
  int success = 1;

  bool *boolA = bitStoboolA (bitS);

  if (!boolA) {
    cerr << "insert_regmem_value: cannot convert bitstring to bool array" 
         << endl;
    return 0;
  }
   
  success = !writeMultiBitstoStore (regmem, index, 0, boolA, bitS.size());
 
  if (success != 1) {
    cerr << "insert_regmem_value: unable to write to the store object"
         << endl;
    return 0;
  }
  
  return success;
}

/* insert_reg_value (string reg_bitS, string bitS):
 * inserts bitS bitstring in the register represented
 * by reg_bitS.
 * takes register bits representing index of the
 * register and bitstring thats needed to be inserted.
 * returns 0 if unsuccessful, else returns 1.
 */
bool insert_reg_value (string reg_bitS, string bitS) {
  if (!reg_bitS_index_map.count (reg_bitS)) {
    cerr << "insert_reg_value: invalid register_bitString" << endl;
    return 0;
  }

  uint16_t reg_index = reg_bitS_index_map[reg_bitS];

  bool success =  insert_regmem_value (regster, reg_index, bitS);

  if (!success) {
    cerr << "insert_reg_value: unable to insert value to regster" 
         << reg_bitS << endl;
  }

  return success;
}
  
/* insert_mem_value (string mem_bitS, string bitS):
 * inserts bitS bitstring in the memory at 
 * memory address represented by reg_bitS.
 * takes register bits representing index of the
 * register and bitstring thats needed to be inserted.
 * returns 0 if unsuccessful, else returns 1.
 */
bool insert_mem_value (string mem_bitS, string bitS) {
  uint64_t mem_index = bitS_to_num (mem_bitS);
  bool success =  insert_regmem_value (memory, mem_index, bitS);

  if (!success) {
    cerr << "insert_mem_value: unable to insert value to memory" 
         << mem_bitS << endl;
  }

  return success;
}
