#include "../H/Ksem.h"
#include "../H/List.h"
#include "../H/System.h"

KernelSem::KernelSem(int init):value(init){
	blocked = new List();
}
KernelSem::~KernelSem(){

	lock;
		delete blocked;
		blocked = nullptr;
	unlock;

}

int KernelSem::wait(Time maxTimeToWait){
	/*int x=1;
	if(--value<0){
		lock;
		System::running->state=PCB::BLOCKED;
		System::running->mySem = this;//
		//running->sem_saved=1;
		if(maxTimeToWait>0){
			running->waiting = maxTimeToWait;
			System::blocked.time_add((PCB*)running);
		}
		blocked->push_back((PCB*)running);
		unlock;
		dispatch();
        x=running->time_unblocked;
	}
	return x;
*/
	lock;
	System::running->state = PCB::BLOCKED;


	unlock;


	return 0;
}
int KernelSem::signal(int n){
	lock;
	/*int x=0;
	if(n<0){return n;}
	else if(n==0){
		if(value++<0){
			PCB* newx=blocked->pop_begin();
			timeblocked.notime_remove(newx->id);
			newx->state=PCB::READY;
			newx->time_unblocked=1;
			newx->sem_saved=0;
			newx->mySem=nullptr;
			Scheduler::put(newx);
		}
	}
	else{
		for(int i=0;i<n;i++){
			if(value++<0){
				PCB* newx=blocked->pop_begin();
				x++;
				timeblocked.notime_remove(newx->id);
				newx->state=PCB::READY;
				newx->time_unblocked=1;
				newx->sem_saved=0;
				newx->mySem=nullptr;
				Scheduler::put(newx);

			}
		}
	}*/
	unlock;
	//return x;
	return 0;
}
int KernelSem::val() const{
	return value;
}
void KernelSem::exit(int i){
	lock;
	/*if(this->blocked->removebyID(i)==1){
		this->value++;
	}*/
	unlock;
}
