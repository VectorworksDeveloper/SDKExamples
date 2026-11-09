//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

static void DoSpecialArcConversion_(CallBackPtr cbp, MCObjectHandle arcHandle, MCObjectHandle arcConversion)
//
//	Factored Low level code shared by ConvertObjToPolygon and ConvertObjToPolygonN
{
	double_gs startAngle, sweepAngle;
	WorldPt center;
	WorldCoord radiusX, radiusY;
	GS_GetArcInfoN(cbp, arcHandle, startAngle, sweepAngle, center, radiusX, radiusY);
	
	if (sweepAngle < 360) {
		
		//	Here we have an arc as opposed to a circle
		GS_SetPolyShapeClose(cbp, arcConversion, false);
		GS_DeleteVertex(cbp, arcConversion, GS_CountVertices(cbp, arcConversion));
	}
}

Handle GS_API ConvertObjToPolygon(CallBackPtr cbp, Handle h, Boolean preserveOriginal)
{
	Handle returnVal = GS_ConvertToPolygon(cbp,  h,  preserveOriginal);
	
	if (gSDK->GetObjectTypeN (h) == arcNode) {
		
		DoSpecialArcConversion_(cbp, h, returnVal);
	}
	return returnVal;
}

Handle GS_API ConvertObjToPolygonN(CallBackPtr cbp, Handle h, Boolean preserveOriginal, short in2DConversionRes)
{
	Handle returnVal = GS_ConvertToPolygonN(cbp,  h,  preserveOriginal, in2DConversionRes);
	
	if (gSDK->GetObjectTypeN ( h) == arcNode) {
		
		DoSpecialArcConversion_(cbp, h, returnVal);
	}
	return returnVal;
}
