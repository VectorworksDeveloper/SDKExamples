//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Implements floating point utilities for MiniCAD & externals..
//


#include "StdHeaders.h" // DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 4/2/96]

#if GS_WIN
	#include <Math.h>
#else
	#include <cmath>
#endif


// kNearlyEqualEpsilonForDoubles
//
// kNearlyEqualEpsilonForDoubles is the very small number we use to decide if 2 double
// floating point values are virtually equal. It's 2 digits less that the published
// precision for IEEE doubles, but we're playing it extra-safe.
const extern double kNearlyEqualEpsilonForDoubles          = 1e-13;

// This (kNearlyEqualEpsilonForNormalizedValues) can't be the same as 
// kNearlyEqualEpsilonForDoubles because we have to deal with
// values that were translated from Fracts from previous file versions.  If think the 
// real value is 9 (digits of precision for Fracts), but I'm going with 8. [MAF 12/15/99]
//
// I saw one with 7 (a normalized value was 1.0000000508999 in an 8.5 translation test file 
// (TextureBitMapNode.mcd had a TextureSpaceNode on a SolidNode). Let's try 7. [MAF 2/23/00]
//
// OK, Dave D. had one with 6 (1.0000001743309) in BrickRoom.mcd. I'll try 6 here but that's
// as low as I'm going! [MAF 6/5/00]
//
//const extern double kNearlyEqualEpsilonForNormalizedValues = 1e-08;
//const extern double kNearlyEqualEpsilonForNormalizedValues = 1e-07;
const extern double kNearlyEqualEpsilonForNormalizedValues = 1e-06;

// The following epsilon is used to determine if a retangular object is oriented at a multiple of 90 degrees.
// Since we have a maximum of 8 decimal places for an angle, if the orientation is displayed as 0.00000000, we
// want it to treat the object as being at a multiple of 90 degrees.  The smallest angle that will be recognized
// by the user as non-zero if 5e-9, since that will round up to 0.00000001.  The sin of 5e-9 degrees is 8.7e-11,
// so we want to treat the object as being at a multiple of 90 degrees if the x or y value of its orientation has
// an absolute value less than 8.7e-11.
const double kRectObjOrientationEpsilon = 8.7e-11;


// An interesting point from a comment that no longer applies to the code below:
//   roundtol(2.5) == 2).   [MAF 8/18/00]


#if BUG

void AssertNum2Short(double x)
{            
	static Sint32 assertCount = 3;		// increase in debugger if you want more.
	if (assertCount > 0) {
		--assertCount;
		if (fabs(x) > 32767)
			DSTOP((kMark, "Num2Short overflow: %f\n", x));
	}
}


void AssertDoubleToLong(double x)
{            
	static Sint32 assertCount = 3;		// increase in debugger if you want more.
	if (assertCount > 0) {
		--assertCount;
		if (fabs(x) > INT32_MAX)  //64-bit, the doubleToLong functions are really now double to Sint32
			DSTOP((kMark, "DoubleToLong overflow: %f\n", x));
	}
}

#endif


/////////////////////////
// Cross-Platform byte swapping & conversion functions
/////////////////////////

// ByteSwapEXTENDED80 swaps 10 consecutive bytes (msb to lsb)
void GS_API ByteSwapEXTENDED80(extended80_gs *pld)
{
	char t;
	char *pb1 = (char *) pld;
	char *pb2 = pb1 + sizeof(extended80_gs) - 1;
	while (pb2 > pb1) {
		t = *pb1;
		*pb1 = *pb2;
		*pb2 = t;
		++pb1;
		--pb2;
	}
}



/////////////////////////
// Low level FP conversion functions
/////////////////////////


#if GS_LITTLE_ENDIAN


/*
	extended80 to/from double conversion routines.  Bit format of the various
	data types is taken from the book "Apple Numerics Manual, Second Edition"
	(see Paul), pages 17 & 18.  These functions only work on Intel byte-ordered
	processors.
*/


