//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include <algorithm>

#if _WINDOWS
#include <Math.h>
#endif

#if _WINDOWS
	// We are going to define min() and max() as templates; however, at this
	// point, they have already been defined as macros by "windef.h", so we
	// undefined them here.  [DMB, 10/19/95]
	#if defined(min)
		#undef min
	#endif
	#if defined(max)
		#undef max
	#endif
#endif // _WINDOWS




inline Bool8 podd(SintptrT x) { return (x & 1) != 0; }

///////////////////////////////////////////////////////////////////////////////
//	Supplementary min and max functions to provide matches for min(x, <constant>).
//
inline int16_t	min(int16_t a,	int16_t b)		{ return a > b ? b : a; } 
inline int32_t	min(int32_t a,	int32_t b)		{ return a > b ? b : a; } 
inline int64_t	min(int64_t a,	int64_t b)		{ return a > b ? b : a; } 
inline size_t	min(size_t a,	size_t b)		{ return a > b ? b : a; } 
#if GS_MAC
inline uint32_t	min(uint32_t a,	uint32_t b)		{ return a > b ? b : a; }  //X64PRJ_REVISIT Miriam - Mac seemed to need this; but in Win it produced size_t conflict
#endif
inline float	min(float a,	float b)		{ return a > b ? b : a; }
inline double	min(double a,	double b)		{ return a > b ? b : a; }
//inline float	min(double a,	float b)		{ return (float)a > b ? b : (float)a; }
//inline float	min(float a,	double b)		{ return a > (float)b ? (float)b : a; }
//inline float	min(float a,	float b)		{ return a > b ? b : a; }

inline int16_t	max(int16_t a,	int16_t b)		{ return b > a ? b : a; } 
inline int32_t	max(int32_t a,	int32_t b)		{ return b > a ? b : a; } 
inline int64_t	max(int64_t a,	int64_t b)		{ return b > a ? b : a; } 
inline size_t	max(size_t a,	size_t b)		{ return b > a ? b : a; } 
inline float	max(float a,	float b)		{ return b > a ? b : a; }
inline double	max(double a,	double b)		{ return b > a ? b : a; }
//inline float	max(double a,	float b)		{ return (float)a > b ? b : (float)a; }
//inline float	max(float a,	double b)		{ return a > (float)b ? (float)b : a; }
//inline float	max(float a,	float b)		{ return a > b ? b : a; }

inline int32_t min(int16_t a, int32_t b)  { return min((int32_t) a, b); }
inline int32_t min(int32_t a, int16_t b)  { return min(a, (int32_t) b); }
inline int64_t min(int64_t a, int32_t b)  { return min(a, (int64_t) b); }
inline int64_t min(int32_t a, int64_t b)  { return min((int64_t) a, b); }

inline int32_t max(int16_t a, int32_t b)  { return max((int32_t) a, b); }
inline int32_t max(int32_t a, int16_t b)  { return max(a, (int32_t) b); }
inline int64_t max(int64_t a, int32_t b)  { return max(a, (int64_t) b); }
inline int64_t max(int32_t a, int64_t b)  { return max((int64_t) a, b); }

/////////////////////////
// TernaryXOR - 
// Returns true iff only one of the three values is true, otherwise false
/////////////////////////

inline bool TernaryXOR(bool a, bool b, bool c)
{
    return (!a && (b ^ c)) || (a && !(b || c));
}


const extern double_gs PI;					// 3.14159...
const extern double_gs kTwoPi;				// 2 * PI
const extern double_gs kHalfPi;				// PI / 2
const extern double_gs kThreePiOver2;		// 3 * PI / 2

#if GS_SDK_VW8_COMPATIBLE
	const extern double_gs radToDeg;	// 180.0 / PI;		// converts from radians to degrees 
	const extern double_gs degToRad;	// PI / 180.0;		// converts from degrees to radians 
	const extern double_gs halfPi;		// PI / 2.0;
	const extern double_gs twoPi;		// 2*PI;
#endif // GS_SDK_VW8_COMPATIBLE

