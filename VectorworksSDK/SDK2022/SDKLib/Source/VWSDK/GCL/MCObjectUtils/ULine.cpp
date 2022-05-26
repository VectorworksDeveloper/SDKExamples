//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Line object utility class
	

#include "StdHeaders.h"

#include "GCL/ULine.h"
#include "GCL/Unclassified.h"

struct FEONearestTwoPtsDataType	{
	Handle pickObj;
	WorldPt pickPt;
	WorldPt p1;
	WorldPt p2;
	Boolean sectFound;
};

extern "C" void GS_API FEOGetLineSects(Handle selObj, CallBackPtr cbp, void* env);


WorldPt GS_API TLine::UnitVector(void)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->EndPt() - this->StartPt()).IsZero() ) {
		retVector = ((WorldPt) (this->EndPt() - this->StartPt())).Normal();
	}
	return retVector;

}

WorldPt GS_API TLine::UnitPerpVector(void)
{
	WorldPt retVector;
	retVector.x = -this->UnitVector().y;
	retVector.y = this->UnitVector().x;
	return retVector;

}


WorldCoord GS_API TLine::ScalarProjection(WorldPt vector)
{
	

	if (!(this->Vector()).IsZero()) {
		return DotProduct(vector, this->UnitVector());
	}
	return 0.0;
}


WorldPt GS_API TLine:: VectorProjection(WorldPt vector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->Vector()).IsZero()) {
		retVector = DotProduct(vector, this->UnitVector()) * this->UnitVector();
	}
	return retVector;
}

WorldCoord GS_API TLine:: PerpScalarProjection(WorldPt vector)
{
	if (!(this->Vector()).IsZero()) {
		return DotProduct(vector, this->UnitPerpVector());
	}
	return 0.0;
}

WorldPt GS_API TLine:: PerpVectorProjection(WorldPt vector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->Vector()).IsZero()) {
		retVector = DotProduct(vector, this->UnitPerpVector()) * this->UnitPerpVector();
	}
	return retVector;
}


double GS_API TLine:: ATanAngleRad()
{
	if (this->Vector().IsZero())
		return 0.0;
		
	if (this->Vector().x == 0L) {
		if (this->Vector().y > 0L)
			return Pi;
		else
			return -Pi;
	}
				
	return atan(this->Vector().y / this->Vector().x);
	
}

short GS_API TLine:: VectorQuadrant()
{
	if (this->Vector().IsZero())
		return -1;
		
	if (this->Vector().x == 0L) {
		if (this->Vector().y > 0L)
			return 90;
		else
			return 270;
	}
			
	if (this->Vector().y == 0L) {
		if (this->Vector().x > 0L)
			return 0;
		else
			return 180;
	}
		
	if (this->Vector().x > 0L) {
		if (this->Vector().y > 0L)
			return 1;
		else
			return 4;
	}
	else {	
		if (this->Vector().y > 0L)
			return 2;
		else
			return 3;
	}
	
}

WorldCoord GS_API TLine:: Angle0To2Pi()
{
	switch (this->VectorQuadrant()) {
		case 2 : 
		case 3 : {
			return this->ATanAngleRad() + Pi;
		}
		case 4 : {
			return this->ATanAngleRad() + 2*Pi;
		}
		case 180 : {
			return Pi;
		}
		case 90 : {
			return Pi/2.0;
		}
		case -90 : {
			return 3*Pi/2.0;
		}
	}
	return this->ATanAngleRad();
}


Boolean GS_API TLine::AsChord(CallBackPtr, WorldCoord percentOfHalfOfLineForBulge, Boolean onLeft, 
					  WorldRect& bounds, WorldCoord& startAngle, WorldCoord& sweepAngle)
{
	WorldCoord m = Length()/2.0;
	WorldCoord bulgeDist = percentOfHalfOfLineForBulge*m;
	if (bulgeDist > m) 
		bulgeDist = m; 
	if (bulgeDist < 0L) 
		bulgeDist = 0L; 
		
	WorldCoord r = bulgeDist ? (bulgeDist*bulgeDist+m*m)/(2.0*bulgeDist) : 0;
	
	WorldPt center;
	
	if (onLeft)
		center = MidPoint() + WorldPt((-UnitPerpVector()* (r-bulgeDist)));
	else
		center = MidPoint() + WorldPt((UnitPerpVector()* (r-bulgeDist)));
	
	TLine line2(center,fEndPt);
	TLine line3(center,fStartPt);
	bounds.Set(center.x-r,center.y+r,center.x+r,center.y-r);
	
	startAngle = line3.Angle0To360();
	if (onLeft) {
		sweepAngle = -ArcSweep(line2.Angle0To360(), line3.Angle0To360(), true);
	}
	else {
		sweepAngle = ArcSweep(line2.Angle0To360(), line3.Angle0To360(), true);
	}

	return true;
}
					  
