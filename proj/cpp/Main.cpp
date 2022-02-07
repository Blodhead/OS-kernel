#include "../H/System.h"
#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"
#include "../H/Node.h"
void userMain(){

   lock;

   cout<<"New created objects: " << System::couter<<endl;

   System::global_list->push_last((PCB*)System::main);
   System::global_list->push_last((PCB*)System::idle);

   for(int s = 0; s < 4; s++){
      System::global_list->push_last((new ThreadA())->getMyPCB());
      System::global_list->tail->pcb->start();
   }
   cout<<"New created objects: " << System::couter<<endl;//51
   unlock;
   for (int i = 0; i < 60; ++i) {
      lock;
      cout<<"main thread = "<<i<<endl;
      unlock;
      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);
   }
/*
   cout<<"New created objects: " << System::couter<<endl;

   System::main->state = PCB::BLOCKED;
   System::blocked_list->push_last(System::main);*/

   /*lock;
      for(Node* temp = System::global_list->head; temp != nullptr; temp = temp->next){
    	  if(temp->pcb->id != System::main->getMyPCB()->id && temp->pcb->state != PCB::FINISHED){
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
*/
   cout<<"New created objects: " << System::couter<<endl;//48
System::running->state = PCB::FINISHED;

dispatch();

}

int main(){
	cout<<"New created objects: " << System::couter<<endl;//17
	System::initialize();
	userMain();
//NE ULAZI SE U SISTEM RESTORE DOK SE NISU SVE NITI ZAVRSILE
	System::restore();
	cout<<"New created objects: " << System::couter<<endl;//19
	return 0;
};


