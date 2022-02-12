#include <iostream.h>
#include "../H/Event.h"
#include "../H/KEvent.h"
#include "../H/IVTEntry.h"
#include "../H/System.h"

Event::Event(IVTNo ivtNo):myImpl(new KernelEv(ivtNo,(PCB*)System::running)){
	IVTEntry::array[ivtNo]->setevent(myImpl);
}

void Event::wait(){
	lock;
	myImpl->wait();
	unlock;
}

void Event::signal(){
	lock;
	myImpl->signal();
	unlock;
}

Event::~Event(){
	lock;
	delete IVTEntry::array[myImpl->getiv()];
	IVTEntry::array[myImpl->getiv()]=nullptr;
	delete myImpl;
	myImpl=nullptr;
	unlock;

}
