emulator:
---------

emulator is a system which can simulate a given general fixed-length encoded 
ISA,

Here is a working model of the system:
emulator has an internal simulated memory and registers.
it takes configuration of how to evaluate different machine codes,
and based on configuration, takes list of machine codes and evaluates each one 
of them 
by changing the memory and registers.

emulator's input has multiple sections, one of the part is 

instruction-module:
------------------
this part describes how the system will change the memory and 
registers when given a particular machine code
more: https://github.com/rishabh38/emulator/docs/init.txt

init:
----
this sections comprises of multiple modules,
what these modules have in common is that it setups the memory and registers and ways to access them.
more: https://github.com/rishabh38/emulator/docs/init.txt
 
There are three modules in the init section 
1.size
2.register-alias
3.register-value

size module:
size module decides the size and number of registers and memories

register-alias:
register-alias sets the mapping between register name and bitstrings that will be used to call the corresponding register
one can also add what other alias can be used to call that register.

register-value:
register-value modules allows one to set the initial values of registers in the emulator.

NOTE: instruction-module, size, register-alias, and register-value needs to be present in a single file

machine codes:
-------------
this is the list of bitstrings that is evaluated by the emulator based on instruction-module.
it needs to be present in a separate file.
