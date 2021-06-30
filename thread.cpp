/*
 * thread.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: OS1
 */

#include "pcb.h"
#include "thread.h"
#include "schedule.h"
#include "system.h"
#include <iostream.h>
#include <dos.h>


class Scheduler;
class System;


Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock
	myPCB = new PCB(this, stackSize, timeSlice);
	unlock
}

Thread::~Thread() {
	lock
	delete myPCB;
	unlock
}

void Thread::start() {
	lock
	if(myPCB->status == PCB::READY) {
		unlock
		return;
	}
	myPCB->createStack();
	myPCB->status = PCB::READY;
	Scheduler::put(myPCB);
	unlock
}

void Thread::waitToComplete() {
	lock
	if(this == (Thread *)PCB::idleThread)  {
		unlock
		return;
	}

	if(myPCB->status == PCB::FINISHED) {
		unlock;
		return;
	}

	if(myPCB == PCB::getPCB(0)) {
		unlock;
		return;
	}

	myPCB->waitQueue->put((PCB*)PCB::running);
	PCB::running->status = PCB::BLOCKED;
	unlock
	dispatch();

}

ID Thread::getId() {
	return myPCB->id;
}

ID Thread::getRunningId() {
	return PCB::running->id;
}

Thread* Thread::getThreadById(ID id) {
	return PCB::getPCB(id)->myThread;
}

void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
#endif
	wanted_change_of_context = 1;
	System::timer();
#ifndef BCC_BLOCK_IGNORE
	asm popf;
#endif
}





