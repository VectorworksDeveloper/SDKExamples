//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::Tools;
using namespace VWFC::VWObjects;

VWLayerObj::VWLayerObj(const TXString& layerName)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	fhObject		= NULL;
	fhObject	= ::GS_GetNamedLayer( gCBP, layerName );

	if ( fhObject == NULL ) {
		// not found -- create
		fhObject	= ::GS_CreateLayer( gCBP, layerName, (short) kLayerDesign );
	}

	VWFC_ASSERT( fhObject );
	VWFC_ASSERT( VWLayerObj::IsLayerObject( fhObject ) );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create layer" );
}

VWLayerObj::VWLayerObj(const TXString& layerName, ELayerType type)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	fhObject		= NULL;
	fhObject	= ::GS_GetNamedLayer( gCBP, layerName );

	if ( fhObject == NULL ) {
		// not found -- create
		fhObject	= ::GS_CreateLayer( gCBP, layerName, (short) type );
	}
	else {
		ELayerType	thisLayerType	= this->GetLayerType();
		VWFC_ASSERT( thisLayerType == type );
		if ( thisLayerType != type )
			THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "found layer with type not as expected" );
	}

	VWFC_ASSERT( fhObject );
	VWFC_ASSERT( VWLayerObj::IsLayerObject( fhObject ) );
	if ( fhObject == NULL )
		THROW_VWFC_EXCEPTION( VWCannotCreateObjectException, 0, "cannot create layer" );
}

VWLayerObj::VWLayerObj(MCObjectHandle hLayer)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	VWFC_ASSERT( VWLayerObj::IsLayerObject( hLayer ) );
	if ( ! VWLayerObj::IsLayerObject( hLayer ) )
		THROW_VWFC_EXCEPTION( VWBadObjectTypeException, 0, "bad handle type when creating" );
	fhObject	= hLayer;
	VWFC_ASSERT( fhObject );
}

VWLayerObj::VWLayerObj(const VWLayerObj& src)
: VWGroupObj( 0 )	// call nothing doing constructor -- we dont want a new group created
{
	fhObject	= src.fhObject;
	VWFC_ASSERT( fhObject );
}

VWLayerObj& VWLayerObj::operator=(const VWLayerObj& src)
{
	fhObject = src.fhObject;
	return *this;
}

VWLayerObj::~VWLayerObj()
{
}

bool VWLayerObj::IsLayerObject(MCObjectHandle hObj)
{
	short	type	= gSDK->GetObjectTypeN( hObj );
	return type == kLayerNode;
}

double_gs VWLayerObj::GetScale() const
{
	VWFC_ASSERT( fhObject );
	double_gs		scale;
	::GS_GetLayerScaleN( gCBP, fhObject, scale );
	return scale;
}

void VWLayerObj::SetScale(double_gs scale)
{
	VWFC_ASSERT( fhObject );
	::GS_SetLayerScaleN( gCBP, fhObject, scale );
}

Boolean VWLayerObj::IsAmbientLightOn() const
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerAmbientIsOn, value ) );
	Boolean	res;
	VERIFYN( kVStanev, value.GetBoolean( res ) );
	return res;
}

void VWLayerObj::SetAmbientLightOn(Boolean on)
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value( on );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovLayerAmbientIsOn, value ) );
}

double_gs VWLayerObj::GetAmbientBrightness() const
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerAmbientBrightness, value ) );
	double_gs			res;
	VERIFYN( kVStanev, value.GetReal64( res ) );
	return res;
}

void VWLayerObj::SetAmbientBrightness(double_gs brightness)
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value( brightness );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovLayerAmbientBrightness, value ) );
}

CRGBColor VWLayerObj::GetAmbientColor() const
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerAmbientColor, value ) );
	WorldPt3	rgb;
	VERIFYN( kVStanev, value.GetWorldPt3( rgb ) );
	return CRGBColor( (Uint8) rgb.x, (Uint8) rgb.y, (Uint8) rgb.z );
}

void VWLayerObj::SetAmbientColor(const CRGBColor& rgb)
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value( WorldPt3( rgb.GetRed(), rgb.GetGreen(), rgb.GetBlue() ) );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovLayerAmbientColor, value ) );
}

