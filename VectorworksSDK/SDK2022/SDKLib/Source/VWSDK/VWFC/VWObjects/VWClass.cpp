//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Tools;
using namespace VWFC::VWObjects;

VWClass::VWClass(InternalIndex index)
{
	fClassIndex				= index;
	
	VWFC_VERIFY(::GS_ValidClass( gCBP, fClassIndex ));
//	if ( ! bValidClass )
//		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "invalid class internal index passed" );
}

VWClass::VWClass(const TXString& name)
{
	fClassIndex				= 0;
	fClassIndex				= ::GS_AddClass( gCBP, name );

	Boolean		bValidClass	= ::GS_ValidClass( gCBP, fClassIndex );
	VWFC_ASSERT( bValidClass );
	if ( ! bValidClass ) {
		fClassIndex	= gSDK->GetNoneClassID();
	}
}

VWClass::~VWClass()
{
}

VWClass::operator InternalIndex() const
{
	return fClassIndex;
}

VWClassAttr VWClass::GetClassAttribs() const
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	return VWClassAttr( fClassIndex );
}

void VWClass::SetThisClassAsDefault() const
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	::GS_SetDefaultClass( gCBP, fClassIndex );
}

bool VWClass::IsValidClass() const
{
	return ::GS_ValidClass( gCBP, fClassIndex );
}

TXString VWClass::GetName() const
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	InternalName className;
	::GS_ClassIDToName( gCBP, fClassIndex, className );
	return className;
}

void VWClass::DeleteThisClass()
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	InternalName className;
	::GS_ClassIDToName( gCBP, fClassIndex, className );
	::GS_DeleteClass( gCBP, className );
}

EClassVisibility VWClass::IsClassVisible() const
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	return (EClassVisibility) ::GS_GetClVisibility( gCBP, fClassIndex );
}

void VWClass::SetClassVisible(EClassVisibility visibility)
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	::GS_SetClVisibility( gCBP, fClassIndex, (short) visibility );
}

bool VWClass::GetUseGraphics() const
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	return ::GS_GetClUseGraphic( gCBP, fClassIndex );
}

void VWClass::SetUseGraphics(bool use)
{
	VERIFYN( kVStanev, ::GS_ValidClass( gCBP, fClassIndex ) );
	::GS_SetClUseGraphic( gCBP, fClassIndex, use );
}

TXString VWClass::GetClassDescription()
{
	TXString	result;
	VERIFYN ( kKIvanov, ::GS_ValidClass( gCBP, fClassIndex ) );
	MCObjectHandle classDef = gSDK->InternalIndexToHandle( fClassIndex );
	if ( classDef && ( gSDK->GetObjectTypeN( classDef ) == kClassDefNode ) )
	{
		result	= gSDK->GetDescriptionText( classDef );
	}
	return result;
}

void VWClass::SetClassDescription(const TXString& description)
{
	VERIFYN (kMLieblein, ::GS_ValidClass( gCBP, fClassIndex ) );
	MCObjectHandle classDef = gSDK->InternalIndexToHandle(fClassIndex);
	if (classDef && (gSDK->GetObjectTypeN(classDef)==kClassDefNode)) {
		gSDK->SetDescriptionText (classDef, description);
	}
}

bool VWClass::EditWithUI() const
{
	return gSDK->EditClassWithUI( fClassIndex );
}

bool VWClass::IsValidClassName(const TXString& name)
{
	bool	isValid	= false;
	if ( ! name.IsEmpty() ) {
		InternalIndex	index				= 0;
		index				= ::GS_ClassNameToID( gCBP, name );

		isValid	= (index != InternalIndex(-1)) ? ::GS_ValidClass( gCBP, index ) : false;
	}

	return isValid;
}

bool VWClass::IsValidClassIndex(InternalIndex index)
{
	return ::GS_ValidClass( gCBP, index );
}

bool VWClass::IsValidClassHandle(MCObjectHandle h)
{
	short type = gSDK->GetObjectTypeN( h );
	return type == kClassDefNode;
}

InternalIndex VWClass::GetClassFromHandle(MCObjectHandle hClass)
{
	InternalIndex result = 0;
	
	short type = gSDK->GetObjectTypeN( hClass );
	if ( type == kClassDefNode )
	{
		result = gSDK->GetObjectInternalIndex( hClass );
	}

	return result;
}

InternalIndex VWClass::GetClassIDByName(const TXString& name)
{
	return ::GS_ClassNameToID( gCBP, name );
}

InternalIndex VWClass::GetMaxClassIndex()
{
	return ::GS_MaxClassID( gCBP );
}

InternalIndex VWClass::AddGuidesClass()
{
	return ::GS_AddGuidesClass( gCBP );
}

InternalIndex VWClass::GetDimensionClassIndex()
{
	return ::GS_GetDimensionClassID( gCBP );
}

InternalIndex VWClass::GetNoneClassIndex()
{
	return ::GS_GetNoneClassID( gCBP );
}

InternalIndex VWClass::GetDefaultClass()
{
	return ::GS_GetDefaultClass( gCBP );
}

EClassOptions VWClass::GetProgramVar_ClassOptions()
{
	short	value;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varClassOptions, & value ) );
	return (EClassOptions) value;
}

/*static*/ InternalIndex VWClass::CreateClassWithUI(TXString& inOutName)
{
	return gSDK->AddClassWithUI( inOutName );
}

/*static*/ void VWClass::ForEachClass(bool doGuestClasses, std::function<void(const VWClass& clas)> callback)
{
	gSDK->ForEachClass( doGuestClasses, [&callback](MCObjectHandle h)
	{
		short type = gSDK->GetObjectTypeN( h );
		if ( type == kClassDefNode )
		{
			VWClass	clas( gSDK->GetObjectInternalIndex( h ) );
			callback( clas );
		}
	});
}
