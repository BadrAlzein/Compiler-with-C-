# BS_Gruppe14
### Betriebsysteme SS 2020 

### Members 
* Badr
* Obada 
* Brishna 


### consider the following Links 

1. ### Lehrstuhl webseite: 
   https://www.b-tu.de/fg-betriebssysteme/lehre/fruehere-semester/betriebssysteme-i/materialien
   
2. ### Crashcurs: 
   https://www-docs.b-tu.de/fg-betriebssysteme/btuauth/bs1/sonstig/doc/assembler.html


C Compiling Comands 
---
nasm -f elf -o main.o main-nasm.asm 
gcc -m32 -c -o c.o main.c
gcc -m32 -o run main.o c.o
./run
