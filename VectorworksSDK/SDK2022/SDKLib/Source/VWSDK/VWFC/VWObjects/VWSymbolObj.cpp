//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWSymbolObj::VWSymbolObj(const TXString& symDefName, const VWPoint2D& location, double dRotDeg)
{
	fhObject	= ::GS_PlaceSymbolByNameN( gCBP, symDefName, location, dRotDeg );
	VWFC_ASSERT( fhObject );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol object" );
}

VWSymbolObj::VWSymbolObj(const VWSymbolDefObj& symDef, const VWPoint2D& location, double dRotDeg)
{
	fhObject	= ::GS_PlaceSymbolN( gCBP, (MCObjectHandle) symDef, location, dRotDeg );
	VWFC_ASSERT( fhObject );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol object" );
}

VWSymbolObj::VWSymbolObj(MCObjectHandle hSymbolDef, const VWPoint2D& location, double dRotDeg)
{
	fhObject	= ::GS_PlaceSymbolN( gCBP, hSymbolDef, location, dRotDeg );
	VWFC_ASSERT( fhObject );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol object" );
}

VWSymbolObj::VWSymbolObj(const VWSymbolDefObj& symDef, const VWTransformMatrix& transform)
{
	fhObject	= ::GS_PlaceSymbolN( gCBP, (MCObjectHandle) symDef, WorldPt(0,0), 0 );
	VWFC_ASSERT( fhObject );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol object" );
	gSDK->SetEntityMatrix( fhObject, transform );
}

VWSymbolObj::VWSymbolObj(MCObjectHandle hSymbolDef, const VWTransformMatrix& transform)
{
	fhObject	= ::GS_PlaceSymbolN( gCBP, hSymbolDef, WorldPt(0,0), 0 );
	VWFC_ASSERT( fhObject );
//	if ( fhObject == NULL )
//		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create symbol object" );
	gSDK->SetEntityMatrix( fhObject, transform );
}

VWSymbolObj::VWSymbolObj(MCObjectHandle hSymbol)
{
	VWFC_ASSERT( VWSymbolObj::IsSymbolObject( hSymbol ) );
	if ( ! VWSymbolObj::IsSymbolObject( hSymbol ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject	= hSymbol;
	VWFC_ASSERT( fhObject );
}

VWSymbolObj::VWSymbolObj(const VWSymbolObj& src)
{
	fhObject	= src.fhObject;
	VWFC_ASSERT( fhObject );
}

VWSymbolObj::~VWSymbolObj()
{
}

VWSymbolObj& VWSymbolObj::operator=(const VWSymbolObj& src)
{
	fhObject = src.fhObject;
	return *this;
}

bool VWSymbolObj::IsSymbolObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kSymbolNode;
}

MCObjectHandle VWSymbolObj::GetSymbolDef() const
{
	return ::GS_GetDefinition( gCBP, fhObject );
}

void VWSymbolObj::SetScaleType(ESymScaleType type)
{
	TVariableBlock	var( (Sint16) type );
	gSDK->SetObjectVariable( fhObject, ovSymbolScaleType, var );
}

ESymScaleType VWSymbolObj::GetScaleType() const
{
	TVariableBlock var;
	gSDK->GetObjectVariable( fhObject, ovSymbolScaleType, var );
	Sint16 result = ESymScaleType::kScaleTypeNone;
	var.GetSint16( result );
	return (ESymScaleType)result;
}

void VWSymbolObj::SetScaleFactorX(double scale)
{
	TVariableBlock	var( scale );
	gSDK->SetObjectVariable( fhObject, ovSymbolXScaleFactor, var );
}

double VWSymbolObj::GetScaleFactorX() const
{
	TVariableBlock	var;
	gSDK->GetObjectVariable( fhObject, ovSymbolXScaleFactor, var );
	double result = 0;
	var.GetReal64( result );
	return result;
}

void VWSymbolObj::SetScaleFactorY(double scale)
{
	TVariableBlock	var( scale );
	gSDK->SetObjectVariable( fhObject, ovSymbolYScaleFactor, var );
}

double VWSymbolObj::GetScaleFactorY() const
{
	TVariableBlock	var;
	gSDK->GetObjectVariable( fhObject, ovSymbolYScaleFactor, var );
	double result = 0;
	var.GetReal64( result );
	return result;
}

void VWSymbolObj::SetScaleFactorZ(double scale)
{
	TVariableBlock	var( scale );
	gSDK->SetObjectVariable( fhObject, ovSymbolZScaleFactor, var );
}

double VWSymbolObj::GetScaleFactorZ() const
{
	TVariableBlock	var;
	gSDK->GetObjectVariable(fhObject, ovSymbolZScaleFactor, var);
	double result = 0;
	var.GetReal64(result);
	return result;
}

/*static*/ bool	VWSymbolObj::IsSymbolObject(MCObjectHandle hObj, const TXString& name)
{
	bool result = false;

	short	type	= gSDK->GetObjectTypeN( hObj );
	if ( type == kSymbolNode )
	{
		MCObjectHandle	hSymbolDef		= gSDK->GetDefinition( hObj );
		MCObjectHandle	hNamedSymbolDef	= gSDK->GetNamedObject( name );
		if ( VWSymbolDefObj::IsSymbolDefObject( hSymbolDef ) && VWSymbolDefObj::IsSymbolDefObject( hNamedSymbolDef ) )
		{
			result = (hNamedSymbolDef == hSymbolDef);
		}
	}

	return result;
}

