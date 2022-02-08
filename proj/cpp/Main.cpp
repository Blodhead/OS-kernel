#include "../H/System.h"
#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Schedule.h"
#include "../H/Operator.h"
#include "../H/PCBList.h"
#include "../H/Node.h"
void userMain(){
	cout<<"New created objects: " << System::couter<<endl;
//17
   for(int s = 0; s < 10; s++){
	   new ThreadA();
   }
	cout<<"New created objects: " << System::couter<<endl;
//77
   unlock;
   for (int i = 0; i < 30; ++i) {
      lock;
      cout<<"main thread = "<<i<<endl;
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
	cout<<"New created objects: " << System::couter<<endl;//9
	System::initialize();
	//67
	userMain();
	System::restore();
	cout<<"New created objects: " << System::couter<<endl;//19
	return 0;
};


