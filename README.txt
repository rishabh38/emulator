emulator
Emulator, a system to emulate multiple ISAs.
Emulator can take configuration about how to emulate a given ISA, and then can act like that ISA's simulator.
It takes 'init' file to configure how emulator should behave, an 'opcode' file to act as input to the ISA simulator.


Depends on:
//install these before using
gflags: https://github.com/gflags/gflags

to install:
$ git clone https://github.com/rishabh38/emulator
$ cd emulator
$ make
$ #generate configuration file init and opcode file opcode
$ ./emulate or $ ./emulate --init=init_file --opcode=opcode_file

look at docs for detailed information