Handle GS_API TLine::OffsetLine(CallBackPtr cbp, Handle orig, const WorldCoord offset)
{
	WorldPt offsetVect = WorldPt(this->UnitPerpVector() * offset);
	
	Handle offsetObj = GS_CreateLine(cbp,fStartPt,fEndPt);
	GS_SetEndPoints(cbp, offsetObj, fStartPt + offsetVect, fEndPt + offsetVect);
	CopyAttributes(cbp, orig, offsetObj);
	return offsetObj;
}

WorldCoord GS_API TLine::Offset(const WorldPt pt)
{
	WorldPt vectorFromStartPt(pt.x-fStartPt.x, pt.y-fStartPt.y);
	return WorldCoord(this->PerpScalarProjection(WorldPt(vectorFromStartPt)));
}

Boolean GS_API TLine::IntersectLine(CallBackPtr cbp, WorldPt startPt, WorldPt endPt, WorldCoord& xDist)
{
	WorldPt xPt;
	Boolean parallel;
	Boolean onBothLines;
	
	GS_LineLineIntersect(cbp,fStartPt, fEndPt, startPt, endPt, 
						parallel, onBothLines, xPt);

				
	if (!parallel) {
		
		xDist = this->ScalarProjection(xPt - fStartPt);

		return true;
	}
	else
		return false;
}


Boolean GS_API TLine::IntersectOval(CallBackPtr cbp, WorldRect ovalBounds, WorldCoord& xDist1, WorldCoord& xDist2)
{
	Sect2Struct xPts;
	 
	GS_LineEllipseIntersect(cbp,fStartPt, fEndPt, ovalBounds, xPts);
	if (!xPts.legal1 && !xPts.legal2)
		return false;
	else {
		if (xPts.legal1)
			xDist1 = this->ScalarProjection(xPts.int1-fStartPt);
		else 
			xDist1 = 0.0;
		if (xPts.legal2)
			xDist2 = this->ScalarProjection(xPts.int2-fStartPt);
		else 
			xDist1 = 0.0;
	}
	return true;
}


WorldCoord GS_API TLine::NearestExtendOffset(CallBackPtr cbp, Handle extendToObj, 
									const Boolean extendFromEnd, const WorldPt lastExtPt)
{
	WorldCoord retVal = 0.0;
	Handle thisLine = GS_CreateLine(cbp, StartPt(), EndPt());
	GS_SelectObject(cbp, thisLine, false);
	
	if (extendToObj && thisLine) {
		WorldCoord dist = 0.0;
		WorldCoord minOffset = 0.0;
		Boolean offsetFound = false;
		
		Handle h = GS_IntersectObjects(cbp, thisLine, extendToObj, false);
		if (h) {
			size_t	num;
			GS_GetHandleSize(cbp, (Handle) h, num);
			size_t numPts = num/sizeof(WorldPt);

			GS_HLock(cbp, (Handle) h);
			WorldPt* cp = (WorldPt*) *h;

			for (size_t i = 0 ; i < numPts ; i++) {
				if (OnObject(cbp, extendToObj, *cp) && *cp != lastExtPt) {
					//CreateLocus(cbp, *cp);
					dist = ScalarProjection(VectorFromStartPt(*cp));
					//Debug("len : %lf dist %lf \n",this->Length(),dist);
					minOffset = MinExtendOffset(dist, minOffset, extendFromEnd);
					//Debug("minOffset %lf \n",minOffset);
					offsetFound = true;
				}
				cp++;
			}
			if (offsetFound) 
				retVal = minOffset;
			else
				retVal = 0.0;
				
			GS_HUnlock(cbp, (Handle) h);
			GS_DisposeHandle(cbp, (Handle) h);
		}
		GS_DeleteObject(cbp, thisLine, false);
	}
	return retVal;
}

WorldCoord GS_API TLine::MinExtendOffset(const WorldCoord off1, const WorldCoord off2, 
								const Boolean extendFromEnd)
{
	WorldCoord retVal= 0.0;
	if (off1 == 0.0 && off2 == 0.0) {
		retVal = 0.0;
	}
	
	else {
		if (extendFromEnd) {
			WorldCoord len = this->Length();
			if (off1 > len || off2 > len ) {
				if (off1 > len && off2 >len ) {
					retVal = Min(off1,off2);
				}
				else {
					if (off1 > off2) 
						retVal = off1;
					else
						retVal = off2;
				}
			}
			else {
				retVal = 0.0;
			}
		}
		else {
			
			if (off1 < 0.0 || off2 < 0.0 ) {
				
				if (off1 < 0.0 && off2 < 0.0 ) {
					retVal = Max(off1,off2);
				}
				else {
					retVal = Min(off1,off2);
				}
			}
			else {
				retVal = 0.0;
			}
		}
		
	}
	return retVal;

}

