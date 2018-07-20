## Install valgrind
In ubuntu `sudo apt -y install valgrind`.

## Basic usage of valgrind
./myprog arg1 arg2  
valgrind --leak-check=yes myprog arg1 arg2  

**NOTE**:
valgrind --leak-check=yes test  
valgrind --leak-check=yes ./test  
  
the first one is running on /usr/bin/test which is built in program.  
you can locate the test program using `whereis test`.  
all we need is 'valgrind --leak-check=yes ./test'  
