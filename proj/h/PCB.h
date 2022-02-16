#ifndef PCB_H_
#define PCB_H_

#include <iostream.h>
#include "Util.h"

class KernelSem;
class PCBList;
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
	Time waiting_time;
	KernelSem* mySem;
	PCBList* myJoin;
	int myJoinNum;
	ID id;
	State state;

	mybool saved_on_sem;
	mybool asked_for_context_switch;
	int lock_cnt;

	int blocked_way;
	static void wrapper();
	PCB(StackSize, Time, Thread*);
	PCB(Runnable run, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	Time getKvant();
	Thread* getMyThread();
	void waitToComplete();
	void start();
	~PCB();

	static void initMainThread();
	static void initIdleThread();
	friend ostream& operator<<(ostream& os,const PCB &pcb);
};


#endif
