#ifndef THREAD_H
#define THREAD_H
#include <iostream.h>
#include "Util.h"
#include "System.h"
#include "PCB.h"

class Thread {
protected:
	friend class PCB;//PREMESTENO ZBOG PREVODJENJA
	friend class System;
	friend void userMain();
public:

  void start();
  void waitToComplete();
  virtual ~Thread();

  ID getId();
  static ID getRunningId();
  static Thread* getThreadById(ID id);
  void exitThread();

  PCB* getMyPCB();

protected:

  Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
  virtual void run();
private:
  PCB* myPCB;
  Thread( PCB* pcb );
};

void dispatch ();

#endif /* INC_THREAD_H_ */
