Jonathan Munro

Files:
ArrayList.h
BSTForwardIterator.h
BSTMultimap.h
BSTNode.h
LinkedList.h
LinkedListNode.h
List.h
Process.cc
Process.h
RBTMultimap.h
RBTNode.h
Scheduler.cc
Scheduler.h
schedulesim.cc
Makefile
cputimes.pdf
timing.pdf
readme.txt

This project contains one main program, which will compile with the command 'make schedulesim'. This will update other components of the program as well.

---schedulesim---
To compile: make schedulesim
To run: ./schedulesim <# of CPU-Bound Processes> <# of IO-Bound Processes> <# of cycles>
Description:
The 'schedulesim' program simulates the operating system as it schedules either CPU-Bound or IO-Bound processes. It requires the number of each type of processes to run as well as the number of cycles for which to run. The simulation uses four Schedulers with different underlying structures to schedule the processes to be simulated. It then prints out the scheduler type, the time in nanoseconds per move, the average CPU time and the average wait times of both types of processes. 
