#include <iostream.h>
#include <dos.h>
#include "../H/System.h"
#include "../H/PCB.h"
#include "../H/ThreadA.h"
#include "../H/Thread.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"


unsigned tsp;
unsigned tss;
unsigned tbp;

IntRoutine System::new_route = 0;
IntRoutine System::old_route = getvect(0x08);

volatile Time System::timer_tics_cnt = 0;
mybool System::content_switch = false;
PCB* System::idleThread = nullptr;


volatile PCB* System::running = nullptr;

//PCB_list* System::blockedPCBs = nullptr;
volatile PCB* running = nullptr;

void System::initialize(){

   cout<<"System initialize"<<endl;

   setvect(0x08,System::timer);
   setvect(0x60,System::old_route);

};

void System::restore(){

   cout<<"System restore"<<endl;
   setvect(0x08,System::old_route);

   lock;

   System::delete_blocked_list();
   System::delete_list();
   old_route = nullptr, new_route = nullptr;
   idleThread = nullptr;
   old_route = nullptr, new_route = nullptr;
   idleThread = nullptr;
   head = nullptr;
   tail = nullptr;
   blocked_head = nullptr;
   blocked_tail = nullptr;

   unlock;
};

void interrupt System::switch_context(...){

   static volatile PCB *current, *next;

      current = running;

      if(current)
      if(current->state != PCB::FINISHED && current->state != PCB::BLOCKED){

         asm {
            mov tsp, sp
            mov tss, ss
            mov tbp, bp
         }

         running->sp = tsp;
         running->ss = tss;
         running->bp = tbp;
      }

      next = Scheduler::get();

      if(next == nullptr){////////////////////
         next = System::blocked_head->pcb;
      }///////////////////////////////////Empty

      if(next){
         tsp = next->sp;
         tss = next->ss;
         tbp = next->sp;

         asm {
            mov sp, tsp
            mov ss, tss
            mov bp, tbp
         }


      if(current->state != PCB::FINISHED && current->state != PCB::BLOCKED)
      Scheduler::put((PCB*)current);
      }
      running = next;
      running->state = PCB::RUNNING;
      timer_tics_cnt = running->kvant;
      content_switch = false;

};

void interrupt System::timer(...){

   System::old_route();
   if(System::content_switch == false) System::timer_tics_cnt--;
   if(System::timer_tics_cnt == 0 || System::content_switch == true){
      System::switch_context();
   }
};

System::List* System::head = nullptr;
System::List* System::tail = nullptr;

PCB* System::get_PCB_from_List(ID _id){
      for(List* temp = System::head; temp->next != nullptr; temp = temp->next)
         if(temp->pcb->id == _id) return temp->pcb;
      return nullptr;
};

void System::put_PCB_to_list(PCB* _pcb){

    if(System::head == nullptr){
       System::head = System::tail = new List();
       System::head->pcb = _pcb;
        return;
     }else{
        System::tail->next = new List();
        System::tail->next->prev = System::tail;
        System::tail = System::tail->next;
        System::tail->pcb = _pcb;
     }
    return;
   };

void System::delete_list(){
   for(; System::tail != nullptr; System::head = System::head->next){
    if(System::head->prev == nullptr) continue;
    if(System::tail->prev == System::tail->next == nullptr) System::tail = nullptr;
    delete(System::head->prev);
   }
   System::head = nullptr;
};


System::List* System::blocked_head = nullptr;
System::List* System::blocked_tail = nullptr;

PCB* System::get_PCB_from_blodked_List(ID _id){
      for(List* temp = System::blocked_head; temp->next != nullptr; temp = temp->next)
         if(temp->pcb->id == _id) return temp->pcb;
      return nullptr;
};

void System::put_PCB_to_blocked_list(PCB* _pcb){

    if(System::blocked_head == nullptr){
       System::blocked_head = System::blocked_tail = new List();
       System::blocked_head->pcb = _pcb;
        return;
     }else{
        System::blocked_tail->next = new List();
        System::blocked_tail->next->prev = System::blocked_tail;
        System::blocked_tail = System::blocked_tail->next;
        System::blocked_tail->pcb = _pcb;
     }
    return;
   };

void System::delete_blocked_list(){
   for(; System::blocked_tail != nullptr; System::blocked_head = System::blocked_head->next){
    if(System::blocked_head->prev == nullptr) continue;
    if(System::blocked_tail->prev == System::blocked_tail->next == nullptr) System::blocked_tail = nullptr;
    delete(System::blocked_head->prev);
   }
   System::blocked_head = nullptr;
};

