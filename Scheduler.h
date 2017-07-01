#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "List.h"
#include "Process.h"
#include "BSTMultimap.h"
#include "RBTMultimap.h"


class Scheduler
{
 public:
  virtual ~Scheduler() = 0;
  /* virtual void printing() = 0; */
  virtual void addProcess(Process* proc) = 0;
  virtual Process* popNext(int curCycle) = 0;
};

class RoundRobin : public Scheduler
{
 protected:
  List<Process*>* procQueue;
 public:
  // Initializes procQueue as an empty ArrayList
  RoundRobin();
  // deletes procQueue
  ~RoundRobin();

  // adds given process to the back of procQueue
  virtual void addProcess(Process* proc);
  // pops the process at the front of the queue and returns it
  virtual Process* popNext(int curCycle);
    
};

class FastRoundRobin : public RoundRobin
{
 public:
  FastRoundRobin();
  /* ~FastRoundRobin(); */
};

class CompletelyFair : public Scheduler
{
 protected:
  BSTMultimap<int, Process*>* procTree;
 public:
  CompletelyFair();
  ~CompletelyFair();
  /* virtual void printing(); */
  virtual void addProcess(Process* proc);
  virtual Process* popNext(int curCycle);
};

class FastCompletelyFair : public CompletelyFair
{
 protected:
  RBTMultimap<int, Process*>* procTree;
 public:
  FastCompletelyFair();
  ~FastCompletelyFair();
};
#endif
