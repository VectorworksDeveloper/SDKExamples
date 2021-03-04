//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/VWPluginToolCustomBar.h"

using namespace VWFC::PluginSupport;

// ---------------------------------------------------------------------------------------------
CustomBarRefID*		VWPluginToolCustomBar::fpArrCustomBarRefIDs			= NULL;
size_t		VWPluginToolCustomBar::fnCustomBarsRefIDsCount		= 0;
void VWPluginToolCustomBar::SetCustomBars(CustomBarRefID* pArrBarRefIDs, size_t count)
{
	VWPluginToolCustomBar::fpArrCustomBarRefIDs			= pArrBarRefIDs;	
	VWPluginToolCustomBar::fnCustomBarsRefIDsCount		= count;
}

// ---------------------------------------------------------------------------------------------
SCustomBarFieldInfo::SCustomBarFieldInfo()
{
	fIsEditable		= true;
	fIsLocked		= true;
}

SCustomBarFieldInfo::SCustomBarFieldInfo(const char* szLabel)
{
	fstrFieldLabel	= szLabel;
	fIsEditable		= true;
	fIsLocked		= true;
}

// ---------------------------------------------------------------------------------------------
VWPluginToolCustomBar::VWPluginToolCustomBar(size_t id)
{
	// check if everything is ok with internal tool handling
	VWFC_ASSERT( VWPluginToolCustomBar::fpArrCustomBarRefIDs );

	// check this ID to the max custom bars allowed
	VWFC_ASSERT( id < VWPluginToolCustomBar::fnCustomBarsRefIDsCount );

	fpCustomBarRefID		= NULL;
	if ( VWPluginToolCustomBar::fpArrCustomBarRefIDs && id < VWPluginToolCustomBar::fnCustomBarsRefIDsCount ) {
		fpCustomBarRefID			= & VWPluginToolCustomBar::fpArrCustomBarRefIDs[ id ];
	}
}

VWPluginToolCustomBar::VWPluginToolCustomBar(const VWPluginToolCustomBar& src)
{
	VWFC_ASSERT( false );
}

VWPluginToolCustomBar::~VWPluginToolCustomBar()
{
}

VWPluginToolCustomBar& VWPluginToolCustomBar::operator=(const VWPluginToolCustomBar& src)
{
	VWFC_ASSERT( false );
	return *this;
}

bool VWPluginToolCustomBar::Create(size_t fieldsCount)
{
	VWFC_ASSERT( fieldsCount > 0 );
	// dont create it twice
	VWFC_ASSERT( fpCustomBarRefID );

	bool	ok		= false;
	if ( fpCustomBarRefID ) {
		CustomBarRefID		refID	= 0;
		ok					= ::GS_CustomBarCreate( gCBP, DemoteTo<short>( kVStanev, fieldsCount ), refID ) ? true : false; 

		*fpCustomBarRefID	= refID;

	}

	return ok;
}

void VWPluginToolCustomBar::Install()
{
	VWFC_ASSERT( fpCustomBarRefID );
	if ( fpCustomBarRefID )
		::GS_CustomBarInstall( gCBP, *fpCustomBarRefID );
}

void VWPluginToolCustomBar::Release()
{
	GS_CustomBarInstall( gCBP, 0 );

	if ( fpCustomBarRefID ) {
		::GS_CustomBarRelease( gCBP, *fpCustomBarRefID );
		*fpCustomBarRefID		= 0;
	}
}

bool VWPluginToolCustomBar::IsValid() const
{
	return fpCustomBarRefID && *fpCustomBarRefID != 0;
}

SCustomBarFieldInfo VWPluginToolCustomBar::GetFieldInfo(size_t fieldIndex)
{
	VWFC_ASSERT( fpCustomBarRefID );

	SCustomBarFieldInfo	result;
	if ( fpCustomBarRefID ) {
		CustomBarFieldInfo	fieldInfo;
		VWFC_VERIFY( ::GS_CustomBarGetFieldInfo( gCBP, *fpCustomBarRefID, DemoteTo<short>( kVStanev, fieldIndex), fieldInfo ) );

		result.fstrFieldLabel		= fieldInfo.fFieldLabel;
		result.fstrFieldValue		= fieldInfo.fFieldValue;
		result.fIsEditable			= fieldInfo.fIsEditable ? true : false;
		result.fIsLocked			= fieldInfo.fIsLocked ? true : false;
	}

	return result;
}

void VWPluginToolCustomBar::SetFieldInfo(size_t fieldIndex, const SCustomBarFieldInfo& info)
{
	VWFC_ASSERT( fpCustomBarRefID );

	if ( fpCustomBarRefID ) {
		CustomBarFieldInfo	fieldInfo;
		fieldInfo.fFieldLabel	= info.fstrFieldLabel;
		fieldInfo.fFieldValue	= info.fstrFieldValue;
		fieldInfo.fIsEditable	= info.fIsEditable;
		fieldInfo.fIsLocked		= info.fIsLocked;

		VWFC_VERIFY( ::GS_CustomBarSetFieldInfo( gCBP, *fpCustomBarRefID, DemoteTo<short>( kVStanev, fieldIndex), fieldInfo ) );
	}
}


void VWPluginToolCustomBar::SetFieldAngle(size_t fieldIndex, double angle)
{
	VWFC_ASSERT( fpCustomBarRefID );
	
	if ( fpCustomBarRefID ) {
		VWFC_VERIFY( ::GS_CustomBarSetFieldAngle( gCBP, *fpCustomBarRefID, DemoteTo<short>( kVStanev, fieldIndex), angle ) );
	}
}

void VWPluginToolCustomBar::SetFieldWorldCoord(size_t fieldIndex, double value)
{
	VWFC_ASSERT( fpCustomBarRefID );

	if ( fpCustomBarRefID ) {
		VWFC_VERIFY( ::GS_CustomBarSetFieldWorldCoord( gCBP, *fpCustomBarRefID, DemoteTo<short>( kVStanev, fieldIndex), value ) );
	}
}

void VWPluginToolCustomBar::DataDisplayBar_SetField(size_t fieldIndex, BarNumberType type, const TXString& label)
{
	::GS_SetDataDisplayBarField( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), type, label );
}

void VWPluginToolCustomBar::DataDisplayBar_Clear()
{
	::GS_ClearDataDisplayBar( gCBP );
}

void VWPluginToolCustomBar::UserBar_SetDimValue(size_t fieldIndex, double dimValue)
{
	::GS_SetDimUserBarValue( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), dimValue );
}

void VWPluginToolCustomBar::UserBar_SetFloatValueGeneral(size_t fieldIndex, double value)
{
	::GS_SetFloatUserBarValueN( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), value, -1 );
}

void VWPluginToolCustomBar::UserBar_SetFloatValueAngle(size_t fieldIndex, double value)
{
	::GS_SetFloatUserBarValueN( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), value, -2 );
}

void VWPluginToolCustomBar::UserBar_SetFloatValue(size_t fieldIndex, double value, Uint8 numPlaces)
{
	::GS_SetFloatUserBarValueN( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), value, numPlaces );
}

void VWPluginToolCustomBar::UserBar_SetTextValue(size_t fieldIndex, const TXString& text)
{
	::GS_SetTextUserBarValue( gCBP, DemoteTo<short>( kVStanev, fieldIndex+1), text );
}
