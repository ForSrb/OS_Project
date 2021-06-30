/*
 * pcb.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: OS1
 */

#include "pcb.h"
#include "idle.h"
#include "queue.h"
#include "schedule.h"
#include "thread.h"
#include "system.h"
#include <iostream.h>
#include <dos.h>

class Thread;
class Idle;

Idle* PCB::idleThread = 0;
volatile PCB* PCB::running = 0;
ID PCB::pos_id = 0;
const unsigned PCB::NEW = 0;
const unsigned PCB::READY = 1;
const unsigned PCB::BLOCKED = 2;
const unsigned PCB::FINISHED = 3;
Queue* PCB::pcb_queue = new Queue();



void PCB::wrapper() {
	PCB::running->myThread->run();
	lock
	PCB::running->status = PCB::FINISHED;
	Elem* temp = PCB::running->waitQueue->first;
	while(temp != 0) {
		temp = temp->next;
		PCB* pcb = PCB::running->waitQueue->take();
		pcb->status = PCB::READY;
		Scheduler::put(pcb);
	}
	temp = 0;
	PCB::running->waitQueue->first = 0;
	unlock
	dispatch();
}

void  PCB::createStack() {
	if(pcbStackSize > 65535) pcbStackSize = 65535;
	pcbStackSize /= sizeof(unsigned);
	stack = new unsigned[pcbStackSize];

	stack[pcbStackSize - 1] = 0x200; // PSW

#ifndef BCC_BLOCK_IGNORE

	stack[pcbStackSize - 2] = FP_SEG(PCB::wrapper);
	stack[pcbStackSize - 3] = FP_OFF(PCB::wrapper); // PC (ukazuje na funkciju wrapper koja ce pozivati run niti

	this->ss = FP_SEG(stack + pcbStackSize - 12);
	this->sp = FP_OFF(stack + pcbStackSize - 12); // izmedju -3 i -12 se nalazi konteksti niti (ax,bx...bp)

	this->bp = this->sp;

#endif
}

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice) {
	status = PCB::NEW;
	id = pos_id++;
	myThread = thread;
	waitQueue = new Queue();
	this->timeSlice = timeSlice;
	pcbStackSize = stackSize;
	stack = 0;
	mySemaphore = 0;
	sleepTime = 0;
	//stavili smo id PCB-a, dodelili mu odgovarajucu nit, dali mu vreme koriscenja procesora i formirali stek i pocetni kontekst

	PCB::pcb_queue->put(this);

	//stavimo nit, tj. PCB u neki red svih niti, tj. PCB-ova ( trebace nam zbog nekih metoda u Thread klasi...)
}

PCB::~PCB() {
	PCB::pcb_queue->remove(this);
	delete waitQueue;
	delete stack;
}

PCB* PCB::getPCB(ID id) {
	return PCB::pcb_queue->get(id);
}

void PCB::inicialize() {
	Thread* loading = new Thread();
	PCB::running = PCB::getPCB(loading->getId());
	PCB::running->status = PCB::READY;
	PCB::idleThread = new Idle();
	PCB::idleThread->start();
}



