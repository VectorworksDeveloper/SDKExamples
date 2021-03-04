//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

#include "VWFC//PluginSupport/DirectModellingSupport.h"


using namespace VWFC::PluginSupport;

// ------------------------------------------------------------------------------------------------------
CParametricHotSpot::CParametricHotSpot()
{
	fHotspotID	= 0;
	fType		= kScreenPlanarSelBox;
	fCursorSpec = "";
	fUserData	= 0;
}

CParametricHotSpot::CParametricHotSpot(HotSpotType type, const WorldPt3& location, const TXString& tipText, Sint32 data)
{
	fHotspotID	= 0;
	fType		= type;
	fLocation	= location;
	fCursorSpec = "";
	fTipText	= tipText;
	fUserData	= data;
}

CParametricHotSpot::CParametricHotSpot(HotSpotType type, const WorldPt3& location, const TXString& cursorSpec, const TXString& tipText, Sint32 data)
{
	fHotspotID	= 0;
	fType		= type;
	fLocation	= location;
	fCursorSpec	= cursorSpec;
	fTipText	= tipText;
	fUserData	= data;
}

CParametricHotSpot::~CParametricHotSpot()
{
}

void CParametricHotSpot::Add()
{
	if ( fHotspotID != 0 ) {
		this->Remove();
	}
	fHotspotID	= gSDK->AddHotSpotN( fType, fLocation, fCursorSpec, fTipText, (Sint32)fUserData );
}

void CParametricHotSpot::Remove()
{
	if ( fHotspotID != 0 ) {
		gSDK->RemoveHotSpot( fHotspotID );
	}
	fHotspotID	= 0;
}

bool CParametricHotSpot::IsAdded() const
{
	return fHotspotID != 0;
}

void CParametricHotSpot::Set(HotSpotType type, const WorldPt3& location, const TXString& tipText)
{
	fType		= type;
	fLocation	= location;
	fCursorSpec.Clear();

	fTipText	= tipText;
	if ( fHotspotID != 0 ) {
		this->Remove();
		this->Add();
	}
}

void CParametricHotSpot::Set(HotSpotType type, const WorldPt3& location, const TXString& cursorSpec, const TXString& tipText)
{
	fType		= type;
	fLocation	= location;
	fCursorSpec	= cursorSpec;
	fTipText	= tipText;
	if ( fHotspotID != 0 ) {
		this->Remove();
		this->Add();
	}
}

void CParametricHotSpot::SetLocation(const WorldPt3& location)
{
	fLocation	= location;
	if ( fHotspotID != 0 ) {
		this->Remove();
		this->Add();
	}
}

HotSpotRefID CParametricHotSpot::GetHotspotID() const
{
	return fHotspotID;
}

const WorldPt3& CParametricHotSpot::GetLocation() const
{
	return fLocation;
}

SintptrT CParametricHotSpot::GetUserData() const
{
	return fUserData;
}

void CParametricHotSpot::SetUserData(SintptrT userData)
{
	fUserData	= userData;
}

// ------------------------------------------------------------------------------------------------------
CParametricCustomBar::CParametricCustomBar()
{
	fCustomBarID	= 0;
}

CParametricCustomBar::~CParametricCustomBar()
{
}

bool CParametricCustomBar::IsValid() const
{
	return fCustomBarID != 0;
}

CustomBarRefID CParametricCustomBar::GetCustomBarID() const
{
	return fCustomBarID;
}

bool CParametricCustomBar::Create()
{
	ASSERTN( kVStanev, fCustomBarID == 0 );
	return gSDK->CustomBarCreate( DemoteTo<short>( kVStanev, farrFields.size() ), fCustomBarID );
}

void CParametricCustomBar::Release()
{
	if ( fCustomBarID != 0 ) {
		gSDK->CustomBarRelease( fCustomBarID );
	}
	fCustomBarID	= 0;
}