#if GS_MAC
static void BuildDouble(double *x, char s, unsigned short e, uint64_t f)
#else
static void BuildDouble(double *x, char s, unsigned short e, unsigned __int64 f)
#endif
/*
 ## Build a "double" variable from a given sign (s), exponent (e), and
 ## fraction (f).  The fraction must be contained in the lower 52 bits of 'f'.
*/
{
	#if GS_MAC
	uint64_t	*v = (uint64_t *) x;
	#else
	unsigned __int64 *v = (unsigned __int64 *)x;
	#endif

	// Fraction.
	*v = f;

	// Exponent.
	#if GS_MAC
	*v |= ((uint64_t)e) << 52;
	#else
	*v |= ((unsigned __int64)e) << 52;
	#endif

	// Set sign bit.
	#if GS_MAC
	if (s) *v |= ((uint64_t) 1 << 63);
	#else
	if (s) *v |= 0x8000000000000000;
	#endif
}

#if GS_MAC
static void BuildExtended80(extended80 *x80, char s, unsigned short e, char i, uint64_t f)
#else
static void BuildExtended80(extended80_gs *x80, char s, unsigned short e, char i, unsigned __int64 f)
#endif
/*
 ## Build an "extended80_gs" variable from a given sign (s), exponent (e), explict
 ## one's bit (i), and fraction (f).
*/
{
	unsigned short *aa = (unsigned short *)x80 + 4;
	#if GS_MAC
	uint64_t	*bb = (uint64_t *) x80;
	#else
	unsigned __int64 *bb = (unsigned __int64 *) x80;
	#endif

	// Set exponent.
	*aa = e;

	// Set sign bit.
	if (s) *aa |= 0x8000;

	// Set fraction.
	*bb = f;

	// Add explicit one's bit.
	#if GS_MAC
	if (i) *bb |= ((uint64_t) 1 << 63);
	#else
	if (i) *bb |= 0x8000000000000000;
	#endif
}

#if GS_MAC
// Must change the name for Intel Mac, as there is an eqivalent name built-in to the Mac OS.
// Why are we using our own x80tod function on Intel Macs, when the Mac OS already has this
// function built-in?  Because on Mac, even on Intel Mac, the extended 80 data is expected to
// be in Motorola byte-order, but ours expects it to be in Intel byte-order.  It is much easier
// to simply use our own extended 80 functions on Intel Macs than to rework our file translation
// code to swap data before calling the Mac's x80tod.
double GS_API x80todNNA(const extended80 *x80)
#else
double GS_API x80tod(const extended80_gs *x80)
#endif
//
// Convert from an 80 bit IEEE extended to a 64 bit IEEE double floating point number
//
// PCP modified this code 8-24-2000 to implement correct support of denormalized numbers
//
{
	double x;
	unsigned short *aa = (unsigned short *)x80 + 4;
	#if GS_MAC
	uint64_t	*bb = (uint64_t *) x80;
	#else
	unsigned __int64 *bb = (unsigned __int64 *) x80;
	#endif

	// Break the "extended80" variable into it's basic parts.
	char s = (char)( (*aa & 0x8000) >> 15 );	// sign
	unsigned short e = *aa & 0x7FFF;	// biased exponent
	char i = (char)( *bb >> 63 );	// explicit one's bit
#if GS_MAC
	uint64_t f = *bb & 0x7FFFFFFFFFFFFFFFULL;	// fraction
#else
	unsigned __int64 f = *bb & 0x7FFFFFFFFFFFFFFF;	// fraction
#endif

	// Check for zero.
	if (f==0 && i==0 && e<=32766) {
		if (s)
			return -0.0;
		else
			return 0.0;
	}

	// Check for infinity and NaN.
	if (e==32767) {

		// we are comparing the original 63 bit f to avoid misidentifying an infinity

		if (f==0) {
			DMSG((kEveryone, "### x80tod INF ###\n"));
			BuildDouble(&x, s, 2047, 0);
		}
		else {
			DMSG((kEveryone, "### x80tod NaN ###\n"));

			// f is the NAN identifier. I assume it should be shifted here.
			f >>= 11;
			BuildDouble(&x, s, 2047, f);
		}
		return x;
	}


	// Put fraction within range. The significand of an IEEE64 has 11 fewer bits than that of an IEEE80
	f >>= 11;

	// Convert to true exponent.
	short e2 = e - 16383;

	// Check if exponent is within range.
	if (e2 > -16383 && e2 < -1022) {
		
		if (e2 < -1073) {
			DMSG((kEveryone, "### x80tod underflow to 0.0 ###\n"));
			x = 0.0;
		}
		else {
			DMSG((kEveryone, "### x80tod gradual underflow to denormal ###\n"));


			// if the exponent is in the range of -1023 to -1073 inclusive
			// then we should underflow gradually by creating denormalized numbers

			short shift = -1022 - e2;
			
			// shift is in the range of 1 to 51 and is the amount by which we shift f
			// to gradually denormalize this number
			
			f >>= shift;
			
			// denormals always have 0 exponents
			BuildDouble(&x, s, 0, f);

		}


		x = DBL_MIN;
	}
	else if (e2 > 1023) {
		DMSG((kEveryone, "### x80tod overflow ###\n"));
		x = DBL_MAX;
	}

	// Check for normalized number.
	else if (i)
		BuildDouble(&x, s, e2+1023, f);

	// Must be a denormalized number.
	else {
		// if an extended number is so small it must be denormalized, it's got to
		// be 0.0 when represented as a double.

		x = 0.0;
	}
	return x;
}

