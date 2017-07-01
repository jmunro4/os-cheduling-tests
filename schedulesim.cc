#include <chrono>
#include <iostream>
#include "Scheduler.h"
#include "Process.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include "BSTMultimap.h"
#include "RBTMultimap.h"

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
  ArrayList<Process*> cpuBound = ArrayList<Process*>(numCPUBound);
  for(int i = 0; i < numCPUBound; i++)
    {
      Process* cpuProc = new CPUBoundProcess(i);
      cpuBound.pushBack(cpuProc);
      sched->addProcess(cpuProc);
    }
  ArrayList<Process*> ioBound = ArrayList<Process*>(numIOBound);
  for(int j = 0; j < numIOBound; j++)
    {
      Process* ioProc = new IOBoundProcess(numCPUBound+j);
      ioBound.pushBack(ioProc);
      sched->addProcess(ioProc); 
    }

  auto ti = chrono::system_clock::now();
  int num = 0;
  int curCycle = 0;

  while(curCycle <= numCycles)
    {
      Process* current = sched->popNext(curCycle);
      num++;
      curCycle += current->simulate(curCycle, 10);
      sched->addProcess(current);
    }

  auto tf = chrono::system_clock::now();
  auto dur = tf - ti;
  auto durNS = chrono::duration_cast<chrono::nanoseconds>(dur);
  unsigned long long elapsed = durNS.count();
  

  double* data = new double[5];
  for(int k = 0; k < (numCPUBound + numIOBound); k++)
    {
      Process* last;
      if(k < numCPUBound)
  	{
	  last = cpuBound.getFront();
	  last->simulate(curCycle, 0);
  	  data[1] += last->getCPUTime();
  	  data[2] += last->getWaitTime();
	  delete last;
	  cpuBound.popFront();
  	}
      else
  	{
	  last = ioBound.getFront();
	  last->simulate(curCycle, 0);
  	  data[3] += last->getCPUTime();
  	  data[4] += last->getWaitTime();
	  delete last;
	  ioBound.popFront();
  	}
    }
  data[0] = elapsed / num;
  data[1] /= numCPUBound;
  data[2] /= numCPUBound;
  data[3] /= numIOBound;
  data[4] /= numIOBound;

  return data;
}


int main(int argc, char** argv)
{
  int numCPU = atoi(argv[1]);
  int numIO = atoi(argv[2]);
  int numCyc = atoi(argv[3]);

  ArrayList<Scheduler*> schedList = ArrayList<Scheduler*>();

  RoundRobin roundrobin;
  schedList.pushBack(&roundrobin);
  FastRoundRobin fastroundrobin;
  schedList.pushBack(&fastroundrobin);
  CompletelyFair completelyfair;
  schedList.pushBack(&completelyfair);
  FastCompletelyFair fastcompletelyfair;
  schedList.pushBack(&fastcompletelyfair);

  ArrayList<string> header = ArrayList<string>();

  header.pushBack("Round Robin Scheduler \n");
  header.pushBack("Fast Round Robin Scheduler \n");
  header.pushBack("Completely Fair Scheduler \n");
  header.pushBack("Fast Completely Fair Scheduler \n");
  
  cout << endl;

  while(not schedList.isEmpty())
    {
      Scheduler* sched = schedList.getFront();
      double* output = simulate(sched, numCPU, numIO, numCyc);
      cout << header.getFront();
      cout << "Time per move (ns): " << output[0] << endl;
      cout << "Average CPU time of CPU-Bound proccesses: " << output[1] << endl;
      cout << "Average wait time of CPU-Bound proccesses: " << output[2] << endl;
      cout << "Average CPU time of IO-Bound proccesses: " << output[3] << endl;
      cout << "Average wait time of IO-Bound proccesses: " << output[4] << endl << endl;
      schedList.popFront();
      header.popFront();
    }
}
