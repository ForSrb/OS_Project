/*
 * ivt.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */


#include "ivt.h"
#include "system.h"

IVTEntry* IVTEntry::IVTEntries[numOfEntries];


IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newRoutine) {
	lock
	this->ivtNo = ivtNo;
	this->myEvent = 0;
	IVTEntries[this->ivtNo] = this;
	unlock
	asm pushf;
	asm cli;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(this->ivtNo);
	setvect(this->ivtNo,newRoutine);
#endif
	asm popf;
}


IVTEntry::~IVTEntry() {
	asm pushf;
	asm cli;
#ifndef BCC_BLOCK_IGNORE
	setvect(this->ivtNo,this->oldRoutine);
#endif
	IVTEntries[this->ivtNo] = 0;
	oldRoutine = 0;
	myEvent = 0;
	asm popf;
}


void IVTEntry::signal() {
	myEvent->signal();
}


void IVTEntry::callOld() {
	oldRoutine();
}
