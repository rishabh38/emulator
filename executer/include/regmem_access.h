#ifndef EMULATOR_INCLUDE_REGMEM_ACCESS_H
#define EMULATOR_INCLUDE_REGMEM_ACCESS_H

#include "StoreLib/include/store.h"

#include <cinttypes>
#include <string>

bool init_reg (uint16_t total_reg, uint16_t width);
bool init_mem (uint32_t size, uint16_t width);
bool insert_reg_bitS (std::string reg_bitS, uint16_t regIndex);
std::string get_reg_value (std::string reg_bitS);
std::string get_mem_value (std::string mem_bitS);
bool insert_reg_value (std::string reg_bitS, std::string bitS);
bool insert_mem_value (std::string mem_bitS, std::string bitS);
//void show_memreg(std::string bitS); //test function

#endif
