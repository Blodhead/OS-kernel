#include <iostream.h>
#include "../H/Thread.h"
#include "../H/System.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"

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

   return (System::blocked_list->pop_by_id(_id))->pcb->myThread;
}

void Thread::exitThread(){
   lock;

	//if(this->getMyPCB()->state != PCB::FINISHED && this->getMyPCB()->state != PCB::NOT_STARTED){
	if(this->getMyPCB()->state == PCB::RUNNING){
	   this->myPCB->state = PCB::FINISHED;
	   //System::global_list->pop_by_id(this->getId());
	   //////////KOD ZA SEMAFORE FALI (IZBACIVANJE IZ SEMAFORA)
	}

	unlock;
	if(this != System::idle && this->getId() != System::main->id){
		dispatch();
	}

};

void dispatch(){

   lock;

	System::content_switch = true;
	System::timer();

	unlock;

}
void Thread::run(){}

Thread::~Thread(){
	delete(this->myPCB);
	this->myPCB = nullptr;
};
