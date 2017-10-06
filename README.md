# corewar

Written with [Jéremy Gagnot](https://github.com/jgagnot) and [Thibaut Fontaine](https://github.com/Thibaut-Fontaine)

Corewar is a pretty confusing project involving a questionable VM and some pieces of bytecode fighting for their life.

It is divided in two parts.

![](https://i.imgur.com/gZEBH4p.png)

# The VM

### Rules

+ The VM allocates some memory in which the processes will fight. This memory is circular.
+ Every cycle, each process is executed. Its PC moves to the next byte and tries to execute an instruction there.
+ Each instruction takes a set time to execute. (forking a process takes 1000 cycles for example).
+ Each process has access to 16 registers.
+ Every set number of cycles, the VM kills every process that hasn't executed the `live` instruction
+ The last process alive is declared winner.

# The pseudo-ASM compiler

The code in the `asm` folder produces a compiler that compiles pseudo assembly code.

There are 16 instructions :
+ `live`          : makes the process live
+ `ld, ldi, lld, lldi`       : load memory bytes into a process' register.
+ `st, sti`       : writes a process' register onto the memory.
+ `add, sub`
+ `and, or, xor`
+ `fork, lfork`   : forks the process
+ `zjmp`          : jumps the PC if the process' internal "carry" is 0
+ `aff`           : display a byte to stdout

### Parameters types :

+ register : one byte, r1 to r16
+ direct : two or four bytes
+ indirect : two bytes

### Syntax :
```
.name "[program name]"
.comment "[program description]"

[label_definition]:
  [instruction] [indirect_arg],%[direct_arg],:[label_name]
 
 #comment
```

### Encoding

One instuction =
+ One byte for the opcode
+ One byte for the parameter types
+ N bytes for the parameters themselves

#### Arguments encoding
```
0x  xx   xx   xx  00
   arg1 arg2 arg3
   
With  01 : register
      10 : direct
      11 : indirect
