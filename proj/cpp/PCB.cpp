#include "../H/PCB.h"
#include "../H/System.h"
#include "../H/Schedule.h"
#include "../H/Thread.h"
#include "../H/Operator.h"
#include "../H/KSem.h"
#include "../H/PCBList.h"

ID PCB::idd = 0;

   PCB::PCB(Runnable run,StackSize stackSize, Time timeSlice){//CHECKED

      if(run){
         lock;

         stackSize/=sizeof(unsigned);
         //ZA 8086 ARHITEKUTURU MOZE MAX 65535B, A MI KORISTION 4096

         this->ss = 0; //da ne prijavljuje warrning
         stack = new unsigned[stackSize];
         stack_size = stackSize;

         stack[stackSize - 1] = FP_SEG(myThread);//Parametri funkcije
         stack[stackSize - 2] = FP_OFF(myThread);//Parametri funkcije
         //-3 i -4 su segment i offset funkcije callback, ona se poziva posel Thread::wrapper
         stack[stackSize - 5] = 0x200; //I fleg enable-ovan u PSW-u
         stack[stackSize - 6] = FP_SEG(PCB::wrapper); //segment CS
         stack[stackSize - 7] = FP_OFF(PCB::wrapper); //offset  IP
         //-8 do -15 su ostali pomocni registri ax,bx,cx...
         this->ss = FP_SEG(stack + stackSize - 16); //na -16 je bp
         this->sp = FP_OFF(stack + stackSize - 16);
         this->bp = sp; //PRAVILO! BP SE NA POCETKU STAVLJA DE JE JEDNAK SP!

         //DODATNI FLEGOVI I PROMENJIVE
         this->state = NOT_STARTED;
         this->kvant = timeSlice;
         this->myThread = myThread;
         this->mySem = new KernelSem();
         this->myJoin = new PCBList();
         this->myJoinNum = 0;
         this->id = this->idd++;
         this->run = run;

         unlock;
      }else{
         this->id = idd++;
         bp = sp = ss = 0;
         this->stack_size = 0;
         this->state = PCB::RUNNING;
         this->kvant = timeSlice;
         this->mySem = new KernelSem();
         this->myJoin = new PCBList();
         this->myJoinNum = 0;
         this->run = nullptr;
         this->stack = nullptr;   // ako se pravi PCB main thread-a, ne treba da mu mi alociramo i dealociramo stek

      }
   };

   void PCB::initMainThread(){
	   System::main = new PCB(nullptr,4096,20);
	   //System::main = (new Thread())->myPCB;
	   System::running = System::main;
   }
   void PCB::initIdleThread(){
	class IdleThread:Thread{
	public:
		IdleThread(StackSize stackSize = defaultStackSize,Time timeSlice = defaultTimeSlice):Thread(stackSize,timeSlice){}
		void run(){
			while(1);}
		~IdleThread(){waitToComplete();}
	};

	//System::idle = (new IdleThread())->myPCB;
	System::idle = new PCB(nullptr,4096,1);
	System::idle->state = PCB::RUNNING;
   };

   Time PCB::getKvant(){//FINISHED
      return this->kvant;
   };

   void PCB::start(){//CHECKED
      if(this->state == NOT_STARTED){

         this->state = READY;
         Scheduler::put((PCB*)this);

      }
   };

   Thread* PCB::getMyThread(){//FINISHED
	   return this->myThread;
   }

   void PCB::waitToComplete(){
	   lock;
	   if(this->state != PCB::FINISHED && this->state != PCB::NOT_STARTED && this->id != System::main->id && this->id != System::idle->id){

		   this->myJoinNum++;
		   ((PCB*)System::running)->state = PCB::BLOCKED;
		   this->myJoin->push_last((PCB*)System::running);
		   unlock;
		   dispatch();
	   }
	   unlock;
	   return;

   }

   PCB::~PCB(){
	if(PCB::FINISHED != this->state){
		System::global_list->pop_by_id(this->id);

		if(stack != nullptr){
			delete[] stack;
			stack=nullptr;
		}

	mySem = nullptr;
	}

	if(myJoin != nullptr) delete myJoin;
	if(mySem != nullptr) delete mySem;
	myJoin = nullptr;
	mySem = nullptr;

   };

   void PCB::wrapper(){//CHECKED
   	System::running->myThread->run();
   }

   ostream& operator<<(ostream& os,const PCB &pcb){
      lock;
      os<<"PCB  "<< pcb.id <<" "<< System::timer_tics_cnt << "|";
      unlock;
      return os;
   }



