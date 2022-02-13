#include <dos.h>
#include "../H/IVTEntry.h"
#include "../H/KEvent.h"

IVTEntry* IVTEntry::array[256];
IVTEntry::IVTEntry(IVTNo ivn,IntRoutine n):iv(ivn),new_event_route(n){

#ifndef BCC_BLOCK_IGNORE
	old_event_route = getvect(iv);
	setvect(iv,new_event_route);
#endif
	array[iv] = this;
	event = nullptr;
}
IVTEntry::~IVTEntry(){
	lock;
#ifndef BCC_BLOCK_IGNORE
	setvect(iv,old_event_route);
#endif
	old_event_route = nullptr;
	new_event_route = nullptr;
	event = nullptr;
	unlock;
}
void IVTEntry::signal(){event->signal();}
void IVTEntry::setevent(KernelEv* k){event=k;}
