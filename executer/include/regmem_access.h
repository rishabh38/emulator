#ifndef EMULATOR_INCLUDE_REGMEM_ACCESS_H
#define EMULATOR_INCLUDE_REGMEM_ACCESS_H

#include "StoreLib/include/store.h"

#include <cinttypes>
#include <string>

bool init_reg (uint16_t total_reg);
bool init_mem (uint32_t size);
bool insert_reg_bitS (std::string reg_bitS, uint16_t regIndex);
std::string get_reg_value (std::string reg_bitS);
std::string get_mem_value (std::string mem_bitS);
void show_memreg();

#endif
