//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// MiniCad Wall object utility class


#include "StdHeaders.h"

#include "GCL/UMCWall.h"


WorldPt GS_API TMCWall:: UnitVector(void)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->EndPt() - this->StartPt()).IsZero() ) {
		retVector = ((WorldPt) (this->EndPt() - this->StartPt())).Normal();
	}
	return retVector;

}

WorldPt GS_API TMCWall:: UnitPerpVector(void)
{
	WorldPt retVector;
	retVector.x = -this->UnitVector().y;
	retVector.y = this->UnitVector().x;
	return retVector;

}

WorldPt GS_API TMCWall:: PerpVector() 
{	
	WorldPt perp(fEndPt - fStartPt);
	perp.Set(-perp.y,perp.x);
	return fEndPt - fStartPt; 
}

WorldCoord GS_API TMCWall:: ScalarProjection(const WorldPt vector) 
{
	WorldCoord retVal = 0L;	
	if (((WorldPt) this->Vector()).Magnitude() != 0.0) 
		retVal = WorldCoord(DotProduct(vector,this->Vector())/
						  ((WorldPt) this->Vector()).Magnitude());
	return retVal;
}

Handle GS_API TMCWall::Offset(CallBackPtr cbp, WorldCoord off)
{
	WorldPt offsetVect = WorldPt(this->UnitPerpVector() * off);
#ifdef GS_WRAP_RETURN_COORD_JAK
	WorldCoord outCoordLen;
	GS_WrapGetWallWidth(cbp, fWallHandle, outCoordLen);
	WorldCoord thickness = outCoordLen;
#else
	WorldCoord thickness = GS_GetWallWidth(cbp, fWallHandle);
#endif
	
	Handle offsetObj = GS_CreateWall(cbp, fStartPt, fEndPt, thickness);
	GS_SetEndPoints(cbp, offsetObj, fStartPt + offsetVect, fEndPt + offsetVect);
	return offsetObj;
}
