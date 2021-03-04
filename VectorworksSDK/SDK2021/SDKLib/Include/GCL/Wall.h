//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#ifndef _WALLWALL_
#define _WALLWALL_

#include "UXLine.h"


enum JoinWhere	{dontJoin=0,joinStart=1,joinEnd=2};
enum WallLine	{wlCenter=0,wlLeft=1,wlRight=2};

struct GetCapsRec
{
	public:
		CapBreakType c1,c2;
		short	index1,index2;
		Boolean found1, found2;
		
		GetCapsRec() {found1 = false; found2 = false;}
};

class Wall
{
	public:
		TXLine 			center,left,right;
		CallBackPtr		cbp;
		WorldCoord			offset;
		GetCapsRec		cr;
		Handle			wh;
		
		void GS_API Setup(CallBackPtr cbpParam, Handle theWal);
		void GS_API SetWallPt(WallLine wl, JoinWhere jw, WorldPt& toWhere);
		void GS_API Show();
		
		WorldCoord GS_API CalcOffset(const WorldPt& toPt, const WorldPt& centerPt);
};


#endif
