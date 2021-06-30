/*
 * semaphor.cpp
 *
 *  Created on: Aug 26, 2019
 *      Author: OS1
 */

#include "semaphor.h"
#include "system.h"
#include "kernsem.h"

Semaphore::Semaphore(int init) {
	lock
	myImpl = new KernelSem(this, init);
	unlock
}

Semaphore::~Semaphore() {
	lock
	delete myImpl;
	unlock
}

int Semaphore::signal(int n) {
	lock
	int a = myImpl->signal(n);
	unlock
	return a;
}

int Semaphore::wait(Time maxTimeToWait) {
	lock
	int a = myImpl->wait(maxTimeToWait);
	unlock
	return a;
}

int Semaphore::val() const {
	return myImpl->val;
}