#if GS_MAC
// Must change the name for Intel Mac, as there is an eqivalent name built-in to the Mac OS.
// Why are we using our own x80tod function on Intel Macs, when the Mac OS already has this
// function built-in?  Because on Mac, even on Intel Mac, the extended 80 data is expected to
// be in Motorola byte-order, but ours expects it to be in Intel byte-order.  It is much easier
// to simply use our own extended 80 functions on Intel Macs than to rework our file translation
// code to swap data before calling the Mac's x80tod.
void GS_API dtox80NNA(const double *x, extended80 *x80)
#else
void GS_API dtox80(const double *x, extended80_gs *x80)
#endif
/*
 ## Convert from "double"/"long double" to "extended80_gs".
*/
{
	const unsigned char *d = (unsigned char *)x + 7;
	char s = (*d & 0x80) >> 7;	// sign

	// Get exponent.
	unsigned short e = ( *(unsigned short *)(d-1) ) >> 4;
	e &= 0x07FF;	// remove sign bit.

	// Get fraction.
#if GS_MAC
	uint64_t f =  (*(uint64_t*)x) & 0x000FFFFFFFFFFFFFULL;
#else
	unsigned __int64 f = (*(unsigned __int64*)x) & 0x000FFFFFFFFFFFFF;
#endif

	// Check for zero.
	if (e==0 && f==0)
		BuildExtended80(x80,s,0,0,0);

	// Check for infinity and NaN.
	else if (e==2047) {
		DMSGIF(f==0, (kEveryone, "### dtox80 INF ###\n"));
		DMSGIF(f!=0, (kEveryone, "### dtox80 NaN ###\n"));
		BuildExtended80(x80, s, 32767, 1, f << 11);
	}

	// Check for denormalized number.
	else if (e==0)
		BuildExtended80(x80, s, 15361, 0, f << 11);

	// Must be a normalized number.
	else
		BuildExtended80(x80, s, e+15360, 1, f << 11);
}


#endif // GS_LITTLE_ENDIAN



/////////////////////////
// Misc Math
/////////////////////////



////////////////////////////////////////////////////////////////////////////////
short WholeNumberDigitsPin16(double_param inValue)
//
// Return how many digits are to the left of the decimal point for inValue;
// Return 16 if it's larger than 15 to avoid doing a slow log when it doesn't
// matter.
//
/////// John Williams - 9/14/00 ////////////////////////////////////////////////
{
	double absValue = Abs(inValue);

	if      (absValue < 1e+0)	return 0;
	else if (absValue < 1e+1)	return 1;
	else if (absValue < 1e+2)	return 2;
	else if (absValue < 1e+3)	return 3;
	else if (absValue < 1e+4)	return 4;
	else if (absValue < 1e+5)	return 5;
	else if (absValue < 1e+6)	return 6;
	else if (absValue < 1e+7)	return 7;
	else if (absValue < 1e+8)	return 8;
	else if (absValue < 1e+9)	return 9;
	else if (absValue < 1e+10)	return 10;
	else if (absValue < 1e+11)	return 11;
	else if (absValue < 1e+12)	return 12;
	else if (absValue < 1e+13)	return 13;
	else if (absValue < 1e+14)	return 14;
	else if (absValue < 1e+15)	return 15;
	else 						return 16;
}


