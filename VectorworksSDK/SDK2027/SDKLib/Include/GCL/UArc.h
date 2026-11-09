//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Arc object utility class

#ifndef _UARC_
#define _UARC_

#include "Unclassified.h"


class TArc
{
	protected:
		WorldRect 	fDefBounds;		// definition bounds of circle
		WorldCoord 		fStartAngle;
		WorldCoord 		fSweepAngle;
			
	public:
		TArc() { /*fDefBounds.Set(0L,0L,0L,0L);*/ fStartAngle = 0.0; fSweepAngle = 360.0;} // EJK 00/10/06 - removed zero initialization since WorldRect constructor will MakeEmpty
		TArc(WorldRect bounds) 
			{ fDefBounds = bounds; fStartAngle = 0.0; fSweepAngle = 360.0;}
		TArc(WorldRect bounds, WorldCoord startAngle, WorldCoord sweepAngle) 
			{ fDefBounds = bounds; fStartAngle = startAngle; fSweepAngle = sweepAngle;}
};

class TMCArc
{
	protected:
		Handle 		fArcHandle;
		WorldRect 	fDefBounds;		// definition bounds of circle
		WorldCoord 		fStartAngle;
		WorldCoord 		fSweepAngle;
		WorldRect	fObjBounds;		// bounding box on drawing
		WorldPt		fCenter;
		WorldCoord 		fRadiusX;
		WorldCoord 		fRadiusY;
		CallBackPtr fCBP;	
		
	public:
		
		GS_API TMCArc(CallBackPtr cbp, Handle arc);
		
		/* 	Accessor functions. Check validity of object. 
		*/
		
		WorldRect DefBounds() { return fDefBounds; }
		WorldCoord StartAngle() { return fStartAngle; }
		WorldCoord SweepAngle() { return fSweepAngle; }

		Handle ArcHandle() { return fArcHandle; }
		WorldRect ObjBounds() { return fObjBounds; }
		WorldPt ArcCenter() { return fCenter; }
		WorldCoord ArcRadiusX() { return fRadiusX; }
		WorldCoord ArcRadiusY() { return fRadiusY; }
		CallBackPtr CBP() { return fCBP; }
		
		WorldPt GS_API ArcStartPt(); 
			
		WorldPt GS_API ArcEndPt();
			
		
		void GS_API SetAngles(const WorldCoord start, const WorldCoord sweep);
		Handle GS_API OffsetArc(const WorldCoord offset);
		WorldCoord GS_API Offset(WorldPt pt);
		WorldCoord GS_API NearestExtendSweep(CallBackPtr cbp, Handle extendToObj, const Boolean extOnlyFromEnd);
										
		WorldCoord GS_API MinExtendSweep(const WorldCoord sweep1, const WorldCoord sweep2, const Boolean posExtend);
		WorldCoord AbsSweep() { return fabs(this->SweepAngle()); }
		Boolean GS_API SweepToPoint(WorldPt xPt, WorldCoord& posSweep, WorldCoord& negSweep);
		WorldCoord GS_API SweepToPtFromStart(const WorldPt xPt);
		Boolean GS_API Picked(WorldPt xPt, Boolean& lastHalfPicked);
		void GS_API Extend(WorldCoord xAngle);
		WorldCoord GS_API SignedSweepPt2Pt(const WorldPt p1, const WorldPt p2);
		WorldCoord PosSweepPt2Pt(const WorldPt p1, const WorldPt p2)
			{ return SignedSweepPt2Pt(p1, p2) >= 0.0 ? SignedSweepPt2Pt(p1, p2) : 360.0+SignedSweepPt2Pt(p1, p2); }
		WorldCoord NegSweepPt2Pt(const WorldPt p1, const WorldPt p2)
			{ return SignedSweepPt2Pt(p1, p2) <= 0.0 ? SignedSweepPt2Pt(p1, p2) : SignedSweepPt2Pt(p1, p2)-360.0; }
		void GS_API InitFEONearestTwoPtsData(const WorldPt p, void* env);
		Boolean GS_API NearestTwoSects(const WorldPt p, WorldPt& s1, WorldPt& s2);
		Boolean GS_API CutArcSectToSect(const WorldPt p1, const WorldPt p2, Handle& h1, Handle& h2, Handle& h3);
		void GS_API Split(const WorldCoord sweep, Handle& h1, Handle& h2);
		void GS_API Rotate(const WorldCoord rotDeg);

		WorldCoord GS_API T2Theta(const WorldCoord tRad); 
		WorldCoord GS_API Theta2T(const WorldCoord thetaRad);
		WorldCoord GS_API TFromPt(const WorldPt p);
		
		Boolean GS_API SweepToPoint2(const WorldPt p, WorldCoord& posSweep, WorldCoord& negSweep);
		WorldCoord GS_API ArcPtToPt(const WorldPt p1, const WorldPt p2, Boolean pos);
		void GS_API SetArcPtToPt(const WorldPt p1, const WorldPt p2, Boolean posSweep);

		void GS_API Extend2(WorldPt p, const Boolean posExtend);
		WorldPt GS_API NearestExtendPt(CallBackPtr cbp, Handle extendToObj, const Boolean posExtend);
		WorldPt GS_API MinExtendPt(const WorldPt p1, const WorldPt p2, const Boolean posExtend);
		WorldPt GS_API ExtendEndPoint( Boolean posExtend);
		
		void Test();
		void DrawBounds() {GS_DrawCoordRect(CBP(), ObjBounds());}
		
		
		
};

Handle GS_API CreateArcPtToPt(CallBackPtr cbp, const WorldPt startPt, const WorldPt endPt, 
					const WorldPt center, const WorldCoord radiusX, const WorldCoord radiusY);



#endif

