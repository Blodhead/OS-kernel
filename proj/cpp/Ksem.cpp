#include "../H/Ksem.h"
#include "../H/List.h"
#include "../H/System.h"
#include "../H/PCBList.h"
#include "../H/Thread.h"
#include "../H/Schedule.h"

KernelSem::KernelSem(int init):value(init){
	value = 0;
}
KernelSem::~KernelSem(){

	/*lock;
		delete blocked;
		blocked = nullptr;
	unlock;*/

};

void KernelSem::incVal(){this->value++;}

int KernelSem::wait(Time maxTimeToWait){

	lock;

	if(this->value <= 0){
		this->value--;
		cout<<"VALUE:       "<<value<<endl;
		System::running->state = PCB::BLOCKED;
		System::running->mySem = this;

		if(maxTimeToWait > 0){
			System::running->waiting_time = maxTimeToWait;
			System::timeblocked_list->push_in_time_list((PCB*)System::running);
		}
		System::blocked_list->push_last((PCB*)System::running);
		unlock;

		for(Node* temp3 = System::blocked_list->head; temp3 != nullptr; temp3 = temp3->next)
			cout<<"--------------Niti u obicnoj listi: "<<temp3->pcb->id<<endl;

		for(Node* temp4 = System::timeblocked_list->head; temp4 != nullptr; temp4 = temp4->next)
			if(temp4 != nullptr)
			cout<<"--------------Niti u vremenskoj listi: "<<temp4->pcb->id<<endl;


		dispatch();
        return 1;
	}
	unlock;
	return 0;
};

int KernelSem::signal(int n){
	lock;
	cout<<"VALUE:       "<<value<<endl;
	if(n <= 0) {unlock; return 0;}
	else { //if(n>0)

		int cnt = 0;

		for(int i = 0; i < n; i++){
			lock;
			if(value < 0){
				value++;
				lock;
				Node* node1 = System::blocked_list->pop_first();
				PCB* temp = node1->pcb;
				delete node1;

				if(System::timeblocked_list->seek_by_id(temp->id) != nullptr){//TODO
					//cout<<"USAO SAM U USLOV    "<< temp->id<<endl;
					System::timeblocked_list->pop_from_time_list(temp->id);
				}
				cout<<"Thread id: "<<temp->id<<" izbacen."<<endl;
				temp->state = PCB::READY;
				temp->mySem = nullptr;
				Scheduler::put(temp);
				cnt++;

			}

		}
		for(Node* temp3 = System::blocked_list->head; temp3 != nullptr; temp3 = temp3->next)
			cout<<"--------------Niti u obicnoj listi: "<<temp3->pcb->id<<endl;

		for(Node* temp4 = System::timeblocked_list->head; temp4 != nullptr; temp4 = temp4->next)
			if(temp4 != nullptr)
			cout<<"--------------Niti u vremenskoj listi: "<<temp4->pcb->id<<endl;

		cout<<"CNT :"<<cnt<<endl;

		unlock;
		return cnt;
	}

};

int KernelSem::getVal() const{
	return value;
};

void KernelSem::exit(int i){
	lock;
	/*Nema potrebe bice izbrsana svakako pri restauraciji*/
	unlock;
}
