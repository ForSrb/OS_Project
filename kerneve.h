/*
 * kerneve.h
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#ifndef _KERNEVE_H_
#define _KERNEVE_H_

#include "event.h"
#include "thread.h"
#include "pcb.h"

typedef unsigned char IVTNo;
class Event;
class Thread;

class KernelEv{
public:
	IVTNo ivtNo;
	Event* myEvent;
	Thread* owner;
	Thread* blocked;
	int value;

	KernelEv(IVTNo ivtNo, Event* event, PCB* pcb);
	~KernelEv();

	void wait();
	void signal();
};



#endif /* KERNEVE_H_ */
