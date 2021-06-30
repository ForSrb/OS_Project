/*
 * event.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */


#include "event.h"
#include "kerneve.h"
#include "system.h"
#include <iostream.h>
#include "pcb.h"

Event::Event(IVTNo ivtNo) {
	lock
	this->myImpl = new KernelEv(ivtNo,this,(PCB*)PCB::running);
	unlock
}

Event::~Event() {
	lock
	delete myImpl;
	unlock
}

void Event::wait() {
	lock
	myImpl->wait();
	unlock
}

void Event::signal() {
	myImpl->signal();
}

