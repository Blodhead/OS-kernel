#include "../H/Semaphor.h"
#include "../H/Util.h"
#include "../H/Ksem.h"
#include <iostream.h>

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init);
};

Semaphore::~Semaphore(){
	lock;

	delete myImpl;
	myImpl = nullptr;

	unlock;
};

int Semaphore::wait(Time maxTimetoWait){
	int x = myImpl->wait(maxTimetoWait);
	cout<<"";
	return x;

};

int Semaphore::signal(int n){
	return myImpl->signal(n);
};

int Semaphore::val() const{
	return myImpl->getVal();
};


