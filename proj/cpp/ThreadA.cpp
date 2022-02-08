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


   for (int i = 0; i < 20; ++i) {
      lock
      cout<< *(this->getMyPCB()) <<i<<endl;
      unlock

      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);

   }

   lock;

   /*if(this->getMyPCB()->myJoin->isEmpty() == false){

	   for(Node* temp = this->getMyPCB()->myJoin->head; temp != nullptr; temp = temp->next){

		   temp->pcb->myJoinNum--;

		   if(temp->pcb->myJoinNum == 0){

			   temp->pcb->state = PCB::READY;
			   if(System::blocked_list->seek_by_id(temp->pcb->id) == nullptr){
				   cout<<"Ne postoji blokirana nit FATAL ERORR!!!"<<endl;
			   }
			   System::blocked_list->pop_by_id(temp->pcb->id);
			   Scheduler::put(temp->pcb);
		   }
		   //cout<<"Number of threads main thread is waitnig for: "<<this->getMyPCB()->myJoinNum<<endl;

		   this->getMyPCB()->myJoin->pop_first();
	   }
   }
*/
   if(this->getId() == 2){//los zavrsetak, kasnije nadoraditi
	   System::main->state = PCB::READY;
	   //System::blocked_list->pop_by_id(System::main->id);
	   Scheduler::put(System::main);
   }

   unlock;

   exitThread();

}