extern const double PI;

extern const double	kDegreesPerRadian;	// = 180.0 / PI
extern const double	kRadiansPerDegree;	// = PI / 180.0
extern const double kGradiansPerDegree;	// = 100.0 / 90.0;
extern const double kDegreesPerGradian;	// = 90.0 / 100.0;

const extern double	kHalfPi;			// = PI / 2.0
const extern double	kThreePiOver2;		// = 3.0 * PI / 2.0
const extern double	kTwoPi;				// = 2.0 * PI



/////////////////////////////////////////////////////////////////////////////////////////
//inline Real64		Abs(Real64 x)		{ return (Real64)fabs(x); }
inline double		Abs(double x)		{ return (x >= 0) ? x : -x; }  // six times faster than fabs on Windows (and maybe Intel Mac?) // [MAF 12/22/05]
inline Sint32		Abs(Sint32 x)		{ return (Sint32)labs(x); }
inline short		Abs(short x)		{ return abs(x); }
inline char			Abs(char x)			{ return abs(x); }
inline signed char	Abs(signed char x)	{ return abs(x); }

//---------------------------------------------------------------------------------------
inline Real32 Truncate(const Real32 fromValue)
//
// Description:
//   Truncates specified float value.
//
// Parameters:
//   fromValue - input - value to truncate.
//
// Returns:
//   float - truncated value.
//
// Created by Victor Long on 04/09/2004.
//
{
	Real32 toValue;
#if GS_WIN
	modf(fromValue, &toValue);
#else
	modff(fromValue, &toValue);
#endif

	return toValue;
}

//---------------------------------------------------------------------------------------
inline Real64 Truncate(const Real64 fromValue)
//
// Description:
//   Truncates specified double value.
//
// Parameters:
//   fromValue - input - value to truncate.
//
// Returns:
//   double - truncated value.
//
// Created by Victor Long on 04/09/2004.
//
{
	Real64 toValue;

	modf(fromValue, &toValue);

	return toValue;
}

//---------------------------------------------------------------------------------------
inline Real32 Round(Real32 value)
//
// Description:
//   Rounds specified float value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   float - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + (float)0.5));
}

//---------------------------------------------------------------------------------------
inline Real64 Round(Real64 value)
//
// Description:
//   Rounds specified double value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   double - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + 0.5));
}

//---------------------------------------------------------------------------------------
inline long double Round(long double value)
//
// Description:
//   Rounds specified long double value.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   long double - rounded value.
//
// Created by Victor Long on 04/09/2004.
//
{
	return (floor(value + 0.5));
}

//---------------------------------------------------------------------------------------
inline Real64 Round5Digits(Real64 value)
//
// Description:
//   Rounds specified double value to 5 decimal places.
//
// Parameters:
//   value - input - value to round.
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
	return (floor(value*100000 + 0.5)/100000);
}
//---------------------------------------------------------------------------------------
inline int signnum(double value)
//
// Description:
//   Return the sign of the specified number
//
// Parameters:
//   value - input - number for which to return the sign.
//
// Returns:
//   int - the sign: positive (1), negative (-1), or neutral (0).
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
    return (value > 0) - (value < 0);
}

//---------------------------------------------------------------------------------------
inline Real64 RoundDown(Real64 value, int decimal_places)
//
// Description:
//   Rounds down the specified double value to the specified number of decimal places.
//   The number will be rounded toward zero.
//
// Parameters:
//   value - input - value to round.
//   decimal_places - input - number of decimal places
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
    return signnum(value) * (floor(Abs(value)* pow(10, decimal_places))/pow(10, decimal_places));
}

//---------------------------------------------------------------------------------------
inline Real64 RoundUp(Real64 value, int decimal_places)
//
// Description:
//   Rounds up the specified double value to the specified number of decimal places.
//   The number will be rounded away from zero.
//
// Parameters:
//   value - input - value to round.
//   decimal_places - input - number of decimal places
//
// Returns:
//   double - rounded value.
//
// Created by Hugues Tsafak on 02/12/2013.
//
{
    return signnum(value) * (ceil(Abs(value)* pow(10, decimal_places))/pow(10, decimal_places));
}

