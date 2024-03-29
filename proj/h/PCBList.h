#ifndef H_PCBLIST_H_
#define H_PCBLIST_H_

#include "List.h"

class PCBList: public List{
public:

	//List<Thread>* lista;

	PCBList();
	virtual ~PCBList();

	//Timed list methods
	void push_in_time_list(PCB* pcb);
	void pop_from_time_list(int id = -1);
	void decWaitVal();

private:

	void sort_by_time();
	void unsort_by_time();
};


#endif /* H_PCBLIST_H_ */
