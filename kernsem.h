/*
 * kernsem.h
 *
 *  Created on: Aug 26, 2019
 *      Author: OS1
 */

#ifndef _KERNSEM_H_
#define _KERNSEM_H_

#include "semaphor.h"
#include "queue.h"

class Queue;
typedef unsigned int Time;

class KernelSem{
public:
	int val;
	int numOfBlockedThreads;
	Semaphore* mySemaphore;
	Queue* blockQueue;

	static Queue* sleepQueue;

	KernelSem(Semaphore* semaphore, int init);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n);

	static void sleepProcess();

	friend class Queue;
	friend class Semaphore;

protected:
	void block(Time maxTimeToWait);
	void deblock();
};


#endif /* KERNSEM_H_ */
