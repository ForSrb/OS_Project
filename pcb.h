/*
 * pcb.h
 *
 *  Created on: Aug 18, 2019
 *      Author: OS1
 */

#ifndef _PCB_H_
#define _PCB_H_
#include "thread.h"
#include "queue.h"
#include "idle.h"
#include "kernsem.h"

class Thread;
class Queue;
class Idle;
class KernelSem;


class PCB {
public:
	static ID pos_id;
	ID id;
	unsigned* stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	volatile unsigned int status;
	StackSize pcbStackSize;
	Time timeSlice;

	volatile Time sleepTime;         // treba nam ovaj clan za semafore i listu uspavljenih niti
	KernelSem* mySemaphore;

	Queue* waitQueue;
	Thread* myThread;

	static const unsigned NEW;
	static const unsigned READY;
	static const unsigned BLOCKED;
	static const unsigned FINISHED;

	friend class Thread;
	friend class KernelSem;
	friend class Queue;
	friend class System;


	PCB(Thread* thread, StackSize stackSize, Time timeSlice);
	~PCB();

	void createStack();

	static volatile PCB* running;
	static Idle* idleThread;
	static Queue* pcb_queue;

	static void inicialize();

	static PCB* getPCB(ID id);

	static void wrapper();

};



#endif /* PCB_H_ */
