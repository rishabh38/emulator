#include "executer/include/bitS_utility.h"

#include <iostream>
#include <cinttypes>
#include <cmath>
#include <string>

using namespace std;

uint64_t bitS_to_unum (string bitS) {
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

string unum_to_bitS (uint64_t num) {
  string bitS;
  
  while (num) {
    char bit = (char)(num % 2) + '0';
    num = num / 2;
    bitS.insert (0, 1, bit);
  }

  return bitS;
} 
