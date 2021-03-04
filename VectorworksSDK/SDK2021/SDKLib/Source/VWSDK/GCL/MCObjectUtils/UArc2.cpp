//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Arc object utility class
	

#include "StdHeaders.h"
#include "GCL/UArc.h"
#include "GCL/Unclassified.h"


const double myPi = 3.141592653589793;
const double myRadToDeg = 180.0 / myPi;		
const double myDegToRad = myPi/180.0;		




Handle GS_API CreateArcPtToPt(CallBackPtr cbp, const WorldPt p1, const WorldPt p2, 
					const WorldPt center, const WorldCoord radiusX, const WorldCoord radiusY)
{
	WorldRect bounds(center.x-radiusX, center.y+radiusY, center.x+radiusX, center.y-radiusY);

	// GS_SDKPPC_JAK	I dont think we need the typecast to extended here because WorldCoord is a double now anyway.	
	//	WorldCoord a1 = asin((p1-center).y/((extended) radiusY))*myRadToDeg;
	//	WorldCoord a2 = asin((p2-center).y/((extended) radiusY))*myRadToDeg;
	WorldCoord a1 = asin((p1-center).y/(radiusY))*myRadToDeg;
	WorldCoord a2 = asin((p2-center).y/(radiusY))*myRadToDeg;
	
	a1 = (p1.x < center.x) ? 180.0-a1 : (p1.y < center.y) ? 360.0+a1 : a1;	// set a1 to 0 to 360 
	a2 = (p2.x < center.x) ? 180.0-a2 : (p2.y < center.y) ? 360.0+a2 : a2;	// set a2 to 0 to 360
	
	//Debug("create arc from a1 to a2  with a1 : %lf,a2 : %lf\n",a1,a2);

	WorldCoord sweep = a2 >= a1 ? a2-a1 : 360.0+a2-a1;
	
	if (fabs(sweep) > 0.1)
		return GS_CreateArcN(cbp, bounds, a1, sweep);
	else 
		return nil;
}

void GS_API TMCArc::SetArcPtToPt(const WorldPt p1, const WorldPt p2, Boolean posSweep)
/*	Sets this arc to start at p1 and end at p2	*/
{
	//Debug("SetArcPtToPt\n");
	
	if ( fabs(p1.x-ArcCenter().x) <= ArcRadiusX() && fabs(p1.y-ArcCenter().y) <= ArcRadiusY() &&
		 fabs(p2.x-ArcCenter().x) <= ArcRadiusX() && fabs(p2.y-ArcCenter().y) <= ArcRadiusY()) {
		
		WorldCoord a1 = asin((p1-ArcCenter()).y/(ArcRadiusY()))*myRadToDeg;
		WorldCoord a2 = asin((p2-ArcCenter()).y/(ArcRadiusY()))*myRadToDeg;
		
		a1 = (p1.x < ArcCenter().x) ? 180.0-a1 : (p1.y < ArcCenter().y) ? 360.0+a1 : a1;	// set a1 to 0 to 360 
		a2 = (p2.x < ArcCenter().x) ? 180.0-a2 : (p2.y < ArcCenter().y) ? 360.0+a2 : a2;	// set a2 to 0 to 360
		//Debug("a1 : %lf, a2 : %lf\n",a1,a2);
		
		WorldCoord sweep;
		/*
		if (posSweep) 
			sweep = a2 >= a1 ? a2-a1 : a1-a2;
		else
			sweep = a2 >= a1 ? a2-a1-360.0 : a1-a2;
		*/
		
		if (a2 >= a1)
			sweep = (posSweep ? a2-a1 : a2-a1-360.0);
		else
			sweep = (posSweep ?  a2-a1+360.0 : a2-a1);
		
		SetAngles(a1, sweep);
	}
}


WorldCoord GS_API TMCArc::ArcPtToPt(const WorldPt p1, const WorldPt p2, Boolean pos)

