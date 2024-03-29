#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "Util.h"

class PCBList;
class PCB;
class Semaphore;

class System{

private:

   static IntRoutine old_route, new_route;

public:

   friend class Thread;

   static volatile Time timer_tics_cnt;
   static volatile PCB* running;
   static volatile PCB* idle;
   static PCBList *global_list, *timeblocked_list;
   static PCB* main;
   static mybool content_switch;
   static Semaphore* semaphore;
   static int couter;
   static int num_of_threads;

   static void initialize();
   static void restore();
   static void interrupt timer(...);
   static void interrupt switch_context(...);

};



#endif
