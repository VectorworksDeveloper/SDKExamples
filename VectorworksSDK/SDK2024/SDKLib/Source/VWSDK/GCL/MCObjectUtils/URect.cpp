//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
// Rect object utility class


#include "StdHeaders.h"
#include "GCL/URect.h"
					  
Handle GS_API TMCRect::OffsetMCRect(const WorldCoord off)
// OffsetMCRect can not be called OffsetRect because of a suspected
// Altura name conflict which causes a link error.
{
	WorldRect newRect = fBounds;
	
	if (off  > 0L || fBounds.bottom-fBounds.top < 2*off) {
		newRect.top = fBounds.top+off;
		newRect.bottom = fBounds.bottom-off;
	}
	if (off > 0L || fBounds.left-fBounds.right < 2*off) {
		newRect.right = fBounds.right+off;
		newRect.left = fBounds.left-off;
	}
		
	if (!newRect.IsEmpty()) 
		return GS_CreateRectangle(fCBP,newRect);

	return  nil;
}


WorldCoord GS_API TMCRect::Offset(WorldPt pt)
{
	WorldCoord vertOff = 0L;
	WorldCoord horOff = 0L;

	horOff = Min(fabs(pt.x-fBounds.left),fabs(pt.x-fBounds.right));

	vertOff = Min(fabs(pt.y-fBounds.top),fabs(pt.y-fBounds.bottom));

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

