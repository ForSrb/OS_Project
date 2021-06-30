/*
 * system.cpp
 *
 *  Created on: Aug 23, 2019
 *      Author: OS1
 */


#include "system.h"
#include "thread.h"
#include "schedule.h"
#include "pcb.h"
#include "idle.h"
#include "kernsem.h"
#include "queue.h"
#include <iostream.h>
#include <dos.h>

class Scheduler;
class PCB;
class KernelSem;

unsigned tss;
unsigned tsp;
unsigned tbp;
volatile int wanted_change_of_context = 0;
volatile unsigned int lockFlag = 0;
volatile Time counter = 5;
pInterrupt oldISR = 0;



void System::inicialize() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	PCB::inicialize();
#ifndef BCC_BLOCK_IGNORE
	oldISR = getvect(0x08);
	setvect(0x60, oldISR);
	setvect(0x08, System::timer);

	asm sti;
#endif
}

void System::restore() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(0x08, oldISR);
	delete PCB::idleThread;
	asm sti;
#endif
}

void interrupt System::timer(...) {
	if(!wanted_change_of_context && lockFlag == 0)  KernelSem::sleepProcess();
	//else if(lockFlag > 0) KernelSem::additionalSleepTime++;


	if(!wanted_change_of_context) {
		tick();
#ifndef BCC_BLOCK_IGNORE
		asm int 0x60;
#endif
	}


	if(!wanted_change_of_context) counter--;
	if(counter == 0 || wanted_change_of_context) {
		if (lockFlag == 0) {
			wanted_change_of_context = 0;
#ifndef BCC_BLOCK_IGNORE
			asm {
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}
#endif
			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			if(PCB::running->status == PCB::READY && PCB::running != PCB::idleThread->myPCB) Scheduler::put((PCB*)PCB::running);
			PCB::running = Scheduler::get();

			if(PCB::running == 0) PCB::running = PCB::idleThread->myPCB;   //PCB::getPCB(PCB::idleThread->getId());

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			counter = PCB::running->timeSlice;
			if(counter == 0) counter = -1;

#ifndef BCC_BLOCK_IGNORE
			asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif

		}
		else wanted_change_of_context = 1;

	}

}
