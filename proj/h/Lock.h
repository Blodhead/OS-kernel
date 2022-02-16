#ifndef LOCK_H_
#define LOCK_H_

class Lock{

public:

	static void lock();
	static void unlock();

	static int lock_cnt;

};

#endif
