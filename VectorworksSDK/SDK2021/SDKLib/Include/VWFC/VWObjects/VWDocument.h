//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef VECTORWORKS_DOCUMENT__H
#define VECTORWORKS_DOCUMENT__H

#pragma once

namespace VWFC
{
	namespace VWObjects
	{
		class VWDocument
		{
		public:
										VWDocument();
			virtual						~VWDocument();

		public:

			// Tools
		public:
			static void					DeselectAll();
			static MCObjectHandle		GetFirstSelectedObject();
			static MCObjectHandle		GetDrawingHeaderFristMember();
			// return true if the current document is in metric units
			// 'mm', 'm', 'cm', or 'dm'
			static bool					IsCurrentDocumentInMetricUnits();
		};
	}
}

/*
	Boolean ::GS_GetDefaultArrowByClass( gCBP);
	void ::GS_GetDefaultArrowHeads( gCBP, Boolean& starting, Boolean& ending, ArrowType& style, short& size);
	void ::GS_GetDefaultArrowHeadsN( gCBP, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
	InternalIndex ::GS_GetDefaultClass( gCBP);
	void ::GS_GetDefaultColors( gCBP, ObjectColorType& colors);
	Boolean ::GS_GetDefaultFColorsByClass( gCBP);
	InternalIndex ::GS_GetDefaultFillPat( gCBP);
	Boolean ::GS_GetDefaultFPatByClass( gCBP);
	MCObjectHandle ::GS_GetDefaultHatch( gCBP);
	short ::GS_GetDefaultLineWeight( gCBP);
	Boolean ::GS_GetDefaultLWByClass( gCBP);
	Boolean ::GS_GetDefaultPColorsByClass( gCBP);
	short ::GS_GetDefaultPenPat( gCBP);
	Boolean ::GS_GetDefaultPPatByClass( gCBP);
	InternalIndex ::GS_GetDocumentDefaultSketchStyle( gCBP);
	void ::GS_SetDefaultArrowByClass( gCBP);
	void ::GS_SetDefaultArrowHeads( gCBP, Boolean starting, Boolean ending, ArrowType style, short size);
	void ::GS_SetDefaultArrowHeadsN( gCBP, Boolean starting, Boolean ending, ArrowType style, double_param size);
	void ::GS_SetDefaultClass( gCBP, InternalIndex classID);
	void ::GS_SetDefaultColors( gCBP, ObjectColorType colors);
	void ::GS_SetDefaultFColorsByClass( gCBP);
	void ::GS_SetDefaultFillPat( gCBP, InternalIndex theFill);
	void ::GS_SetDefaultFPatByClass( gCBP);
	CBBoolean ::GS_SetDefaultHatch( gCBP, MCObjectHandle inHatchDef);
	void ::GS_SetDefaultLineWeight( gCBP, short mils);
	void ::GS_SetDefaultLWByClass( gCBP);
	void ::GS_SetDefaultPColorsByClass( gCBP);
	void ::GS_SetDefaultPenPat( gCBP, short penPat);
	void ::GS_SetDefaultPPatByClass( gCBP);
	void ::GS_SetDefaultWallThickness( gCBP, WorldCoord thickness);
	Boolean ::GS_SetDocumentDefaultSketchStyle( gCBP, InternalIndex sketchIndex);
	void ::GS_WrapGetDefaultWallThickness( gCBP, double_gs& outCoordLen);

	short ::GS_GetLineWeightDisplayMM( gCBP, short mils);
	Boolean ::GS_SetLineWeightDisplayMM( gCBP, short hundredths);
	short ::GS_GetLineWeightDisplayPt( gCBP, short mils);
	Boolean ::GS_SetLineWeightDisplayPt( gCBP, short sixteenths);

		extern "C" WorldCoord GS_CALLBACK GS_WorldCoordsPerDrawingUnit(CallBackPtr);

*/

#endif // VECTORWORKS_DOCUMENT__H