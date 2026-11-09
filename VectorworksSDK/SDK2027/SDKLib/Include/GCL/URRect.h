//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Rounded Rect object utility class

#ifndef _URRECT_
#define _URRECT_

class TRRect
{
	protected:
		WorldRect 	fBounds;	
		WorldCoord 		fXDiam;
		WorldCoord 		fYDiam;
			
	public:
		TRRect()
		{ /*fBounds.Set(0L,0L,0L,0L);*/ fXDiam = 0L; fYDiam = 0L; } // EJK 00/10/03 - removed 0 initialization since WorldRect constructor makes it empty
		TRRect(WorldRect bounds) 
			{ fBounds = bounds; fXDiam = 0L; fYDiam = 0L;}
		TRRect(WorldRect bounds, WorldCoord xDiam, WorldCoord yDiam) 
			{ fBounds = bounds; fXDiam = xDiam; fYDiam = yDiam;}
		TRRect(CallBackPtr cbp, Handle rRect)
			{GS_GetObjectBounds(cbp, rRect, fBounds); GS_GetRRectDiameters(cbp, rRect, fXDiam, fYDiam);}
		WorldRect Bounds() { return fBounds; }
		WorldCoord XDiam() { return fXDiam; }
		WorldCoord YDiam() { return fYDiam; }
		
		
};

class TMCRRect : public TRRect
{
	protected:
		Handle fRRectHandle;
		CallBackPtr fCBP;	
		
	public:
	
		TMCRRect(CallBackPtr cbp, Handle rRect)
			{ GS_GetObjectBounds(cbp, rRect, fBounds); GS_GetRRectDiameters(cbp, rRect, fXDiam, fYDiam);
			   fCBP = cbp;}
		
		Handle GS_API OffsetRRect(const WorldCoord offset);
		WorldCoord GS_API Offset(WorldPt pt);
		void GS_API DrawCoordRRect();

};

#endif

