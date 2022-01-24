#include "../H/System.h"
#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"
#include "../H/Node.h"
void userMain(){

   lock;

   for(int s = 0; s < 10; s++){
      System::global_list->push_first((new ThreadA())->getMyPCB());
      System::global_list->head->pcb->start();
   }

   Thread* main = new Thread(new PCB(nullptr,4096,20));
   System::running = main->myPCB;
   System::timer_tics_cnt = main->getMyPCB()->kvant;

   System::global_list->push_first(main->getMyPCB());


   unlock;

   for (int i = 0; i < 50; ++i) {
      lock;
      cout<<"main thread = "<<i<<endl;
      unlock;
      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);
   }

   lock;
      for(Node* temp = System::global_list->head; temp != nullptr; temp = temp->next){
    	  if(temp->pcb->id != main->getMyPCB()->id && temp->pcb->state != PCB::FINISHED){
    		  temp->pcb->getMyThread()->waitToComplete();
    		  //Relativno je sve ok, samo ne radi promena konteksta za main nit iz nekog razloga
    		  for (int i = 0; i < 10; ++i){
				lock;
				cout<<"main thread = "<<i<<endl;
				unlock;
    		  }
    	  }
      }
   unlock;


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


