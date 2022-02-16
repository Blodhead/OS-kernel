#include "../H/Lock.h"
#include "../H/Thread.h"
#include "../H/System.h"

int Lock::lock_cnt = 0;

void Lock::lock(){
	asm cli;
	Lock::lock_cnt--;
	asm sti;
}

void Lock::unlock(){
	asm cli;
	Lock::lock_cnt++;
	if(Lock::lock_cnt >= 0 && System::content_switch == true){
		asm sti;
		dispatch();
	}
	if(Lock::lock_cnt > 0) Lock::lock_cnt = 0;
	asm sti;
}


