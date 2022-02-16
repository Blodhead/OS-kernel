#ifndef H_KSEM_H_
#define H_KSEM_H_

class List;

typedef unsigned int Time;
class PCBList;

class KernelSem {

public:
	//static PCBList timeblocked;
	KernelSem(int init = 1);
	virtual ~KernelSem ();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n = 0);
	int getVal () const;
	void incVal();
	void exit(int i);
	PCBList* blocked;
private:
	int value;

};


#endif /* H_KSEM_H_ */
