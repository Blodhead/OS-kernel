#include <iostream.h>
#include "../H/Thread.h"
#include "../H/System.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"
#include "../H/Lock.h"

Thread::Thread(StackSize stackSize, Time timeSlice){//CHECKED
	this->myPCB = new PCB(PCB::wrapper, stackSize,timeSlice);
	this->myPCB->myThread = this;
	this->myPCB->myJoin->head = this->myPCB->myJoin->tail = nullptr;
	this->myPCB->myJoinNum = 0;
	if(this->getId() > 1){
	System::global_list->push_last(this->getMyPCB());
    this->start();
	}
};

void Thread::start(){//CHECKED
   if(this->myPCB == nullptr) cout<<"Greska"<<endl;
	if(this->myPCB->state == PCB::NOT_STARTED) {
		this->myPCB->state = PCB::READY;
	    Scheduler::put(this->myPCB);
	}
}

Thread::Thread(PCB* pcb){
   this->myPCB = pcb;
   this->myPCB->myThread = this;
}

void Thread::waitToComplete(){
	this->myPCB->waitToComplete();
}

PCB* Thread::getMyPCB(){//FINISHED
	return this->myPCB;
}

ID Thread::getId(){//FINISHED
	return this->myPCB->id;
}

ID Thread::getRunningId(){//FINISHED
	return System::running->id;
}

Thread* Thread::getThreadById(ID _id){//CHECKED

   return (System::global_list->pop_by_id(_id))->pcb->myThread;
}

void Thread::exitThread(){
	Lock::lock();
	//if(this->getMyPCB()->state != PCB::FINISHED && this->getMyPCB()->state != PCB::NOT_STARTED){
	if(this->getMyPCB()->state == PCB::RUNNING){
	   this->myPCB->state = PCB::FINISHED;
	   //System::global_list->pop_by_id(this->getId());
	   //////////KOD ZA SEMAFORE FALI (IZBACIVANJE IZ SEMAFORA)
	}

	System::num_of_threads--;
	Lock::unlock();
	if(this != System::idle && this->getId() != System::main->id){
		dispatch();
	}

};

void dispatch(){

	if(Lock::lock_cnt == 0) System::switch_context();
	else System::content_switch = true;

}
void Thread::run(){}

Thread::~Thread(){

	Lock::lock();
	   if(this->getMyPCB()->myJoin->isEmpty() == false){
		   Node* temp = this->getMyPCB()->myJoin->pop_first();
		   if(temp!=nullptr)

		   while(temp != nullptr){
			   if(temp->pcb->myJoinNum == 0){
			   temp->pcb->state = PCB::READY;
			   Scheduler::put(temp->pcb);
			   delete temp;
			   }
			   temp = this->getMyPCB()->myJoin->pop_first();
		   }
	   }
	Lock::unlock();
	delete(this->myPCB);
	this->myPCB = nullptr;
};
