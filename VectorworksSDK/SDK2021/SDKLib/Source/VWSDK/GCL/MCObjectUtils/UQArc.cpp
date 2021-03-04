//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Quarter Arc object utility class

#include "StdHeaders.h"
#include "GCL/UMCPolygon.h"
#include "GCL/UArc.h"
#include "GCL/UQArc.h"
					  


WorldRect GS_API TMCQArc::QArcOvalBox()
{
	WorldRect newRect = Bounds();
	
	switch (fQuadrant) {
		case 1 : {
			newRect.left = fBounds.left - (fBounds.right-fBounds.left);
			newRect.bottom = fBounds.bottom - (fBounds.top-fBounds.bottom);
			
			break;
		}
		case 2 : {
			newRect.right = fBounds.right + (fBounds.right-fBounds.left);
			newRect.bottom = fBounds.bottom - (fBounds.top-fBounds.bottom);
			break;
		}
		case 3 : {
			newRect.right = fBounds.right + (fBounds.right-fBounds.left);
			newRect.top = fBounds.top + (fBounds.top-fBounds.bottom);
			break;
		}
		case 4 : {
			newRect.left = fBounds.left - (fBounds.right-fBounds.left);
			newRect.top = fBounds.top + (fBounds.top-fBounds.bottom);
			break;
		}
	}
	return newRect;
}

	
Handle GS_API TMCQArc::ArcFromQArc()
{
	if (QArcHandle()) {
		switch (Quadrant()) {
			case 1: {
				return GS_CreateArcN(CBP(), QArcOvalBox(), 0.0, 90.0);
				break;
			}
			case 2: {
				return GS_CreateArcN(CBP(), QArcOvalBox(), 90.0, 90.0);
				break;
			}
			case 3: {
				return GS_CreateArcN(CBP(), QArcOvalBox(), 180.0, 90.0);
				break;
			}
			case 4: {
				return GS_CreateArcN(CBP(), QArcOvalBox(), 270.0, 90.0);
				break;
			}
			
		}
	}
	return nil;	
}

Handle GS_API TMCQArc::OffsetQArc(const WorldCoord offset)
{
	if (QArcHandle()) {
	

		TMCArc arc(fCBP, ArcFromQArc());
		
		if (arc.ArcHandle()) {
			Handle offsetObj = nil;
			if (arc.ArcRadiusX() == arc.ArcRadiusY() ) {
				offsetObj = arc.OffsetArc(offset);
			}
			else {
				Handle h = GS_ConvertToPolygon(fCBP, arc.ArcHandle(), true);
				if (h) {
					TMCPolygon poly(fCBP, h);
					offsetObj = poly.OffsetPoly(offset, false);
					GS_DeleteObject(fCBP,h, false);
				}
			}
			GS_DeleteObject(fCBP, arc.ArcHandle(), false);
			return offsetObj;
		}	
	}
	return nil;
}
		
		
WorldCoord GS_API TMCQArc::Offset(WorldPt pt)
{
	if (QArcHandle()) {
		TMCArc arc(fCBP, ArcFromQArc());
		if (arc.ArcHandle()) {
		
			WorldCoord val = 0L;
			
			if (arc.ArcRadiusX() == arc.ArcRadiusY() ) {
				val = arc.Offset(pt);
			}
			else {
				Handle h = GS_ConvertToPolygon(fCBP, arc.ArcHandle(), true);
				if (h) {
					TMCPolygon poly(fCBP, h);
					val = poly.Offset(pt);
					GS_DeleteObject(fCBP,h, false);
				}
			}
			GS_DeleteObject(fCBP, arc.ArcHandle(), false);
			return val;
		}
	
	}
	return 0L;
}


void GS_API TMCQArc::DrawCoordQArc()
{

	if (QArcHandle()) {
		switch (Quadrant()) {
			
			case 1: {
				GS_DrawCoordArcN(CBP(), QArcOvalBox(), 0.0, 90.0);
				break;
			}
			case 2: {
				GS_DrawCoordArcN(CBP(), QArcOvalBox(), 90.0, 90.0);
				break;
			}
			case 3: {
				GS_DrawCoordArcN(CBP(), QArcOvalBox(), 180.0, 90.0);
				break;
			}
			case 4: {
				GS_DrawCoordArcN(CBP(), QArcOvalBox(), 270.0, 90.0);
				break;
			}
			
		}
	}
}