{
	WorldCoord retVal = 0.0;
	
	if ( fabs(p1.x-ArcCenter().x) <= ArcRadiusX() && fabs(p1.y-ArcCenter().y) <= ArcRadiusY() &&
		 fabs(p2.x-ArcCenter().x) <= ArcRadiusX() && fabs(p2.y-ArcCenter().y) <= ArcRadiusY()) {
		if (p1 == p2) {
			if (SweepAngle() > 0.0) 
				return 360.0;
			else
				return -360.0;
		}
		else {
			WorldCoord a1 = asin((p1-ArcCenter()).y/(ArcRadiusY()))*myRadToDeg;
			WorldCoord a2 = asin((p2-ArcCenter()).y/(ArcRadiusY()))*myRadToDeg;
		
			a1 = (p1.x < ArcCenter().x) ? 180.0-a1 : (p1.y < ArcCenter().y) ? 360.0+a1 : a1;	// set a1 to 0 to 360 
			a2 = (p2.x < ArcCenter().x) ? 180.0-a2 : (p2.y < ArcCenter().y) ? 360.0+a2 : a2;	// set a2 to 0 to 360
			
			if (pos) {
				return a2 >= a1 ? a2-a1 : 360.0 - (a1-a2);
			}
			else {
				return a2 >= a1 ?  a2-a1 - 360.0 : a2-a1;
			}
		}
		
	}
	return retVal;
}

WorldPt GS_API TMCArc::NearestExtendPt(CallBackPtr cbp, Handle extendToObj, const Boolean posExtend)
{
	//Debug("NearestExtendPt with posExtend %d\n",posExtend);
	
	WorldPt retVal = ArcEndPt();

	if (extendToObj) {
	
		WorldPt extendFromPt = ExtendEndPoint(posExtend);
	
		Handle h = GS_IntersectObjects(cbp, ArcHandle(), extendToObj, false);
	
		if (h) {
			
			WorldCoord thisDeltaT = 0.0;
			
			size_t hSize;
			GS_GetHandleSize(cbp, h, hSize);
			size_t num = hSize/sizeof(WorldPt);
			
			//Debug("there are %ld intersections \n",num);
			
			GS_HLock(cbp, (Handle) h);
			
			WorldPt* cp = (WorldPt*) *h;
			
			WorldCoord deltaT = (posExtend) ? 360.0 : -360.0;

			for (size_t i = 0 ; i < num ; i++) {
				
				if (OnObject(cbp,extendToObj,*cp)) {
				
					thisDeltaT = ArcPtToPt(extendFromPt,*cp, posExtend);
					
					WorldPt pt = *cp;
					//Debug("pt : %ld,%ld\n",pt.x,pt.y);
										
					if (posExtend) {
					
						if (thisDeltaT < deltaT) {
							retVal= *cp;
							//Debug("pos Extend retVal set to : %ld,%ld\n",retVal.x,retVal.y);
							deltaT = thisDeltaT;
						} 
					}
					else {
					
						if (thisDeltaT > deltaT) {
							retVal= *cp;
							//Debug("neg Extend retVal set to : %ld,%ld\n",retVal.x,retVal.y);
							deltaT = thisDeltaT;
						} 
					}
				}
				//Debug("i = %d , retVal is : %ld,%ld\n",i,retVal.x,retVal.y);
				cp++;
			}
			GS_HUnlock(cbp, (Handle) h);
			GS_DisposeHandle(cbp, (Handle) h);
		}
	}
	
	return retVal;
}

WorldPt GS_API TMCArc::MinExtendPt(const WorldPt p1, const WorldPt p2, const Boolean posExtend)
{	
	WorldPt retVal= ArcEndPt();
	
	if ( fabs(p1.x-ArcCenter().x) <= ArcRadiusX() && fabs(p1.y-ArcCenter().y) <= ArcRadiusY() &&
		 fabs(p2.x-ArcCenter().x) <= ArcRadiusX() && fabs(p2.y-ArcCenter().y) <= ArcRadiusY()) {
		 
		//Debug("MinExtendPt\n");
		
		WorldPt extendFromPt = ExtendEndPoint(posExtend);
												 		
		WorldCoord d1 = ArcPtToPt(extendFromPt,p1, posExtend);
		WorldCoord d2 = ArcPtToPt(extendFromPt,p2, posExtend);
		
		//Debug("d1 : %lf, d2 : %lf\n",d1,d2);
		
		if (posExtend) {
			if (d1 < d2)
				return p1;
			else 
				return p2; 
		}
		else {
			if (d1 > d2)
				return p1;
			else 
				return p2; 
		}
	}
	else if ( fabs(p1.x-ArcCenter().x) <= ArcRadiusX() && fabs(p1.y-ArcCenter().y) <= ArcRadiusY() )
			retVal = p1;
	else if (fabs(p2.x-ArcCenter().x) <= ArcRadiusX() && fabs(p2.y-ArcCenter().y) <= ArcRadiusY() )
			retVal = p2;

	return retVal;
}

