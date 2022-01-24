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
	System::global_list->push_first(this->myPCB);
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

   this->myPCB->myJoin->push_last((PCB*)System::running);

   System::running->state = PCB::BLOCKED;
   System::running->myJoinNum++;


   /*asm {
      mov tsp, sp
      mov tss, ss
      mov tbp, bp
   };

   System::global_list->seek_by_id(System::running->id)->pcb->sp = tsp;
   System::global_list->seek_by_id(System::running->id)->pcb->ss = tss;
   System::global_list->seek_by_id(System::running->id)->pcb->bp = tbp;
*/
   /*System::blocked_list->head->pcb->sp = tsp;
   System::blocked_list->head->pcb->ss = tss;
   System::blocked_list->head->pcb->bp = tbp;*/
   //System::old_route();

   //dispatch();
   unlock;
   dispatch();
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
