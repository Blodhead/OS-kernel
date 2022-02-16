#ifndef H_EVENT_H_
#define H_EVENT_H_
#include "IVTEntry.h"

#define PREPAREENTRY(No,flag)\
	void interrupt intr##No(...){\
	    IVTEntry::array[No]->signal();\
		if(flag){\
			IVTEntry::array[No]->old_event_route();\
		}\
    }\
    IVTEntry* IVTEntry##No = new IVTEntry(No,&intr##No);

typedef unsigned char IVTNo;
class KernelEv;

class Event {
	public:
		Event (IVTNo ivtNo);
		~Event ();

		void wait ();

	protected:

		friend class KernelEv;

		void signal(); // can call KernelEv private: KernelEv* myImpl;
		KernelEv* getMyKernelEvent();
	private:
		KernelEv* myImpl;
};




#endif /* H_EVENT_H_ */
