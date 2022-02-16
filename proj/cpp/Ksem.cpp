#include "../H/Ksem.h"
#include "../H/List.h"
#include "../H/System.h"
#include "../H/PCBList.h"
#include "../H/Thread.h"
#include "../H/Schedule.h"
#include "../H/Lock.h"

KernelSem::KernelSem(int init):value(init){
	//value = 0;
	this->blocked = new PCBList;
}
KernelSem::~KernelSem(){
	Lock::lock();
		delete blocked;
		blocked = nullptr;
	Lock::unlock();
};

void KernelSem::incVal(){this->value++;}

int KernelSem::wait(Time maxTimeToWait){

	Lock::lock();

	if(this->value-- <= 0){
		System::running->state = PCB::BLOCKED;
		System::running->mySem = this;

		if(maxTimeToWait > 0){
			System::running->waiting_time = maxTimeToWait;
			System::timeblocked_list->push_in_time_list((PCB*)System::running);
		}
		this->blocked->push_last((PCB*)System::running);

		Lock::unlock();
		//dispatch();
		System::switch_context();

	}
	//cout<<"Lock cnt: "<<Lock::lock_cnt;
	Lock::unlock();
	return System::running->blocked_way;
};

int KernelSem::signal(int n){
	Lock::lock();
	//cout<<"VALUE:       "<<value<<endl;

	if(n < 0) {
		Lock::unlock();
		return 0;
	}
	else if(n == 0){
		n = 1;
	}
	int cnt = 0;

	for(int i = 0; i < n; i++){
		if(value++ < 0){

			Node* node1 = this->blocked->pop_first();
			PCB* temp = node1->pcb;
			delete node1;

			if(System::timeblocked_list->seek_by_id(temp->id) != nullptr){//TODO
				//cout<<"USAO SAM U USLOV    "<< temp->id<<endl;
				System::timeblocked_list->pop_from_time_list(temp->id);
			}
			//cout<<"Thread id: "<<temp->id<<" izbacen."<<endl;
			temp->state = PCB::READY;
			temp->mySem = nullptr;
			temp->blocked_way = 1;
			Scheduler::put(temp);
			cnt++;
		}
	}
	Lock::unlock();
	return cnt;
};

int KernelSem::getVal() const{
	return value;
};

void KernelSem::exit(int i){
}
