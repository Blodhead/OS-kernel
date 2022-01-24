/*
 * ThreadA.cpp
 *
 *  Created on: Aug 13, 2021
 *      Author: OS1
 */

#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Node.h"
#include "../H/PCBList.h"
#include "../H/Schedule.h"

ThreadA::ThreadA(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice) {//CHECKED
	// TODO Auto-generated constructor stub

}

ThreadA::~ThreadA() {//
	// TODO Auto-generated destructor stub
}

void ThreadA::run(){


   for (int i = 0; i < 30; ++i) {
      lock
      cout<< *(this->getMyPCB()) <<i<<endl;
      unlock

      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);

   }

   lock;

   if(this->getMyPCB()->myJoin->isEmpty() == false){

	   for(Node* temp = this->getMyPCB()->myJoin->head; temp != nullptr; temp = temp->next){

		   temp->pcb->myJoinNum--;

		   if(temp->pcb->myJoinNum == 0){

			   cout<<"Main was put in scheduler: "<< temp->pcb->id <<endl;
			   lock;
			   temp->pcb->state = PCB::READY;
			   Scheduler::put(temp->pcb);
		   }
		   cout<<this->getMyPCB()->myJoin->head->pcb->id<<" was popped out!"<<endl;
		   lock;
		   this->getMyPCB()->myJoin->pop_first();
	   }
   }

   unlock;

   exitThread();

}
