//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;
using namespace VWFC::Tools;

VWTextureShaderBase::VWTextureShaderBase()
	// protected constructor for inherited objects
{
	fhObject		= NULL;
}

VWTextureShaderBase::VWTextureShaderBase(MCObjectHandle hShaderRecord)
{
	fhObject		= hShaderRecord;
}

VWTextureShaderBase::VWTextureShaderBase(const VWTextureShaderBase& src)
{
	fhObject		= src.fhObject;
}

VWTextureShaderBase::~VWTextureShaderBase()
{
	fhObject		= nil;
}

VWTextureShaderBase& VWTextureShaderBase::operator=(const VWTextureShaderBase& src)
{
	fhObject		= src.fhObject;
	return *this;
}

bool VWTextureShaderBase::GetShaderRecordFamilyAndPrototype(ShaderFamily& family, Sint32& prototype) const
{
	return VWTextureShaderBase::GetShaderRecordFamilyAndPrototype( fhObject, family, prototype );
}

/*static*/ bool VWTextureShaderBase::GetShaderRecordFamilyAndPrototype(MCObjectHandle hObj, ShaderFamily& family, Sint32& prototype)
{
	bool result = false;


	if (VERIFYHANDLE(kDaveD, hObj, sizeof(NGNodeType))) {

		// Get family and prototype fields

		TRecordHandler recordHandler(hObj);
		
		TRecordItem recordItem(kFieldLongInt);

		Sint32	valueFamily = 0L;
		if (recordHandler.GetFieldObject(1, recordItem) && recordItem.GetFieldValue(valueFamily) &&
				recordHandler.GetFieldObject(2, recordItem) && recordItem.GetFieldValue(prototype)) {

			family	= (ShaderFamily) valueFamily;
			result = true;
		}
	}


	return result;
}

Sint32 VWTextureShaderBase::GetShaderRecordLong(short fieldID) const
{
	Sint32 result = 0L;

	TRecordHandler recordHandler(fhObject);
	TRecordItem recordItem(kFieldLongInt);

	Sint32 longValue = 0L;
	if (VERIFYN(kDaveD, recordHandler.GetFieldObject(fieldID, recordItem)) && VERIFYN(kDaveD, recordItem.GetFieldValue(longValue)))
		result = longValue;

	return result;
}

double VWTextureShaderBase::GetShaderRecordDouble(short fieldID) const
{
	double result = 0.0;

	TRecordHandler recordHandler(fhObject);
	TRecordItem recordItem(kFieldReal);

	double doubleValue = 0.0;
	if (VERIFYN(kDaveD, recordHandler.GetFieldObject(fieldID, recordItem)) && VERIFYN(kDaveD, recordItem.GetFieldValue(doubleValue)))
		result = doubleValue;

	return result;
}

WorldCoord VWTextureShaderBase::GetShaderRecordCoord(short fieldID) const
{
	WorldCoord result = 0.0;

	TRecordHandler recordHandler(fhObject);
	TRecordItem recordItem(kFieldCoordDisp);

	WorldCoord coordValue = 0.0;
	if (VERIFYN(kDaveD, recordHandler.GetFieldObject(fieldID, recordItem)) && VERIFYN(kDaveD, recordItem.GetFieldValue(coordValue)))
		result = coordValue;

	return result;
}

CRGBColor VWTextureShaderBase::GetShaderRecordColor(short fieldID) const
{
	Sint32 redLong = GetShaderRecordLong(fieldID);
	Sint32 greenLong = GetShaderRecordLong(fieldID + 1);
	Sint32 blueLong = GetShaderRecordLong(fieldID + 2);
	
	CRGBColor color( (Uint8) (redLong & 0xff), (Uint8) (greenLong & 0xff), (Uint8) (blueLong & 0xff) );

	return color;
}

bool VWTextureShaderBase::GetShaderRecordBool(short fieldID) const
{
	bool result = false;

	TRecordHandler recordHandler(fhObject);
	TRecordItem recordItem(kFieldBoolean);

	Boolean boolValue = 0L;
	if (VERIFYN(kDaveD, recordHandler.GetFieldObject(fieldID, recordItem)) && VERIFYN(kDaveD, recordItem.GetFieldValue(boolValue)))
		result = boolValue;

	return result;
}

void VWTextureShaderBase::SetShaderRecordLong(short fieldID, Sint32 value)
{
	TRecordItem recordItem(kFieldLongInt);
	recordItem.SetFieldValue(value);
	
	TRecordHandler recordHandler(fhObject);
	recordHandler.SetFieldObject(fieldID, recordItem);
}

void VWTextureShaderBase::SetShaderRecordColor(short fieldID, const CRGBColor& color)
{
	unsigned char redChar		= color.GetRed();
	unsigned char greenChar		= color.GetGreen();
	unsigned char blueChar		= color.GetBlue();

	this->SetShaderRecordLong(fieldID, redChar);
	this->SetShaderRecordLong(fieldID + 1, greenChar);
	this->SetShaderRecordLong(fieldID + 2, blueChar);
}

void VWTextureShaderBase::SetShaderRecordDouble(short fieldID, double value)
{
	TRecordItem recordItem(kFieldReal);
	recordItem.SetFieldValue(value);
	
	TRecordHandler recordHandler(fhObject);
	recordHandler.SetFieldObject(fieldID, recordItem);
}

void VWTextureShaderBase::SetShaderRecordBool(short fieldID, bool value)
{
	TRecordItem recordItem(kFieldBoolean);
	recordItem.SetFieldValue((Boolean) value);
	
	TRecordHandler recordHandler(fhObject);
	recordHandler.SetFieldObject(fieldID, recordItem);
}

void VWTextureShaderBase::SetShaderRecordCoord(short fieldID, WorldCoord value)
{
	TRecordItem recordItem(kFieldCoordDisp);
	recordItem.SetFieldValue(value);
	
	TRecordHandler recordHandler(fhObject);
	recordHandler.SetFieldObject(fieldID, recordItem);
}

