//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// Contains functions that are very similar to existing callbacks except take
// C-strings instead of Pascal strings.
//

#include "StdHeaders.h"


static bool IsJapaneseSystem()
{
	CPINFO      cpInfo;

	return GetCPInfo(CP_ACP, &cpInfo) && (cpInfo.MaxCharSize>1);
}


///////////////////////////////////////////////////////////////////////////////
void GS_CALLBACK GS_Mac2WinString(CallBackPtr /*cbp*/, const TXString& ps, TXString& sz, Sint32 max)
// 'max' should be the length of the input string
{
	sz = ps;
}

///////////////////////////////////////////////////////////////////////////////
void GS_CALLBACK GS_Win2MacString(CallBackPtr /*cbp*/, const TXString& sz, TXString& ps, Sint32 max)
// 'max' should be the length of the input string
{
	ps = sz;
}

///////////////////////////////////////////////////////////////////////////////
void GS_CALLBACK GS_AngleToCString(CallBackPtr cbp, double_param angle, TXString& sz, Sint32 max)
{
	TXString ps;
	GS_AngleToStringN(cbp, angle, ps);
	GS_Mac2WinString(cbp, ps, sz, max);
}

///////////////////////////////////////////////////////////////////////////////
void GS_CALLBACK GS_CoordToDimCString(CallBackPtr cbp, const WorldCoord &c, TXString& sz, Sint32 max)
{
	TXString ps;
	GS_CoordToDimString(cbp, c, ps);
	GS_Mac2WinString(cbp, ps, sz, max);
}

///////////////////////////////////////////////////////////////////////////////
Boolean GS_CALLBACK GS_CStringToAngle(CallBackPtr cbp, const TXString& sz, double &angle)
{
	TXString ps;
	GS_Win2MacString(cbp, sz, ps, 256);
	return GS_StringToAngleN(cbp, ps, angle);
}

///////////////////////////////////////////////////////////////////////////////
Boolean GS_CALLBACK GS_DimCStringToCoord(CallBackPtr cbp, const TXString& sz, WorldCoord& c)
{
	TXString ps;
	GS_Win2MacString(cbp, sz, ps, 256);
	return GS_DimStringToCoord(cbp, ps, c);
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
