//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "GCL/UXLine.h"


GS_API TXLine::TXLine()
{
	fStartPt.Set(0,0);
	fEndPt.Set(0,0);
}

WorldPt GS_API TXLine::operator[](double t)
{
	if (t<0) t = 0;
	else if (t>1) t = 1;
	
	return (1-t)*fStartPt + t*fEndPt;
}


#define PrintPoint(P) Debug(#P " x = %Lf, y = %Lf",P.x,P.y)
#define PrintDouble(D) Debug(#D " = %Lf",D)

double GS_API TXLine::TFromP(const WorldPt& p)
{
#if 0
	double t;
	WorldPt p1 = (p-fStartPt);
	WorldPt p2 = (fEndPt - fStartPt);
	t = p1.Magnitude() / p2.Magnitude();
	short sign1 = (p1.x/p1.x) * (p1.y/p1.y);
	short sign2 = (p2.x/p2.x) * (p2.y/p2.y);
	t *= sign1 * sign2;

	return t;
#endif
#if 0
	double len = this->Length();
	
	WorldPt pV = p - fStartPt;
	WorldPt eV = fEndPt - fStartPt;
	
	double dot = pV.x * eV.x + pV.y * eV.y;
	double sp = dot / eV.Magnitude();
	
	PrintPoint(pV);
	PrintPoint(eV);
	PrintDouble(dot);
	PrintDouble(sp);
	PrintPoint(p);
	PrintPoint(fStartPt);
	PrintPoint(fEndPt);
	return sp/len;
#endif
	
	double len = this->Length();
	double sp = this->ScalarProjection(p - fStartPt);
	return sp / len;
}


double GS_API TXLine::Angle()
{
	if (this->Vector().IsZero())
		return 0.0;
		
	if (this->Vector().x == 0L) {
		if (this->Vector().y > 0L)
			return 1.570796326794897;
		else
			return 4.71238898038469;
	}
				
	return atan((double) this->Vector().y/(double) this->Vector().x);	
}


WorldPt GS_API TXLine::UnitVector(void)
{
	WorldPt retVector(0,0);
	
	if (!(this->EndPt() - this->StartPt()).IsZero() ) {
		retVector = ((WorldPt) (this->EndPt() - this->StartPt())).Normal();
	}
	return retVector;

}

WorldPt GS_API TXLine::UnitPerpVector(void)
{
	WorldPt retVector;
	retVector.x = -this->UnitVector().y;
	retVector.y = this->UnitVector().x;
	
	return retVector;
}


WorldCoord GS_API TXLine::ScalarProjection(WorldPt vector)
{
	if (!(this->Vector()).IsZero()) {
		return DotProduct(vector, this->UnitVector());
	}
	return 0.0;
}


WorldPt GS_API TXLine::VectorProjection(WorldPt vector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->Vector()).IsZero()) {
		retVector = DotProduct(vector, this->UnitVector()) * this->UnitVector();
	}
	return retVector;
}

WorldCoord GS_API TXLine::PerpScalarProjection(WorldPt vector)
{
	if (!(this->Vector()).IsZero()) {
		return DotProduct(vector, this->UnitPerpVector());
	}
	return 0.0;
}

WorldPt GS_API TXLine::PerpVectorProjection(WorldPt vector)
{
	WorldPt retVector(0.0,0.0);
	
	if (!(this->Vector()).IsZero()) {
		retVector = DotProduct(vector, this->UnitPerpVector()) * this->UnitPerpVector();
	}
	return retVector;
}

double_t GS_API TXLine::YIntercept() 
{
	return fStartPt.y - this->Slope() * fStartPt.x;
}

void GS_API TXLine::Rotate(double angle, WorldPt center)
{
	fStartPt -= center;
	fEndPt -= center;
	
	double cosTheta = cos(angle);
	double sinTheta = sin(angle);
		
	fStartPt.x = fStartPt.x * cosTheta - fStartPt.y * sinTheta;
	fStartPt.y = fStartPt.x * sinTheta + fStartPt.y * cosTheta;
	fEndPt.x = fEndPt.x * cosTheta - fEndPt.y * sinTheta;
	fEndPt.y = fEndPt.x * sinTheta + fEndPt.y * cosTheta;
	
	fStartPt += center;
	fEndPt += center;
}

void GS_API TXLine::Scale(double sx, double sy, WorldPt center)
{
	fStartPt 	-= center;
	fEndPt 		-= center;
	
	fStartPt.x 	*= sx;
	fStartPt.y 	*= sy;
	fEndPt.x 	*= sx;
	fEndPt.y	*= sy;
		
	fStartPt 	+= center;
	fEndPt 		+= center;
}

#if 0
Quadrants GS_API TXLine::VectorQuadrant()
{
	if (this->Vector().IsZero())
		return none;
		
	if (this->Vector().x == 0L) {
		if (this->Vector().y > 0L)
			return ypos;
		else
			return yneg;
	}
			
	if (this->Vector().y == 0L) {
		if (this->Vector().x > 0L)
			return xpos;
		else
			return xneg;
	}
		
	if (this->Vector().x > 0L) {
		if (this->Vector().y > 0L)
			return I;
		else
			return IV;
	}
	else {	
		if (this->Vector().y > 0L)
			return II;
		else
			return III;
	}
	
}
#endif

