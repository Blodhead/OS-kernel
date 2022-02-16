/*
 * KEvent.h
 *
 *  Created on: Feb 12, 2022
 *      Author: OS1
 */

#ifndef H_KEVENT_H_
#define H_KEVENT_H_

#include "Util.h"

class PCB;
class Semaphore;

class KernelEv{
public:
	KernelEv(IVTNo ivn,PCB* run);
	~KernelEv();
	void wait();
	void signal();
	IVTNo getiv();
private:
	Semaphore *sem;
	IVTNo iv;
	PCB* owner;
};


#endif /* H_KEVENT_H_ */