/////////////////////////////////////////////////////////////////////////////////////////
// Min and Max, 2 to 6 parameter versions. JDW.

template<class T> inline T	Max(T a, T b)		{ return( a > b ? a : b ); }
template<class T> inline T	Min(T a, T b)		{ return( a < b ? a : b ); }
template<class T> inline T	Max(T a, T b, T c)	{ return Max(Max(a,b), c); }
template<class T> inline T	Min(T a, T b, T c)	{ return Min(Min(a,b), c); }
template<class T> inline T	Max(T a, T b, T c, T d)				{ return Max(Max(a,b), Max(c,d)); }
template<class T> inline T	Min(T a, T b, T c, T d)				{ return Min(Min(a,b), Min(c,d)); }
template<class T> inline T	Max(T a, T b, T c, T d, T e)		{ return Max(Max(a,b), Max(c,d,e)); }
template<class T> inline T	Min(T a, T b, T c, T d, T e)		{ return Min(Min(a,b), Min(c,d,e)); }
template<class T> inline T	Max(T a, T b, T c, T d, T e, T f)	{ return Max(Max(a,b), Max(c,d), Max(e,f)); }
template<class T> inline T	Min(T a, T b, T c, T d, T e, T f)	{ return Min(Min(a,b), Min(c,d), Min(e,f)); }


/////////////////////////////////////////////////////////////////////////////////////////

#if 0
	// These will always give the correct result, even on compilers 
	// that use logical shift for >>. 
	inline Sint32 Div2(Sint32 x) 											{ return (x < 0 ? -((-x)>>1) : x >> 1); }
	inline Sint32 Div4(Sint32 x) 											{ return (x < 0 ? -((-x)>>2) : x >> 2); }
	inline Sint32 ASR(Sint32 x, short shiftBy)								{ return (x < 0 ? -((-x)>>shiftBy) : x >> shiftBy); }

#else
	// Use these if the compiler uses arithmetic shift for >>.
	inline Sint32 Div2(Sint32 x)											{ return x >> 1; }
	inline Sint32 Div4(Sint32 x)											{ return x >> 2; }
	inline Sint32 ASR(Sint32 x, short shiftBy)								{ return x >> shiftBy; }

#endif


/////////////////////////////////////////////////////////////////////////////////////////
inline double sqr(double x)	{ return x*x; }
inline double xpwr2(double x) { return x*x; }
inline double xpwr3(double x) { return x*x*x; }
inline double xpwr4(double x) { return x*x*x*x; }

inline double Sqrt(double x)		{ return sqrt(fastFabs(x)); }


/////////////////////////////////////////////////////////////////////////////////////////
inline double FPRemainder(double_param num, double_param denom)
{
	#if _WINDOWS
		return fmod(num, denom);		
	#else
		return remainder(num, denom);
	#endif
}

inline double NormalizeAngle(double a)
{
	if (a < 0.0) {
		if (a < -360.0) {
			a = -FPRemainder(-a, 360.0);
		}
		a += 360.0;
	}
	else if (a >= 360.0) {
		a = FPRemainder(a, 360.0);
	}

	return a;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Functions for returning whether two values of any type are approximately equal.

template <class Type> inline bool
ApproxEqual(Type x, Type y, Type fudgeFactor)
{
	return Abs(x-y) <= fudgeFactor;
}

template <class NumericType> inline bool
NotApproxEqual(NumericType x, NumericType y, NumericType fudgeFactor)
{
	return !ApproxEqual(x,y,fudgeFactor);
}


/////////////////////////////////////////////////////////////////////////////////////////

template <class NumType> inline NumType
IncModulo(NumType base, NumType modulo)
{
	return ( base == modulo-1 ? 0 : base+1 );
}

template <class NumType> inline NumType
DecModulo(NumType base, NumType modulo)
{
	return ( base == 0 ? modulo-1 : base-1 );
}
