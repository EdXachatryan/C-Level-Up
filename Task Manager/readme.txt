compile ===   g++ -std=c++11 main.cpp TaskManager.cpp Client.cpp -o mng
run     ===   ./mng

Please follow these instructions
  1. At First pass FIFO name
  2. Second parameter for command

The command can have more than one value `  ls -a , you mast put one space between commands

For seeing the output you can use the "read" command `  fifoName read
E.g. 
  lsFifo ls -a
  lsFifo read

  pwdFifo pwd
  pwdFifo read

For exit use ` "Program exit"



