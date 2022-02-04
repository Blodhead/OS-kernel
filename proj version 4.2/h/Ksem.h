#ifndef H_KSEM_H_
#define H_KSEM_H_

class List;

typedef unsigned int Time;

class KernelSem {

public:
	//static PCBList timeblocked;
	KernelSem(int init = 1);
	virtual ~KernelSem ();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n = 0);
	int val () const;
	void exit(int i);
private:
	int value;
	List* blocked;

};


#endif /* H_KSEM_H_ */
