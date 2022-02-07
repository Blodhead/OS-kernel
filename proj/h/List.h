#ifndef H_LIST_H_
#define H_LIST_H_

#include "Util.h"
#include "Node.h"

class List{

public:
   List();
   ~List();

   //Shared methods
   mybool isEmpty();
   Node* pop_first();

   //Regular list methods
   Node* pop_last();
   Node* pop_by_id(ID);

   void push_last(PCB*);
   void push_first(PCB*);

   Node* seek_by_id(ID);

   Node *head, *tail;

};



#endif /* H_LIST_H_ */
