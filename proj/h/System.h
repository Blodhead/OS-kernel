#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Util.h"

class PCBList;
class PCB;
class System{

private:

   static IntRoutine old_route, new_route;
   static PCB* idleThread;


public:

   static PCBList *global_list, *blocked_list, *timeblocked_list;

   friend class Thread;
   static volatile PCB* running;
   static mybool content_switch;
   static volatile Time timer_tics_cnt;
   static void initialize();
   static void restore();
   static void interrupt timer(...);
   static void interrupt switch_context(...);
/*
   //List operations:
   static void delete_list();
   static void put_PCB_to_list(PCB*);
   static PCB* get_PCB_from_List(ID);

   //List operations:
   static void delete_blocked_list();
   static void put_PCB_to_blocked_list(PCB*);
   static PCB* get_PCB_from_blodked_List(ID);
*/
};



#endif