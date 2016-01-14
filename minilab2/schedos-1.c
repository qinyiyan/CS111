#include "schedos-app.h"
#include "x86sync.h"
#include "schedos-kern.h"
#include "x86.h"
#include "lib.h"
/*****************************************************************************
 * schedos-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (schedos-kern.c) pick another
 *   application to run, if it wants.
 *
 *   The other schedos-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/
 #define __PRIORITY_1__ 1
 #define __PRIORITY_2__ 2
 #define __PRIORITY_3__ 3
 #define __PRIORITY_4__ 4
 #define __SHARE_1__ 1
 #define __SHARE_2__ 2
 #define __SHARE_3__ 3
 #define __SHARE_4__ 4

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif
#ifndef PRIORITY
#define PRIORITY __PRIORITY_3__
#endif
#ifndef SHARE
#define SHARE __SHARE_3__
#endif
// UNCOMMENT THE NEXT LINE TO USE EXERCISE 4A CODE INSTEAD OF EXERCISE 4B
//#define __EXERCISE_4A__


// UNCOMMENT THE NEXT LINE TO USE EXERCISE 8 CODE INSTEAD OF EXERCISE 6
// #define __EXERCISE_8__
// Use the following structure to choose between them:



void
start(void)
{
	int i;
	sys_share(SHARE);
	sys_priority(PRIORITY);
	#ifdef __EXERCISE_4A__ 
	sys_yield();//for 4a
	#endif
	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters to the console, yielding after each one.
		//cursorpos++ = PRINTCHAR;
		//atomic_swap(uint32_t *addr, uint32_t val);
		#ifdef __EXERCISE_8__  // exercise 8 sync method
			sys_atomic_print(PRINTCHAR);
		#else // exercise 6 sync method
		while(atomic_swap(&lock,1)!= 0)
		{
			//return 0 means get the lock;
			continue;
		}
		*cursorpos++ = PRINTCHAR;
		atomic_swap(&lock,0);
		#endif
		sys_yield();
		
		//release the lock
	}

	// Yield forever.
	sys_exit(0);
}
