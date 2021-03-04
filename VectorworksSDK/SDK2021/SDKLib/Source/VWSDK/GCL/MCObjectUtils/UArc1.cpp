//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Arc object utility class
	
#include "StdHeaders.h"
#include "GCL/UArc.h"
#include "GCL/Unclassified.h"

//#include <Debug.h>

// GS_SDKPPC_JAK	Changing "extended" to "double"
const double myPi = 3.141592653589793;
const double myRadToDeg = 180.0 / myPi;		
const double myDegToRad = myPi/180.0;		


struct FEONearestTwoPtsDataType	{
	Handle 	pickObj;
	WorldPt pickPt;
	WorldCoord pickPtSweep;
	WorldCoord s1;
	WorldCoord s2;
	WorldPt p1;
	WorldPt p2;
	Boolean sectFound;
};
extern "C" void GS_API FEOGetArcSects(Handle selObj, CallBackPtr cbp, void* env);

GS_API TMCArc::TMCArc(CallBackPtr cbp, Handle arc)
{
	GS_GetObjectBounds(cbp, arc, fObjBounds);
	fArcHandle = arc;
	GS_GetArcInfoN(cbp, arc, fStartAngle, fSweepAngle, fCenter, fRadiusX, fRadiusY); 
	fDefBounds.Set(	fCenter.x-fRadiusX,fCenter.y+fRadiusY,
					fCenter.x+fRadiusX,fCenter.y-fRadiusY);
					
	fCBP = cbp;
	
	if (fSweepAngle < 0.0) {
		fStartAngle = fStartAngle+fSweepAngle;
		fSweepAngle = -fSweepAngle;
		SetAngles(fStartAngle,fSweepAngle);
	}
}

					  
Handle GS_API TMCArc::OffsetArc(const WorldCoord offset)
{
	Handle hObj = nil;
	
	WorldCoord radX = ArcRadiusX() + offset;
	WorldCoord radY = ArcRadiusY() + offset;

	if (radX > 0 && radY > 0) {
		WorldRect newRect = DefBounds();
		newRect.Set(ArcCenter().x - radX, ArcCenter().y + radY,
	 				ArcCenter().x + radX, ArcCenter().y - radY);

		hObj = GS_CreateArcN(fCBP, newRect, StartAngle(), SweepAngle());
	}

	return hObj;
}

WorldCoord GS_API TMCArc::Offset(WorldPt pt)
{	
	
	return WorldCoord(WorldPt(pt - ArcCenter()).Magnitude() - ArcRadiusX());
}

WorldCoord GS_API TMCArc::MinExtendSweep(const WorldCoord sweep1, const WorldCoord sweep2, const Boolean positiveExtend)

/*	return the sweep angle from start of the arc.  If neither sweep is 
	good then zero is returned.  sweep1 and sweep2 are sweeps measured from start point of this arc.
*/
{
	//Debug("sweep1 : %lf, sweep2 : %lf\n",sweep1,sweep2);
	
	WorldCoord retVal= 0.0;
	
	
	if (positiveExtend) {
	
		if (SweepAngle() > 0.0) {
			if ( Min(sweep1, sweep2) > SweepAngle()) 
				retVal =  Min(sweep1, sweep2);
			else if ( Max(sweep1, sweep2) > SweepAngle() ) 
				retVal = Max(sweep1, sweep2);
			else
				retVal = 0.0;
		}
		else {
			if ( Min(sweep1, sweep2) > 0.0) 
				retVal =  Min(sweep1, sweep2);
			else if ( Max(sweep1, sweep2) > 0.0 ) 
				retVal = Max(sweep1, sweep2);
			else
				retVal = 0.0;
		}	
	}
	
	else {
	
		if (SweepAngle() > 0.0) {
			if ( Max(sweep1, sweep2) < 0.0) 
				retVal =  Max(sweep1, sweep2);
			else if ( Min(sweep1, sweep2) < 0.0 ) 
				retVal = Min(sweep1, sweep2);
			else
				retVal = 0.0;
		}
		else {
			if ( Max(sweep1, sweep2) < SweepAngle()) 
				retVal =  Max(sweep1, sweep2);
			else if ( Min(sweep1, sweep2) < SweepAngle() ) 
				retVal = Min(sweep1, sweep2);
			else
				retVal = 0.0;
		}	
	}
	

	//Debug("TMCArc::MinExtendSweep returned : %lf\n",retVal);
	return retVal;
}


