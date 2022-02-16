#include "../h/PCBList.h"
#include "../h/System.h"
#include "../h/Thread.h"
#include "../h/Schedule.h"
#include "../H/Ksem.h"
#include "../H/Lock.h"

PCBList::PCBList():List(){head = tail = nullptr;};

PCBList::~PCBList(){
	Lock::lock();

	Node* curr = head, *prev = nullptr;
	if(this == System::global_list){

		while(curr != nullptr){
			prev = curr;
			curr = curr->next;
			if(curr->pcb != System::main)
			delete prev->pcb->getMyThread(); //delete pcb = 4
			//else delete prev->pcb;
			delete prev; // delete elem = 1
		}
		head = tail = nullptr;
		Lock::unlock();
		return;
	}

	while(curr != nullptr){
		prev = curr;
		curr = curr->next;
		delete prev;
	}

	head = tail = nullptr;

	Lock::unlock();
	return;
}

void PCBList::push_in_time_list(PCB* pcb){

	Lock::lock();

	if (this->head == nullptr) {
		this->push_first(pcb);
		Lock::unlock();
		return;
	}

	this->unsort_by_time();
	for(Node* temp = head; temp != nullptr; temp = temp->next){

		if((temp->pcb->waiting_time) > (pcb->waiting_time)){

			Node* left = temp->prev, *right = temp;

			temp = new Node(pcb);

			if(left != nullptr)
				left->next = temp;

				right->prev = temp;

			temp->prev = left;
			temp->next = right;
			if(temp->prev == nullptr) head = temp;

			this->sort_by_time();

			Lock::unlock();

			return;
		}else if(temp == tail){

			temp->next = new Node(pcb);
			tail = temp->next;
			tail->prev = temp;
			this->sort_by_time();
			Lock::unlock();
			return;
		}


	}

	this->push_last(pcb);

	this->sort_by_time();

	Lock::unlock();

	return;

}

void PCBList::pop_from_time_list(int ID){
	Lock::lock();
	if(ID == -1){
		while(head->pcb->waiting_time == 0){

			//cout<<"Vreme preostalo za id:" << head->pcb->id <<" niti je: "<<head->pcb->waiting_time<<endl;
			if(System::timeblocked_list->head == nullptr) cout<<"ERROR"<<endl;
			Node* node1 = System::timeblocked_list->pop_first();

			PCB* temp1 = node1->pcb;
			delete node1;
			delete temp1->mySem->blocked->pop_by_id(temp1->id);

			temp1->state = PCB::READY;
			temp1->blocked_way = 0;
			temp1->mySem->incVal();
			temp1->mySem = nullptr;

			Scheduler::put(temp1);
		}
	}else if(ID > 1){

		this->unsort_by_time();

		Node* node1 = System::timeblocked_list->pop_by_id(ID);

		PCB* temp1 = node1->pcb;
		delete node1;

		//temp1->state = PCB::READY;
		//temp1->mySem = nullptr;

		this->sort_by_time();
	}

	Lock::unlock();
	return;
}

void PCBList::unsort_by_time(){

	Lock::lock();

	for(Node* temp = head; temp->next != nullptr; temp = temp->next){
		if(temp->next != nullptr)
		temp->next->pcb->waiting_time += temp->pcb->waiting_time;
	}

	Lock::unlock();

};

void PCBList::sort_by_time(){

	Lock::lock();

	for(Node* temp = tail; temp->prev != nullptr; temp = temp->prev){
		if(temp->prev != nullptr)
		temp->pcb->waiting_time -= temp->prev->pcb->waiting_time;
	}

	Lock::unlock();

};

void PCBList::decWaitVal(){
	Lock::lock();
	if(this->head != nullptr && (--this->head->pcb->waiting_time) <= 0) {
		this->pop_from_time_list();
	}
	Lock::unlock();
};
