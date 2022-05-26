//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "GCL/UMCCurveSeg.h"
#include <GCL/UMCPolyline.h>
#include "GCL/Unclassified.h"



GS_API TMCCurveSeg::TMCCurveSeg(CallBackPtr cbp, Handle p, const short index)
{
	if (p) {
		TMCPolyline poly(cbp,p);
		fSegType = (VertexType) poly.ControlNeighborhood(index,fE1, fCV, fE2, fV);
		if (fSegType == vtArc) {
			WorldPt temp;
			temp = fCV;
			fCV = fV;
			fV = temp;
		}
		fPoly = p;
		fIndex = index;
		fCBP = cbp;
	}
	else 
		fSegType = -1;		// invalid TmcCurveSeg
}

Boolean GS_API TMCCurveSeg::Contains(const WorldPt p, const Sint32 /*maxLevel*/)
{
	switch (SegType()) {
		case vtCorner : {
			break;
		}
		case vtArc : {
			break;
		}
		case vtBezier :
		case vtCubic : {
			return PtOnSpline(CBP(), EndPoint1(), CntrlVert(), EndPoint2(), p, 0, 5);
			break;
		}
		default : {
		
		}
	}
	return false;
}

void GS_API TMCCurveSeg::DrawCoordCurveSeg(const WorldCoord level, const WorldCoord maxLevel)
{
	DrawCoordSpline(CBP(),EndPoint1(), EndPoint2(), CntrlVert(),level, maxLevel);
}

void GS_API TMCCurveSeg::SetCntrlVert(const WorldPt p)
{
	TMCPolyline poly(CBP(), PolyHandle());
	poly.SetVertex(Index(), p, poly.VertType(Index()), 0L);
	fCV = p;
}

#ifdef MYBUG
void TMCCurveSeg::Report()
{
	Debug("EndPoint1(): %ld,%ld\n",EndPoint1().x,EndPoint1().y);
	Debug("EndPoint2(): %ld,%ld\n",EndPoint2().x,EndPoint2().y);
	Debug("CntrlVert(): %ld,%ld\n",CntrlVert().x,CntrlVert().y);
	Debug("Center(): %ld,%ld\n",Center().x,Center().y);
	Debug("Vertex(): %ld,%ld\n",Vertex().x,Vertex().y);
	Debug("PolyHandle(): %lx\n",PolyHandle());
	Debug("SegType(): %ld\n",SegType());
}
#endif