WorldCoord GS_API TMCArc::NearestExtendSweep(CallBackPtr cbp, Handle extendToObj, const Boolean posExtend)
{
	//Debug("NearestExtendSweep with posExtend %d\n",posExtend);
		
	WorldCoord retVal = 0.0;
	if (extendToObj) {
	
		Handle h = GS_IntersectObjects(cbp, ArcHandle(), extendToObj, false);
	
		if (h) {
		
			WorldCoord posSweep = 0.0;
			WorldCoord negSweep = 0.0;
			WorldCoord sweep = 0.0;
			Boolean sweepFound = false;
			size_t hSize;
			GS_GetHandleSize(cbp, h, hSize);
			size_t num = hSize / sizeof(WorldPt);
			//Debug("there are %ld intersections \n",num);
			GS_HLock(cbp, (Handle) h);
			WorldPt* cp = (WorldPt*) *h;
			for (size_t i = 0 ; i < num ; i++) {
				WorldCoord thisSweep;
				
				if (OnObject(cbp,extendToObj,*cp)) {
				
					if ( SweepToPoint(WorldPt(*cp), posSweep, negSweep) ) {
					
						thisSweep = MinExtendSweep(posSweep, negSweep, posExtend);
						sweep = MinExtendSweep(thisSweep, sweep, posExtend);
					}
					sweepFound = true;
				}
				cp++;
			}
			
			if (sweepFound)
				retVal = sweep;
			else 
				return 0.0;
				
			GS_HUnlock(cbp, (Handle) h);
			GS_DisposeHandle(cbp, (Handle) h);
		}

	}
	return retVal;
}


Boolean GS_API TMCArc::SweepToPoint(WorldPt xPt, WorldCoord& posSweep, WorldCoord& negSweep)

/*	Sweeps measured from the start angle of this arc
*/
{
	const Boolean kSweepPos = true;
	posSweep = ArcPtToPt(ArcStartPt(), xPt, kSweepPos);
	negSweep = ArcPtToPt(ArcStartPt(), xPt, !kSweepPos);
	
	return true;		
}

WorldCoord GS_API TMCArc::SweepToPtFromStart(const WorldPt xPt)
{
	WorldCoord p,n;
	SweepToPoint(xPt,p,n);
	return p;
}


WorldCoord GS_API TMCArc::SignedSweepPt2Pt(const WorldPt p1, const WorldPt p2)
{
	WorldCoord ps1,ps2,ns;			//pos and neg sweeps to points 1 and 2	
	
	SweepToPoint(p1,ps1,ns);
	SweepToPoint(p2,ps2,ns);
	
	return ps2-ps1;
}
#if 0
WorldCoord GS_API PosSweepPt2Pt(const WorldPt p1, const WorldPt p2)
{
 	signedSweep = SignedSweepPt2Pt(p1, p2);
 	return signedSweep >= 0.0 ? signedSweep : 360.0+signedSweep; 
}

WorldCoord GS_API NegSweepPt2Pt(const WorldPt p1, const WorldPt p2)
{
 	signedSweep = SignedSweepPt2Pt(p1, p2);
 	return signedSweep <= 0.0 ? signedSweep : signedSweep-360.0; 
}
#endif
Boolean GS_API TMCArc::Picked(WorldPt xPt, Boolean& positiveExtend)
{
	WorldCoord posSweep, negSweep;
	
	if ( SweepToPoint(xPt, posSweep, negSweep)) {
	
		if ( SweepAngle() >= 0.0)
			positiveExtend = posSweep > SweepAngle()/2.0;
		else
			positiveExtend = negSweep > SweepAngle()/2.0;
			
		//Debug("SweepToPoint returned posSweep : %lf, and negSweep : %lf\n",posSweep,negSweep);	
		//Debug("ArcPicked with  positiveExtend : %ld\n",positiveExtend);
			
		return true;	
	}
	else
		return false;
}

void GS_API TMCArc::Extend(WorldCoord xAngle)

{
	//Debug("TMCArc::ExtendArc\n");
	
	if (SweepAngle() > 0.0) {											// Positive SweepAngle 
		if (xAngle > SweepAngle()) {
			SetAngles(StartAngle(), xAngle);
		}
		else  if (xAngle < 0.0) {
			SetAngles(StartAngle() + xAngle, SweepAngle() - xAngle);
		}
	}
	else {																// Negative SweepAngle 
		if (xAngle < SweepAngle()) {
			SetAngles(StartAngle() , xAngle);
		}
		
		else if (xAngle > 0.0){
			SetAngles(StartAngle() + xAngle, SweepAngle() - xAngle);
		}
	}
	GS_DrawObject(fCBP, ArcHandle(), false);
}

