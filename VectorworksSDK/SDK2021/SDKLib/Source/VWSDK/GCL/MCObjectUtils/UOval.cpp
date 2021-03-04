//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Oval object utility class
	


#include "StdHeaders.h"
#include "GCL/UOval.h"
#include "GCL/ULine.h"

#include "GCL/Debug.h"



					  
Handle GS_API TOval::OffsetOval(CallBackPtr cbp, const WorldCoord off)
{
	WorldRect newRect = fBounds;
	WorldCoord major = (fBounds.right-fBounds.left)/2.0;
	WorldCoord minor = (fBounds.top-fBounds.bottom)/2.0;

	
	if (off  > 0L || -major < off) {
		newRect.top = fBounds.top+off;
		newRect.bottom = fBounds.bottom-off;
	}
	if (off > 0L || -minor < off) {
		newRect.right = fBounds.right+off;
		newRect.left = fBounds.left-off;
	}
		
	if (!newRect.IsEmpty()) 
		return GS_CreateOval(cbp,newRect);

	return  nil;
}

WorldCoord GS_API TOval::Offset(CallBackPtr, WorldPt pt)
{
	WorldCoord cosTheta, sinTheta,theta;
	WorldCoord pickPtMag2;
	WorldCoord major = (fBounds.right-fBounds.left)/2.0;
	WorldCoord minor = (fBounds.top-fBounds.bottom)/2.0;
	WorldPt center = fBounds.Center();
	WorldPt pv(fabs(pt.x-center.x),fabs(pt.y-center.y));
	
	{	TLine ptVector(pv);
		pickPtMag2 = ptVector.Vector().x*ptVector.Vector().x + ptVector.Vector().y*ptVector.Vector().y;
		theta = ptVector.Angle0To2Pi();
	}
	if (theta > 0.0 && theta < Pi/2.0 && minor != 0) {
		WorldCoord k = major/minor*tan(theta);
		//Debug("k : %lf\n",k);
		cosTheta = 1/sqrt(1+ xpwr2(k));
		//Debug("cosTheta : %lf\n",cosTheta);
		sinTheta = k/sqrt(1+ xpwr2(k));
		//Debug("sinTheta : %lf\n",sinTheta);
	}
	else {
		cosTheta = cos(theta);
		sinTheta = sin(theta);
	}
	
	

	WorldCoord a = 1.0;
	WorldCoord b = 2.0*(major*xpwr2(cosTheta) + minor*xpwr2(sinTheta));
	WorldCoord c = xpwr2(major*cosTheta) + xpwr2(minor*sinTheta) - pickPtMag2;
	
	WorldCoord soln1,soln2;
	Boolean real1,real2;
	
	SolveQuadratic(a, b, c, soln1, soln2, real1, real2);
	//Debug("real1 : %ld\n",real1);
	//Debug("soln1 : %lf\n",soln1);
	//Debug("real2 : %ld\n",real2);
	//Debug("soln2 : %lf\n",soln2);
	
	return WorldCoord(soln1);
}

void GS_API SolveQuadratic(WorldCoord a, WorldCoord b, WorldCoord c, WorldCoord& s1,
			WorldCoord& s2, Boolean& g1, Boolean& g2)
{
	WorldCoord					tmp1;
	WorldCoord					tmp2;

	tmp1 = -(b/(2.0*a));
	tmp2 = xpwr2(b) - 4.0*a*c;
	if (tmp2 < 0) {
		g1 = false;
		g2 = false;
		return;
	}
	g1 = true;
	g2 = true;
	tmp2 = sqrt(tmp2) / (2.0*a);
	s1 = tmp1+tmp2;
	s2 = tmp1-tmp2;
}
// QuadraticSolve

