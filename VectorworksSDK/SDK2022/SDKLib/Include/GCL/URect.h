//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Rect object utility class

#ifndef _URECTANGLES_
#define _URECTANGLES_

class TRect
{
	protected:
		WorldRect 	fBounds;	
	public:
		TRect() { /*fBounds.Set(0L,0L,0L,0L);*/ } //EJK 00/09/26 - removed 0 initialization since WorldRect constructor makes it empty
		TRect(WorldRect bounds) { fBounds = bounds;}
		TRect(CallBackPtr cbp, Handle mcBox) { GS_GetObjectBounds(cbp,mcBox,fBounds); }
		
};

class TMCRect : public TRect
{
	protected:
		Handle fRRectHandle;
		CallBackPtr fCBP;	
		
	public:
	
		TMCRect(CallBackPtr cbp, Handle rRect)
			{ GS_GetObjectBounds(cbp, rRect, fBounds); fCBP = cbp;}
		
		WorldRect Bounds() { return fBounds; }

		// OffsetMCRect can not be called OffsetRect because of a suspected
		// Altura name conflict which causes a link error.
		Handle GS_API OffsetMCRect(const WorldCoord offset);

		WorldCoord GS_API Offset(WorldPt pt);
};

#endif