ELayerVisibility VWLayerObj::GetVisibility() const
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerVisibility, value ) );
	short				res;
	VERIFYN( kVStanev, value.GetSint16( res ) );
	return (ELayerVisibility) res;
}

void VWLayerObj::SetVisibility(ELayerVisibility vis)
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value( (Sint16) vis );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovLayerVisibility, value ) );
}

Sint32 VWLayerObj::GetSheetPrintDPI() const
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerDPI, value ) );
	Sint16				res;
	VERIFYN( kVStanev, value.GetSint16( res ) );
	return (Sint32) res;
}

void VWLayerObj::SetSheetPrintDPI(Sint32 dpi)
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	TVariableBlock		value( (Sint32) dpi );
	VERIFYN( kVStanev, ::GS_SetObjectVariable( gCBP, fhObject, ovLayerDPI, value ) );
}

TXString VWLayerObj::GetSheetExpandedName()
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );

	TVariableBlock	varSheetName;
	gSDK->GetObjectVariable( fhObject, ovLayerExpandedSheetName, varSheetName );

	TXString result;
	varSheetName.GetTXString(result);
	
	return result;
}

ELayerType VWLayerObj::GetLayerType() const
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerType, value ) );
	short				res;
	VERIFYN( kVStanev, value.GetSint16( res ) );
	return (ELayerType) res;
}

VWRectangle2D VWLayerObj::GetCropRectangle()
{
	VWFC_ASSERT( fhObject );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerCropRect, value ) );
	WorldRect		rect;
	VERIFYN( kVStanev, value.GetWorldRect( rect ) );
	VWRectangle2D	rc;
	rc.SetRect( VWPoint2D( rect.left, rect.top ), VWPoint2D( rect.right, rect.bottom ) );
	return rc;
}

ELayerProjection VWLayerObj::GetProjection() const
{
	VWFC_ASSERT( fhObject );
	return (ELayerProjection) ::GS_GetProjection( gCBP, fhObject );
}

void VWLayerObj::SetProjection(ELayerProjection proj, Boolean bConfirmWithUser, Boolean bDoProgress)
{
	VWFC_ASSERT( fhObject );
	::GS_SetProjection( gCBP, fhObject, (short) proj, bConfirmWithUser, bDoProgress );
}

void VWLayerObj::GetPerspectiveInfo(WorldCoord& perspectiveDistance, WorldCoord& clipDistance, VWRectangle2D& clipRect) const
{
	VWFC_ASSERT( fhObject );
	WorldRect		clipRc;
	::GS_GetPerspectiveInfo( gCBP, fhObject, perspectiveDistance, clipDistance, clipRc);
	clipRect.SetRect( VWPoint2D( clipRc.left, clipRc.top ), VWPoint2D( clipRc.right, clipRc.bottom ) );
}

ELayerRender VWLayerObj::GetRenderMode() const
{
	VWFC_ASSERT( fhObject );
	return (ELayerRender) ::GS_GetRenderMode( gCBP, fhObject );
}

void VWLayerObj::SetRenderMode(ELayerRender mode, Boolean bImmediate, Boolean bDoProgress)
{
	VWFC_ASSERT( fhObject );
	VERIFYN( kVStanev, ::GS_SetRenderMode( gCBP, fhObject, (short) mode, bImmediate, bDoProgress ) );
}

void VWLayerObj::GetViewMatrix(VWTransformMatrix& matrix)
{
	VWFC_ASSERT( fhObject );
	::GS_GetViewMatrix( gCBP, fhObject, matrix );
}

void VWLayerObj::SetViewMatrix(const VWTransformMatrix& matrix)
{
	VWFC_ASSERT( fhObject );
	::GS_SetViewMatrix( gCBP, fhObject, matrix );
}

MCObjectHandle VWLayerObj::GetCurrentLayer()
{
	return ::GS_GetCurrentLayer( gCBP );
}

double_gs VWLayerObj::GetElevation() const
{
	WorldCoord	bottomHeight;
	::GS_Kludge( gCBP, 1000, fhObject, & bottomHeight );
	return bottomHeight;
}

void VWLayerObj::SetElevation(double_gs value)
{
	WorldCoord	height	= value;
	::GS_Kludge( gCBP, 1002, fhObject, & height );
}

