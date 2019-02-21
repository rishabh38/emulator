#ifndef EMULATOR_INCLUDE_REGMEM_ACCESS_H
#define EMULATOR_INCLUDE_REGMEM_ACCESS_H

#include "StoreLib/include/store.h"

#include <cinttypes>
#include <string>

bool add_reg_alias (std::string alias, std::string bitS);
bool init_reg (uint16_t total_reg, uint16_t width);
bool init_mem (uint32_t size, uint16_t width);
bool insert_reg_bitS (std::string reg_bitS, uint16_t regIndex);
std::string alias_to_reg_bitS (std::string alias);
std::string get_reg_value (std::string reg);
std::string get_mem_value (std::string mem_bitS);
bool insert_reg_value (std::string reg_bitS, std::string bitS);
bool insert_mem_value (std::string addr_bin, std::string bitS);
void disp_reg_status ();
void disp_mem_status ();
void display_register (std::string);
void display_memory (std::string);

#endif
