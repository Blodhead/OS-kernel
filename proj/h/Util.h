#ifndef UTIL_H_
#define UTIL_H_

#define MK_FP( seg,ofs )( (void _seg * )( seg ) +( void near * )( ofs ))
#define FP_SEG( fp )( (unsigned )( void _seg * )( void far * )( fp ))
#define FP_OFF( fp )( (unsigned )( fp ))


typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;

typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 55; // default = 2*55ms

typedef unsigned char IVTNo;
typedef void interrupt (*IntRoutine) (...);
typedef int ID;
typedef unsigned int mybool;
typedef unsigned long ulong;
typedef void (*Runnable)();


#define true 1
#define false 0
#define nullptr 0

#endif
