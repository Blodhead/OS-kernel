/*
 * KEvent.cpp
 *
 *  Created on: Feb 12, 2022
 *      Author: OS1
 */

#ifndef CPP_KEVENT_CPP_
#define CPP_KEVENT_CPP_

#include <iostream.h>
#include "../H/PCB.h"
#include "../H/KEvent.h"
#include "../H/Semaphor.h"
#include "../H/System.h"

KernelEv::KernelEv(IVTNo ivn,PCB* run):iv(ivn),owner(run){
	sem=new Semaphore(0);
};
void KernelEv::wait(){
	if(System::running->id == owner->id){
		sem->wait(0);
	}
};

void KernelEv::signal(){
	if(sem->val()<0){
		sem->signal(System::num_of_threads-2);
	}
};
IVTNo KernelEv::getiv(){
	return iv;
};
KernelEv::~KernelEv(){
	lock;
	delete sem;
	sem = nullptr;
	owner = nullptr;
	unlock;
};


#endif /* CPP_KEVENT_CPP_ */