void CParametricCustomBar::Install()
{
	if ( VERIFYN( kVStanev, fCustomBarID != 0 ) ) {
		gSDK->CustomBarInstall( fCustomBarID );
	}
}

void CParametricCustomBar::Pause(bool beginPause)
{
	if ( beginPause ) {
		gSDK->CustomBarInstall( 0 );
	}
	else {
		if ( fCustomBarID != 0 ) {
			gSDK->CustomBarInstall( fCustomBarID );
		}
	}
}

void CParametricCustomBar::ClearFields()
{
	farrFields.clear();
}

void CParametricCustomBar::AddField(const TXString& field)
{
	CustomBarFieldInfo theField;
	theField.fIsEditable	= true;
	theField.fFieldLabel = field;

	farrFields.push_back( theField );
}

void CParametricCustomBar::SetUp()
{
	if ( this->IsValid() ) {
		size_t	fieldsCnt	= farrFields.size();
		for(size_t i=0; i<fieldsCnt; i++) {
			const CustomBarFieldInfo& fi	= farrFields[ i ];
			gSDK->CustomBarSetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, i), fi );
		}
	}
}

void CParametricCustomBar::SetDown()
{
}

void CParametricCustomBar::SetFieldWorldCoord(size_t fieldIndex, WorldCoord value)
{
	if ( this->IsValid() ) {
		gSDK->CustomBarSetFieldWorldCoord( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), value );
	}
}

void CParametricCustomBar::SetFieldAngle(size_t fieldIndex, WorldCoord value)
{
	if ( this->IsValid() ) {
		gSDK->CustomBarSetFieldAngle( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), value );
	}
}

void CParametricCustomBar::SetFieldText(size_t fieldIndex, const TXString& value)
{
	if ( this->IsValid() ) {
		CustomBarFieldInfo fi;
		gSDK->CustomBarGetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), fi );
		fi.fFieldValue	= value;
		gSDK->CustomBarSetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), fi );
	}
}

void CParametricCustomBar::SetFieldLock(size_t fieldIndex, bool isLocked)
{
	if ( this->IsValid() ) {
		CustomBarFieldInfo fi;
		gSDK->CustomBarGetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), fi );
		fi.fIsLocked	= isLocked;
		gSDK->CustomBarSetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), fi );
	}
}

void CParametricCustomBar::GetFieldDef(size_t fieldIndex, CustomBarFieldInfo& outInfo)
{
	if ( this->IsValid() )
	{
		gSDK->CustomBarGetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), outInfo );
	}
}

void CParametricCustomBar::SetFieldDef(size_t fieldIndex, const CustomBarFieldInfo& info)
{
	if ( this->IsValid() )
	{
		gSDK->CustomBarSetFieldInfo( fCustomBarID, DemoteTo<short>(kVStanev, fieldIndex), info );
	}
}

/*static*/ void CParametricCustomBar::SetSmartCursorLockX(double value)
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialX, &value );
}

/*static*/ void CParametricCustomBar::SetSmartCursorLockY(double value)
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialY, &value );
}

/*static*/ void CParametricCustomBar::SetSmartCursorLockLength(double value)
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialLength, &value );
}

/*static*/ void CParametricCustomBar::SetSmartCursorLockAngle(double value)
{
	WorldPt angleLockPt( WorldPtFromXAngle( value, 1.0 ) );
	gSDK->SetProgramVariable( varSmartCursorLockSpecialAngle2D, &angleLockPt );
}

/*static*/ void CParametricCustomBar::ClearSmartCursorLockX()
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialX, nullptr );
}

/*static*/ void CParametricCustomBar::ClearSmartCursorLockY()
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialY, nullptr );
}

/*static*/ void CParametricCustomBar::ClearSmartCursorLockLength()
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialLength, nullptr );
}

/*static*/ void CParametricCustomBar::ClearSmartCursorLockAngle()
{
	gSDK->SetProgramVariable( varSmartCursorLockSpecialAngle2D, nullptr );
}

