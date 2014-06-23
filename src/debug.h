#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

// uncomment this to enable colors

#define ENABLE_DEBUG
#define ENABLE_COLORS

//////
// debug check for classes

#if defined ENABLE_DEBUG && defined CLASS_NAME
   	#if defined ENABLE_COLORS
		// constructor -> name = bright yellow, entering = green
  	    #define _debug_entercon() { printf("\033[1m\033[33m %s : \033[32mEntering\033[0m\n",CLASS_NAME); }
		// constructor -> name = bright yellow, leaving = red
		#define _debug_leavecon() { printf("\033[1m\033[33m %s : \033[31mLeaving\033[0m\n",CLASS_NAME); }
		// destructor -> name = blue, entering = green
		#define _debug_enterdes() { printf("\033[34m %s : \033[32mEntering\033[0m\n",CLASS_NAME); }
		// destructor -> name = blue, leaving = red
		#define _debug_leavedes() { printf("\033[34m %s : \033[31mLeaving\033[0m\n",CLASS_NAME); }
		// functions -> name = nocolor, entering = green
		#define _debug_enter(x) { printf(" %s::%s : \033[32mEntering\033[0m\n",CLASS_NAME,x); }
		// functions -> name = nocolor, leaving = blue
		#define _debug_leave(x) { printf(" %s::%s : \033[31mLeaving\033[0m\n",CLASS_NAME,x); }
		// checkpoints -> name = nocolor, checkpoint = bg green fg black
		#define _debug_checkpoint(x) { printf(" %s::%s : \033[42m\033[30mCheckpoint\033[0m\n",CLASS_NAME,x); }
		// warning -> name = nocolor, warning = bg blue fg yellow
		#define _debug_warning(x,y) { printf(" %s::%s : \033[44m\033[1m\033[33mWarning : %s\033[0m\n",CLASS_NAME,x,y); }
		// fatal -> bg red fg bright white
		#define _debug_fatal(x,y) { printf("\033[41m\033[1m\033[37m %s::%s : FATAL!!! %s\033[0m\n",CLASS_NAME,x,y); exit(1); }
	#else  // ! ENABLE_COLORS
		// constructor -> name, entering 
		#define _debug_entercon() { printf(" %s : Entering Constructor\n",CLASS_NAME); }
		// constructor -> name, leaving
		#define _debug_leavecon() { printf(" %s : Leaving Constructor\n",CLASS_NAME); }
		// destructor -> name entering
		#define _debug_enterdes() { printf(" %s : Entering Destructor\n",CLASS_NAME); }
		// destructor -> name leaving
		#define _debug_leavedes() { printf(" %s : Leaving Destructor\n",CLASS_NAME); }
		// functions -> name entering
		#define _debug_enter(x) { printf(" %s::%s : Entering\n",CLASS_NAME,x); }
		// functions -> name leaving 
		#define _debug_leave(x) { printf(" %s::%s : Leaving\n",CLASS_NAME,x); }
		// checkpoints -> name checkpoint
		#define _debug_checkpoint(x) { printf(" %s::%s : Checkpoint\n",CLASS_NAME,x); }
		// warning -> name warning
		#define _debug_warning(x,y) { printf(" %s::%s : Warning : %s\n",CLASS_NAME,x,y); }
		// fatal -> name fatal
		#define _debug_fatal(x,y) { printf(" %s::%s : FATAL!!! : %s\n",CLASS_NAME,x,y); exit(1); }
	#endif // ENABLE_COLORS
#else // ! (ENABLE_DEBUG && CLASS_NAME) 
	#define _debug_entercon()
	#define _debug_leavecon()
	#define _debug_enterdes() 
	#define _debug_leavedes() 
	#define _debug_enter(x) 
	#define _debug_leave(x)
	#define _debug_checkpoint(x)
	#define _debug_warning(x,y)
	#define _debug_fatal(x,y)  exit(1);
#endif


#if defined ENABLE_DEBUG
	#define _debug_1arg(fmt,arg1) { printf(fmt,arg1); }
	#define _debug_2arg(fmt,arg1,arg2) { printf(fmt,arg1,arg2); }
	#define _debug_3arg(fmt,arg1,arg2,arg3) { printf(fmt,arg1,arg2,arg3); }
#else
	#define _debug_1arg(fmt,arg1) 
	#define _debug_2arg(fmt,arg1,arg2)
	#define _debug_3arg(fmt,arg1,arg2,arg3) 
#endif



#endif // DEBUG_H






