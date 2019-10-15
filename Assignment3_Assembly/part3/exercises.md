## Static Analysis 
 
Our Cycle Count Tool is what we call a 'static analysis'. That is, it uncovers information about our programs before it is running (during compile-time). Given that our tool uncovers information before the program, what is (at least) one pro of this, and one con you can think of?

Pro:
1. *Testing statically is far less complex than testing dynamically and is thus a quick method for getting a rough estimate of the     resource cost of a progam*

Con:
1. *Static anlalysis may not reveal things such as memory/other resource consumption because we dont know the status of certain conditions and instructions that may affect resource usage. For example, in a program that requires input, this input could affect a certain condition that either stops the program or causes the program to do advanced encryption. Statically we can not determine which will occur.*

## Dyanmic Analysis

The opposite of a static analysis is a dynamic analysis. Dynamic analysis tools record and return information about programs that are in the process or have finished executing. An example of a dynamic analysis tool is [valgrind](http://valgrind.org/). What do you think a pro and con of dynamic analysis would be?

Pro:
1. *Dynamic analysis can give more accurate information about the resource consumption of a program by analyzing how the program actually operates under specific use cases.*

Con:
1. *Dynamic analysis also costs resources as long as the program runs, where as static analysis takes a fixed amount of time and resources, only effected by the size of the input program.*
