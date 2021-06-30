#ifndef _THREAD_H_
#define _THREAD_H_



typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB;
class KernelEv;
// Kernel's implementation of a user's thread

class Thread {

public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);
	virtual void pisi() {}

protected:
	friend class PCB;
	friend class Idle;
	friend class System;
	friend class KernelEv;

	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
};

void dispatch();

#endif
