#include <iostream.h>
#include "../H/Event.h"
#include "../H/KEvent.h"
#include "../H/IVTEntry.h"
#include "../H/System.h"
#include "../H/Lock.h"

Event::Event(IVTNo ivtNo):myImpl(new KernelEv(ivtNo,(PCB*)System::running)){
	IVTEntry::array[ivtNo]->setevent(myImpl);
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}

Event::~Event(){
	Lock::lock();
	delete IVTEntry::array[myImpl->getiv()];
	IVTEntry::array[myImpl->getiv()] = nullptr;
	delete myImpl;
	myImpl = nullptr;
	Lock::unlock();
}

KernelEv* Event::getMyKernelEvent(){
	return this->myImpl;
}
