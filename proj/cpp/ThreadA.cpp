/*
 * ThreadA.cpp
 *
 *  Created on: Aug 13, 2021
 *      Author: OS1
 */

#include "../H/ThreadA.h"
#include "../H/PCB.h"
#include "../H/Node.h"
#include "../H/PCBList.h"
#include "../H/Schedule.h"
#include "../H/Semaphor.h"

ThreadA::ThreadA(StackSize stackSize, Time timeSlice):Thread(stackSize,timeSlice) {//CHECKED
	// TODO Auto-generated constructor stub

}

ThreadA::~ThreadA() {//
	// TODO Auto-generated destructor stub
}

void ThreadA::run(){

/*
   for (int i = 0; i < 10; ++i) {
      lock
      cout<< *(this->getMyPCB()) <<i<<endl;
      unlock

      for (int k = 0; k<10000; ++k)
         for (int j = 0; j <30000; ++j);

   }

   lock;
*/


   /*
   if(this->getId() == 18) System::semaphore->wait(0);
   if(this->getId() == 17) System::semaphore->wait(5000);
   if(this->getId() == 16) System::semaphore->wait(2000);
   if(this->getId() == 16) System::semaphore->wait(1000);
   if(this->getId() == 15) System::semaphore->wait(10);
   if(this->getId() == 15) System::semaphore->signal(3);
   if(this->getId() == 8) System::semaphore->wait(50);
*/
 /*  for (int m = 10; m < 20; ++m) {
       lock
       cout<< *(this->getMyPCB()) <<m<<endl;
       unlock

       for (int z = 0; z<10000; ++z)
          for (int b = 0; b <30000; ++b);

    }

*/
/*
   if(this->getId() == 2){//los zavrsetak, kasnije nadoraditi
	   System::main->state = PCB::READY;
	   //System::blocked_list->pop_by_id(System::main->id);
	   Scheduler::put(System::main);
   }
*/
	/*
   unlock;

   exitThread();
*/
}