////////////////////////////////////////////////////////////////////////////////
double WholeNumberDigitsPow10PinE16(double_param inValue)
//
// Return pow10(digits of inValue to the left of the decimal point);
// Return 1e16 if it's >= 15 digits.
//
/////// John Williams - 9/14/00 ////////////////////////////////////////////////
{
	double absValue = Abs(inValue);

	if      (absValue < 1e+0)	return 1e+0;
	else if (absValue < 1e+1)	return 1e+1;
	else if (absValue < 1e+2)	return 1e+2;
	else if (absValue < 1e+3)	return 1e+3;
	else if (absValue < 1e+4)	return 1e+4;
	else if (absValue < 1e+5)	return 1e+5;
	else if (absValue < 1e+6)	return 1e+6;
	else if (absValue < 1e+7)	return 1e+7;
	else if (absValue < 1e+8)	return 1e+8;
	else if (absValue < 1e+9)	return 1e+9;
	else if (absValue < 1e+10)	return 1e+10;
	else if (absValue < 1e+11)	return 1e+11;
	else if (absValue < 1e+12)	return 1e+12;
	else if (absValue < 1e+13)	return 1e+13;
	else if (absValue < 1e+14)	return 1e+14;
	else if (absValue < 1e+15)	return 1e+15;
	else 						return 1e+16;
}


////////////////////////////////////////////////////////////////////////////////
short WholeNumberDigits(double_param inValue)
//
// Return how many digits are to the left of the decimal point for inValue;
//
/////// John Williams - Recreated 9/14/00 //////////////////////////////////////
{
	short digits = WholeNumberDigitsPin16(inValue);
	
	if (digits == 16) {
		double exponent = log10(Abs(inValue));
		double ceiling	= ceil(exponent);
		// ceil(log10(999))-> 3, ceil(log10(1000))->3 but 4 places, ceil(log10(1001))->4
		return (short)( (ceiling == exponent) ? ceiling : ceiling + 1 );
	}
	else 
		return digits;
}


////////////////////////////////////////////////////////////////////////////////
double Modf(const double inNum, double* outIntegralPart, 
	const double inEpsilon /*= kNearlyEqualEpsilonForDoubles*/)
//
// This is a "smarter" modf, which uses an epsilon to determine if the fractional part
// is very close to 1.0 or 0.0. This is useful for doubles that are off by just a small 
// amount, so for example if you have a value that looks like 2.0 but is actually 1.99999... 
// then modf might give the seemingly incorrect values of 1.0 as integral part and 0.99999... 
// as the fractional part. 
//
// For display purposes, such as when converting a length to a number string in an edit
// field, we use kNearlyEqualEpsilonForDoubles, which is larger than the smallest 
// possible epsilon of DBL_EPSILON. 
//
// For other purposes, such as calculating internal geometry, a smaller epsilon or 0.0 
// epsilon might be preferable. But be careful: some geometry calcuations have been 
// buggy in the past due to using modf with no epsilon.
//
/////// John Williams - Recreated 9/14/00 ///////////////////////////////////////
{
	double leftPrecision = WholeNumberDigitsPow10PinE16(inNum);
	double fractionalPart = modf(inNum, outIntegralPart);
	
	if (leftPrecision == 1e+16) {
		fractionalPart = 0.0;
	}
	else {
		double epsilon = inEpsilon * leftPrecision;
		if (DoublesAreNearlyEqual(fractionalPart, 0.0, epsilon))
			fractionalPart = 0.0;
		else if (DoublesAreNearlyEqual(fractionalPart, 1.0, epsilon)) {
			fractionalPart = 0.0;
			*outIntegralPart += 1.0;
		}
	}
	
	return fractionalPart;
}

//**************************************************************************
// Native implementation of legacy QuickTime calls:
// NNAFrac2X, NNAFix2X, NNAX2Fix, NNAX2Frac, NNAFracMul, & NNALong2Fix
//							
//	
//	
//**************************************************************************

