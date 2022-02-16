#ifndef H_IVTENTRY_H_
#define H_IVTENTRY_H_

#include "Util.h"

class KernelEv;


class IVTEntry{
public:
	IntRoutine old_event_route;
	IntRoutine new_event_route;
	KernelEv* event;
	IVTNo iv;
	static IVTEntry* array[256];
	IVTEntry(IVTNo ivn,IntRoutine n);
	void signal();
	void setevent(KernelEv* k);
	~IVTEntry();



};



#endif /* H_IVTENTRY_H_ */
