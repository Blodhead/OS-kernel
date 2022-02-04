/*
 * Producer.h
 *
 *  Created on: Aug 14, 2021
 *      Author: OS1
 */

/*#ifndef CPP_PRODUCER_H_
#define CPP_PRODUCER_H_

#include "thread.h"

class Buffer;
class Data;

class Producer : public Thread {
public:
	Producer(Buffer* buf, int numOfItems) : myBuffer(buf), n(numOfItems) {}
	virtual ~Producer() {
		waitToComplete();
	}
protected:
	Data* produce();
	virtual void run();
private:
	int n;
	Buffer* myBuffer;
};
#endif /* CPP_PRODUCER_H_ */

