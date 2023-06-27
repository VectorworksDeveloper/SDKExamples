//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

///////////////////////////////////////////////////////////////////////////////
//	Casting related functions.

// Intended use of DemoteTo, Trunctate, Round and PinTo.
//
// The DemoteTo casting function is intended to be used in any case where a cast is performed between numerical types in such a way
// that data can be lost depending on the value of the variable being cast. The .NET compiler on Windows will generate a warning or error
// in these cases if the cast is not explicit. 
//
// Rather than using an explicit cast to satisfy these cases, VectorWorks code is required to use the DemoteTo function as follows:
//
//      shortVariable = (short)longVariable;  //NOT PREFERRED
//
//      shortVariable = DemoteTo<short>(kVictor, longVariable);  //PREFERRED
//
// This allows the DemoteTo function to perform rigorous runtime checks to prevent unexpected data values from going unnoticed
// and causing subtle or serious functional problems.
//
// Cases where DemoteTo must be used:
// 
//     floating point to integer
//         (double to Sint32)
//     signed integer to unsigned integer of any size
//         (char to Uint32)
//     unsigned integer to signed integer of the same or smaller size
//         (unsigned short to short)
//     larger integer to smaller integer
//         (Sint32 to short or short to char)
//     larger floating point to smaller floating point
//         (double to float)
//     Sint32 integer to short floating point
//         (Sint32 to float)
// 
// Cases where a DemoteTo should not be used:
// 
//     integer to floating point
//         (Sint32 to double)
//     integer to boolean
//         (Sint32 to bool)
//     smaller integer to larger integer
//         (short to Sint32)
//     assignments between like types
//         (Sint32 to Sint32)
//     shorter floating point to longer floating point
//         (float to double)
//     non-numeric types
//         (handles, classes, strings, etc.)
//
// An important side effect of this requirement is that you understand that casting alone can no longer be used to intentionally
// truncate floating point values or pin or wrap integer values. The value passed into the DemoteTo function must be exactly
// representable by the destination variable or a runtime ASSERT message will be generated, which is unacceptable and must be
// fixed. The one exception to this is that normal roundoff errors due to the inability of shorter floating point types to represent longer
// floating point numbers are ignored:
//
//     longVariable = DemoteTo<Sint32>(kVictor, doubleVariable); 
//            This case is OK only if the value in doubleVariable is constrained to be in the range MINLONG to MAXLONG and has no
//            fractional component. e.g. it's illegal to pass 10.5 in doubleVariable.
//
//     longVariable = DemoteTo<Sint32>(kVictor, Round(doubleVariable));
//     longVariable = DemoteTo<Sint32>(kVictor, Truncate(doubleVariable));
//            This is more likely the correct way to approach this problem as you are guaranteeing that there is no fractional component.
//
//     longVariable = DemoteTo<Sint32>(kVictor, PinTo<Sint32>(kVictor, doubleVariable));
//            This specifies that the value be pinned either to the maximum or minimum of the destination type's range
//            if it is outside that range.

//---------------------------------------------------------------------------------------
template <typename PinType, typename FromType> 
#if !(GS_MAC && TEST)
inline 
#endif
FromType PinTo(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue)
//
// Description:
//   Templated function to pin the specified value to the range of the specified pin type.
//
//   - Debug only behavior:
//     - Warns if type size is greater than maximum size
//     - Warns if identical types are being pinned between.
//     - Warns if pin type is larger than source type.
//
// Parameters:
//   toWhom    - input - the programmer to whom any DSTOP messages will be addressed.
//   fromValue - input - the value to be pinned.
//
// Returns:
//   FromType - the pinned value.
//
// Created by Victor Long on 04/09/2004.
//
{

	FromType		toValue;
	const size_t	kMaxByteSize = 8;
	size_t			pinTypeSize = sizeof(PinType);
	size_t			fromTypeSize = sizeof(FromType);
	bool			mayPinValue = true;
	PinType			minPinValue;
	PinType			maxPinValue;

	// Check to see if data type sizes are larger than maximum supported size
	// and if so send DSTOP message.
	if (pinTypeSize > kMaxByteSize || 
		fromTypeSize > kMaxByteSize) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;

		outStream << "PINNING WITH LARGER THAN SUPPORTED TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occured where the size of one or both " << std::endl;
		outStream << "of the source and pin types is greater " << std::endl;
		outStream << "than the pinning function's maximum supported size " << std::endl;
		outStream << "of " << kMaxByteSize << " bytes." << std::endl; //-V128
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}
	// Check to see if data types are identical 
	// and if so send DSTOP message.
	else if (typeid(FromType) == typeid(PinType)) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;

		outStream << "PINNING BETWEEN IDENTICAL TYPES. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occurred where no pin should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}
	// Check to see if casting results in promotion 
	// and if so send DSTOP message.
	else if (!(std::numeric_limits<FromType>::is_signed && !std::numeric_limits<PinType>::is_signed) &&
			 sizeof(PinType) > sizeof(FromType)) {
		mayPinValue = false;

#if TEST
		std::ostringstream outStream;
	
		outStream << "PINNING TO LARGER TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Pinning has occured where no pin should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this pinning function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
#endif
	}

	maxPinValue = std::numeric_limits<PinType>::max ();

	if (std::numeric_limits<PinType>::is_integer) {
		minPinValue = std::numeric_limits<PinType>::min ();
	}
	else {
		minPinValue = -std::numeric_limits<PinType>::max ();
	}
			 
	if (mayPinValue &&
		fromValue > maxPinValue) {
		toValue = maxPinValue;
	}
	else if (mayPinValue &&
			 fromValue < minPinValue) {
		toValue = minPinValue;
	}
	else {
		toValue = fromValue;
	}

	return toValue;
}

