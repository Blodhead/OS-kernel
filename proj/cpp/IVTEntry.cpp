#include <dos.h>
#include "../H/IVTEntry.h"
#include "../H/KEvent.h"

IVTEntry* IVTEntry::array[256];
IVTEntry::IVTEntry(IVTNo ivn,IntRoutine n):iv(ivn),newx(n){

#ifndef BCC_BLOCK_IGNORE
	old = getvect(iv);
	setvect(iv,newx);
#endif
	event = nullptr;
	array[iv]=this;
}
IVTEntry::~IVTEntry(){
	lock;
#ifndef BCC_BLOCK_IGNORE
	setvect(iv,old);
#endif
	old=nullptr;
	newx=nullptr;
	event=nullptr;
	unlock;
}
void IVTEntry::signal(){event->signal();}
void IVTEntry::setevent(KernelEv* k){event=k;}
