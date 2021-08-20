#ifndef PCB_H_
#define PCB_H_

#include "Util.h"

class PCB{

public:
	friend class Thread;
	friend class System;
	enum State {NOT_STARTED,READY,RUNNING,BLOCKED,FINISHED};
private:
	unsigned* stack;
	StackSize stack_size;
	Thread* myThread;
   Runnable run;
	static ID idd;

public:

   unsigned bp;
   unsigned sp;
   unsigned ss;
   Time kvant;
   ID id;
	State state;
	static void wrapper();
	PCB(StackSize, Time, Thread*);
	PCB(Runnable run, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	Time getKvant();
	Thread* getMyThread();
	void waitToComplete();
	void start();
	~PCB();

   friend ostream& operator<<(ostream& os,const PCB &pcb);
};


#endif
