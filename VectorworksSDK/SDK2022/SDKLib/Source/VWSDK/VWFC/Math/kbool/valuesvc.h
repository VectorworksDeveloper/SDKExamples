/* @@(#) $Source: /cvs/wlv/src/pde/source/adb/kbool/valuesvc.h,v $ $Revision: 1.1 $ $Date: 2001/09/26 01:59:43 $ */

#pragma once


#define	bmax(a,b)		((a) > (b) ? (a) : (b))
#define	bmin(a,b)		((a) < (b) ? (a) : (b))
#define	babs(a)			((a) < 0 ? -(a) : (a))

#ifndef M_PI
# define M_PI			3.1415926535897932384626433832795028841972
#endif // #ifndef M_PI

#ifndef M_PI_2
# define M_PI_2			1.57079632679489661923
#endif // #ifndef M_PI_2

#ifndef M_PI_4
# define M_PI_4			0.785398163397448309616
#endif // #ifndef M_PI_4

#define MAXDOUBLE		DBL_MAX
#define MAXLONG			0x7fffffff

typedef Sint64			B_INT;						// 8 bytes integer

#define MAXB_INT		0x7fffffffffffffffLL		// 8 bytes integer
#define MINB_INT		0x8000000000000000



