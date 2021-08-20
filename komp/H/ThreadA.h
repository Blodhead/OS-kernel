/*
 * ThreadA.h
 *
 *  Created on: Aug 13, 2021
 *      Author: OS1
 */

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
