/*
 * List.cpp
 *
 *  Created on: Dec 27, 2021
 *      Author: OS1
 */
#include "../H/List.h"

List::List(){
   head = tail = nullptr;
};

List::~List(){

	lock;
	Node* curr = head, *prev = nullptr;
	while(curr != nullptr){
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	head = tail = nullptr;

	unlock;
};

mybool List::isEmpty(){
   if(head == nullptr) return true;
   else return false;
};

Node* List::pop_first(){

	lock;

	if(isEmpty()) {
		unlock;
		return nullptr;
	}

	Node* temp = head;
	head = head->next;
	temp->next = nullptr;
	head->prev = nullptr;
	temp->prev = nullptr;

	if(head == nullptr) tail = head;

	unlock;

	return temp;
};

Node* List::pop_last(){

	lock;

	if(isEmpty()) {
		unlock;
		return nullptr;
	}

	Node* temp = tail;
	tail = tail->prev;
	tail->next = nullptr;
	temp->prev = nullptr;
	temp->next = nullptr;

	if(tail == nullptr) head = tail;

	unlock;

	return temp;
}

Node* List::pop_by_id(ID id){

	lock;

	if(this->head == nullptr) {
		unlock;
		return nullptr;
	}

   for(Node* temp = head; temp != nullptr; temp = temp->next)
      if(temp->pcb->id == id){

         Node *left = temp->prev, *right = temp->next;

         if(left != nullptr)
         left->next = right;
         else head = right;

         if(right != nullptr)
         right->prev = left;
         else tail = left;

         temp->next = temp->prev = nullptr;

         unlock;

         return temp;
      }

   unlock;

   return nullptr;
};

void List::push_last(PCB* el){

	lock;

   if(isEmpty()){
      head = new Node(el);
      tail = head;
   }else if(this->seek_by_id(el->id) == nullptr){
      tail->next = new Node(el);
      Node* temp = tail;
      tail = tail->next;
      tail->prev = temp;
   }

   unlock;

   return;
};

void List::push_first(PCB* el){

	lock;

   if(isEmpty()){
      head = new Node(el);
      tail = head;
   }else if(this->seek_by_id(el->id) == nullptr){
      head->prev = new Node(el);
      Node* temp = head;
      head = head->prev;
      head->next = temp;
   }
   /*
   if(this-> == System::timeblocked_list)
   cout<<"Thread with id: "<<this->head->pcb->id<<" pushed in to timed list!"<<endl;
   */
   unlock;

   return;
};

Node* List::seek_by_id(ID id){
	lock;

		if(isEmpty()) {
			unlock;
			return nullptr;
		}

	   for(Node* temp = head; temp != nullptr; temp = temp->next)
	      if(temp->pcb->id == id){
	         return temp;
	      }

	   unlock;

	   return nullptr;
}