const	NNAFixed	kFixedMinimum				= 0x80000000;
const	NNAFixed	kFixedMaximum				= 0x7FFFFFFF;
const	int		kNumberOfFixedIntegerBits	= 16;
const	int		kNumberOfFixedFractionBits	= 16;

struct NNATFixedParts 
{
	unsigned	short	fFraction	: kNumberOfFixedFractionBits;
	signed		short	fInteger	: kNumberOfFixedIntegerBits;
};

union NNATFixedUnion 
{
	NNAFixed		fWhole;
	NNATFixedParts	fPart;
};

//**************************************************************************
//
// Fract           2-bit signed integer plus 30-bit fraction
//                 to represent fixed-point decimal
//                 numbers in the interval:
//
//                 [-2, 1 + ((2^30 - 1)/2^30)]
//
//**************************************************************************

const	NNAFract	kFractMinimum				= 0x80000000;
const	NNAFract	kFractMaximum				= 0x7FFFFFFF;
const	int		kNumberOfFractIntegerBits	= 2;
const	int		kNumberOfFractFractionBits	= 30;

struct NNATFractParts 
{
	Uint32		fFraction	: kNumberOfFractFractionBits;
	Sint32	fInteger	: kNumberOfFractIntegerBits;
};

union NNATFractUnion 
{
	NNAFract		fWhole;
	NNATFractParts	fPart;
};

//**************************************************************************
//
// Function Name:  NNAFrac2X
//
// Description:
//	Converts a Fract number to an Extended number.
//	Native implementation of the legacy QuickTime call: Frac2X
// Parameters:
//
//	x
//		The Fract number to be converted to an Extended number.
//
// Return Value:
//	The Extended equivalent of the Fract number x.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
double NNAFrac2X(NNAFract x)
{
	NNATFractUnion	fractNumber;
	double		extendedNumber;

	fractNumber.fWhole = x;

	extendedNumber	= fractNumber.fPart.fInteger
					+ fractNumber.fPart.fFraction
					/ pow(2.0, kNumberOfFractFractionBits);

	return extendedNumber;
}

//**************************************************************************
//
// Function Name:  NNAFix2X
//
// Description:
//	Converts a Fixed number to an Extended number.
//	Native implementation of the legacy QuickTime call: Fix2X
// Parameters:
//
//	x
//		The Fixed number to be converted to an Extended number.
//
// Return Value:
//	The Extended equivalent of the Fixed number x.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
double NNAFix2X(NNAFixed x)
{
	NNATFixedUnion	fixedNumber;
	double		extendedNumber;

	fixedNumber.fWhole = x;

	extendedNumber	= fixedNumber.fPart.fInteger 
					+ fixedNumber.fPart.fFraction
					/ pow(2.0, kNumberOfFixedIntegerBits);

	return extendedNumber;
}

//**************************************************************************
//
// Function Name:  NNAX2Fix
//
// Description:
//	Converts an Extended number to a Fixed number.
//	Native implementation of the legacy QuickTime call: X2Fix
// Parameters:
//
//	x
//		The Extended number to be converted to a Fixed number.
//
// Return Value:
//	The best Fixed approximation of the Extended number x. If x is greater
//	than the maximum representable Fixed number, the X2Fix function returns
//	$7FFFFFFF. If x is less than the negative number with the highest
//	absolute value, NNAX2Fix returns $80000000.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
NNAFixed NNAX2Fix(double x)
{
	NNATFixedUnion	fixedNumber;
	double		fraction;

	if (x > NNAFix2X(kFixedMaximum))
	{
		return kFixedMaximum;
	}

	if (x < NNAFix2X(kFixedMinimum))
	{
		return kFixedMinimum;
	}

	fixedNumber.fPart.fInteger = (signed short) floor(x);

	fraction	= (x - fixedNumber.fPart.fInteger) 
				* pow(2.0, kNumberOfFixedFractionBits);

	fixedNumber.fPart.fFraction = (unsigned short) fraction;

	return fixedNumber.fWhole;
}

