#include <iostream.h>
#include <dos.h>
#include "../H/System.h"
#include "../H/PCB.h"
#include "../H/ThreadA.h"
#include "../H/Thread.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/KSem.h"
#include "../H/PCBList.h"
#include "../H/Semaphor.h"
#include "../H/Lock.h"

#ifndef BCC_BLOCK_IGNORE
IntRoutine System::old_route = getvect(0x08);
#endif

IntRoutine System::new_route = 0;
mybool System::content_switch = false;
volatile Time System::timer_tics_cnt = 0;
volatile PCB* running = nullptr;
volatile PCB* System::running = nullptr;
volatile PCB* System::idle = nullptr;
PCBList* System::global_list = new PCBList();
PCBList* System::timeblocked_list = new PCBList();
Semaphore* System::semaphore = new Semaphore();
PCB* System::main = nullptr;
int System::num_of_threads = 0;

int System::couter = 0;

unsigned tsp;
unsigned tss;
unsigned tbp;

void System::initialize(){

   cout<<"System initialize"<<endl;

#ifndef BCC_BLOCK_IGNORE
   setvect(0x08,System::timer);
   setvect(0x60,System::old_route);
#endif

   //9
	//cout<<"New created objects: " << System::couter<<endl;
   PCB::initMainThread();//+2
	//cout<<"New created objects: " << System::couter<<endl;
   //11
   PCB::initIdleThread();//+4
	//cout<<"New created objects: " << System::couter<<endl;
   //15
   System::timer_tics_cnt = System::main->kvant;

   System::global_list->push_last((PCB*)System::main);//+1
   System::global_list->push_last((PCB*)System::idle);//+1
   //17
};

void System::restore(){

	System::running->state = PCB::FINISHED;
	dispatch();
	Lock::lock();
	((PCB*)System::idle)->getMyThread()->exitThread();
	((PCB*)System::main)->getMyThread()->exitThread();

	delete System::global_list;
	delete System::timeblocked_list;
	delete System::idle;
	delete System::main;
	delete System::running;

	delete System::semaphore;
//4
#ifndef BCC_BLOCK_IGNORE
   setvect(0x08,System::old_route);
#endif

	System::main = nullptr;
	System::idle = nullptr;
	old_route = nullptr; new_route = nullptr;
	global_list = timeblocked_list = nullptr;
	Lock::lock_cnt = 0;
   Lock::unlock();
};

void interrupt System::switch_context(...){

	static volatile PCB *current = nullptr;
	current = System::running;
	static volatile PCB *next = nullptr;
	next = Scheduler::get();

	if(System::num_of_threads == 2){
		System::num_of_threads--;
		System::main->state = PCB::READY;
		next = System::main;
	}

	if(current == nullptr || current->state == PCB::NOT_STARTED || current->state == PCB::READY){
		cout<<"FATAL EROR OCCURED, CURRENT THREAD IS NOT RUNNING NOT FINISHED!!!"<<endl;
	}

	if(next == nullptr){
		if(current->state == PCB::FINISHED || current->state == PCB::BLOCKED){
			next = System::idle;
		}
		else if(current->state == PCB::RUNNING){

			System::timer_tics_cnt = current->kvant;
			System::content_switch = false;
			return;

		}

	}
	if((next->state == PCB::READY || next == System::idle) && (current == System::main || current->state != PCB::FINISHED)){

		if(current->saved_on_sem == true){
			current->lock_cnt = Lock::lock_cnt;
			current->asked_for_context_switch = System::content_switch;
		}

#ifndef BCC_BLOCK_IGNORE
		asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			 };
#endif

			 running->sp = tsp;
			 running->ss = tss;
			 running->bp = tbp;

			 if(current->state != PCB::BLOCKED)
			 if((System::main != current || System::main->state != PCB::FINISHED) && current != System::idle){
				 current->state = PCB::READY;
				 Scheduler::put((PCB*)current);
			 }
	}
	if(next->state == PCB::RUNNING || next->state == PCB::READY){
// && (current->state == PCB::READY || current->state == PCB::FINISHED)
		//if(next == System::idle) cout<<"IDLE THREAD RUNNING"<<endl;
		tsp = next->sp;
		tss = next->ss;
		tbp = next->sp;

#ifndef BCC_BLOCK_IGNORE
		asm {
		mov sp, tsp
		mov ss, tss
		mov bp, tbp
		}
#endif

		if(next->saved_on_sem == true && next != System::idle){
			Lock::lock_cnt = next->lock_cnt;
			System::content_switch =current->asked_for_context_switch;
		}

		next->state = PCB::RUNNING;
		System::running = next;
		System::timer_tics_cnt = next->kvant;
		System::content_switch = false;

		/*if(System::running == System::idle)
		cout<<"IDLE is now running"<<endl;*/
		return;

	}

};

void interrupt System::timer(...){

	   System::old_route();
		void tick();
		tick();
	   if(System::timeblocked_list->head != nullptr){
	   		   System::timeblocked_list->decWaitVal();
	   }

	   System::timer_tics_cnt--;

	   if(System::timer_tics_cnt <= 0){
	      dispatch();
	   }

};
