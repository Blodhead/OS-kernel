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
PCBList* System::blocked_list = new PCBList();
PCBList* System::timeblocked_list = new PCBList();
PCB* System::main = nullptr; //MOZDA JE PROBLEM STO NIJE VOLATILE?

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

   PCB::initMainThread();
   cout<<"Main id: "<<System::main->id<<endl;
   PCB::initIdleThread();
   cout<<"Idle id: "<<System::idle->id<<endl;
   System::timer_tics_cnt = System::main->kvant;

};

void System::restore(){

#ifndef BCC_BLOCK_IGNORE
   setvect(0x08,System::old_route);
#endif

	lock;

	((PCB*)System::idle)->getMyThread()->exitThread();
	((PCB*)System::main)->getMyThread()->exitThread();

	delete System::global_list;
	delete System::blocked_list;

	//delete System::idle;
	//delete System::main;

	System::main = nullptr;
	System::idle = nullptr;
	old_route = nullptr; new_route = nullptr;
	global_list = blocked_list = timeblocked_list = nullptr;

	cout<<"System restore finished!"<<endl;

	unlock;
};

void interrupt System::switch_context(...){////!!!!!

	//static volatile PCB *current = nullptr, *next = nullptr;
/*
	cout<<"-----------Prekidna start(Thread id current running :"<<running->id<<")-----------"<<endl;
	lock;
	current = running;

	if(current && current->state != PCB::FINISHED && current->state != PCB::BLOCKED){
		current->state = PCB::READY;

	 asm {
		mov tsp, sp
		mov tss, ss
		mov tbp, bp
	 };


	 running->sp = tsp;
	 running->ss = tss;
	 running->bp = tbp;

	}

	next = Scheduler::get();

	if(next == nullptr && current->state == PCB::FINISHED){next = System::idle;}//treba pogledati kad se budu radili smeafori
	else if(next == nullptr) next = current;

	lock;
	if(next){
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

		lock;
		if(current!=next)
		if(current->state != PCB::FINISHED && current->state != PCB::BLOCKED && current != System::idle)
		Scheduler::put((PCB*)current);
	}

	running = next;
	running->state = PCB::RUNNING;
	timer_tics_cnt = running->kvant;
	content_switch = false;
	cout<<"-----------Prekidna end(Thread id next running:"<<running->id<<")-----------"<<endl;
*/
lock;

	static volatile PCB *current = nullptr;
	current = System::running;
	static volatile PCB *next = nullptr;
	next = Scheduler::get();

	if(current == nullptr || current->state == PCB::NOT_STARTED || current->state == PCB::READY || current->state == PCB::BLOCKED){
		cout<<"FATAL EROR CURRENT THREAD IS NOT RUNNING NOT FINISHED!!!"<<endl;
		lock;
	}

	if(next == nullptr){
		 if(current->state == PCB::FINISHED){
			 next = System::idle;
			}
		 else if(current->state == PCB::RUNNING){
			 next = current;
			 System::timer_tics_cnt = current->kvant;
			 System::content_switch = false;
			 unlock;
			 return;
			}

	}
	if((next->state == PCB::READY && current->state == PCB::RUNNING) || (next->state == PCB::READY && current == System::main && System::main->state == PCB::FINISHED)){

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

			 if(System::main != current || System::main->state != PCB::FINISHED){
				 current->state = PCB::READY;
				 Scheduler::put((PCB*)current);
			 }
	}
	if((next->state == PCB::RUNNING || next->state == PCB::READY) && (current->state == PCB::READY || current->state == PCB::FINISHED)){

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

		next->state = PCB::RUNNING;
		System::running = next;
		System::timer_tics_cnt = next->kvant;
		System::content_switch = false;
		unlock;
		return;

	}

};

void interrupt System::timer(...){

   System::old_route();
   if(System::content_switch == false) System::timer_tics_cnt--;
   if(System::timer_tics_cnt == 0 || System::content_switch == true){
      System::switch_context();
   }

};

