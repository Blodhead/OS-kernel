#include "../H/System.h"
#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"

void userMain(){

   lock;

   for(int s = 0; s < 100; s++){
      System::put_PCB_to_list((new ThreadA())->getMyPCB());
      System::tail->pcb->start();

   }


   Thread* main = new Thread(new PCB(nullptr,4096,20));
   System::running = main->myPCB;
   System::timer_tics_cnt = main->getMyPCB()->kvant;

   unlock;

   for (int i = 0; i < 130; ++i) {
      lock
      cout<<"main thread = "<<i<<endl;
      unlock
      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);
   }

   lock;
   ((PCB*)System::running)->getMyThread()->waitToComplete();
   unlock;

   while(System::running->state == PCB::BLOCKED){};

   lock;
   cout<<"Happy End"<<endl;
   unlock;
}

int main(){

   System::initialize();

   userMain();

   System::restore();

   return 0;
};


