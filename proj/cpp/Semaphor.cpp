#include <iostream.h>
#include "../H/Semaphor.h"
#include "../H/Util.h"
#include "../H/Ksem.h"
#include "../H/Lock.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init);
};

Semaphore::~Semaphore(){
	Lock::lock();

	delete myImpl;
	myImpl = nullptr;

	Lock::unlock();
};

int Semaphore::wait(Time maxTimetoWait){
	return myImpl->wait(maxTimetoWait);
};

int Semaphore::signal(int n){
	return myImpl->signal(n);
};

int Semaphore::val() const{
	return myImpl->getVal();
};