void GS_API TMCArc::Extend2(WorldPt p, const Boolean posExtend)
{
	//Debug("Extend2 p %ld,%ld\n",p.x,p.y);
	
	
	if (posExtend) 												
		SetArcPtToPt(ArcStartPt(), p, posExtend);
	else 
		SetArcPtToPt(ArcEndPt(), p, posExtend);
	
	GS_DrawObject(fCBP, ArcHandle(), false);
}

WorldPt GS_API TMCArc::ExtendEndPoint( Boolean posExtend)
{
	if (ArcHandle()) {
	WorldPt extendFromPt;
		
		if (SweepAngle() >= 0.0) {
			if (posExtend)
				return ArcEndPt();
			else
				return ArcStartPt();
		}
		else {
			if (posExtend)
				return ArcStartPt();
			else
				return ArcEndPt();
		}
	}
	return ArcEndPt();
}


void GS_API TMCArc::InitFEONearestTwoPtsData(const WorldPt p, void* env)
{
	FEONearestTwoPtsDataType* data = (FEONearestTwoPtsDataType*) env;
	
	data->pickObj = ArcHandle();
	data->pickPt = p;
	data->sectFound = false;
	
	WorldCoord posSweep,negSweep;
	SweepToPoint(p,posSweep,negSweep);
	
	
	if (fmod(SweepAngle(), 360) == 0L ) {
	
		//Debug("Ellipse\n");
		data->pickPtSweep = SweepAngle() >= 0.0 ? posSweep : negSweep;
		data->s1 = -360.0;
		data->s2 = 360.0;
		data->p1 = ArcStartPt();
		data->p2 = ArcEndPt();

		
	}
	else {
		if (SweepAngle() >= 0.0) {
			data->pickPtSweep = posSweep;
			data->s1 = NegSweepPt2Pt(data->pickPt,ArcStartPt());
			data->s2 = PosSweepPt2Pt(data->pickPt,ArcEndPt());
			data->p1 = ArcStartPt();
			data->p2 = ArcEndPt();
		}
		else {	
			data->pickPtSweep = negSweep;
			data->s1 = NegSweepPt2Pt(data->pickPt,ArcEndPt());
			data->s2 = PosSweepPt2Pt(data->pickPt,ArcStartPt());
			data->p2 = ArcStartPt();
			data->p1 = ArcEndPt();
		}
	}
	
	
}


Boolean TMCArc::NearestTwoSects(const WorldPt p, WorldPt& p1, WorldPt& p2)
{
	FEONearestTwoPtsDataType	data;
	
	InitFEONearestTwoPtsData(p, &data);
		
	GS_ForEachObject(fCBP, allSelected+descendIntoGroups, FEOGetArcSects, &data);
	
	p1 = data.p1;
	p2 = data.p2;
	
	return data.sectFound;
}


extern "C" void GS_API FEOGetArcSects(Handle selObj, CallBackPtr cbp, void* env)
{
	FEONearestTwoPtsDataType* data = (FEONearestTwoPtsDataType*) env;
	Boolean intersectFound = false;
	WorldPt center;

	Handle h = GS_IntersectObjects(cbp, data->pickObj, selObj, true);
	
	if (h && selObj != data->pickObj) {
		size_t hSize;
		GS_GetHandleSize(cbp, h, hSize);
		size_t num = hSize/sizeof(WorldPt);
		
		//Debug("there are %ld intersections \n",num);
		
		GS_HLock(cbp, h);
		TMCArc arc(cbp, data->pickObj);
		
		center = arc.ArcCenter();
		WorldPt* cp = (WorldPt*) *h;
		intersectFound = true;
		
		for (size_t i = 0 ; i < num ; i++) {		// for each of the intersection points
			
			WorldPt p = *cp;
			
			if (WorldPt(p-arc.ArcStartPt()).Magnitude() > 2.0 &&
				WorldPt(p-arc.ArcEndPt()).Magnitude() > 2.0 ) {
				
				WorldCoord posSweepToSect = arc.PosSweepPt2Pt(data->pickPt,*cp);
				//Debug("posSweepToSect : %lf\n",posSweepToSect);
				WorldCoord negSweepToSect = arc.NegSweepPt2Pt(data->pickPt,*cp);
				//Debug("negSweepToSect : %lf\n",negSweepToSect);
				
				if (posSweepToSect < data->s2) {
					data->s2 = posSweepToSect;
					data->p2 = *cp;
				}
	
				if (negSweepToSect > data->s1 ) {
					 data->s1 = negSweepToSect;
					 data->p1 = *cp;
					 
				}
			}			
			cp++;
		}
			
		GS_HUnlock(cbp, h);
		GS_DisposeHandle(cbp, h);
		
		data->sectFound = 	(data->sectFound || intersectFound);

	}
}


