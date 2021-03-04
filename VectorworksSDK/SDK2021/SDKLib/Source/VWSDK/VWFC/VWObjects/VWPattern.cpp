//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::VWObjects;

VWPattern::VWPattern(bool isFillPattern)
	: VWPattern( 0, isFillPattern )
{
}

VWPattern::VWPattern(InternalIndex index, bool isFillPattern)
{
	
	if(isFillPattern){
		// 0 if h is an object with no fill pattern 
		// [none is 0, white is 1, black is 2, and so on.
		// If the object is hatched, the number is negative, and valid values are not consecutive.
		fFillPatternIndex	= index;
		fbIsFillPattern		= true;
		fPenPatternIndex	= 0;
	}
	else{
		// 0 if h is an object with no pen pattern (e.g. group). 
		// [none is 0, white is 1, black is 2, and so on.]
		fPenPatternIndex	= index;
		fbIsFillPattern		= false;
		fFillPatternIndex	= 0;
	}
}


VWPattern::~VWPattern()
{
}

VWPattern::operator InternalIndex() const
{
	return fbIsFillPattern ? fFillPatternIndex : fPenPatternIndex;
}

Boolean VWPattern::IsNonePattern() const
{
	return fbIsFillPattern ? fFillPatternIndex == 0 : fPenPatternIndex == 0;
}

void VWPattern::SetNonePattern()
{
	if ( fbIsFillPattern )
		fFillPatternIndex	= 0;
	else
		fPenPatternIndex	= 0;
}

Boolean VWPattern::IsSolidPattern() const
{
	return fbIsFillPattern ? (fFillPatternIndex == 1 || fFillPatternIndex == 2) : (fPenPatternIndex ==  1 || fPenPatternIndex == 2) ;
}

void VWPattern::SetSolidPattern()
{
	if ( fbIsFillPattern )
		fFillPatternIndex	= 1;
	else
		fPenPatternIndex	= 2;
}

Boolean VWPattern::IsHatchPattern() const
{
	// this applicable only for fill patterns
	VWFC_ASSERT( fbIsFillPattern );
	if ( ! fbIsFillPattern )
		return false;

	if ( fFillPatternIndex >= 0 )
		return false;
	if ( fFillPatternIndex == -2 )
		return true;

	InternalIndex	absIndex	= abs( fFillPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	return type == kHatchDefNode;
}

/*Boolean VWPattern::IsDashPattern() const
{
	// this is applicable only for pen patterns
	VWFC_ASSERT( ! fbIsFillPattern );
	if ( fbIsFillPattern )
		return false;

	if (fPenPatternIndex >= 0)
		return false;

	InternalIndex	absIndex	= abs( fPenPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	if (type == kLineTypeDefNode){
		TVariableBlock	value;
		gSDK->GetObjectVariable( hObj, ovLineTypeIsSimple, value );

		Boolean isSimpleLT = false;
		return value.GetBoolean( isSimpleLT ) && isSimpleLT;
		
	}
	return false; 
}*/

Boolean VWPattern::IsLineTypePattern() const
{
	// this is applicable only for pen patterns
	VWFC_ASSERT( ! fbIsFillPattern );
	if ( fbIsFillPattern )
		return false;

	if (fPenPatternIndex >= 0)
		return false;

	InternalIndex	absIndex	= abs( fPenPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	return  (type == kLineTypeDefNode);
}

Boolean VWPattern::IsGradientPattern() const
{
	// this applicable only for fill patterns
	VWFC_ASSERT( fbIsFillPattern );
	if ( ! fbIsFillPattern )
		return false;

	if ( fFillPatternIndex >= 0 )
		return false;
	if ( fFillPatternIndex == -2 )
		return true;

	InternalIndex	absIndex	= abs( fFillPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	return type == kGradientDefNode;
}

Boolean VWPattern::IsImagePattern() const
{
	// this applicable only for fill patterns
	VWFC_ASSERT( fbIsFillPattern );
	if ( ! fbIsFillPattern )
		return false;

	if ( fFillPatternIndex >= 0 )
		return false;
	if ( fFillPatternIndex == -2 )
		return true;

	InternalIndex	absIndex	= abs( fFillPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	return type == kImageDefNode;
}

Boolean VWPattern::IsTilePattern() const
{
	// this applicable only for fill patterns
	VWFC_ASSERT( fbIsFillPattern );
	if ( ! fbIsFillPattern )
		return false;

	if ( fFillPatternIndex >= 0 )
		return false;
	if ( fFillPatternIndex == -2 )
		return true;

	InternalIndex	absIndex	= abs( fFillPatternIndex );

	MCObjectHandle	hObj		= ::GS_InternalIndexToHandle( gCBP, absIndex );
	if ( hObj == NULL )
		return false;

	short			type	= gSDK->GetObjectTypeN( hObj );
	return type == kTileDefNode;
}
