/*
 * idle.h
 *
 *  Created on: Aug 24, 2019
 *      Author: OS1
 */

#ifndef _IDLE_H_
#define _IDLE_H_

#include "thread.h"
#include "pcb.h"

class Thread;

class Idle : public Thread {
public:
	Idle(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	void start();
protected:
	void run();
};



#endif /* IDLE_H_ */
