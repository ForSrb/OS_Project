/*
 * main.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: OS1
 */

#include "system.h"
#include "pcb.h"
#include "kernsem.h"
#include <iostream.h>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	System::inicialize();

	int a = userMain(argc,argv);

	lock
	cout << "izasao iz userMain-a" << endl;
	unlock

	System::restore();

	lock
	delete PCB::pcb_queue;
	delete KernelSem::sleepQueue;
	unlock


	return a;
}

