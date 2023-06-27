//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// MiniCad polyline curve segment object utility class

#ifndef _UMCCURVESEG_
#define _UMCCURVESEG_

#include "UMCPolyline.h"

class TMCCurveSeg 
{
	
	private:
		WorldPt 	fE1;			// first endpoint 
		WorldPt 	fCV;			// spline control vertex or arc center
		WorldPt 	fE2;			// last endpoint
		WorldPt 	fV;				// vertex
		short		fIndex;			// index
		Handle 		fPoly;			// minicad poly
		Sint32		fSegType;		// curve type
		CallBackPtr fCBP;			// callback parameter
		
	public:
		GS_API TMCCurveSeg(CallBackPtr cbp, Handle p, const short index);
		
		WorldPt 	EndPoint1() 	{ return fE1; }
		WorldPt 	EndPoint2() 	{ return fE2; }
		WorldPt 	CntrlVert() 	{ return fCV; }
		WorldPt 	Center() 		{ return fCV; }
		WorldPt	 	Vertex() 		{ return fV; }
		short 		Index()			{ return fIndex; }
		Handle	 	PolyHandle() 	{ return fPoly; }
		Sint32 		SegType() 		{ return fSegType; }
		CallBackPtr	CBP()			{ return fCBP; }
		
		void GS_API SetCntrlVert(const WorldPt p);
		Boolean GS_API Contains(const WorldPt p, const Sint32 maxLevel);
		void GS_API DrawCoordCurveSeg(const WorldCoord level, const WorldCoord maxLevel);
		//void Offset(const WorldCoord offset);
		void GS_API Report();
};
		
#endif
		
