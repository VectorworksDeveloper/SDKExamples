//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Oval object utility class

#ifndef _UOVAL_
#define _UOVAL_

class TOval
{
	protected:
		WorldRect fBounds;		
	public:
	
		TOval(WorldRect bounds) 
			{ fBounds = bounds; }
		TOval(CallBackPtr cbp, Handle mcOval) { GS_GetObjectBounds(cbp,mcOval,fBounds); }
		
		WorldRect Bounds() { return fBounds;}
		Handle GS_API OffsetOval(CallBackPtr cbp, const WorldCoord off);
		WorldCoord GS_API Offset(CallBackPtr cbp,  WorldPt pt);
		WorldPt Center() { return Bounds().Center(); }
};

		void GS_API SolveQuadratic(WorldCoord a, WorldCoord b, WorldCoord c, WorldCoord& s1,
							WorldCoord& s2, Boolean& g1, Boolean& g2);

#endif