Boolean GS_API TLine::Picked(WorldPt pt, Boolean& endOfLinePicked)
{
	WorldCoord proj = ScalarProjection(WorldPt(pt-StartPt()));
	endOfLinePicked = proj > Length()/2.0;
	return (proj >= 0.0 && proj < Length()/2.0);
			
}

#if 0
static WorldCoord AngleTurnDeg(const WorldPt prevVector, const WorldPt turnedVector)
{ 
	return (OnLeftOf(turnedVector, prevVector) ? AngleBetweenDeg(turnedVector, prevVector) :
												- AngleBetweenDeg(turnedVector, prevVector)); 
}
#endif



Boolean GS_API TLine::NearestTwoPts(CallBackPtr cbp, Handle line, const WorldPt p, 
							WorldPt& p1, WorldPt& p2)
{
	
	FEONearestTwoPtsDataType	data;
	
	data.pickObj = line;
	data.pickPt = p;
	data.p1 = StartPt();
	data.p2 = EndPt();
	data.sectFound = false;
	
	GS_ForEachObject(cbp, allSelected+descendIntoGroups, FEOGetLineSects, &data);
	
	p1 = data.p1;
	p2 = data.p2;
	
	return data.sectFound;
}

extern "C" void GS_API FEOGetLineSects(Handle selObj, CallBackPtr cbp, void* env)
{
	FEONearestTwoPtsDataType* data = (FEONearestTwoPtsDataType*) env;
	
	Handle h = GS_IntersectObjects(cbp, data->pickObj, selObj, true);
		
	Boolean intersectFound = false;
	if (h && selObj != data->pickObj) {
	
		size_t num;
		GS_GetHandleSize(cbp, (Handle) h, num);
		size_t numPts = num / sizeof(WorldPt);
		//Debug("there are %ld intersections \n",num);
		GS_HLock(cbp, (Handle) h);
		TLine line(cbp, data->pickObj);
		
		WorldPt* cp = (WorldPt*) *h;
		intersectFound = true;
		
		for (size_t i = 0 ; i < numPts ; i++) {
		
			WorldCoord pickPtProj = line.ScalarProjection(data->pickPt-line.StartPt());
			WorldCoord p1Proj = line.ScalarProjection(data->p1-line.StartPt());
			WorldCoord p2Proj = line.ScalarProjection(data->p2-line.StartPt());
			WorldCoord thisPtProj = line.ScalarProjection(*cp-line.StartPt());
			
			if (thisPtProj < pickPtProj && thisPtProj > p1Proj)
				data->p1 = *cp;
			else if (thisPtProj > pickPtProj && thisPtProj < p2Proj)
				data->p2 = *cp;
			cp++;
		}
			
		GS_HUnlock(cbp, (Handle) h);
		GS_DisposeHandle(cbp, (Handle) h);
	}
	data->sectFound = data->sectFound || intersectFound;
}

Boolean GS_API TLine::CutPtToPt(CallBackPtr cbp, const WorldPt pickPt, const WorldPt p1, 
						const WorldPt p2, Handle& h1, Handle& h2, Handle& h3)
{
	if ( (p1 != StartPt() && p2 != EndPt() ) || ( p2 != StartPt() && p1 != EndPt() &&
		  h1 == nil && h2 == nil && h3 == nil) ) {
	
		//WorldCoord distToPickPt = ScalarProjection(pickPt-StartPt());
		WorldCoord distToP1 = ScalarProjection(p1-StartPt());
		WorldCoord distToP2 = ScalarProjection(p2-StartPt());
		
		if (distToP1 <= distToP2) {
		
			if (p1 == StartPt()) {
				h2 = GS_CreateLine(cbp, StartPt(), p2);
				h1 = GS_CreateLine(cbp, p2, EndPt());
			}
			else if (p2 == EndPt()) {
				h2 = GS_CreateLine(cbp, p1, EndPt());
				h1 = GS_CreateLine(cbp, StartPt(), p1);
			}
			else {
				//Debug("distToPickPt < distToP2\n");
				h1 = GS_CreateLine(cbp, StartPt(), p1);
				h2 = GS_CreateLine(cbp, p1, p2);
				h3 = GS_CreateLine(cbp, p2, EndPt());
			}
		}
		else {
		
			if (p2 == StartPt()) {
				h2 = GS_CreateLine(cbp, StartPt(), p1);
				h1 = GS_CreateLine(cbp, p1, EndPt());
			}
			else if (p1 == EndPt()) {
				h2 = GS_CreateLine(cbp, p2, EndPt());
				h1 = GS_CreateLine(cbp, StartPt(), p2);
			}
			else {
				//Debug("distToPickPt < distToP2\n");
				h1 = GS_CreateLine(cbp, StartPt(), p2);
				h2 = GS_CreateLine(cbp, p2, p1);
				h3 = GS_CreateLine(cbp, p1, EndPt());
			}
		}
		
		return (h1 || h2 || h3);
	}
	return false;
}
