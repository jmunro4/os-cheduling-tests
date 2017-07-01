#include "Scheduler.h"
#include "ArrayList.h"
#include "Process.h"
#include "LinkedList.h"
#include "BSTMultimap.h"
#include "RBTMultimap.h"
#include "BSTForwardIterator.h"
#include <iostream>

using namespace std;

Scheduler::~Scheduler()
{
}

RoundRobin::RoundRobin()
{
  this->procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin()
{
  delete this->procQueue;
}

void RoundRobin::addProcess(Process* proc)
{
  this->procQueue->pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle)
{
  Process* p = this->procQueue->getFront();
  this->procQueue->popFront();
  return p;
}

FastRoundRobin::FastRoundRobin()
{
  delete this->procQueue;
  this->procQueue = new LinkedList<Process*>();
}

// FastRoundRobin::~FastRoundRobin()
// {
//   delete this->procQueue;
// }

CompletelyFair::CompletelyFair()
{
  this->procTree = new BSTMultimap<int, Process*>();
}

CompletelyFair::~CompletelyFair()
{
  delete this->procTree;
}

void CompletelyFair::addProcess(Process* proc)
{
  this->procTree->insert(proc->getCPUTime(), proc);
}

// void CompletelyFair::printing()
// {
//   this->procTree->printTree();
// }

Process* CompletelyFair::popNext(int curCycle)
{
  BSTForwardIterator<int, Process*> iter = this->procTree->getMin();
  while(iter.getValue()->isBlocked(curCycle))
    {
      iter.next();
      if(iter.isPastEnd())
	{
	  cout << "Error" << endl;
	}
    }
  // cout << "found unblocked" << endl;
  Process* next = iter.getValue();
  this->procTree->remove(iter);
  return next;
}

FastCompletelyFair::FastCompletelyFair()
{
  this->procTree = new RBTMultimap<int, Process*>();
}

FastCompletelyFair::~FastCompletelyFair()
{
  delete this->procTree;
}
