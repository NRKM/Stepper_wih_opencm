#ifndef	_Common_H
#define	_Common_H
#include	<math.h>
#include	<wirish.h>

#define		DebugMode
#undef		DebugMode

typedef	unsigned char	U08;
typedef	signed char		S08;

typedef	unsigned int	U16;
typedef	signed int		S16;

#define	DXL_BUS_SERIAL1	1
#define	DXL_BUS_SERIAL2	2
#define	DXL_BUS_SERIAL3	3

#define	TAPING_MOTOR	0
#define	LINEAR_MOTOR	1

#define		STEP_FIRST_2_LAPS  0
#define		STEP_MOVING_LINEAR 1
#define		STEP_LAST_2_LAPS   2
#define		TAPING_FINISHED    3

//#define		CHANGE_LOOPCONDITION 10
#define		INIT_LOOPCONDITION   50
#define		WAIT_INPUT			100
#define		INIT_LINEAR			200
#define		INIT_TAPING			300
#define		START_TAPING		400
#define		START_TAPING2		450
#define		START_MOVING_LINEAR	500
#define		STOP_MOVING_LINEAR	600
#define		ACCESSORIES_START	700
#define		OKURI_START         800
#define		OKURI_START2		850
#define		CUTTING_START		900
#define		CHECK_CHOMEPOS		950
#define		ZERO_RETURN			999
#define		SYSTEM_RUNNING		99

#include	"Controller.h"
#include	"TapingMotor.h"
#include	"Accessories.h"
#include	"Interface.h"


#define		INVERSE_RGB(x)	( 255 - (x) ) * 256
#define		ARRAY_SIZE(x)	( sizeof( (x) ) / sizeof( (x)[0] ) )				// Length of array
#define		ABS(x)			( ( (x) < 0 ) ? -(x):(x) )							// Absolute Value
#define		SQUARE(x)		( (x)*(x) ) 										// Square Root
#define		MAX(x,y)		( (x) > (y) ? (x) : (y) )							// Max Value
#define		MIN(x,y)		( (x) < (y) ? (x) : (y) )							// Min Value
#define		MOD2(x)			( ( (x) % 2 ) )										// Check Odd or Even
#define		MOD_FRQ(x,FRQ)	( (x) % FRQ )										// Mod FRQ
#define		MOD256(x)		( ( (x) % 256 ) )									// x & 0xFF
#define		MOD6(x)			( ( (x) > 0 ) ? ( (x) % 6 ):((x+60) % 6 ) )			// Obtain Direction Num
#define		UPCASE(c)		( ( (c)>='a' && (c)<='z') ? (c)-('a'-'A') : (c) )	// Lower-Case -> Upper-Case
#define		LOWCASE(c)		( ( (c)>='A' && (c)<='Z') ? (c)+('a'-'A') : (c) )	// Upper-Case -> Lower-Case
#define		NUM_TO_RAD(x,y)	( (float)(x) / (float)(y) ) * 6.283185307179586476925286766559
#define		EULAR_NUMBER	2.7182818284590452353602874

extern int cur_step;
extern int Running_Status;
extern int loopCount;
extern int loopCount2;
extern int InputEntered;
extern int microsec;

extern char key;

#endif