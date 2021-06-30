/*
 * queue.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: OS1
 */

#include "thread.h"
#include "queue.h"
#include "pcb.h"
#include "schedule.h"
#include "system.h"
#include "kernsem.h"
#include <iostream.h>

class Scheduler;

Queue::Queue() {
	lock
	first = 0;
	unlock
}


void Queue::put(PCB* pcb) {
	lock
	if(first == 0) {
		first = new Elem(pcb);
	}
	else {
		Elem* temp = first;
		Elem* before = 0;
		while(temp != 0) {
			before = temp;
			temp = temp->next;
		}
		before->next = new Elem(pcb);
		before = 0;
		temp = 0;
	}
	unlock
}

// STAVLJA NIT U LISTU

PCB* Queue::get(ID id) {
	if(first == 0) return 0;
	Elem* temp = first;
	while(temp != 0 && temp->pcb->id != id) temp = temp->next;
	if(temp == 0) {
		return 0;
	}
	PCB* pcb = temp->pcb;
	return pcb;
}

// UZIMA NIT IZ LISTE NA OSNOVU ID-A

void Queue::remove(PCB* pcb) {
	lock

	if(first == 0) {
		unlock
		return;
	}
	Elem* temp = first;
	Elem* before = 0;
	while(temp != 0 && temp->pcb != pcb) {
		before = temp; temp = temp->next;
	}

	if(temp == 0) {
		unlock
		return;
	}
	if(temp == first) {
		first = first->next;
	}
	else {
		before->next = temp->next;
	}

	delete temp;
	unlock
}

// UKLANJA NIT IZ LISTE

Queue::~Queue() {
	lock
	Elem* temp;
	while(first != 0) {
		temp = first;
		first = first->next;
		delete temp;
	}
	first = 0;
	unlock
}


PCB* Queue::take() {
	if(first == 0) return 0;
	PCB* pcb = first->pcb;
	remove(pcb);
	return pcb;
}

// UZIMA PRVU NIT IZ LISTE I UKLANJA JE



