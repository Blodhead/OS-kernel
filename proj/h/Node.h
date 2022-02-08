#ifndef H_ELEMENT_
#define H_ELEMENT_
#include "Util.h"
#include "PCB.h"

class Node{

public:
   PCB* pcb;
   Node* next,* prev;

   Node(PCB* pcb_):pcb(pcb_){
      prev = next = nullptr;
   }

   ~Node(){

	   pcb = nullptr;

   }

};



#endif
