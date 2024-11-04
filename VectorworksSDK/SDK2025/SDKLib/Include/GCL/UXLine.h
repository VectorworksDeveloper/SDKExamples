//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#ifndef _UACL_XLINE_
#define _UACL_XLINE_


const double myPi = 3.141592653589793;
const double myRadToDeg = 180.0 / myPi;		
const double myDegToRad = myPi/180.0;		

class TXLine
{
	enum Quadrants {I,II,III,IV,xpos,xneg,ypos,yneg,none};
	
	protected:
		WorldPt 		fStartPt;
		WorldPt 		fEndPt;
		
	public:
	// basics
		GS_API TXLine();
		TXLine(WorldPt start, WorldPt end): fStartPt(start), fEndPt(end) {}
		TXLine(TXLine &lhs): fStartPt(lhs.fStartPt), fEndPt(lhs.fEndPt) {}
		TXLine& operator=(TXLine& lhs) 
			{fStartPt = lhs.fStartPt;fEndPt = lhs.fEndPt; return *this;}
		
		void Set(const WorldPt& startPt, const WorldPt& endPt) 
			{fStartPt = startPt; fEndPt = endPt;}
		void Set(WorldCoord sx, WorldCoord sy, WorldCoord ex, WorldCoord ey)
			{fStartPt.Set(sx,sy); fEndPt.Set(ex,ey);}
	
	// accessors
		WorldPt& StartPt() { return fStartPt; }
		WorldPt& EndPt() { return fEndPt; }
		WorldPt MidPoint() { return this->StartPt() + this->Vector()/2.0; }
		WorldPt GS_API operator[](double t);		// parametric access
		double GS_API TFromP(const WorldPt& p);
		
		double GS_API Angle();
//		Quadrants VectorQuadrant();
		
	// calculations
		WorldPt Vector() { return (this->EndPt() - this->StartPt()); }
		WorldPt GS_API UnitVector();  
		WorldPt GS_API UnitPerpVector();

		WorldCoord GS_API ScalarProjection(WorldPt vector);
		WorldPt GS_API VectorProjection(WorldPt vector);
		WorldCoord GS_API PerpScalarProjection(WorldPt vector);
		WorldPt GS_API PerpVectorProjection(WorldPt vector);
		
		WorldPt VectorFromStartPt(WorldPt pt)
			{ return pt - this->StartPt(); }
		WorldPt VectorFromEndPt(WorldPt pt)
			{ return pt - this->EndPt(); }
		
		WorldCoord Length() { return (this->Vector()).Magnitude(); }
		double_t Slope() {return (fEndPt.y - fStartPt.y)/(fEndPt.x - fStartPt.x);}
		double_t GS_API YIntercept();
		
	// modify
		void OffSet(const WorldPt& v) {fStartPt += v; fEndPt += v;}
		void OffSet(const WorldCoord& s)	{this->OffSet(this->UnitVector()*s);}
		void OffSetPerp(const WorldCoord& s) {this->OffSet(this->UnitPerpVector()*s);}
		
		void OffSetStart(const WorldCoord& off) {fStartPt += this->UnitVector()*off;}
		void OffSetEnd(const WorldCoord& off) {fEndPt += this->UnitVector()*off;}
		
	// special
		void GS_API Rotate(double angle, WorldPt center);
		void GS_API Scale(double sx, double sy, WorldPt center);
};



#endif

