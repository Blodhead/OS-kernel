/*
 * ThreadA.cpp
 *
 *  Created on: Aug 13, 2021
 *      Author: OS1
 */

#include "ThreadA.h"
#include "PCB.h"

ThreadA::ThreadA(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice) {//CHECKED
	// TODO Auto-generated constructor stub

}

ThreadA::~ThreadA() {//
	// TODO Auto-generated destructor stub
}

void ThreadA::run(){
   lock;

   for (int i =0; i < 30; ++i) {
      lock
      cout<< *(this->getMyPCB()) <<i<<endl;
      unlock

      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);

   }
   unlock;

   exitThread();

}
