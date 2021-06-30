/*
 * semaphor.h
 *
 *  Created on: Aug 26, 2019
 *      Author: OS1
 */

#ifndef _SEMAPHOR_H_
#define _SEMAPHOR_H_

typedef unsigned int Time;

class KernelSem;

class Semaphore {
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();

	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n = 0);

	int val() const; // Returns the current value of the semaphore

private:
	KernelSem* myImpl;
};

#endif /* SEMAPHOR_H_ */