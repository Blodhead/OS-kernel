#ifndef THREADA_H_
#define THREADA_H_

#include "Thread.h"

class ThreadA : public Thread {
public:
	ThreadA(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	~ThreadA();
	void run();
};

#endif /* H_THREADA_H_ */
