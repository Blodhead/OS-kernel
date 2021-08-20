#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Util.h"

class PCB;

;

struct PCB_list
{
	PCB_list(PCB* element):pcb(element){
		next = prev = nullptr;
	}

	PCB* pcb;
	PCB_list*next,*prev;
};

class System{
public:

   struct List{

      PCB* pcb;
      List *prev, *next;
      List(){
         prev = next = nullptr;
         pcb = nullptr;
      }
   };
   static List *head, *tail;
   static List *blocked_head, *blocked_tail;

private:

   static IntRoutine old_route, new_route;
   static PCB* idleThread;


public:
   friend class Thread;
   static volatile PCB* running;
   static mybool content_switch;
   static volatile Time timer_tics_cnt;
   static void initialize();
   static void restore();
   static void interrupt timer(...);
   static void interrupt switch_context(...);

   //List operations:
   static void delete_list();
   static void put_PCB_to_list(PCB*);
   static PCB* get_PCB_from_List(ID);

   //List operations:
   static void delete_blocked_list();
   static void put_PCB_to_blocked_list(PCB*);
   static PCB* get_PCB_from_blodked_List(ID);

};



#endif
