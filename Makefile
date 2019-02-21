vpath %.h executer/include:utility/include:StoreLib/include
vpath %.c StoreLib
vpath %.cc executer:utility

Cpp_compile = g++
C_compile = gcc
with_headers_at = -I./
and_nameit  = -o
to_compile = -c
to_build = 



objects = executer.o fileio.o initializer.o opcode_matcher.o operator.o \
          regmem_access.o statement_reader.o store.o storeutil.o        \
          bitS_utility.o string_utility.o

allheaders = executer.h fileio.h initializer.h opcode_matcher.h store.h\
						 operator.h regmem_access.h statement_reader.h storeutil.h \
						 bitS_utility.h string_utility.h

emulate : $(objects) main.o
	$(Cpp_compile) $(to_build) $(objects) main.o $(and_nameit) $@

main.o : main.cc $(allheaders)
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

executer.o : executer.cc executer.h regmem_access.h opcode_matcher.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

fileio.o : fileio.cc fileio.h string_utility.h bitS_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

initializer.o : initializer.cc initializer.h bitS_utility.h fileio.h    \
                operator.h opcode_matcher.h regmem_access.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

opcode_matcher.o : opcode_matcher.cc opcode_matcher.h string_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

operator.o : operator.cc operator.h regmem_access.h bitS_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

regmem_access.o : regmem_access.cc regmem_access.h store.h storeutil.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

statement_reader.o : statement_reader.cc statement_reader.h operator.h  \
                     regmem_access.h bitS_utility.h string_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

bitS_utility.o : bitS_utility.cc bitS_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

string_utility.o : string_utility.cc string_utility.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

store.o : store.c store.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

storeutil.o : storeutil.c storeutil.h store.h
	$(Cpp_compile) $(with_headers_at) $(to_compile) $<

.PHONY : clean cleanobj
clean : 
	rm $(objects) main.o emulate 

cleanobj :
	rm $(objects) 
