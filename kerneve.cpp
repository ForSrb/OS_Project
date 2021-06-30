/*
 * kerneve.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */


#include "kerneve.h"
#include "event.h"
#include "system.h"
#include "Schedule.h"
#include <iostream.h>
#include "ivt.h"

class Scheduler;
class System;

KernelEv::KernelEv(IVTNo ivtNo, Event* event, PCB* pcb) {
	this->ivtNo = ivtNo;
	this->myEvent = event;
	this->owner = pcb->myThread;
	this->blocked = 0;
	this->value = 0;
	IVTEntry::IVTEntries[this->ivtNo]->myEvent = this;
}

KernelEv::~KernelEv() {
	this->myEvent = 0;
	this->owner = 0;
	this->blocked = 0;
	IVTEntry::IVTEntries[this->ivtNo]->myEvent = 0;
}

void KernelEv::wait() {
	if((PCB::running)->myThread == this->owner) {
		if(value == 0) {
			PCB::running->status = PCB::BLOCKED;
			blocked = (Thread*)(PCB::running->myThread);
			unlock
			dispatch();
			lock
			return;
		}

		else value = 0;
	}
}

void KernelEv::signal() {
	if(!value && blocked) {
		blocked = 0;
		PCB* pcb = PCB::getPCB(owner->getId());
		pcb->status = PCB::READY;
		Scheduler::put(pcb);
	}

	else value = 1;

}









