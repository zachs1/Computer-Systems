In a brief sentence or two,  modify this file with your answers.

1. In each of the programs what was the bug?  

*prog: segfault At the time of segfault, the program tries to dereference the %rax register to obtain a value and move it into %eax. However the value in %rax is 0, representing a null pointer, which cannot be dereferenced and causes the program to crash.*

*prog1: This program seems to be displaying another misuse of a pointer, however not a null pointer error. A variable's value relative to the stack based pointer is dereferenced and passed into %rax. This value is then dereferenced, which is obviously bad because it was assigned a value and not a memory address, leading to a segfault.*

2. What file and lines did the bugs occur? 

*prog: error at prog2.c line 42.*

*prog1: error at seg.c line 15*

3. What would your educated guess be for a fix for each bug? 

*prog: add a null pointer check before dereferencing the pointer in the program to avoid the segfault.*

*prog1: In the list initalization (this occurs in initialize_front), the bug seems to occur due to the user dereferencing a pointer when they simply should instead be be passing the memory address to whatever variable is stored in %rax.*
