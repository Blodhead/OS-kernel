#include "../h/PCBList.h"
#include "../h/System.h"
#include "../h/Thread.h"
#include "../h/Schedule.h"
#include "../H/Ksem.h"

PCBList::PCBList():List(){head = tail = nullptr;};

PCBList::~PCBList(){
	lock;

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
		unlock;
		return;
	}

	while(curr != nullptr){
		prev = curr;
		curr = curr->next;
		delete prev;
	}

	head = tail = nullptr;

	unlock;
	return;
}

void PCBList::push_in_time_list(PCB* pcb){

	lock;

	if (this->head == nullptr) {
		this->push_first(pcb);
		unlock;
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

			unlock;

			return;
		}else if(temp == tail){

			temp->next = new Node(pcb);
			tail = temp->next;
			tail->prev = temp;
			this->sort_by_time();
			unlock;
			return;
		}


	}

	this->push_last(pcb);

	this->sort_by_time();

	unlock;

	return;

}

void PCBList::pop_from_time_list(int ID){
	lock;
	if(ID == -1){
		while(head->pcb->waiting_time == 0){

			cout<<"Vreme preostalo za id:" << head->pcb->id <<" niti je: "<<head->pcb->waiting_time<<endl;

			Node* node1 = System::timeblocked_list->pop_first();

			PCB* temp1 = node1->pcb;
			delete node1;
			delete System::blocked_list->pop_by_id(temp1->id);

			temp1->state = PCB::READY;
			temp1->mySem->incVal();
			cout<<"VALUE:       "<<temp1->mySem->getVal()<<endl;
			temp1->mySem = nullptr;

			Scheduler::put(temp1);
			cout<<"----------THREAD ID: "<<temp1->id<<" PUT IN SCHEDULER"<<endl;
			for(Node* temp3 = System::blocked_list->head; temp3 != nullptr; temp3 = temp3->next)
				cout<<"--------------Niti u obicnoj listi: "<<temp3->pcb->id<<endl;

			for(Node* temp4 = System::timeblocked_list->head; temp4 != nullptr; temp4 = temp4->next)
				if(temp4 != nullptr)
				cout<<"--------------Niti u vremenskoj listi: "<<temp4->pcb->id<<endl;
		}
	}else if(ID > 1){

		this->unsort_by_time();

		Node* node1 = System::timeblocked_list->pop_by_id(ID);

		PCB* temp1 = node1->pcb;
		delete node1;

		//temp1->state = PCB::READY;
		//temp1->mySem = nullptr;

		this->sort_by_time();

		//Scheduler::put(temp1);

		for(Node* temp3 = System::blocked_list->head; temp3 != nullptr; temp3 = temp3->next)
			cout<<"--------------Niti u obicnoj listi: "<<temp3->pcb->id<<endl;

		for(Node* temp4 = System::timeblocked_list->head; temp4 != nullptr; temp4 = temp4->next)
			if(temp4 != nullptr)
			cout<<"--------------Niti u vremenskoj listi: "<<temp4->pcb->id<<endl;
	}
	unlock;
	return;
}

void PCBList::unsort_by_time(){

	lock;

	for(Node* temp = head; temp->next != nullptr; temp = temp->next){
		if(temp->next != nullptr)
		temp->next->pcb->waiting_time += temp->pcb->waiting_time;
	}

	unlock;

};

void PCBList::sort_by_time(){

	lock;

	for(Node* temp = tail; temp->prev != nullptr; temp = temp->prev){
		if(temp->prev != nullptr)
		temp->pcb->waiting_time -= temp->prev->pcb->waiting_time;
	}

	unlock;

};

void PCBList::decWaitVal(){
	lock;
	if(this->head != nullptr && (--this->head->pcb->waiting_time) <= 0) {
		this->pop_from_time_list();
	}
	unlock;
};
