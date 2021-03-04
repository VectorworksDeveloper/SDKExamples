//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"

#ifndef WINVER
//	#include <MiniMObject.h>
#endif

#include <ADebug.h>



Boolean GS_API CommandKeyDown()
{
	return false;
}

void GS_API SetObjColor(CallBackPtr cbp, Handle obj, Uint8 penFore, Uint8 fillFore)
{
	ObjectColorType c;
	c.fillFore = fillFore;
	c.fillBack = mcWhiteColor;
	c.penFore = penFore;
	c.penBack = mcWhiteColor;
	GS_SetColor(cbp,obj,c);
	GS_ResetObject(cbp,obj);
}

void GS_API ShowPoint(CallBackPtr cbp, const WorldPt& p, Uint8 penFore, Uint8 fillFore)
{
	WorldCoord rd;
	GS_PixelLengthToCoordLength(cbp,5,rd);
//	PrintCoord(rd);
//	WorldRect r(ConvertToCoord(p.x-rd),ConvertToCoord(p.y+rd),ConvertToCoord(p.x+rd),ConvertToCoord(p.y-rd));
	WorldRect r((p.x-rd),(p.y+rd),(p.x+rd),(p.y-rd));
	Handle oval = GS_CreateOval(cbp,r);
	if (oval) {
		SetObjColor(cbp,oval,penFore,fillFore);
		GS_SetFillPat(cbp,oval,0);
	}
}



char GS_API * Bool2Str(const Boolean b)
{
	static char t[] = "TRUE";
	static char f[] = "FALSE";
	if (b)
		return t;
	return f;
}




//////////
//
//	TObjectViewer
//
//////////

//
//	wallNode
//	

#if 0
extern "C" Boolean GS_API _PrintBreaks(Handle wall, Sint32 index, WorldCoord off, Sint32 breakType, void* breakData, CallBackPtr cbp, void* dataParam)
{
	A4Recaller a4r(cbp);
	
	Debug("break(%d) offset = %ld\n",index,off);
	switch (breakType) {
		case kCapBreak:
			Debug("Cap: lOff = %ld   rOff = %ld\n",((CapBreakType*)breakData)->leftOff,((CapBreakType*)breakData)->rightOff);
			break;
		case kPeakBreak:
			Debug("Peak:  peakHeight = %ld   topPeak = %s\n",((PeakBreakType*)breakData)->peakHeight, Bool2Str(((PeakBreakType*)breakData)->topPeak));
			break;
		case kHalfBreak:
			Debug("Half:  rightSide = %s   gapWidth = %ld\n",Bool2Str(((HalfBreakType*)breakData)->rightSide),((HalfBreakType*)breakData)->gapWidth);
			break;
		case kSymbolBreak:
			Str255 s;
			s[0] = 0;
			Handle theDef = GetDefinition(cbp,((SymbolBreakType*)breakData)->theSymbol);
			if (theDef)
				GetObjectName(cbp,theDef,s);
			s[s[0]+1] = 0;
			Debug("Sym: name = %s  rightSide = %s   flip = %s   height = %ld\n",&(s[1]),Bool2Str(((SymbolBreakType*)breakData)->rightSide),
				Bool2Str(((SymbolBreakType*)breakData)->flipH),((SymbolBreakType*)breakData)->height);
			break;
	}
	return false;
}

void GS_API TObjectViewer::PrintWall()
{
	WorldPt startPt,endPt;
	GetEndPoints(cbp,obj,startPt,endPt);
	PrintCPoint(startPt);
	PrintCPoint(endPt);
	Debug("width = %ld   s height = %ld   e Height = %ld\n",(**(WallHandle) obj).off,
		(**(WallHandle) obj).startHeightTop, (**(WallHandle) obj).endHeightTop);
	ForEachBreak(cbp,obj, _PrintBreaks, NULL);
}




//
//	Dispatcher
//

void GS_API TObjectViewer::PrintObj(CallBackPtr cbpParam, Handle objParam) 
{
	if (!(cbpParam && objParam)) {
		Debug("Invalid parameters sent to PrintObj\n");
		return;
	}
	
	cbp = cbpParam;
	obj = objParam;
	
	short t = GetObjectType(cbp,obj);
	 
	Debug("*** ");
	switch (t) {
		case termNode:		Debug("termNode:\n"); 		break;
		case lineNode:		Debug("lineNode:\n"); 		break;
		case boxNode:		Debug("boxNode:\n"); 		break;
		case ovalNode:		Debug("ovalNode:\n"); 		break;
		case polyNode:		Debug("polyNode:\n"); 		break;
		case arcNode:		Debug("arcNode:\n"); 		break;
		case curveNode:		Debug("curveNode:\n"); 		break;
		case textNode:		Debug("textNode:\n"); 		break;
		case groupNode:		Debug("groupNode:\n"); 		break;
		case qArcNode:		Debug("qArcNode:\n"); 		break;
		case rBoxNode:		Debug("rBoxNode:\n"); 		break;
		case paintNode:		Debug("paintNode:\n"); 		break;
		case symNode:		Debug("symNode:\n"); 		break;
		case symDefNode:	Debug("symDefNode:\n"); 	break;
		case locNode:		Debug("locNode:\n"); 		break;
		case polylineNode:	Debug("polylineNode:\n"); 	break;
		case picTDNode:		Debug("picTDNode:\n"); 		break;
		case xtrdNode:		Debug("xtrdNode:\n"); 		break;
		case qPolyNode:		Debug("qPolyNode:\n"); 		break;
		case layerRefNode:	Debug("layerRefNode:\n"); 	break;
		case sweepNode:		Debug("sweepNode:\n"); 		break;
		case mxtrdNode:		Debug("mxtrdNode:\n");	 	break;
		case meshNode:		Debug("meshNode:\n"); 		break;
		case worksheetDummyNode: Debug("worksheetNode:\n");	break;
		case wallNode:		Debug("wallNode:\n");		PrintWall(); 	break;
		case slabNode:		Debug("slabNode:\n");		break;
		default:			Debug("tdType : %d\n",t); 	break;
	}
	Debug("\n");
}
#endif
