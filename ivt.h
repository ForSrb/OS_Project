/*
 * ivt.h
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#ifndef _IVT_H_
#define _IVT_H_

#include "event.h"
#include "system.h"
#include <dos.h>
#include "kerneve.h"

typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt) (...);
const int numOfEntries = 256;
class KernelEv;



class IVTEntry {
public:
	IVTNo ivtNo;
	KernelEv* myEvent;
	pInterrupt oldRoutine;

	static IVTEntry *IVTEntries[numOfEntries];

	IVTEntry(IVTNo ivtNo, pInterrupt newRoutine);
	~IVTEntry();

	void signal();
	void callOld();


};


#define PREPAREENTRY(num,old)\
	void interrupt inter##num(...);\
	IVTEntry newEntry##num(num,inter##num);\
	void interrupt inter##num(...){\
		if(old==1)\
				newEntry##num.callOld();\
		if(newEntry##num.myEvent != 0)  newEntry##num.signal();\
		dispatch();\
	}

#endif /* IVT_H_ */