double_gs VWLayerObj::GetHeight() const
{
	WorldCoord	thickness;
	::GS_Kludge( gCBP, 1001, fhObject, & thickness );
	return thickness;
}

void VWLayerObj::SetHeight(double_gs height)
{
	::GS_Kludge( gCBP, 1003, fhObject, & height );
}

TXString VWLayerObj::GetName()
{
	TXString	name;
	gSDK->GetObjectName( fhObject, name );
	return name;
}

InternalIndex VWLayerObj::GetStory() const
{
	InternalIndex storyIndex = 0;
	MCObjectHandle story = gSDK->GetStoryOfLayer(fhObject);
	if (story)
		storyIndex = gSDK->GetObjectInternalIndex(story);

	return storyIndex;
}

TXString VWLayerObj::GetDescription()
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	TVariableBlock		value;
	VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerDescription, value ) );
	TXString				res;
	VERIFYN( kVStanev, value.GetTXString( res ) );
	return res;
}

void VWLayerObj::SetDescription(const TXString& desc)
{
    TVariableBlock	var(desc);
	gSDK->SetObjectVariable( fhObject, ovLayerDescription, var );
}

TXString VWLayerObj::GetNameExpanded()
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	if ( this->GetLayerType() == kLayerSheet )
	{
		TVariableBlock		value;
		VERIFYN( kVStanev, ::GS_GetObjectVariable( gCBP, fhObject, ovLayerExpandedSheetName, value ) );
		TXString				res;
		VERIFYN( kVStanev, value.GetTXString( res ) );
		return res;
	}
	else
		return this->GetName();
}

void VWLayerObj::SetThisLayerAsCurrent() const
{
	VWFC_ASSERT( fhObject );
	::GS_SetCurrentLayer( gCBP, fhObject );
}

VWPoint2D VWLayerObj::GetSheetOrigin() const
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	WorldPt		origin;
	VERIFYN( kVStanev, ::GS_GetSheetLayerUserOrigin( gCBP, fhObject, origin ) );
	return VWPoint2D( origin.x, origin.y );
}

void VWLayerObj::SetSheetOrigin(const VWPoint2D& pt)
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	VERIFYN( kVStanev, ::GS_SetSheetLayerUserOrigin( gCBP, fhObject, pt ) );
}

double VWLayerObj::GetSheetWidht() const
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet || this->GetLayerType() == kLayerDesign );
	TVariableBlock	var;
	gSDK->GetObjectVariable( fhObject, ovLayerSheetWidth, var );
	double result = 0;
	return var.GetReal64( result ) ? result : 0;
}

void VWLayerObj::SetSheetWidht(double value)
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	TVariableBlock	var( value );
	gSDK->SetObjectVariable( fhObject, ovLayerSheetWidth, var );
}

double VWLayerObj::GetSheetHeight() const
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet || this->GetLayerType() == kLayerDesign );
	TVariableBlock	var;
	gSDK->GetObjectVariable( fhObject, ovLayerSheetHeight, var );
	double result = 0;
	return var.GetReal64( result ) ? result : 0;
}

void VWLayerObj::SetSheetHeight(double value)
{
	VWFC_ASSERT( fhObject );
	// this can be applied only to sheet layers
	VWFC_ASSERT( this->GetLayerType() == kLayerSheet );
	TVariableBlock	var( value );
	gSDK->SetObjectVariable( fhObject, ovLayerSheetHeight, var );
}

Boolean VWLayerObj::GetProgramVar_UseLayerColor()
{
	Boolean	result;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varUseLayerColor, & result ) );
	return result;
}

void VWLayerObj::SetProgramVar_UseLayerColor(Boolean use)
{
	VERIFYN( kVStanev, ::GS_SetProgramVariable( gCBP, varUseLayerColor, & use ) );
}

ELayerOptions VWLayerObj::GetProgramVar_LayerOptions()
{
	short	value;
	VERIFYN( kVStanev, ::GS_GetProgramVariable( gCBP, varLayerOptions, & value ) );
	return (ELayerOptions) value;
}

void VWLayerObj::SetProgramVar_LayerOptions(ELayerOptions options)
{
	short	value	= (short) options;
	VERIFYN( kVStanev, ::GS_SetProgramVariable( gCBP, varLayerOptions, & value ) );
}

