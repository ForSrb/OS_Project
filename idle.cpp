/*
 * idle.cpp
 *
 *  Created on: Aug 24, 2019
 *      Author: OS1
 */

#include <iostream.h>
#include "idle.h"
#include "thread.h"
#include "pcb.h"
#include "system.h"


Idle::Idle(StackSize stackSize, Time timeSlice) : Thread(stackSize,timeSlice) {}

void Idle::start() {
	lock
	myPCB->status = PCB::READY;
	myPCB->createStack();
	unlock
}

void Idle::run() {
	while(1) {
	}
}


