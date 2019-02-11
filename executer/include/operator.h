#ifndef EXECUTER_INCLUDE_OPERATOR_H
#define EXECUTER_INCLUDE_OPERATOR_H

#include <vector>
#include <string>

using opfunc = std::string (std::vector<std::string>);

opfunc *match_operator (std::string operator_name);
void init_opfuncmap ();
#endif
