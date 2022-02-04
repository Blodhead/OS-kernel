#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Util.h"

class PCBList;
class PCB;
class System{

private:

   static IntRoutine old_route, new_route;

public:

   static PCBList *global_list, *blocked_list, *timeblocked_list;

   friend class Thread;

   static volatile PCB* running;
   static volatile PCB* idle;
   static PCB* main;
   static mybool content_switch;
   static volatile Time timer_tics_cnt;
   static void initialize();
   static void restore();
   static void interrupt timer(...);
   static void interrupt switch_context(...);

};



#endif
