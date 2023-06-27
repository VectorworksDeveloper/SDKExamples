//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "VectorworksSDK.h"

using namespace VWFC::Math;
using namespace VWFC::VWObjects;

VWDocument::VWDocument()
{
}

VWDocument::~VWDocument()
{
}

void VWDocument::DeselectAll()
{
	::GS_DeselectAll( gCBP );
}

MCObjectHandle VWDocument::GetFirstSelectedObject()
{
	return ::GS_FirstSelectedObject( gCBP );
}

MCObjectHandle VWDocument::GetDrawingHeaderFristMember()
{
	return ::GS_FirstMemberObj( gCBP, ::GS_GetDrawingHeader( gCBP ) );
}

bool VWDocument::IsCurrentDocumentInMetricUnits()
{
	double	dUPI;
	if ( !GS_GetProgramVariable( gCBP, varUnit1UnitsPerInch, & dUPI ) )
		dUPI		= 1.0;

	if ( MathUtils::Equalish( dUPI, 0.000254, 0.0001 ) )	return true;
	if ( MathUtils::Equalish( dUPI, 0.00254, 0.0001 ) )		return true;
	if ( MathUtils::Equalish( dUPI, 0.0254, 0.0001 ) )		return true;
	if ( MathUtils::Equalish( dUPI, 0.254, 0.0001 ) )		return true;
	if ( MathUtils::Equalish( dUPI, 2.54, 0.0001 ) )		return true;
	if ( MathUtils::Equalish( dUPI, 25.4, 0.0001 ) )		return true;
	if ( MathUtils::Equalish( dUPI, 254, 0.0001 ) )			return true;

	return false;
}
