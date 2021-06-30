/*
 * system.h
 *
 *  Created on: Aug 19, 2019
 *      Author: OS1
 */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "thread.h"
#include "idle.h"
#include "pcb.h"
#include "kernsem.h"
#include "kerneve.h"
#include <dos.h>

class Thread;
class PCB;
class Idle;


extern unsigned tss;
extern unsigned tsp;
extern unsigned tbp;

extern volatile Time counter;
extern volatile int wanted_change_of_context;
extern volatile unsigned int lockFlag;

#define lock lockFlag++;

#define unlock lockFlag--;

//makroi za kriticne sekcije

typedef void interrupt (*pInterrupt) (...);

extern pInterrupt oldISR;

class System {
public:
	friend class Thread;
	friend class PCB;
	friend class KernelEv;
	friend class KernelSem;

	static void inicialize();
	static void restore();
	static void interrupt timer(...);


	System();
};


extern void tick();



#endif /* SYSTEM_H_ */