Boolean GS_API TMCArc::CutArcSectToSect(const WorldPt p1, const WorldPt p2, Handle& h1, Handle& h2, Handle& h3)

/*	h2 is the arc between p1 and p2	*/
{
	if (ArcHandle() && !h1 && !h2 && !h3)  {
		
		Boolean wasCut = false;
		
		if (SweepAngle() == 360.0) {
			h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
			h1 = CreateArcPtToPt(fCBP, p2, p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
			wasCut = h1 && h2;
		}
		else {
			if (SweepAngle() >= 0.0) {
				//Debug("Positive sweep\n");
				if (WorldPt(p1) == WorldPt(ArcStartPt())) {
					//Debug("WorldPt(p1) == WorldPt(ArcStartPt())\n");
					h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h1 = CreateArcPtToPt(fCBP, p2, ArcEndPt(), ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2;
				}
				else if (WorldPt(p2) == WorldPt(ArcEndPt())) {
					//Debug("WorldPt(p2) == WorldPt(ArcStartPt())\n");
					h1 = CreateArcPtToPt(fCBP, ArcStartPt(), p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2;
				}
				else {
					h1 = CreateArcPtToPt(fCBP, ArcStartPt(), p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h3 = CreateArcPtToPt(fCBP, p2, ArcEndPt(), ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2 && h3;
				}
			}
			else {
				//Debug("Negtive sweep\n");
				if (WorldPt(p2) == WorldPt(ArcStartPt())) {
					//Debug("WorldPt(p2) == WorldPt(ArcStartPt())\n");
					h2 = CreateArcPtToPt(fCBP, p2, p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h1 = CreateArcPtToPt(fCBP, ArcEndPt(), p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2;
				}
				else if (WorldPt(p1) == WorldPt(ArcEndPt())) {
					//Debug("WorldPt(p1) == WorldPt(ArcStartPt())\n");
					h1 = CreateArcPtToPt(fCBP, p2, ArcStartPt(), ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2;
				}
				else {
					h1 = CreateArcPtToPt(fCBP, ArcEndPt(), p1, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h2 = CreateArcPtToPt(fCBP, p1, p2, ArcCenter(), ArcRadiusX(), ArcRadiusY());
					h3 = CreateArcPtToPt(fCBP, p2, ArcStartPt(), ArcCenter(), ArcRadiusX(), ArcRadiusY());
					wasCut = h1 && h2 && h3;
					
				}
			}
		
		}
		return  ((h1 && h2) || h3);
	}
	return false;
}

void GS_API TMCArc::SetAngles(const WorldCoord start, const WorldCoord sweep)
{
	if (ArcHandle() ) {

		//Debug("ArcHandle() before set: %ld\n",ArcHandle());
		GS_SetArcAnglesN(CBP(), ArcHandle(), start, sweep);
		//Debug("ArcHandle() after set: %ld\n",ArcHandle());
		
		fStartAngle = start;
		fSweepAngle = sweep;
		GS_GetObjectBounds(CBP(), ArcHandle(), fObjBounds);
	}
}



WorldPt GS_API TMCArc::ArcStartPt() 
{ 
	WorldPt retVal(ArcCenter().x+cos(StartAngle()*myDegToRad)*ArcRadiusX(),
					ArcCenter().y+sin(StartAngle()*myDegToRad)*ArcRadiusY());
	return retVal;
}
			
WorldPt GS_API TMCArc::ArcEndPt() 
{ 
	WorldPt retVal(ArcCenter().x+cos((StartAngle()+SweepAngle())*myDegToRad)*ArcRadiusX(),
					ArcCenter().y+sin((StartAngle()+SweepAngle())*myDegToRad)*ArcRadiusY() );

	return retVal;
}




