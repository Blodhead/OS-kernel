#include "../H/Semaphor.h"
#include "../H/Util.h"
#include "../H/Ksem.h"

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
	return myImpl->wait(maxTimetoWait);
};

int Semaphore::signal(int n){
	return myImpl->signal(n);
};

int Semaphore::val() const{
	return myImpl->val();
};


