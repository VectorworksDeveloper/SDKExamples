//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	MiniCad Wall object utility class

#ifndef _UWALL_
#define _UWALL_

class TMCWall
{
	protected:
		WorldPt 	fStartPt;
		WorldPt 	fEndPt;
		Handle		fWallHandle;
		
	public:
		TMCWall(CallBackPtr cbp, Handle theWall) 
			{ fWallHandle = theWall; GS_GetEndPoints(cbp, theWall, fStartPt, fEndPt); }
		Handle WallHandle() { return fWallHandle; }
		WorldPt StartPt() { return fStartPt; }
		WorldPt EndPt() { return fEndPt; }
		inline WorldPt Vector() { return fEndPt - fStartPt; }
		WorldPt GS_API UnitVector();
		WorldCoord Length()  { return WorldPt(fEndPt - fStartPt).Magnitude(); }
		WorldPt GS_API PerpVector();
		WorldPt GS_API UnitPerpVector(); 
		WorldCoord GS_API ScalarProjection(const WorldPt vector);
		WorldPt VectorProjection(const WorldPt vector) 
						{ return this->UnitVector() * this->ScalarProjection(vector); }
		Handle GS_API Offset(CallBackPtr cbp, WorldCoord off);
};


#endif

