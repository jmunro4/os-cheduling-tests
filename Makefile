OPTS = -g -Wall -std=c++11

schedulesim: schedulesim.cc Process.o Scheduler.o
	g++ ${OPTS} -o schedulesim schedulesim.cc Process.o Scheduler.o

Scheduler.o: Scheduler.cc Scheduler.h ArrayList.h LinkedList.h LinkedListNode.h BSTMultimap.h BSTForwardIterator.h BSTNode.h RBTMultimap.h RBTNode.h
	g++ ${OPTS} -c Scheduler.cc

Process.o: Process.cc Process.h
	g++ ${OPTS} -c Process.cc

clean:
	rm *.o

cleanprog:
	rm schedulesim

cleanemacs:
	rm *~
