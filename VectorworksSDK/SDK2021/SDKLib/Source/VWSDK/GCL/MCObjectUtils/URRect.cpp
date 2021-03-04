//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Rounded Rect object utility class


#include "StdHeaders.h"
#include "GCL/URRect.h"
					  
Handle GS_API TMCRRect::OffsetRRect(const WorldCoord off)
{

	WorldRect newRect = fBounds;
	WorldCoord xDiam,yDiam;
	
	xDiam = (fXDiam + (2 * off) > 0L) ? fXDiam + (2 * off) : 0L;
	yDiam = (fYDiam + (2 * off) > 0L) ? fYDiam + (2 * off) : 0L;
	if (fBounds.top-fBounds.bottom > -2*off) {
		newRect.top = fBounds.top+off;
		newRect.bottom = fBounds.bottom-off;
	}
	else {
		WorldCoord vert = (fBounds.top+fBounds.bottom)/2;
		newRect.top = vert;
		newRect.bottom = vert;
	}
	if (fBounds.right-fBounds.left > -2*off) {
		newRect.right = fBounds.right+off;
		newRect.left = fBounds.left-off;
	}
	else {
		WorldCoord hor = (fBounds.right+fBounds.left)/2;
		newRect.right = hor;
		newRect.left = hor;
	}

	if (!newRect.IsEmpty()) 
		return GS_CreateRRectangle(fCBP, newRect, xDiam, yDiam);

	return  nil;
}

WorldCoord GS_API TMCRRect::Offset(WorldPt pt)
{
	WorldCoord vertOff = 0L;
	WorldCoord horOff = 0L;

	horOff = Min(fabs(pt.x-fBounds.left),fabs(pt.x-fBounds.right));
	//Debug("horOff : %ld\n",horOff);

	vertOff = Min(fabs(pt.y-fBounds.top),fabs(pt.y-fBounds.bottom));
	//Debug("vertOff : %ld\n",vertOff);

	if (fBounds.Union(pt) == fBounds) 
		 return -Min(horOff, vertOff);
	else {
		if (pt.x > fBounds.left && pt.x < fBounds.right)
			return vertOff;
		if (pt.y > fBounds.bottom && pt.y < fBounds.top)
			return horOff;
		return Max(horOff,vertOff);
	}
	
}

void GS_API TMCRRect::DrawCoordRRect()
{
	WorldPt p1(Bounds().left+XDiam()/2,Bounds().top); 
	WorldPt p2(Bounds().right-XDiam()/2,Bounds().top); 
	GS_DrawCoordLine(fCBP, p1, p2);
	
	p1.Set(Bounds().right,Bounds().top-YDiam()/2);
	p2.Set(Bounds().right,Bounds().bottom+YDiam()/2);
	GS_DrawCoordLine(fCBP, p1, p2);
	
	p1.Set(Bounds().right-XDiam()/2,Bounds().bottom);
	p2.Set(Bounds().left+XDiam()/2,Bounds().bottom);
	GS_DrawCoordLine(fCBP, p1, p2);
	
	p1.Set(Bounds().left,Bounds().top-YDiam()/2);
	p2.Set(Bounds().left,Bounds().bottom+YDiam()/2);
	GS_DrawCoordLine(fCBP, p1, p2);
}