#if TEST
// Check for floating point loss during DemoteTo.  RBerge 08/27/2013.
//
// Split from DemoteTo so DemoteTo works with x64 data types.
// If needed, this can be specialized so e.g. OtherType == Uint64 is a noop, to prevent compiler warning
template <typename RealType, typename OtherType> 
#if !(GS_MAC && TEST)
inline 
#endif
bool DemotionDoubleTest(const RealType& realValue, const OtherType& otherValue)
{
	#if _WINDOWS
	#pragma warning ( push )
	#pragma warning( disable : 4244 ) // conversion from 'size_t' to 'double', possible loss of data.  The check itself will tell us.
	#endif
	return DoublesAreNotNearlyEqual (realValue, otherValue);
	#if _WINDOWS
	#pragma warning ( pop )
	#endif
}
#endif

//---------------------------------------------------------------------------------------
template <typename ToType, typename FromType> 
#if !(GS_MAC && TEST)
inline 
#endif
ToType DemoteTo(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue)
//
// Description:
//   Templated function to cast one data type to another.
//
//   - Debug only behavior:
//     - Warns if type size is greater than maximum size
//     - Warns if identical types are being cast between.
//     - Warns if value is actually being promoted, not demoted.
//     - Warns if loss of data has occurred.
//
// Parameters:
//   toWhom    - input - the programmer to whom any DSTOP messages will be addressed.
//   fromValue - input - the value to be cast from.
//
// Returns:
//   ToType - the value of the cast input value.
//
// Created by Victor Long on 03/31/2004.
//
{
	ToType toValue;

	// The input value is ALWAYS cast and returned.
	// This is to preserve existing casting behavior where this function is used.
	toValue = (ToType) fromValue;

#if TEST
	// This debug only section evaluates the casting operation
	// for certain problems (see function description above).

	const size_t	kMaxByteSize = 8;
	size_t			toTypeSize = sizeof(ToType);
	size_t			fromTypeSize = sizeof(FromType);
	bool			castingResultsInLossOfData = false;

	// Check to see if data type sizes are larger than maximum supported size
	// and if so send DSTOP message.
	if (toTypeSize > kMaxByteSize || 
		fromTypeSize > kMaxByteSize) {
		std::ostringstream outStream;
	
		outStream << "CASTING WITH LARGER THAN SUPPORTED TYPE. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where the size of one or both " << std::endl;
		outStream << "of the source and destination types is greater " << std::endl;
		outStream << "than the casting function's maximum supported size " << std::endl;
		outStream << "of " << kMaxByteSize << " bytes." << std::endl; //-V128
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	else if ((typeid(FromType) == typeid(ToType)) && (sizeof(SintptrT) == sizeof(FromType)) && (sizeof(Sint32) == sizeof(ToType))) {
		// For x32, quietly allow SintptrT demote to (same size) Sint32. 
		// For x64, they're different sizes, so this case can't be hit
	}
	// Check to see if data types are identical 
	// and if so send DSTOP message.
	else if (typeid(FromType) == typeid(ToType)) {
		std::ostringstream outStream;
	
		outStream << "CASTING BETWEEN IDENTICAL TYPES. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where no cast should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	// Check to see if casting results in promotion 
	// and if so send DSTOP message.
	else if (!(std::numeric_limits<FromType>::is_signed && !std::numeric_limits<ToType>::is_signed) &&
			 sizeof(ToType) > sizeof(FromType)) {
		std::ostringstream outStream;

		outStream << "CASTING RESULTS IN PROMOTION. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has occured where no cast should be required." << std::endl;
		outStream << std::endl;
		outStream << "Please remove the use of this casting function," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
	
	// Always check for loss of data due to casting
	// and if so send DSTOP message.
	if (std::numeric_limits<FromType>::is_integer || std::numeric_limits<ToType>::is_integer) {
		if (fromValue != (FromType)toValue) {
			castingResultsInLossOfData = true;
		}
	}
	// check if floating point loss.
	// X64 RBerge - Split out to a separate template so template instantiation isn't blindly casting e.g. Uint64 to double when compiling these statements
	else if (std::numeric_limits<FromType>::is_integer && !std::numeric_limits<ToType>::is_integer && DemotionDoubleTest (toValue, fromValue)) {
		castingResultsInLossOfData = true;
	}
	else if (std::numeric_limits<ToType>::is_integer && !std::numeric_limits<FromType>::is_integer && DemotionDoubleTest (fromValue, toValue)) {
		castingResultsInLossOfData = true;
	}

	if (castingResultsInLossOfData) {
		std::ostringstream outStream;

		outStream << "CASTING RESULTS IN LOSS OF DATA. PLEASE STOP AND EVALUATE." << std::endl;
		outStream << std::endl;
		outStream << "Casting has caused a loss of data." << std::endl;
		outStream << std::endl;
		outStream << "Please evaluate this cast to determine what may be done to fix this error," << std::endl;
		outStream << "or submit a bug that includes steps on how to reproduce this assert." << std::endl;
		outStream << std::endl;
		outStream << "Cast of:" << std::endl;
		outStream << std::endl;
		outStream << "  " << typeid(FromType).name() << "  to  " << typeid(ToType).name() << std::endl;
		outStream << std::endl;
		outStream << "Has changed value from:" << std::endl;
		outStream << std::endl;
		outStream << "  " << fromValue << "  to  " << toValue << std::endl << std::ends;

		DSTOP((toWhom, "%s", outStream.str().c_str()));
	}
#endif // #if TEST #else !TEST
    
	// Return cast input value.
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastToPointer(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue){
	ToType toValue;
	
	toValue = reinterpret_cast<ToType>(static_cast<uintptr_t>(fromValue));
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastToPointer(const FromType fromValue){
	ToType toValue;
	
	toValue = reinterpret_cast<ToType>(static_cast<uintptr_t>(fromValue));
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastFromPointer(const TProgrammer& TEST_ONLY(toWhom), const FromType fromValue){
	ToType toValue;
	
	toValue = static_cast<ToType>(reinterpret_cast<uintptr_t>(fromValue));
	return toValue;
}

template <typename ToType, typename FromType>
#if !(GS_MAC && TEST)
inline 
#endif
ToType CastFromPointer(const FromType fromValue){
	ToType toValue;
	
	toValue = static_cast<ToType>(reinterpret_cast<uintptr_t>(fromValue));
	return toValue;
}

inline size_t operator""_szt(unsigned long long int number)
{
	return static_cast<size_t>( number );
}


///////////////////////////////////////////////////////////////////////////////
//	PIN template function (constrains input v to be in the interval [lo, hi].)
//

template <class T1, class T2, class T3>
inline T1 PIN(const T1& v, const T2& lo, const T3& hi)
	{ return (v < (T1)lo) ? (T1)lo : (v >(T1) hi) ? (T1)hi : v; }


/*
template <class T>
inline const T& PIN(const T& v, const T& lo, const T& hi)
	{ return (v < lo) ? lo : (v > hi) ? hi : v; }

template <class IntegralType>
inline IntegralType PIN(IntegralType v, Sint32 lo, Sint32 hi)
	{ return (v < (IntegralType)lo) ? (IntegralType) lo : (v > (IntegralType)hi) ? (IntegralType) hi : v; }

inline Sint32 PIN(Sint32 v, Sint32 lo, Sint32 hi)
	{ return (v < lo) ? lo : (v > hi) ? hi : v; }
*/

inline Sint32 PIN(Sint32 v, Sint32 lo, Sint32 hi, Bool8& outWasPinned)
{
	Sint32 result = (v < lo) ? lo : (v > hi) ? hi : v;
	outWasPinned = (v == result) ? false : true;
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
force_inline float DoubleToFloat(double dblVal)
//
// We use this func in case we ever end up needing it to
// check for overflow.
////////////////////////////////////////////////////////////
{
	double pinnedDouble = PinTo<float>(kBiplab, dblVal);
	ASSERTN(kMark, (pinnedDouble == dblVal));

	return (float) pinnedDouble;
}	

