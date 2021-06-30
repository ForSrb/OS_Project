/*
 * event.h
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#include "ivt.h"

typedef unsigned char IVTNo;
class KernelEv;



class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();

protected:
	friend class KernelEv;
	void signal(); // can call KernelEv

private:
	KernelEv* myImpl;

};



#endif /* EVENT_H_ */
