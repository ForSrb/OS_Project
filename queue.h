/*
 * queue.h
 *
 *  Created on: Aug 19, 2019
 *      Author: OS1
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "thread.h"
#include "pcb.h"

struct Elem {
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcb_) { pcb = pcb_; next = 0; }
	};


class Queue{
public:


	Elem* first;

	void put(PCB* pcb);
	PCB* get(ID id);
	void remove(PCB* pcb);
	PCB* take();
	void ispisi();

	Queue();

	~Queue();

};



#endif /* QUEUE_H_ */
