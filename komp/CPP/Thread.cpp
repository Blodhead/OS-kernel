#include <iostream.h>
#include "../H/Thread.h"
#include "../H/PCB.h"
#include "../H/System.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"

Thread::Thread(StackSize stackSize, Time timeSlice){//CHECKED
	this->myPCB = new PCB(PCB::wrapper, stackSize,timeSlice);
	this->myPCB->myThread = this;

	System::put_PCB_to_list(this->myPCB);
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

   lock;

   unsigned tsp;
   unsigned tss;
   unsigned tbp;


   System::put_PCB_to_blocked_list(this->getMyPCB());
   this->myPCB->state = PCB::BLOCKED;

   asm {
      mov tsp, sp
      mov tss, ss
      mov tbp, bp
   }
   System::blocked_head->pcb->sp;
   System::blocked_head->pcb->ss = tss;
   System::blocked_head->pcb->bp = tbp;
   //System::old_route();
   unlock;
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

   return (System::get_PCB_from_List(_id))->myThread;
}

void Thread::exitThread(){
   lock;
   System::running->state = PCB::FINISHED;
   unlock;
   dispatch();
}

void dispatch(){

   lock;

	System::content_switch = true;
	System::timer();

	unlock;

}
void Thread::run(){}

Thread::~Thread(){//CHECKED
	delete(this->myPCB);
	this->myPCB = nullptr;
};