//**************************************************************************
//
// Function Name:  X2Frac
//
// Description:
//	Converts an Extended number to a Fract number.
//	Native implementation of the legacy QuickTime call: X2Frac
// Parameters:
//
//	x
//		The Extended number to be converted to a Fract number.
//
// Return Value:
//	The best Fract approximation of the Extended number x. If x is greater
//	than the maximum representable Fract number, the X2Frac function returns
//	$7FFFFFFF. If x is less than the negative number with the highest
//	absolute value, NNAX2Frac returns $80000000.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
NNAFract NNAX2Frac(double x)
{
	NNATFractUnion	fractNumber;
	double		fraction;

	if (x > NNAFrac2X(kFractMaximum))
	{
		return kFractMaximum;
	}

	if (x < NNAFrac2X(kFractMinimum))
	{
		return kFractMinimum;
	}

	fractNumber.fPart.fInteger = (Sint32) floor(x);

	fraction	= (x - fractNumber.fPart.fInteger)
				* pow(2.0, kNumberOfFractFractionBits);

	fractNumber.fPart.fFraction = (Uint32) (fraction);

	return fractNumber.fWhole;
}

//**************************************************************************
//
// Function Name:  FracMul
//
// Description:
//	Multiplies a variable of type Fract with another variable of type Fract
//	or with a variable of type Fixed or LongInt.
//	Native implementation of the legacy QuickTime call: NNAFracMul
// Parameters:
//
//	x
//		The first operand, which can be a variable of type Fract or a
//		variable of type Fixed or LongInt.
//
//	y
//		The second operand, which can be a variable of type Fract or a
//		variable of type Fixed or LongInt.
//
// Return Value:
//	The product of the numbers in a and b. At least one of a or b should be
//	a variable of type Fract.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
NNAFract NNAFracMul(NNAFract x, NNAFract y)
{
	return NNAX2Frac(NNAFrac2X(x) * NNAFrac2X(y));
}

//**************************************************************************
//
// Function Name:  Long2Fix
//
// Description:
//	Converts a LongInt number to a Fixed number.
//
// Parameters:
//
//	x
//		The long integer to be converted to a Fixed number.
//
// Return Value:
//		The Fixed number equivalent to the long integer x. If x is greater
//		than the maximum representable fixed-point number, the Long2Fix
//		function returns $7FFFFFFF. If x is less than the negative number
//		with the highest absolute value, Long2Fix returns $80000000.
//
// Created by:  Alan Owens, December 2012
//
//**************************************************************************
NNAFixed NNALong2Fix(Sint32 x)
{
	NNATFixedUnion	fixedMaximum;
	NNATFixedUnion	fixedMinimum;
	NNATFixedUnion	fixedNumber;

	fixedMaximum.fWhole = kFixedMaximum;
	fixedMinimum.fWhole = kFixedMinimum;

	if (x > fixedMaximum.fPart.fInteger)
	{
		return kFixedMaximum;
	}

	if (x < fixedMinimum.fPart.fInteger)
	{
		return kFixedMinimum;
	}

	fixedNumber.fPart.fInteger	= x;
	fixedNumber.fPart.fFraction	= 0;

	return fixedNumber.fWhole;
}

#if GS_WIN

////////////////////////////////////////////////////////////////////////////////
Sint32 FPClassify(double v)
//
// Maps Windows floating point number classifications to corresponding Mac values
//
/////// John Williams - Created 5/14/03 ////////////////////////////////////////
{

	switch(_fpclass(v)) {
		case _FPCLASS_NINF:			return FP_INFINITE;		// Negative infinity (-INF) 
		case _FPCLASS_PINF:			return FP_INFINITE;		// Positive infinity (+INF) 

		case _FPCLASS_NZ:			return FP_ZERO;			// Negative zero (-0) 
		case _FPCLASS_PZ:			return FP_ZERO;			// Positive zero (+0) 

		case _FPCLASS_ND:			return FP_SUBNORMAL;	// Negative denormalized 
		case _FPCLASS_PD:			return FP_SUBNORMAL;	// Positive denormalized 

		case _FPCLASS_NN:			return FP_NORMAL;		// Negative normalized non-zero 
		case _FPCLASS_PN:			return FP_NORMAL;		// Positive normalized non-zero 

		case _FPCLASS_SNAN:			return FP_SNAN;			// Signaling NaN 
		case _FPCLASS_QNAN:			return FP_QNAN;			// Quiet NaN 
		default: ASSERTN(kChao, 0);	return FP_QNAN;
	}
};

#endif // GS_WIN
