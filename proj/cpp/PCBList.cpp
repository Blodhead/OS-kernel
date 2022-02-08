#include "../h/PCBList.h"
#include "../h/System.h"
#include "../h/Thread.h"
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
}//missing

void PCBList::push_in_time_list(PCB* pcb){

	lock;

	if (this->isEmpty()) {
		this->push_first(pcb);
		unlock;
		return;
	}

	this->unsort_by_time();

	for(Node* temp = head; temp != nullptr; temp = temp->next){

		if((temp->pcb->kvant) > (pcb->kvant)){

			Node* left = temp->prev, *right = temp;

			temp = new Node(pcb);

			if(left != nullptr)
				left->next = temp;

				right->prev = temp;

			temp->prev = left;
			temp->next = right;

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

void PCBList::unsort_by_time(){

	lock;

	for(Node* temp = head; temp->next != nullptr; temp = temp->next){
		temp->next->pcb->kvant += temp->pcb->kvant;
	}

	unlock;

};

void PCBList::sort_by_time(){

	lock;

	for(Node* temp = tail; temp->prev != nullptr; temp = temp->prev){
		temp->pcb->kvant -= temp->prev->pcb->kvant;
	}

	unlock;

};
