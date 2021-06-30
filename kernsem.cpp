/*
 * kernsem.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: OS1
 */


#include "kernsem.h"
#include "semaphor.h"
#include "system.h"
#include "thread.h"
#include "pcb.h"
#include "schedule.h"



Queue* KernelSem::sleepQueue = new Queue();

KernelSem::KernelSem(Semaphore* semaphore, int init) {
	this->mySemaphore = semaphore;
	this->val = init;
	this->numOfBlockedThreads = 0;
	this->blockQueue = new Queue();
}

KernelSem::~KernelSem() {
	delete this->blockQueue;
}

int KernelSem::signal(int n) {
	if(n == 0) {
	 	if(val++ < 0)
	 		deblock();
	 	return 0;
	 }

	 if(n > 0) {
		val+=n;
	 	if(n > numOfBlockedThreads)
	 		n = numOfBlockedThreads;
	 	for(int i=0; i<n; i++)
	 		deblock();
	 	return n;
	 }

	 return n;
}

int KernelSem::wait(Time maxTimeToWait) {

	if(maxTimeToWait > 0) {
		val--;
		numOfBlockedThreads++;
		block(maxTimeToWait);
		unlock
		dispatch();
		lock
		if(PCB::running->sleepTime > 0) return 1; // ovo znaci da je nit odblokirana preko signala
		else return 0; // ovo znaci da je nit odblokirana nakon sto je odspavala svoje vreme sto znaci da treba opet da se blokira
	}

	if(maxTimeToWait == 0) {
		if(--val < 0) {
			numOfBlockedThreads++;
			block(maxTimeToWait);
			unlock
			dispatch();
			lock
			return 1;
		}
	}

	return 1;
}


void KernelSem::block(Time maxTimeToWait) {
	PCB::running->sleepTime = maxTimeToWait;
	PCB::running->mySemaphore = this;
	PCB::running->status = PCB::BLOCKED;
	blockQueue->put((PCB*)PCB::running);
	if(maxTimeToWait > 0) KernelSem::sleepQueue->put((PCB*)PCB::running);
}

void KernelSem::deblock() {
	numOfBlockedThreads--;
	PCB* pcb = blockQueue->take();
	pcb->status = PCB::READY;
	KernelSem::sleepQueue->remove(pcb);
	Scheduler::put(pcb);
}


void KernelSem::sleepProcess() {
	if(sleepQueue->first == 0) return;
	Elem* temp = sleepQueue->first;
	Elem* before = 0;
	while(temp != 0) {
		temp->pcb->sleepTime--;
		before = temp;
		temp = temp->next;
		if(before->pcb->sleepTime == 0) {
			(before->pcb)->status = PCB::READY;
			((before->pcb)->mySemaphore)->numOfBlockedThreads--;
			((before->pcb)->mySemaphore)->val++;
			Scheduler::put(before->pcb);
			(((before->pcb)->mySemaphore)->blockQueue)->remove(before->pcb);
			sleepQueue->remove(before->pcb);
		}
	}
	temp = 0;
	before = 0;
}
