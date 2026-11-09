//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	Line object utility class

#ifndef _UMCLINE_
#define _UMCLINE_

const double myPi = 3.141592653589793;
const double myRadToDeg = 180.0 / myPi;		
const double myDegToRad = myPi/180.0;		

class TMCLine
{
	protected:
		Handle 		fLineHandle;
		WorldPt 	fStartPt;
		WorldPt 	fEndPt;
		CallBackPtr fCBP;
		
	public:
	
		TMCLine(CallBackPtr cbp, Handle mcLine) 
			{ GS_GetEndPoints(cbp,mcLine, fStartPt, fEndPt); fLineHandle = mcLine; fCBP = cbp; }

		inline WorldPt StartPt() { return fStartPt; }
		inline WorldPt EndPt() { return fEndPt; }
		inline Handle LineHandle() { return fLineHandle; }
		inline CallBackPtr CBP() { return fCBP; }

		inline void SetStartPt(WorldPt s) { fStartPt = s; }
		inline void SetEndPt(WorldPt e) { fEndPt = e; }
		
		
		inline WorldPt Vector() { return (this->EndPt() - this->StartPt()); }
		
		WorldPt GS_API UnitVector();  
		WorldPt GS_API UnitPerpVector();

		WorldCoord GS_API ScalarProjection(WorldPt vector);
		WorldPt GS_API VectorProjection(WorldPt vector);
		WorldCoord GS_API PerpScalarProjection(WorldPt vector);
		WorldPt GS_API PerpVectorProjection(WorldPt vector);
		
		inline WorldCoord Length() { return WorldPt(this->Vector()).Magnitude(); }
		

		inline WorldPt VectorFromStartPt(WorldPt pt)
			{ return pt - this->StartPt(); }
		inline WorldPt VectorFromEndPt(WorldPt pt)
			{ return pt - this->EndPt(); }
		inline WorldPt MidPoint() { return this->StartPt()+WorldPt(this->Vector()/2L); }
		double GS_API ATanAngleRad();
		inline double ATanAngleDeg() { return  this->ATanAngleRad() * myRadToDeg; }
		WorldCoord GS_API Angle0To2Pi();
		inline WorldCoord Angle0To360() {return this->Angle0To2Pi() * myRadToDeg; }
		short GS_API VectorQuadrant();
		Boolean GS_API AsChord(CallBackPtr cbp, WorldCoord percentOfSegLenForBulge, Boolean onLeft, 
					  WorldRect& bounds, WorldCoord& startAngle, WorldCoord& sweepAngle);
		Handle GS_API OffsetLine(CallBackPtr cbp, const WorldCoord offset);
		WorldCoord GS_API Offset(const WorldPt pt);
		Boolean GS_API IntersectLine(CallBackPtr cbp, WorldPt startPt, WorldPt endPt, WorldCoord& xDist);
		Boolean GS_API IntersectOval(CallBackPtr cbp, WorldRect ovalBounds, WorldCoord& xDist1, WorldCoord& xDist2);
		WorldCoord GS_API NearestExtendOffset(CallBackPtr cbp, Handle extendToObj, 
									const Boolean extendFromEnd, const WorldPt lastExtPt);
		WorldCoord GS_API MinExtendOffset(const WorldCoord off1, const WorldCoord off2, const Boolean extendFromEnd);
		Boolean GS_API Picked(WorldPt pt, Boolean& endOfLinePicked);
		void GS_API NearestTwoPts(CallBackPtr cbp, Handle line, const WorldPt p, 
							WorldPt& p1, WorldPt& p2);
		void GS_API CutPtToPt(CallBackPtr cbp, const WorldPt pickPt, const WorldPt p1, 
						const WorldPt p2, Handle& h1, Handle& h2);

};


#endif

