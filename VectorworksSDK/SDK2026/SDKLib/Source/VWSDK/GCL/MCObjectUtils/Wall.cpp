//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"
#include "GCL/Wall.h"


//////////
//
//	Debugging
//
//////////

#if 0

extern "C" Boolean GS_API _PrintBreaks(Handle wall, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr cbp, void* dataParam)
{
	GSCalledRoutineSetup(cbp);
	
	Debug("break(%d) offset = %ld   type = %ld",index,off,breakType);
	if (breakType == kCapBreak)
		Debug("lOff = %ld   rOff = %ld",((CapBreakType*)breakData)->leftOff,((CapBreakType*)breakData)->rightOff);
	return false;
}

void PrintBreaks(CallBackPtr cbp, Handle theWall)
{
	ForEachBreak(cbp,theWall, _PrintBreaks, NULL);
}

void PrintWall(Wall &w)
{
	Debug("w.c.x1 = %Lf   w.c.y1 = %Lf   w.c.x2 = %Lf   w.c.y2 = %Lf",w.center.StartPt().x,w.center.StartPt().y,w.center.EndPt().x,w.center.EndPt().y);
	Debug("w.l.x1 = %Lf   w.l.y1 = %Lf   w.l.x2 = %Lf   w.l.y2 = %Lf",w.left.StartPt().x,w.left.StartPt().y,w.left.EndPt().x,w.left.EndPt().y);
	Debug("w.r.x1 = %Lf   w.r.y1 = %Lf   w.r.x2 = %Lf   w.r.y2 = %Lf",w.right.StartPt().x,w.right.StartPt().y,w.right.EndPt().x,w.right.EndPt().y);

}

#endif 

//////////
//
//	CLASS:	Wall
//
//////////


extern "C" {

	// this can't be static, but shouldn't be in a header file either
	Boolean GS_API _GetCaps(Handle /*wall*/, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr, void* dataParam);


	Boolean GS_API _GetCaps(Handle /*wall*/, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr, void* dataParam)
	{
		GetCapsRec *data = (struct GetCapsRec *)dataParam;
		
		if (breakType != kCapBreak)
			return false;
		
		if (off == -1) {
			data->c1 = *((CapBreakType*)breakData);
			data->index1 = (short) index;
			data->found1 = true;
		}
		else {
			data->c2 = *((CapBreakType*)breakData);
			data->index2 = (short) index;
			data->found2 = true;
		}
			
		return false;
	}
}

void GS_API Wall::Setup(CallBackPtr cbpParam, Handle theWall)
{
	cbp = cbpParam;
	wh = theWall;
	
	// setup lines
		GS_ForEachBreak(cbp,theWall, _GetCaps, (void*) &cr);
#ifdef GS_WRAP_RETURN_COORD_JAK
		WorldCoord outCoordLen;
		GS_WrapGetWallWidth(cbp, theWall, outCoordLen);
		offset = outCoordLen;
#else
		offset  = GS_GetWallWidth(cbp,theWall);
#endif				
		WorldPt s,e;
		GS_GetEndPoints(cbp,theWall,s,e);
		center.Set(s.x,s.y,e.x,e.y);
		
		
		if (!cr.found1) {
			cr.c1.rightOff = 0;
			cr.c1.leftOff = 0;
			cr.c1.closed = false;
			cr.c1.round = false;
		}
		if (!cr.found2) {
			cr.c2.rightOff = 0;
			cr.c2.leftOff = 0;
			cr.c2.closed = false;
			cr.c2.round = false;
		}
		
		left = center;
		left.OffSetPerp(offset/2);
		left.OffSetStart(cr.c1.leftOff);
		left.OffSetEnd(cr.c2.leftOff);
		
		right = center;
		right.OffSetPerp(-offset/2);
		right.OffSetStart(cr.c1.rightOff);
		right.OffSetEnd(cr.c2.rightOff);
		
}

// GS_SDKPPC_JAK	comment out the sqr() definition here because it is already in BasicMath.X.h
// inline double_t sqr(const double_t& x) {return x*x;}

WorldCoord GS_API Wall::CalcOffset(const WorldPt& toPt, const WorldPt& centerPt)
// the ppc 68k emulator has trouble with sqrt() call in Magnitude,
// that's why there is the near zero check for tot.  if ppc specific 
// problems come up in this tool suspect sqrt()
{
		
	double_t	mag = sqr((toPt - centerPt).Magnitude());
	double_t	off = sqr(offset / 2.0);
	double_t 	tot = mag - off;
	
	if (tot > 0.0)
		tot = sqrt(tot);
	else
		tot = 0.0;
	
	return (WorldCoord) tot;
}

void GS_API Wall::SetWallPt(WallLine wl, JoinWhere jw, WorldPt& toWhere)
{
//	Debug("line %d    where &d\n",wl,jw);
	
	if (wl == wlCenter) {
		WorldPt		s,e;
		GS_GetEndPoints(cbp,wh,s,e);
		if (jw == joinStart)
			s = toWhere;
		else
			e = toWhere;
		GS_SetEndPoints(cbp,wh,s,e);
	}
	else {
		if (jw == joinStart) {
			if (wl == wlLeft) {
//				ShowPoint(cbp,toWhere,mcRedColor);
				cr.c1.leftOff = - CalcOffset(toWhere,center.StartPt());
				if (center.TFromP(toWhere) > 0)
					cr.c1.leftOff *= -1;
			}
			if (wl == wlRight) {
//				ShowPoint(cbp,toWhere,mcLtBlueColor);
				cr.c1.rightOff = - CalcOffset(toWhere,center.StartPt());
				if (center.TFromP(toWhere) > 0)
					cr.c1.rightOff *= -1;
			}
			if (cr.found1) 
				GS_DeleteBreak(cbp,wh,cr.index1);
			GS_AddBreak(cbp,wh,-1,kCapBreak,&(cr.c1));
		}
		else {
			if (wl == wlLeft) {
//				ShowPoint(cbp,toWhere,mcDkGreenColor);
				cr.c2.leftOff = CalcOffset(toWhere,center.EndPt());
				if (center.TFromP(toWhere) < 1)
					cr.c2.leftOff *= -1;
			}
			if (wl == wlRight) {
//				ShowPoint(cbp,toWhere,mcLtPurpleColor);
				cr.c2.rightOff =  CalcOffset(toWhere,center.EndPt());
				if (center.TFromP(toWhere) < 1)
					cr.c2.rightOff *= -1;
			}
			if (cr.found2) 
				GS_DeleteBreak(cbp,wh,cr.index2);
			GS_AddBreak(cbp,wh,INT32_MAX,kCapBreak,&(cr.c2));
		}
	}			
	
	this->Setup(cbp,wh);
}

void GS_API Wall::Show()
{
#if 0
	ShowPoint(cbp,center.StartPt(),mcRedColor);
	ShowPoint(cbp,left.StartPt(),mcLtBlueColor);
	ShowPoint(cbp,right.StartPt(),mcDkBlueColor);
	ShowPoint(cbp,center.EndPt(),mcLtGreenColor);
	ShowPoint(cbp,left.EndPt(),mcDkGreenColor);
	ShowPoint(cbp,right.EndPt(),mcYellowColor);
#endif
}

