#include "../H/System.h"
#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"
#include "../H/Node.h"
void userMain(){
//17
   for(int s = 0; s < 20 ; s++){
	   new ThreadA();
   }
	cout<<System::num_of_threads<<endl;
//77
   unlock;
   for (int i = 0; i < 50; ++i) {
      lock;
      cout<<"main thread = "<<i << " | " << System::timer_tics_cnt<<endl;
      unlock;
      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);
   }


  /* System::blocked_list->push_last(System::main);

   lock;
      for(Node* temp = System::global_list->head; temp != nullptr; temp = temp->next){
    	  if(temp->pcb->id != System::main->id && temp->pcb->state != PCB::FINISHED){
    		  temp->pcb->getMyThread()->waitToComplete();
    		  }
    	  }
      }
   unlock;
*/
};

int main(){
//9
	System::initialize();
//17

	userMain();
//67
	System::restore();
//9
	return 0;
};


