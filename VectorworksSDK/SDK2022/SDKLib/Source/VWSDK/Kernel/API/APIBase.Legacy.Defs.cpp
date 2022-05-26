//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-COMMENT LINE.  [DMB, 10/30/95]


extern "C" {
// GS_SDKPPC_JAK2
#ifdef _MINICAD_
	// If _MINICAD_ we are building the main application...
	#define CALLBACKPTR CallBackPtr
//	#ifdef powerc
//	#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) FIDToPtr(kcb##fn); \
//							if (f) f = (UniversalProcPtr) f->routineRecords[0].procDescriptor
//	#else
	// The macro GET_CB_UPP is used by the AppleScript which generates "MiniCadCallBacks.Defs.cpp".
	#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) FIDToPtr(kcb##fn)
//	#endif
	#define CALL_PROC(fn)	((fn##Ptr) f)
#else
	// else we are building Plug-ins...
//	#define XCALL(fn)	GenericFunctionPtr f = (*cbp->rPtr)(kcb##fn); if (f) ((fn##Ptr) f)
//	#define XFN(fn)		GenericFunctionPtr f = (*cbp->rPtr)(kcb##fn); return f ? ((fn##Ptr) f)
	
	#define CALLBACKPTR CallBackPtr cbp

//	#ifdef powerc		
//		#define GET_CB_UPP(fn) UniversalProcPtr f = (UniversalProcPtr) CallRetrieverProc(cbp->rPtr, kcb##fn); \
//							if (f) f = (UniversalProcPtr) f->routineRecords[0].procDescriptor
//	#else
		#define GET_CB_UPP(fn) GenericFunctionPtr f = cbp ? (*cbp->rPtr)(kcb##fn) : nil;
//	#endif
	#define CALL_PROC(fn)	((fn##Ptr) f)
#endif

// include the automatically generated portion of this file
#if !GS_INLINE_SDK_CALLS


///////////////////////////////////////////
//  Attributes (Class)
///////////////////////////////////////////


CBBoolean GS_CALLBACK GS_GetClassBeginningMarker(CALLBACKPTR, InternalIndex index, SMarkerStyle& mstyle)
{
	GET_CB_UPP(GetClassBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetClassBeginningMarkerPtr)(InternalIndex index, SMarkerStyle& mstyle);
		CBBoolean gsResult = CALL_PROC(GetClassBeginningMarker)(index, mstyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetClassEndMarker(CALLBACKPTR, InternalIndex index, SMarkerStyle& mstyle)
{
	GET_CB_UPP(GetClassEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetClassEndMarkerPtr)(InternalIndex index, SMarkerStyle& mstyle);
		CBBoolean gsResult = CALL_PROC(GetClassEndMarker)(index, mstyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetClColor(CALLBACKPTR, InternalIndex index, ObjectColorType& color)
{
	GET_CB_UPP(GetClColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClColorPtr)(InternalIndex index, ObjectColorType& color);
		CALL_PROC(GetClColor)(index, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


InternalIndex GS_CALLBACK GS_GetClFillPat(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetClFillPatPtr)(InternalIndex index);
		InternalIndex gsResult = CALL_PROC(GetClFillPat)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetClLineWeight(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetClLineWeightPtr)(InternalIndex index);
		short gsResult = CALL_PROC(GetClLineWeight)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetClMarker(CALLBACKPTR, InternalIndex index, MarkerType& style, short& size, short& angle)
{
	GET_CB_UPP(GetClMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClMarkerPtr)(InternalIndex index, MarkerType& style, short& size, short& angle);
		CALL_PROC(GetClMarker)(index, style, size, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



Boolean GS_CALLBACK GS_GetClUseGraphic(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClUseGraphic);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetClUseGraphicPtr)(InternalIndex index);
		Boolean gsResult = CALL_PROC(GetClUseGraphic)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_GetClVisibility(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetClVisibilityPtr)(InternalIndex index);
		short gsResult = CALL_PROC(GetClVisibility)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 999;
}


InternalIndex GS_CALLBACK GS_GetVPClassFillStyle(CALLBACKPTR, MCObjectHandle viewport, InternalIndex classIndex)
{
	GET_CB_UPP(GetVPClassFillStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetVPClassFillStylePtr)(MCObjectHandle viewport, InternalIndex classIndex);
		InternalIndex gsResult = CALL_PROC(GetVPClassFillStyle)(viewport, classIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetClassBeginningMarker(CALLBACKPTR, InternalIndex index, SMarkerStyle mstyle)
{
	GET_CB_UPP(SetClassBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetClassBeginningMarkerPtr)(InternalIndex index, SMarkerStyle mstyle);
		CBBoolean gsResult = CALL_PROC(SetClassBeginningMarker)(index, mstyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetClassEndMarker(CALLBACKPTR, InternalIndex index, SMarkerStyle mstyle)
{
	GET_CB_UPP(SetClassEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetClassEndMarkerPtr)(InternalIndex index, SMarkerStyle mstyle);
		CBBoolean gsResult = CALL_PROC(SetClassEndMarker)(index, mstyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetClColor(CALLBACKPTR, InternalIndex index, ObjectColorType color)
{
	GET_CB_UPP(SetClColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClColorPtr)(InternalIndex index, ObjectColorType color);
		CALL_PROC(SetClColor)(index, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClFillPat(CALLBACKPTR, InternalIndex index, InternalIndex fill)
{
	GET_CB_UPP(SetClFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClFillPatPtr)(InternalIndex index, InternalIndex fill);
		CALL_PROC(SetClFillPat)(index, fill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClLineWeight(CALLBACKPTR, InternalIndex index, short mils)
{
	GET_CB_UPP(SetClLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClLineWeightPtr)(InternalIndex index, CBSignedShort mils);
		CALL_PROC(SetClLineWeight)(index, mils);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClMarker(CALLBACKPTR, InternalIndex index, MarkerType style, short size, short angle)
{
	GET_CB_UPP(SetClMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClMarkerPtr)(InternalIndex index, MarkerType style, CBSignedShort size, CBSignedShort angle);
		CALL_PROC(SetClMarker)(index, style, size, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




void GS_CALLBACK GS_SetClUseGraphic(CALLBACKPTR, InternalIndex index, Boolean use)
{
	GET_CB_UPP(SetClUseGraphic);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClUseGraphicPtr)(InternalIndex index, CBBoolean use);
		CALL_PROC(SetClUseGraphic)(index, use);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClVisibility(CALLBACKPTR, InternalIndex index, short vis)
{
	GET_CB_UPP(SetClVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClVisibilityPtr)(InternalIndex index, CBSignedShort vis);
		CALL_PROC(SetClVisibility)(index, vis);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_VPClassHasOverride(CALLBACKPTR, MCObjectHandle viewport, InternalIndex classIndex)
{
	GET_CB_UPP(VPClassHasOverride);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*VPClassHasOverridePtr)(MCObjectHandle viewport, InternalIndex classIndex);
		Boolean gsResult = CALL_PROC(VPClassHasOverride)(viewport, classIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Attributes (Default)
///////////////////////////////////////////


CBBoolean GS_CALLBACK GS_DeleteAllDLComponents(CALLBACKPTR)
{
	GET_CB_UPP(DeleteAllDLComponents);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteAllDLComponentsPtr)();
		CBBoolean gsResult = CALL_PROC(DeleteAllDLComponents)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_DeleteDLComponent(CALLBACKPTR, CBSignedShort index)
{
	GET_CB_UPP(DeleteDLComponent);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteDLComponentPtr)(CBSignedShort index);
		CBBoolean gsResult = CALL_PROC(DeleteDLComponent)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetDefaultArrowByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultArrowByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultArrowByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultArrowByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetDefaultArrowHeads(CALLBACKPTR, Boolean& starting, Boolean& ending, ArrowType& style, short& size)
{
	GET_CB_UPP(GetDefaultArrowHeads);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetDefaultArrowHeadsPtr)(Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		CALL_PROC(GetDefaultArrowHeads)(starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetDefaultArrowHeadsN(CALLBACKPTR, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size)
{
	GET_CB_UPP(GetDefaultArrowHeadsN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetDefaultArrowHeadsNPtr)(Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		CALL_PROC(GetDefaultArrowHeadsN)(starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetDefaultBeginningMarker(CALLBACKPTR, SMarkerStyle& mstyle, CBBoolean& visibility)
{
	GET_CB_UPP(GetDefaultBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultBeginningMarkerPtr)(SMarkerStyle& mstyle, CBBoolean& visibility);
		CBBoolean gsResult = CALL_PROC(GetDefaultBeginningMarker)(mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetDefaultClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetDefaultClassPtr)();
		InternalIndex gsResult = CALL_PROC(GetDefaultClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetDefaultColors(CALLBACKPTR, ObjectColorType& colors)
{
	GET_CB_UPP(GetDefaultColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetDefaultColorsPtr)(ObjectColorType& colors);
		CALL_PROC(GetDefaultColors)(colors);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetDefaultEndMarker(CALLBACKPTR, SMarkerStyle& mstyle, CBBoolean& visibility)
{
	GET_CB_UPP(GetDefaultEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultEndMarkerPtr)(SMarkerStyle& mstyle, CBBoolean& visibility);
		CBBoolean gsResult = CALL_PROC(GetDefaultEndMarker)(mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetDefaultFColorsByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultFColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultFColorsByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultFColorsByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetDefaultFillPat(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetDefaultFillPatPtr)();
		InternalIndex gsResult = CALL_PROC(GetDefaultFillPat)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetDefaultFPatByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultFPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultFPatByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultFPatByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_GetDefaultHatch(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultHatch);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetDefaultHatchPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetDefaultHatch)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_GetDefaultLineWeight(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetDefaultLineWeightPtr)();
		short gsResult = CALL_PROC(GetDefaultLineWeight)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetDefaultLWByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultLWByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultLWByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultLWByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetDefaultPColorsByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultPColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultPColorsByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultPColorsByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_GetDefaultPPatByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultPPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultPPatByClassPtr)();
		Boolean gsResult = CALL_PROC(GetDefaultPPatByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentClass(CALLBACKPTR, CBSignedShort index, Sint32 &componentClass)
{
	GET_CB_UPP(GetDLComponentClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentClassPtr)(CBSignedShort index, Sint32 &componentClass);
		CBBoolean gsResult = CALL_PROC(GetDLComponentClass)(index, componentClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentFill(CALLBACKPTR, CBSignedShort index, Sint32 &fill)
{
	GET_CB_UPP(GetDLComponentFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentFillPtr)(CBSignedShort index, Sint32 &fill);
		CBBoolean gsResult = CALL_PROC(GetDLComponentFill)(index, fill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentFillColors(CALLBACKPTR, CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor)
{
	GET_CB_UPP(GetDLComponentFillColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentFillColorsPtr)(CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor);
		CBBoolean gsResult = CALL_PROC(GetDLComponentFillColors)(index, fillForeColor, fillBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentName(CALLBACKPTR, CBSignedShort index, InternalName &componentName)
{
	GET_CB_UPP(GetDLComponentName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentNamePtr)(CBSignedShort index, InternalName &componentName);
		CBBoolean gsResult = CALL_PROC(GetDLComponentName)(index, componentName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentPenColors(CALLBACKPTR, CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor)
{
	GET_CB_UPP(GetDLComponentPenColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentPenColorsPtr)(CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		CBBoolean gsResult = CALL_PROC(GetDLComponentPenColors)(index, leftPenForeColor, leftPenBackColor, rightPenForeColor, rightPenBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



CBBoolean GS_CALLBACK GS_GetDLComponentPenWeights(CALLBACKPTR, CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight)
{
	GET_CB_UPP(GetDLComponentPenWeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentPenWeightsPtr)(CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight);
		CBBoolean gsResult = CALL_PROC(GetDLComponentPenWeights)(index, penWeightLeft, penWeightRight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentUseFillClassAttr(CALLBACKPTR, CBSignedShort index, CBBoolean &useClassAttr)
{
	GET_CB_UPP(GetDLComponentUseFillClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentUseFillClassAttrPtr)(CBSignedShort index, CBBoolean &useClassAttr);
		CBBoolean gsResult = CALL_PROC(GetDLComponentUseFillClassAttr)(index, useClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentUsePenClassAttr(CALLBACKPTR, CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr)
{
	GET_CB_UPP(GetDLComponentUsePenClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentUsePenClassAttrPtr)(CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr);
		CBBoolean gsResult = CALL_PROC(GetDLComponentUsePenClassAttr)(index, leftPenUseClassAttr, rightPenUseClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetDLComponentWidth(CALLBACKPTR, CBSignedShort index, WorldCoord &width)
{
	GET_CB_UPP(GetDLComponentWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDLComponentWidthPtr)(CBSignedShort index, WorldCoord &width);
		CBBoolean gsResult = CALL_PROC(GetDLComponentWidth)(index, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


WorldCoord GS_CALLBACK GS_GetDLControlOffset(CALLBACKPTR)
{
	GET_CB_UPP(GetDLControlOffset);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef WorldCoord (*GetDLControlOffsetPtr)();
		WorldCoord gsResult = CALL_PROC(GetDLControlOffset)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBSignedShort GS_CALLBACK GS_GetDLOptions(CALLBACKPTR)
{
	GET_CB_UPP(GetDLOptions);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetDLOptionsPtr)();
		CBSignedShort gsResult = CALL_PROC(GetDLOptions)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


WorldCoord GS_CALLBACK GS_GetDLSeparation(CALLBACKPTR)
{
	GET_CB_UPP(GetDLSeparation);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef WorldCoord (*GetDLSeparationPtr)();
		WorldCoord gsResult = CALL_PROC(GetDLSeparation)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


InternalIndex GS_CALLBACK GS_GetDocumentDefaultSketchStyle(CALLBACKPTR)
{
	GET_CB_UPP(GetDocumentDefaultSketchStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetDocumentDefaultSketchStylePtr)();
		InternalIndex gsResult = CALL_PROC(GetDocumentDefaultSketchStyle)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_GetNumberOfDLComponents(CALLBACKPTR, short& numComponents)
{
	GET_CB_UPP(GetNumberOfDLComponents);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetNumberOfDLComponentsPtr)(short& numComponents);
		CBBoolean gsResult = CALL_PROC(GetNumberOfDLComponents)(numComponents);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetObjectInternalIndex(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetObjectInternalIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetObjectInternalIndexPtr)(MCObjectHandle h);
		InternalIndex gsResult = CALL_PROC(GetObjectInternalIndex)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetProgramVariable(CALLBACKPTR, short variableSelector, void* result)
{
	GET_CB_UPP(GetProgramVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetProgramVariablePtr)(CBSignedShort variableSelector, void* result, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(GetProgramVariable)(variableSelector, result, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetWallPrefStyle(CALLBACKPTR, InternalIndex& wallStyleNum)
{
	GET_CB_UPP(GetWallPrefStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetWallPrefStylePtr)(InternalIndex& wallStyleNum);
		Boolean gsResult = CALL_PROC(GetWallPrefStyle)(wallStyleNum);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetWallStyle(CALLBACKPTR, MCObjectHandle theWall, InternalIndex& wallStyle)
{
	GET_CB_UPP(GetWallStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetWallStylePtr)(MCObjectHandle theWall, InternalIndex& wallStyle);
		Boolean gsResult = CALL_PROC(GetWallStyle)(theWall, wallStyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



void GS_CALLBACK GS_SetDefaultArrowByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultArrowByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultArrowByClassPtr)();
		CALL_PROC(SetDefaultArrowByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultArrowHeads(CALLBACKPTR, Boolean starting, Boolean ending, ArrowType style, short size)
{
	GET_CB_UPP(SetDefaultArrowHeads);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultArrowHeadsPtr)(CBBoolean starting, CBBoolean ending, ArrowType style, CBSignedShort size);
		CALL_PROC(SetDefaultArrowHeads)(starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultArrowHeadsN(CALLBACKPTR, Boolean starting, Boolean ending, ArrowType style, double_param size)
{
	GET_CB_UPP(SetDefaultArrowHeadsN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultArrowHeadsNPtr)(CBBoolean starting, CBBoolean ending, ArrowType style, CBDouble_param size);
		CALL_PROC(SetDefaultArrowHeadsN)(starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetDefaultBeginningMarker(CALLBACKPTR, SMarkerStyle mstyle, CBBoolean visibility)
{
	GET_CB_UPP(SetDefaultBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDefaultBeginningMarkerPtr)(SMarkerStyle mstyle, CBBoolean visibility);
		CBBoolean gsResult = CALL_PROC(SetDefaultBeginningMarker)(mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDefaultClass(CALLBACKPTR, InternalIndex classID)
{
	GET_CB_UPP(SetDefaultClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultClassPtr)(InternalIndex classID);
		CALL_PROC(SetDefaultClass)(classID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultColors(CALLBACKPTR, ObjectColorType colors)
{
	GET_CB_UPP(SetDefaultColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultColorsPtr)(ObjectColorType colors);
		CALL_PROC(SetDefaultColors)(colors);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetDefaultEndMarker(CALLBACKPTR, SMarkerStyle mstyle, CBBoolean visibility)
{
	GET_CB_UPP(SetDefaultEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDefaultEndMarkerPtr)(SMarkerStyle mstyle, CBBoolean visibility);
		CBBoolean gsResult = CALL_PROC(SetDefaultEndMarker)(mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDefaultFColorsByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultFColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultFColorsByClassPtr)();
		CALL_PROC(SetDefaultFColorsByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultFillPat(CALLBACKPTR, InternalIndex theFill)
{
	GET_CB_UPP(SetDefaultFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultFillPatPtr)(InternalIndex theFill);
		CALL_PROC(SetDefaultFillPat)(theFill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultFPatByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultFPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultFPatByClassPtr)();
		CALL_PROC(SetDefaultFPatByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetDefaultHatch(CALLBACKPTR, MCObjectHandle inHatchDef)
{
	GET_CB_UPP(SetDefaultHatch);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDefaultHatchPtr)(MCObjectHandle inHatchDef);
		CBBoolean gsResult = CALL_PROC(SetDefaultHatch)(inHatchDef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDefaultLineWeight(CALLBACKPTR, short mils)
{
	GET_CB_UPP(SetDefaultLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultLineWeightPtr)(CBSignedShort mils);
		CALL_PROC(SetDefaultLineWeight)(mils);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultLWByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultLWByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultLWByClassPtr)();
		CALL_PROC(SetDefaultLWByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultPColorsByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultPColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultPColorsByClassPtr)();
		CALL_PROC(SetDefaultPColorsByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



void GS_CALLBACK GS_SetDefaultPPatByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultPPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultPPatByClassPtr)();
		CALL_PROC(SetDefaultPPatByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultWallThickness(CALLBACKPTR, WorldCoord thickness)
{
	GET_CB_UPP(SetDefaultWallThickness);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultWallThicknessPtr)(CBWorldCoord_param thickness);
		CALL_PROC(SetDefaultWallThickness)(thickness);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetDLComponentClass(CALLBACKPTR, CBSignedShort index, Sint32 componentClass)
{
	GET_CB_UPP(SetDLComponentClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentClassPtr)(CBSignedShort index, Sint32 componentClass);
		CBBoolean gsResult = CALL_PROC(SetDLComponentClass)(index, componentClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentFill(CALLBACKPTR, CBSignedShort index, Sint32 fill)
{
	GET_CB_UPP(SetDLComponentFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentFillPtr)(CBSignedShort index, Sint32 fill);
		CBBoolean gsResult = CALL_PROC(SetDLComponentFill)(index, fill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentFillColors(CALLBACKPTR, CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor)
{
	GET_CB_UPP(SetDLComponentFillColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentFillColorsPtr)(CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor);
		CBBoolean gsResult = CALL_PROC(SetDLComponentFillColors)(index, fillForeColor, fillBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentName(CALLBACKPTR, CBSignedShort index, const InternalName& componentName)
{
	GET_CB_UPP(SetDLComponentName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentNamePtr)(CBSignedShort index, const InternalName& componentName);
		CBBoolean gsResult = CALL_PROC(SetDLComponentName)(index, componentName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentPenColors(CALLBACKPTR, CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor)
{
	GET_CB_UPP(SetDLComponentPenColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentPenColorsPtr)(CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		CBBoolean gsResult = CALL_PROC(SetDLComponentPenColors)(index, leftPenForeColor, leftPenBackColor, rightPenForeColor, rightPenBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



CBBoolean GS_CALLBACK GS_SetDLComponentPenWeights(CALLBACKPTR, CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight)
{
	GET_CB_UPP(SetDLComponentPenWeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentPenWeightsPtr)(CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight);
		CBBoolean gsResult = CALL_PROC(SetDLComponentPenWeights)(index, penWeightLeft, penWeightRight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentUseFillClassAttr(CALLBACKPTR, CBSignedShort index, CBBoolean useClassAttr)
{
	GET_CB_UPP(SetDLComponentUseFillClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentUseFillClassAttrPtr)(CBSignedShort index, CBBoolean useClassAttr);
		CBBoolean gsResult = CALL_PROC(SetDLComponentUseFillClassAttr)(index, useClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentUsePenClassAttr(CALLBACKPTR, CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr)
{
	GET_CB_UPP(SetDLComponentUsePenClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentUsePenClassAttrPtr)(CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr);
		CBBoolean gsResult = CALL_PROC(SetDLComponentUsePenClassAttr)(index, leftPenUseClassAttr, rightPenUseClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetDLComponentWidth(CALLBACKPTR, CBSignedShort index, WorldCoord width)
{
	GET_CB_UPP(SetDLComponentWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDLComponentWidthPtr)(CBSignedShort index, CBWorldCoord_param width);
		CBBoolean gsResult = CALL_PROC(SetDLComponentWidth)(index, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDLControlOffset(CALLBACKPTR, WorldCoord controlOffset)
{
	GET_CB_UPP(SetDLControlOffset);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDLControlOffsetPtr)(CBWorldCoord_param controlOffset);
		CALL_PROC(SetDLControlOffset)(controlOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDLOptions(CALLBACKPTR, CBSignedShort options)
{
	GET_CB_UPP(SetDLOptions);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDLOptionsPtr)(CBSignedShort options);
		CALL_PROC(SetDLOptions)(options);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDLSeparation(CALLBACKPTR, WorldCoord separation)
{
	GET_CB_UPP(SetDLSeparation);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDLSeparationPtr)(CBWorldCoord_param separation);
		CALL_PROC(SetDLSeparation)(separation);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetDocumentDefaultSketchStyle(CALLBACKPTR, InternalIndex sketchIndex)
{
	GET_CB_UPP(SetDocumentDefaultSketchStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDocumentDefaultSketchStylePtr)(InternalIndex sketchIndex);
		Boolean gsResult = CALL_PROC(SetDocumentDefaultSketchStyle)(sketchIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetProgramVariable(CALLBACKPTR, short variableSelector, const void* value)
{
	GET_CB_UPP(SetProgramVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetProgramVariablePtr)(CBSignedShort variableSelector, const void* value, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(SetProgramVariable)(variableSelector, value, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallPrefStyle(CALLBACKPTR, InternalIndex wallStyleNum)
{
	GET_CB_UPP(SetWallPrefStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallPrefStylePtr)(InternalIndex wallStyleNum);
		CBBoolean gsResult = CALL_PROC(SetWallPrefStyle)(wallStyleNum);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_WrapGetDefaultWallThickness(CALLBACKPTR, double_gs& outCoordLen)
{
	GET_CB_UPP(WrapGetDefaultWallThickness);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*WrapGetDefaultWallThicknessPtr)(double_gs& outCoordLen);
		CALL_PROC(WrapGetDefaultWallThickness)(outCoordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Attributes (Geometric)
///////////////////////////////////////////


void GS_CALLBACK GS_Add3DVertex(CALLBACKPTR, MCObjectHandle h, const WorldPt3& v, Boolean recalcBounds)
{
	GET_CB_UPP(Add3DVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Add3DVertexPtr)(MCObjectHandle h, const WorldPt3& v, CBBoolean recalcBounds, bool bUseLegacyZ);
		CALL_PROC(Add3DVertex)(h, v, recalcBounds, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_AddVertex(CALLBACKPTR, MCObjectHandle h, const WorldPt& p, VertexType t, WorldCoord arcRadius, Boolean recalcBounds)
{
	GET_CB_UPP(AddVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddVertexPtr)(MCObjectHandle h, const WorldPt& p, VertexType t, CBWorldCoord_param arcRadius, CBBoolean recalcBounds);
		CALL_PROC(AddVertex)(h, p, t, arcRadius, recalcBounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CalcAreaN(CALLBACKPTR, MCObjectHandle h, double_gs& area)
{
	GET_CB_UPP(CalcAreaN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CalcAreaNPtr)(MCObjectHandle h, double_gs& area);
		CALL_PROC(CalcAreaN)(h, area);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CalcPerimN(CALLBACKPTR, MCObjectHandle h, double_gs& perim)
{
	GET_CB_UPP(CalcPerimN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CalcPerimNPtr)(MCObjectHandle h, double_gs& perim);
		CALL_PROC(CalcPerimN)(h, perim);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


double_gs GS_CALLBACK GS_CalcSurfaceArea(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(CalcSurfaceArea);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*CalcSurfaceAreaPtr)(MCObjectHandle h);
		double_gs gsResult = CALL_PROC(CalcSurfaceArea)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


double_gs GS_CALLBACK GS_CalcVolume(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(CalcVolume);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*CalcVolumePtr)(MCObjectHandle h);
		double_gs gsResult = CALL_PROC(CalcVolume)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


Boolean GS_CALLBACK GS_Centroid3D(CALLBACKPTR, MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG)
{
	GET_CB_UPP(Centroid3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*Centroid3DPtr)(MCObjectHandle h, double_gs &xCG, double_gs &yCG, double_gs &zCG, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(Centroid3D)(h, xCG, yCG, zCG, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_CountVertices(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(CountVertices);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CountVerticesPtr)(MCObjectHandle h);
		short gsResult = CALL_PROC(CountVertices)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_CreateSkylight(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateSkylight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateSkylightPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateSkylight)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_DeleteVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum)
{
	GET_CB_UPP(DeleteVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum);
		CALL_PROC(DeleteVertex)(h, vertexNum);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ForEach3DPointInObject(CALLBACKPTR, MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env)
{
	GET_CB_UPP(ForEach3DPointInObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ForEach3DPointInObjectPtr)(MCObjectHandle h, GS_3DPointIteratorProcPtr proc, void* env);
		CALL_PROC(ForEach3DPointInObject)(h, proc, env);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ForEachPolyEdge(CallBackPtr cbp, MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv)
{
	GET_CB_UPP(ForEachPolyEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ForEachPolyEdgePtr)(MCObjectHandle inPolyH, GS_ForEachPolyEdgeProcPtr inProc, void* inEnv, CallBackPtr cbp);
		CALL_PROC(ForEachPolyEdge)(inPolyH, inProc, inEnv, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Get3DVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum, WorldPt3& vertex)
{
	GET_CB_UPP(Get3DVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Get3DVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum, WorldPt3& vertex, bool bUseLegacyZ);
		CALL_PROC(Get3DVertex)(h, vertexNum, vertex, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetArcInfoN(CALLBACKPTR, MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY)
{
	GET_CB_UPP(GetArcInfoN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetArcInfoNPtr)(MCObjectHandle h, double_gs& startAngle, double_gs& sweepAngle, WorldPt& center, WorldCoord& radiusX, WorldCoord& radiusY);
		CALL_PROC(GetArcInfoN)(h, startAngle, sweepAngle, center, radiusX, radiusY);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetBatAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint)
{
	GET_CB_UPP(GetBatAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetBatAttributesPtr)(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, WorldCoord& topWidth, WorldCoord& baseHeight, double_gs& topSlope, WorldCoord& controlPoint);
		Boolean gsResult = CALL_PROC(GetBatAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, topWidth, baseHeight, topSlope, controlPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetControlVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius)
{
	GET_CB_UPP(GetControlVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetControlVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		CALL_PROC(GetControlVertex)(h, vertexNum, vertex, vType, arcRadius);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetDormerAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset)
{
	GET_CB_UPP(GetDormerAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDormerAttributesPtr)(MCObjectHandle object, const short dormerID, short& edgeIndex, WorldCoord& cornerOffset, Boolean& isPerpOffset, WorldCoord& perpOrHeightOffset, InternalIndex& symName, Boolean& centerSymbol, WorldCoord& symOffset);
		Boolean gsResult = CALL_PROC(GetDormerAttributes)(object, dormerID, edgeIndex, cornerOffset, isPerpOffset, perpOrHeightOffset, symName, centerSymbol, symOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetEndPoints(CALLBACKPTR, MCObjectHandle h, WorldPt& startPt, WorldPt& endPt)
{
	GET_CB_UPP(GetEndPoints);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetEndPointsPtr)(MCObjectHandle h, WorldPt& startPt, WorldPt& endPt);
		CALL_PROC(GetEndPoints)(h, startPt, endPt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetEntityMatrix(CALLBACKPTR, MCObjectHandle h, TransformMatrix& theMat)
{
	GET_CB_UPP(GetEntityMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetEntityMatrixPtr)(MCObjectHandle h, TransformMatrix& theMat, bool bUseLegacyZ);
		CALL_PROC(GetEntityMatrix)(h, theMat, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetExtrudeValues(CALLBACKPTR, MCObjectHandle h, WorldCoord& bottom, WorldCoord& top)
{
	GET_CB_UPP(GetExtrudeValues);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetExtrudeValuesPtr)(MCObjectHandle h, WorldCoord& bottom, WorldCoord& top);
		CALL_PROC(GetExtrudeValues)(h, bottom, top);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetGableAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang)
{
	GET_CB_UPP(GetGableAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGableAttributesPtr)(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, WorldCoord& overhang);
		Boolean gsResult = CALL_PROC(GetGableAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, leftSlope, rightSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetHipAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang)
{
	GET_CB_UPP(GetHipAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetHipAttributesPtr)(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& frontSlope, WorldCoord& overhang);
		Boolean gsResult = CALL_PROC(GetHipAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, leftSlope, rightSlope, frontSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetLocus3DPosition(CALLBACKPTR, MCObjectHandle h, WorldPt3& locPos)
{
	GET_CB_UPP(GetLocus3DPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetLocus3DPositionPtr)(MCObjectHandle h, WorldPt3& locPos, bool bUseLegacyZ);
		CALL_PROC(GetLocus3DPosition)(h, locPos, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetLocusPosition(CALLBACKPTR, MCObjectHandle h, WorldPt& locPos)
{
	GET_CB_UPP(GetLocusPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetLocusPositionPtr)(MCObjectHandle h, WorldPt& locPos);
		CALL_PROC(GetLocusPosition)(h, locPos);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetMarkerPolys(CALLBACKPTR, MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly)
{
	GET_CB_UPP(GetMarkerPolys);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetMarkerPolysPtr)(MCObjectHandle object, MCObjectHandle& startMarkerPoly, MCObjectHandle& endMarkerPoly);
		CALL_PROC(GetMarkerPolys)(object, startMarkerPoly, endMarkerPoly);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetNumRoofElements(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(GetNumRoofElements);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumRoofElementsPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(GetNumRoofElements)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_GetObjectBoundingBoxVerts(CALLBACKPTR, MCObjectHandle h, WorldRectVerts &outBoxVerts)
{
	GET_CB_UPP(GetObjectBoundingBoxVerts);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjectBoundingBoxVertsPtr)(MCObjectHandle h, WorldRectVerts &outBoxVerts);
		Boolean gsResult = CALL_PROC(GetObjectBoundingBoxVerts)(h, outBoxVerts);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetObjectBounds(CALLBACKPTR, MCObjectHandle h, WorldRect& bounds)
{
	GET_CB_UPP(GetObjectBounds);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjectBoundsPtr)(MCObjectHandle h, WorldRect& bounds);
		Boolean gsResult = CALL_PROC(GetObjectBounds)(h, bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetObjectCube(CALLBACKPTR, MCObjectHandle h, WorldCube& boundsCube)
{
	GET_CB_UPP(GetObjectCube);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetObjectCubePtr)(MCObjectHandle h, WorldCube& boundsCube, bool bUseLegacyZ);
		CALL_PROC(GetObjectCube)(h, boundsCube, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetPolyDirection(CALLBACKPTR, MCObjectHandle polyToCheck)
{
	GET_CB_UPP(GetPolyDirection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetPolyDirectionPtr)(MCObjectHandle polyToCheck);
		short gsResult = CALL_PROC(GetPolyDirection)(polyToCheck);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetPolyShapeClose(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetPolyShapeClose);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPolyShapeClosePtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetPolyShapeClose)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_GetQArcQuadrant(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetQArcQuadrant);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetQArcQuadrantPtr)(MCObjectHandle h);
		short gsResult = CALL_PROC(GetQArcQuadrant)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_GetRoofAttributes(CALLBACKPTR, MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter)
{
	GET_CB_UPP(GetRoofAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetRoofAttributesPtr)(MCObjectHandle object, Boolean& genGableWall, WorldCoord& bearingInset, WorldCoord& roofThick, short& miterType, WorldCoord& vertMiter);
		Boolean gsResult = CALL_PROC(GetRoofAttributes)(object, genGableWall, bearingInset, roofThick, miterType, vertMiter);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetRoofElementType(CALLBACKPTR, MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType)
{
	GET_CB_UPP(GetRoofElementType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetRoofElementTypePtr)(MCObjectHandle object, const short dormerID, short& edgeIndex, Boolean& isDormer, short& dormerType);
		Boolean gsResult = CALL_PROC(GetRoofElementType)(object, dormerID, edgeIndex, isDormer, dormerType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetRRectDiameters(CALLBACKPTR, MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam)
{
	GET_CB_UPP(GetRRectDiameters);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetRRectDiametersPtr)(MCObjectHandle h, WorldCoord& xDiam, WorldCoord& yDiam);
		CALL_PROC(GetRRectDiameters)(h, xDiam, yDiam);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetShedAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang)
{
	GET_CB_UPP(GetShedAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetShedAttributesPtr)(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, double_gs& topSlope, WorldCoord& overhang);
		Boolean gsResult = CALL_PROC(GetShedAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, topSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetSkylight(CALLBACKPTR, MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName)
{
	GET_CB_UPP(GetSkylight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetSkylightPtr)(MCObjectHandle object, const short skylightID, short& edgeIndex, WorldCoord& cornerOffset, WorldCoord& perpOffset, InternalIndex& symName);
		Boolean gsResult = CALL_PROC(GetSkylight)(object, skylightID, edgeIndex, cornerOffset, perpOffset, symName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetSweepAnglesN(CALLBACKPTR, MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle)
{
	GET_CB_UPP(GetSweepAnglesN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSweepAnglesNPtr)(MCObjectHandle theSweep, double_gs& startAngle, double_gs& arcAngle, double_gs& incrAngle);
		CALL_PROC(GetSweepAnglesN)(theSweep, startAngle, arcAngle, incrAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetTrapeziumAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope)
{
	GET_CB_UPP(GetTrapeziumAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetTrapeziumAttributesPtr)(MCObjectHandle object, const short dormerID, Boolean& useHeight, WorldCoord& heightDepthValue, WorldCoord& bottomWidth, Boolean& useTopWidth, WorldCoord& topWidth, double_gs& leftSlope, double_gs& rightSlope, double_gs& topSlope);
		Boolean gsResult = CALL_PROC(GetTrapeziumAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, useTopWidth, topWidth, leftSlope, rightSlope, topSlope);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius)
{
	GET_CB_UPP(GetVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum, WorldPt& vertex, VertexType& vType, WorldCoord& arcRadius);
		CALL_PROC(GetVertex)(h, vertexNum, vertex, vType, arcRadius);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Insert3DVertex(CALLBACKPTR, MCObjectHandle h, const WorldPt3& p, short beforeVertex, Boolean recalcBounds)
{
	GET_CB_UPP(Insert3DVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Insert3DVertexPtr)(MCObjectHandle h, const WorldPt3& p, CBSignedShort beforeVertex, CBBoolean recalcBounds, bool bUseLegacyZ);
		CALL_PROC(Insert3DVertex)(h, p, beforeVertex, recalcBounds, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_InsertVertex(CALLBACKPTR, MCObjectHandle h, const WorldPt& p, short beforeVertex, VertexType t, WorldCoord arcRadius, Boolean recalcBounds)
{
	GET_CB_UPP(InsertVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InsertVertexPtr)(MCObjectHandle h, const WorldPt& p, CBSignedShort beforeVertex, VertexType t, CBWorldCoord_param arcRadius, CBBoolean recalcBounds);
		CALL_PROC(InsertVertex)(h, p, beforeVertex, t, arcRadius, recalcBounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_Moments3D(CALLBACKPTR, MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz)
{
	GET_CB_UPP(Moments3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*Moments3DPtr)(MCObjectHandle h, double_gs &Ixx, double_gs &Iyy, double_gs &Izz);
		Boolean gsResult = CALL_PROC(Moments3D)(h, Ixx, Iyy, Izz);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsCurveEvaluatePoint(CALLBACKPTR, MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt)
{
	GET_CB_UPP(NurbsCurveEvaluatePoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsCurveEvaluatePointPtr)(MCObjectHandle nurbsHandle, Sint32 index, double u, WorldPt3& pt, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(NurbsCurveEvaluatePoint)(nurbsHandle, index, u, pt, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_NurbsCurveGetNumPieces(CALLBACKPTR, MCObjectHandle nHandle)
{
	GET_CB_UPP(NurbsCurveGetNumPieces);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*NurbsCurveGetNumPiecesPtr)(MCObjectHandle nHandle);
		Sint32 gsResult = CALL_PROC(NurbsCurveGetNumPieces)(nHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_NurbsCurveType(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index, bool& isByWeight)
{
	GET_CB_UPP(NurbsCurveType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsCurveTypePtr)(MCObjectHandle nHandle, Sint32 index, bool& isByWeight);
		Boolean gsResult = CALL_PROC(NurbsCurveType)(nHandle, index, isByWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_NurbsDegree(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index)
{
	GET_CB_UPP(NurbsDegree);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*NurbsDegreePtr)(MCObjectHandle nHandle, Sint32 index);
		short gsResult = CALL_PROC(NurbsDegree)(nHandle, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_NurbsDelVertex(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2)
{
	GET_CB_UPP(NurbsDelVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsDelVertexPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2);
		Boolean gsResult = CALL_PROC(NurbsDelVertex)(nHandle, index1, index2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_NurbsGetNumPts(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index)
{
	GET_CB_UPP(NurbsGetNumPts);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*NurbsGetNumPtsPtr)(MCObjectHandle nHandle, Sint32 index);
		Sint32 gsResult = CALL_PROC(NurbsGetNumPts)(nHandle, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_NurbsGetPt3D(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt)
{
	GET_CB_UPP(NurbsGetPt3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsGetPt3DPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3& pt, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(NurbsGetPt3D)(nHandle, index1, index2, pt, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsGetWeight(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight)
{
	GET_CB_UPP(NurbsGetWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsGetWeightPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& weight);
		Boolean gsResult = CALL_PROC(NurbsGetWeight)(nHandle, index1, index2, weight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsKnot(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot)
{
	GET_CB_UPP(NurbsKnot);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsKnotPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double& knot);
		Boolean gsResult = CALL_PROC(NurbsKnot)(nHandle, index1, index2, knot);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_NurbsNumKnots(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index)
{
	GET_CB_UPP(NurbsNumKnots);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*NurbsNumKnotsPtr)(MCObjectHandle nHandle, Sint32 index);
		Sint32 gsResult = CALL_PROC(NurbsNumKnots)(nHandle, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_NurbsSetKnot(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot)
{
	GET_CB_UPP(NurbsSetKnot);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsSetKnotPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double knot);
		Boolean gsResult = CALL_PROC(NurbsSetKnot)(nHandle, index1, index2, knot);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsSetPt3D(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt)
{
	GET_CB_UPP(NurbsSetPt3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsSetPt3DPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, WorldPt3 pt, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(NurbsSetPt3D)(nHandle, index1, index2, pt, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsSetWeight(CALLBACKPTR, MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight)
{
	GET_CB_UPP(NurbsSetWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsSetWeightPtr)(MCObjectHandle nHandle, Sint32 index1, Sint32 index2, double weight);
		Boolean gsResult = CALL_PROC(NurbsSetWeight)(nHandle, index1, index2, weight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NurbsSurfaceEvaluatePoint(CALLBACKPTR, MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt)
{
	GET_CB_UPP(NurbsSurfaceEvaluatePoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NurbsSurfaceEvaluatePointPtr)(MCObjectHandle nurbsHandle, double u, double v, WorldPt3& pt, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(NurbsSurfaceEvaluatePoint)(nurbsHandle, u, v, pt, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


double_gs GS_CALLBACK GS_ObjArea(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(ObjArea);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*ObjAreaPtr)(MCObjectHandle h);
		double_gs gsResult = CALL_PROC(ObjArea)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


double_gs GS_CALLBACK GS_ObjSurfaceArea(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(ObjSurfaceArea);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*ObjSurfaceAreaPtr)(MCObjectHandle h);
		double_gs gsResult = CALL_PROC(ObjSurfaceArea)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


double_gs GS_CALLBACK GS_ObjVolume(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(ObjVolume);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*ObjVolumePtr)(MCObjectHandle h);
		double_gs gsResult = CALL_PROC(ObjVolume)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


Boolean GS_CALLBACK GS_Products3D(CALLBACKPTR, MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx)
{
	GET_CB_UPP(Products3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*Products3DPtr)(MCObjectHandle h, double_gs &Ixy, double_gs &Iyz, double_gs &Izx);
		Boolean gsResult = CALL_PROC(Products3D)(h, Ixy, Iyz, Izx);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_RemoveRoofElement(CALLBACKPTR, MCObjectHandle object, short id)
{
	GET_CB_UPP(RemoveRoofElement);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveRoofElementPtr)(MCObjectHandle object, CBSignedShort id);
		CALL_PROC(RemoveRoofElement)(object, id);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Set3DVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum, const WorldPt3& vertex, Boolean recalcBounds)
{
	GET_CB_UPP(Set3DVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Set3DVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum, const WorldPt3& vertex, CBBoolean recalcBounds, bool bUseLegacyZ);
		CALL_PROC(Set3DVertex)(h, vertexNum, vertex, recalcBounds, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetArcAnglesN(CALLBACKPTR, MCObjectHandle h, double_param startAngle, double_param sweepAngle)
{
	GET_CB_UPP(SetArcAnglesN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetArcAnglesNPtr)(MCObjectHandle h, CBDouble_param startAngle, CBDouble_param sweepAngle);
		CALL_PROC(SetArcAnglesN)(h, startAngle, sweepAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetBatAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, WorldCoord topWidth, WorldCoord baseHeight, double_param topSlope, WorldCoord controlPoint)
{
	GET_CB_UPP(SetBatAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetBatAttributesPtr)(MCObjectHandle object, const short dormerID, CBBoolean useHeight, CBWorldCoord_param heightDepthValue, CBWorldCoord_param bottomWidth, CBWorldCoord_param topWidth, CBWorldCoord_param baseHeight, CBDouble_param topSlope, CBWorldCoord_param controlPoint);
		Boolean gsResult = CALL_PROC(SetBatAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, topWidth, baseHeight, topSlope, controlPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetDormerAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, short edgeIndex, WorldCoord cornerOffset, Boolean isPerpOffset, WorldCoord perpOrHeightOffset, InternalIndex symName, Boolean centerSymbol, WorldCoord symOffset)
{
	GET_CB_UPP(SetDormerAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetDormerAttributesPtr)(MCObjectHandle object, const short dormerID, CBSignedShort edgeIndex, CBWorldCoord_param cornerOffset, CBBoolean isPerpOffset, CBWorldCoord_param perpOrHeightOffset, InternalIndex symName, CBBoolean centerSymbol, CBWorldCoord_param symOffset);
		Boolean gsResult = CALL_PROC(SetDormerAttributes)(object, dormerID, edgeIndex, cornerOffset, isPerpOffset, perpOrHeightOffset, symName, centerSymbol, symOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDormerThick(CALLBACKPTR, MCObjectHandle object, WorldCoord wallThick, WorldCoord roofThick)
{
	GET_CB_UPP(SetDormerThick);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDormerThickPtr)(MCObjectHandle object, CBWorldCoord_param wallThick, CBWorldCoord_param roofThick);
		CALL_PROC(SetDormerThick)(object, wallThick, roofThick);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetEndPoints(CALLBACKPTR, MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt)
{
	GET_CB_UPP(SetEndPoints);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetEndPointsPtr)(MCObjectHandle h, const WorldPt& startPt, const WorldPt& endPt);
		CALL_PROC(SetEndPoints)(h, startPt, endPt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetEntityMatrix(CALLBACKPTR, MCObjectHandle h, const TransformMatrix& theMat)
{
	GET_CB_UPP(SetEntityMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetEntityMatrixPtr)(MCObjectHandle h, const TransformMatrix& theMat, bool bUseLegacyZ);
		CALL_PROC(SetEntityMatrix)(h, theMat, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetExtrudeValues(CALLBACKPTR, MCObjectHandle h, WorldCoord bottom, WorldCoord top)
{
	GET_CB_UPP(SetExtrudeValues);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetExtrudeValuesPtr)(MCObjectHandle h, CBWorldCoord_param bottom, CBWorldCoord_param top);
		CALL_PROC(SetExtrudeValues)(h, bottom, top);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetGableAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, WorldCoord overhang)
{
	GET_CB_UPP(SetGableAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGableAttributesPtr)(MCObjectHandle object, const short dormerID, CBBoolean useHeight, CBWorldCoord_param heightDepthValue, CBWorldCoord_param bottomWidth, CBDouble_param leftSlope, CBDouble_param rightSlope, CBWorldCoord_param overhang);
		Boolean gsResult = CALL_PROC(SetGableAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, leftSlope, rightSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetHipAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param leftSlope, double_param rightSlope, double_param frontSlope, WorldCoord overhang)
{
	GET_CB_UPP(SetHipAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetHipAttributesPtr)(MCObjectHandle object, const short dormerID, CBBoolean useHeight, CBWorldCoord_param heightDepthValue, CBWorldCoord_param bottomWidth, CBDouble_param leftSlope, CBDouble_param rightSlope, CBDouble_param frontSlope, CBWorldCoord_param overhang);
		Boolean gsResult = CALL_PROC(SetHipAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, leftSlope, rightSlope, frontSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetLocus3DPosition(CALLBACKPTR, MCObjectHandle h, const WorldPt3& locPos)
{
	GET_CB_UPP(SetLocus3DPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLocus3DPositionPtr)(MCObjectHandle h, const WorldPt3& locPos, bool bUseLegacyZ);
		CALL_PROC(SetLocus3DPosition)(h, locPos, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetLocusPosition(CALLBACKPTR, MCObjectHandle h, const WorldPt& locPos)
{
	GET_CB_UPP(SetLocusPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLocusPositionPtr)(MCObjectHandle h, const WorldPt& locPos);
		CALL_PROC(SetLocusPosition)(h, locPos);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetObjectBounds(CALLBACKPTR, MCObjectHandle h, const WorldRect& bounds)
{
	GET_CB_UPP(SetObjectBounds);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetObjectBoundsPtr)(MCObjectHandle h, const WorldRect& bounds);
		CALL_PROC(SetObjectBounds)(h, bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetPolyShapeClose(CALLBACKPTR, MCObjectHandle h, Boolean closed)
{
	GET_CB_UPP(SetPolyShapeClose);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPolyShapeClosePtr)(MCObjectHandle h, CBBoolean closed);
		CALL_PROC(SetPolyShapeClose)(h, closed);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetQArcQuadrant(CALLBACKPTR, MCObjectHandle h, short quadrant)
{
	GET_CB_UPP(SetQArcQuadrant);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetQArcQuadrantPtr)(MCObjectHandle h, CBSignedShort quadrant);
		CALL_PROC(SetQArcQuadrant)(h, quadrant);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetRoofAccessoriesParameters(CALLBACKPTR, MCObjectHandle roof, Boolean insertAttic, Boolean insertSoffit, Boolean insertFascia, WorldCoord fasciaWidth, WorldCoord fasciaHeight, WorldCoord atticHeight, WorldCoord recess, WorldCoord rakeThick, WorldCoord trimDepth)
{
	GET_CB_UPP(SetRoofAccessoriesParameters);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetRoofAccessoriesParametersPtr)(MCObjectHandle roof, CBBoolean insertAttic, CBBoolean insertSoffit, CBBoolean insertFascia, CBWorldCoord_param fasciaWidth, CBWorldCoord_param fasciaHeight, CBWorldCoord_param atticHeight, CBWorldCoord_param recess, CBWorldCoord_param rakeThick, CBWorldCoord_param trimDepth);
		CALL_PROC(SetRoofAccessoriesParameters)(roof, insertAttic, insertSoffit, insertFascia, fasciaWidth, fasciaHeight, atticHeight, recess, rakeThick, trimDepth);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetRoofAttributes(CALLBACKPTR, MCObjectHandle object, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter)
{
	GET_CB_UPP(SetRoofAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetRoofAttributesPtr)(MCObjectHandle object, CBBoolean genGableWall, CBWorldCoord_param bearingInset, CBWorldCoord_param roofThick, CBSignedShort miterType, CBWorldCoord_param vertMiter);
		CALL_PROC(SetRoofAttributes)(object, genGableWall, bearingInset, roofThick, miterType, vertMiter);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetRRectDiameters(CALLBACKPTR, MCObjectHandle h, WorldCoord xDiam, WorldCoord yDiam)
{
	GET_CB_UPP(SetRRectDiameters);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetRRectDiametersPtr)(MCObjectHandle h, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam);
		CALL_PROC(SetRRectDiameters)(h, xDiam, yDiam);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetShedAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, double_param topSlope, WorldCoord overhang)
{
	GET_CB_UPP(SetShedAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetShedAttributesPtr)(MCObjectHandle object, const short dormerID, CBBoolean useHeight, CBWorldCoord_param heightDepthValue, CBWorldCoord_param bottomWidth, CBDouble_param topSlope, CBWorldCoord_param overhang);
		Boolean gsResult = CALL_PROC(SetShedAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, topSlope, overhang);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetSkylight(CALLBACKPTR, MCObjectHandle object, const short skylightID, short edgeIndex, WorldCoord cornerOffset, WorldCoord perpOffset, InternalIndex symName)
{
	GET_CB_UPP(SetSkylight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetSkylightPtr)(MCObjectHandle object, const short skylightID, CBSignedShort edgeIndex, CBWorldCoord_param cornerOffset, CBWorldCoord_param perpOffset, InternalIndex symName);
		Boolean gsResult = CALL_PROC(SetSkylight)(object, skylightID, edgeIndex, cornerOffset, perpOffset, symName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetSweepAnglesN(CALLBACKPTR, MCObjectHandle theSweep, double_param startAngle, double_param arcAngle, double_param incrAngle)
{
	GET_CB_UPP(SetSweepAnglesN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetSweepAnglesNPtr)(MCObjectHandle theSweep, CBDouble_param startAngle, CBDouble_param arcAngle, CBDouble_param incrAngle);
		CALL_PROC(SetSweepAnglesN)(theSweep, startAngle, arcAngle, incrAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetSweepScrew(CALLBACKPTR, MCObjectHandle theSweep, WorldCoord dist)
{
	GET_CB_UPP(SetSweepScrew);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetSweepScrewPtr)(MCObjectHandle theSweep, CBWorldCoord_param dist);
		CALL_PROC(SetSweepScrew)(theSweep, dist);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetTrapeziumAttributes(CALLBACKPTR, MCObjectHandle object, const short dormerID, Boolean useHeight, WorldCoord heightDepthValue, WorldCoord bottomWidth, Boolean useTopWidth, WorldCoord topWidth, double_param leftSlope, double_param rightSlope, double_param topSlope)
{
	GET_CB_UPP(SetTrapeziumAttributes);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetTrapeziumAttributesPtr)(MCObjectHandle object, const short dormerID, CBBoolean useHeight, CBWorldCoord_param heightDepthValue, CBWorldCoord_param bottomWidth, CBBoolean useTopWidth, CBWorldCoord_param topWidth, CBDouble_param leftSlope, CBDouble_param rightSlope, CBDouble_param topSlope);
		Boolean gsResult = CALL_PROC(SetTrapeziumAttributes)(object, dormerID, useHeight, heightDepthValue, bottomWidth, useTopWidth, topWidth, leftSlope, rightSlope, topSlope);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetVertex(CALLBACKPTR, MCObjectHandle h, short vertexNum, const WorldPt& vertex, VertexType vType, WorldCoord arcRadius, Boolean recalcBounds)
{
	GET_CB_UPP(SetVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetVertexPtr)(MCObjectHandle h, CBSignedShort vertexNum, const WorldPt& vertex, VertexType vType, CBWorldCoord_param arcRadius, CBBoolean recalcBounds);
		CALL_PROC(SetVertex)(h, vertexNum, vertex, vType, arcRadius, recalcBounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_WrapGetSweepScrew(CALLBACKPTR, MCObjectHandle theSweep, double_gs& outCoordLen)
{
	GET_CB_UPP(WrapGetSweepScrew);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*WrapGetSweepScrewPtr)(MCObjectHandle theSweep, double_gs& outCoordLen);
		CALL_PROC(WrapGetSweepScrew)(theSweep, outCoordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Attributes (Graphic)
///////////////////////////////////////////


MCObjectHandle GS_CALLBACK GS_CreateCircularDimension(CALLBACKPTR, const WorldPt& center, const WorldPt& end, WorldCoord startOffset, WorldCoord textOffset, const WorldRect& box, Boolean isRadius)
{
	GET_CB_UPP(CreateCircularDimension);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCircularDimensionPtr)(const WorldPt& center, const WorldPt& end, CBWorldCoord_param startOffset, CBWorldCoord_param textOffset, const WorldRect& box, CBBoolean isRadius);
		MCObjectHandle gsResult = CALL_PROC(CreateCircularDimension)(center, end, startOffset, textOffset, box, isRadius);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_GetArrowByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetArrowByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetArrowByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetArrowByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetArrowHeads(CALLBACKPTR, MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size)
{
	GET_CB_UPP(GetArrowHeads);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetArrowHeadsPtr)(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, short& size);
		CALL_PROC(GetArrowHeads)(h, starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetArrowHeadsN(CALLBACKPTR, MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size)
{
	GET_CB_UPP(GetArrowHeadsN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetArrowHeadsNPtr)(MCObjectHandle h, Boolean& starting, Boolean& ending, ArrowType& style, double_gs& size);
		CALL_PROC(GetArrowHeadsN)(h, starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetColor(CALLBACKPTR, MCObjectHandle h, ObjectColorType& colors)
{
	GET_CB_UPP(GetColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetColorPtr)(MCObjectHandle h, ObjectColorType& colors);
		Boolean gsResult = CALL_PROC(GetColor)(h, colors);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


OpacityRef GS_CALLBACK GS_GetDefaultOpacity(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultOpacity);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef OpacityRef (*GetDefaultOpacityPtr)();
		OpacityRef gsResult = CALL_PROC(GetDefaultOpacity)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_GetDefaultOpacityByClass(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultOpacityByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDefaultOpacityByClassPtr)();
		CBBoolean gsResult = CALL_PROC(GetDefaultOpacityByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetFColorsByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetFColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFColorsByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetFColorsByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFillIAxisEndPoint(CALLBACKPTR, MCObjectHandle objectHandle, WorldPt& iAxisEndPoint)
{
	GET_CB_UPP(GetFillIAxisEndPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFillIAxisEndPointPtr)(MCObjectHandle objectHandle, WorldPt& iAxisEndPoint);
		Boolean gsResult = CALL_PROC(GetFillIAxisEndPoint)(objectHandle, iAxisEndPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFillJAxisEndPoint(CALLBACKPTR, MCObjectHandle objectHandle, WorldPt& jAxisEndPoint)
{
	GET_CB_UPP(GetFillJAxisEndPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFillJAxisEndPointPtr)(MCObjectHandle objectHandle, WorldPt& jAxisEndPoint);
		Boolean gsResult = CALL_PROC(GetFillJAxisEndPoint)(objectHandle, jAxisEndPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFillOriginPoint(CALLBACKPTR, MCObjectHandle objectHandle, WorldPt& originPoint)
{
	GET_CB_UPP(GetFillOriginPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFillOriginPointPtr)(MCObjectHandle objectHandle, WorldPt& originPoint);
		Boolean gsResult = CALL_PROC(GetFillOriginPoint)(objectHandle, originPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetFillPat(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetFillPatPtr)(MCObjectHandle h);
		InternalIndex gsResult = CALL_PROC(GetFillPat)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetFillPoints(CALLBACKPTR, MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint)
{
	GET_CB_UPP(GetFillPoints);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFillPointsPtr)(MCObjectHandle objectHandle, WorldPt& originPoint, WorldPt& iAxisEndPoint, WorldPt& jAxisEndPoint);
		Boolean gsResult = CALL_PROC(GetFillPoints)(objectHandle, originPoint, iAxisEndPoint, jAxisEndPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFPatByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetFPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFPatByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetFPatByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_GetLineWeight(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetLineWeightPtr)(MCObjectHandle h);
		short gsResult = CALL_PROC(GetLineWeight)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetLineWeightDisplayMM(CALLBACKPTR, short mils)
{
	GET_CB_UPP(GetLineWeightDisplayMM);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetLineWeightDisplayMMPtr)(CBSignedShort mils);
		short gsResult = CALL_PROC(GetLineWeightDisplayMM)(mils);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetLineWeightDisplayPt(CALLBACKPTR, short mils)
{
	GET_CB_UPP(GetLineWeightDisplayPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetLineWeightDisplayPtPtr)(CBSignedShort mils);
		short gsResult = CALL_PROC(GetLineWeightDisplayPt)(mils);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetLWByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetLWByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLWByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetLWByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetMarker(CALLBACKPTR, MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end)
{
	GET_CB_UPP(GetMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetMarkerPtr)(MCObjectHandle obj, MarkerType& style, short& size, short& angle, Boolean& start, Boolean& end);
		CALL_PROC(GetMarker)(obj, style, size, angle, start, end);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetObjBeginningMarker(CALLBACKPTR, MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility)
{
	GET_CB_UPP(GetObjBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjBeginningMarkerPtr)(MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility);
		CBBoolean gsResult = CALL_PROC(GetObjBeginningMarker)(h, mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetObjEndMarker(CALLBACKPTR, MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility)
{
	GET_CB_UPP(GetObjEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjEndMarkerPtr)(MCObjectHandle h, SMarkerStyle& mstyle, CBBoolean& visibility);
		CBBoolean gsResult = CALL_PROC(GetObjEndMarker)(h, mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


OpacityRef GS_CALLBACK GS_GetOpacity(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetOpacity);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef OpacityRef (*GetOpacityPtr)(MCObjectHandle h);
		OpacityRef gsResult = CALL_PROC(GetOpacity)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_GetOpacityByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetOpacityByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetOpacityByClassPtr)(MCObjectHandle h);
		CBBoolean gsResult = CALL_PROC(GetOpacityByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetPColorsByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetPColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPColorsByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetPColorsByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_GetPPatByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetPPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPPatByClassPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(GetPPatByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetVertexVis(CALLBACKPTR, MCObjectHandle h, short vertNum, Boolean& vis)
{
	GET_CB_UPP(GetVertexVis);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetVertexVisPtr)(MCObjectHandle h, CBSignedShort vertNum, Boolean& vis);
		CALL_PROC(GetVertexVis)(h, vertNum, vis);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetArrowByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetArrowByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetArrowByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetArrowByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetArrowHeads(CALLBACKPTR, MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, short size)
{
	GET_CB_UPP(SetArrowHeads);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetArrowHeadsPtr)(MCObjectHandle h, CBBoolean starting, CBBoolean ending, ArrowType style, CBSignedShort size);
		CALL_PROC(SetArrowHeads)(h, starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetArrowHeadsN(CALLBACKPTR, MCObjectHandle h, Boolean starting, Boolean ending, ArrowType style, double_param size)
{
	GET_CB_UPP(SetArrowHeadsN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetArrowHeadsNPtr)(MCObjectHandle h, CBBoolean starting, CBBoolean ending, ArrowType style, CBDouble_param size);
		CALL_PROC(SetArrowHeadsN)(h, starting, ending, style, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetColor(CALLBACKPTR, MCObjectHandle h, ObjectColorType colors)
{
	GET_CB_UPP(SetColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetColorPtr)(MCObjectHandle h, ObjectColorType colors);
		CALL_PROC(SetColor)(h, colors);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultOpacity(CALLBACKPTR, OpacityRef inOpacity)
{
	GET_CB_UPP(SetDefaultOpacity);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultOpacityPtr)(OpacityRef inOpacity);
		CALL_PROC(SetDefaultOpacity)(inOpacity);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultOpacityByClass(CALLBACKPTR)
{
	GET_CB_UPP(SetDefaultOpacityByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultOpacityByClassPtr)();
		CALL_PROC(SetDefaultOpacityByClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetFColorsByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetFColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetFColorsByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetFColorsByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetFillIAxisEndPoint(CALLBACKPTR, MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint)
{
	GET_CB_UPP(SetFillIAxisEndPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetFillIAxisEndPointPtr)(MCObjectHandle objectHandle, const WorldPt& iAxisEndPoint);
		Boolean gsResult = CALL_PROC(SetFillIAxisEndPoint)(objectHandle, iAxisEndPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetFillJAxisEndPoint(CALLBACKPTR, MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint)
{
	GET_CB_UPP(SetFillJAxisEndPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetFillJAxisEndPointPtr)(MCObjectHandle objectHandle, const WorldPt& jAxisEndPoint);
		Boolean gsResult = CALL_PROC(SetFillJAxisEndPoint)(objectHandle, jAxisEndPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetFillOriginPoint(CALLBACKPTR, MCObjectHandle objectHandle, const WorldPt& originPoint)
{
	GET_CB_UPP(SetFillOriginPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetFillOriginPointPtr)(MCObjectHandle objectHandle, const WorldPt& originPoint);
		Boolean gsResult = CALL_PROC(SetFillOriginPoint)(objectHandle, originPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetFillPat(CALLBACKPTR, MCObjectHandle h, InternalIndex theFill)
{
	GET_CB_UPP(SetFillPat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetFillPatPtr)(MCObjectHandle h, InternalIndex theFill);
		CALL_PROC(SetFillPat)(h, theFill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetFPatByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetFPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetFPatByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetFPatByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetLineWeight(CALLBACKPTR, MCObjectHandle h, short mils)
{
	GET_CB_UPP(SetLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLineWeightPtr)(MCObjectHandle h, CBSignedShort mils);
		CALL_PROC(SetLineWeight)(h, mils);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetLineWeightDisplayMM(CALLBACKPTR, short hundredths)
{
	GET_CB_UPP(SetLineWeightDisplayMM);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLineWeightDisplayMMPtr)(CBSignedShort hundredths);
		Boolean gsResult = CALL_PROC(SetLineWeightDisplayMM)(hundredths);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetLineWeightDisplayPt(CALLBACKPTR, short sixteenths)
{
	GET_CB_UPP(SetLineWeightDisplayPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLineWeightDisplayPtPtr)(CBSignedShort sixteenths);
		Boolean gsResult = CALL_PROC(SetLineWeightDisplayPt)(sixteenths);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetLWByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetLWByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLWByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetLWByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetObjBeginningMarker(CALLBACKPTR, MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility)
{
	GET_CB_UPP(SetObjBeginningMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetObjBeginningMarkerPtr)(MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility);
		CBBoolean gsResult = CALL_PROC(SetObjBeginningMarker)(h, mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetObjEndMarker(CALLBACKPTR, MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility)
{
	GET_CB_UPP(SetObjEndMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetObjEndMarkerPtr)(MCObjectHandle h, SMarkerStyle mstyle, CBBoolean visibility);
		CBBoolean gsResult = CALL_PROC(SetObjEndMarker)(h, mstyle, visibility);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetOpacity(CALLBACKPTR, MCObjectHandle h, OpacityRef inNewOpacity)
{
	GET_CB_UPP(SetOpacity);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetOpacityPtr)(MCObjectHandle h, OpacityRef inNewOpacity);
		CALL_PROC(SetOpacity)(h, inNewOpacity);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetOpacityByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetOpacityByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetOpacityByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetOpacityByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetPColorsByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetPColorsByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPColorsByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetPColorsByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



void GS_CALLBACK GS_SetPPatByClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(SetPPatByClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPPatByClassPtr)(MCObjectHandle h);
		CALL_PROC(SetPPatByClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetVertexVis(CALLBACKPTR, MCObjectHandle h, short vertNum, Boolean vis)
{
	GET_CB_UPP(SetVertexVis);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetVertexVisPtr)(MCObjectHandle h, CBSignedShort vertNum, CBBoolean vis);
		CALL_PROC(SetVertexVis)(h, vertNum, vis);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Attributes (System)
///////////////////////////////////////////


MCObjectHandle GS_CALLBACK GS_GetDefinition(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetDefinition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetDefinitionPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(GetDefinition)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_GetDXFColorToLineWeight(CALLBACKPTR, const short inDXFColorIndex)
{
	GET_CB_UPP(GetDXFColorToLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetDXFColorToLineWeightPtr)(const short inDXFColorIndex);
		short gsResult = CALL_PROC(GetDXFColorToLineWeight)(inDXFColorIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kUnmappedLineWeight;
}


MCObjectHandle GS_CALLBACK GS_GetNamedObject(CALLBACKPTR, const InternalName& objName)
{
	GET_CB_UPP(GetNamedObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetNamedObjectPtr)(const InternalName& objName);
		MCObjectHandle gsResult = CALL_PROC(GetNamedObject)(objName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


InternalIndex GS_CALLBACK GS_GetObjectClass(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetObjectClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetObjectClassPtr)(MCObjectHandle h);
		InternalIndex gsResult = CALL_PROC(GetObjectClass)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetObjectName(CALLBACKPTR, MCObjectHandle h, InternalName& name)
{
	GET_CB_UPP(GetObjectName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetObjectNamePtr)(MCObjectHandle h, InternalName& name);
		CALL_PROC(GetObjectName)(h, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetObjectType(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetObjectType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetObjectTypePtr)(MCObjectHandle h);
		short gsResult = CALL_PROC(GetObjectType)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetSymbolDefinitionIcon(CALLBACKPTR, MCObjectHandle theSymDef, Sint32 icon[32])
{
	GET_CB_UPP(GetSymbolDefinitionIcon);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSymbolDefinitionIconPtr)(MCObjectHandle theSymDef, Sint32 icon[32]);
		CALL_PROC(GetSymbolDefinitionIcon)(theSymDef, icon);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetSymbolDefinitionType(CALLBACKPTR, MCObjectHandle theSymDef)
{
	GET_CB_UPP(GetSymbolDefinitionType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetSymbolDefinitionTypePtr)(MCObjectHandle theSymDef);
		short gsResult = CALL_PROC(GetSymbolDefinitionType)(theSymDef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_IsLocked(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(IsLocked);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsLockedPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(IsLocked)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsSelected(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(IsSelected);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsSelectedPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(IsSelected)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsVisible(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(IsVisible);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsVisiblePtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(IsVisible)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_LockObject(CALLBACKPTR, MCObjectHandle h, Boolean lock)
{
	GET_CB_UPP(LockObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*LockObjectPtr)(MCObjectHandle h, CBBoolean lock);
		CALL_PROC(LockObject)(h, lock);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SelectObject(CALLBACKPTR, MCObjectHandle h, Boolean select)
{
	GET_CB_UPP(SelectObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SelectObjectPtr)(MCObjectHandle h, CBBoolean select);
		CALL_PROC(SelectObject)(h, select);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDXFColorToLineWeight(CALLBACKPTR, const short inDXFColorIndex, const short inLineWeight)
{
	GET_CB_UPP(SetDXFColorToLineWeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDXFColorToLineWeightPtr)(const short inDXFColorIndex, const short inLineWeight);
		CALL_PROC(SetDXFColorToLineWeight)(inDXFColorIndex, inLineWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetObjectClass(CALLBACKPTR, MCObjectHandle h, InternalIndex classID)
{
	GET_CB_UPP(SetObjectClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetObjectClassPtr)(MCObjectHandle h, InternalIndex classID);
		CALL_PROC(SetObjectClass)(h, classID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


GSError GS_CALLBACK GS_SetObjectName(CALLBACKPTR, MCObjectHandle h, const InternalName& name)
{
	GET_CB_UPP(SetObjectName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSError (*SetObjectNamePtr)(MCObjectHandle h, const InternalName& name);
		GSError gsResult = CALL_PROC(SetObjectName)(h, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return noErr;
}


void GS_CALLBACK GS_SetSymbolDefinitionIcon(CALLBACKPTR, MCObjectHandle theSymDef, const Sint32 icon[32])
{
	GET_CB_UPP(SetSymbolDefinitionIcon);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetSymbolDefinitionIconPtr)(MCObjectHandle theSymDef, const Sint32 icon[32]);
		CALL_PROC(SetSymbolDefinitionIcon)(theSymDef, icon);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetVisibility(CALLBACKPTR, MCObjectHandle h, Boolean visible)
{
	GET_CB_UPP(SetVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetVisibilityPtr)(MCObjectHandle h, CBBoolean visible);
		CALL_PROC(SetVisibility)(h, visible);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Auxiliary and Data Objects
///////////////////////////////////////////


void GS_CALLBACK GS_AttachAuxObject(CALLBACKPTR, MCObjectHandle h, MCObjectHandle newOwner)
{
	GET_CB_UPP(AttachAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AttachAuxObjectPtr)(MCObjectHandle h, MCObjectHandle newOwner);
		CALL_PROC(AttachAuxObject)(h, newOwner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DeleteAuxObject(CALLBACKPTR, MCObjectHandle h, MCObjectHandle owner)
{
	GET_CB_UPP(DeleteAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteAuxObjectPtr)(MCObjectHandle h, MCObjectHandle owner);
		CALL_PROC(DeleteAuxObject)(h, owner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_FindAuxObject(CALLBACKPTR, MCObjectHandle owner, short objectType)
{
	GET_CB_UPP(FindAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*FindAuxObjectPtr)(MCObjectHandle owner, CBSignedShort objectType);
		MCObjectHandle gsResult = CALL_PROC(FindAuxObject)(owner, objectType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_FindDataObject(CALLBACKPTR, MCObjectHandle owner, OSType tag)
{
	GET_CB_UPP(FindDataObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*FindDataObjectPtr)(MCObjectHandle owner, OSType tag);
		MCObjectHandle gsResult = CALL_PROC(FindDataObject)(owner, tag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_FirstAuxObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(FirstAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*FirstAuxObjectPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(FirstAuxObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


OSType GS_CALLBACK GS_GetDataTag(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(GetDataTag);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef OSType (*GetDataTagPtr)(MCObjectHandle h);
		OSType gsResult = CALL_PROC(GetDataTag)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return '    ';
}


Boolean GS_CALLBACK GS_GetPluginType(CALLBACKPTR, const InternalName& name, EVSPluginType& type)
{
	GET_CB_UPP(GetPluginType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPluginTypePtr)(const InternalName& name, EVSPluginType& type);
		Boolean gsResult = CALL_PROC(GetPluginType)(name, type);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsPluginFormat(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(IsPluginFormat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsPluginFormatPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(IsPluginFormat)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_NewDataObject(CALLBACKPTR, MCObjectHandle attachTo, OSType tag, size_t objectSize)
{
	GET_CB_UPP(NewDataObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*NewDataObjectPtr)(MCObjectHandle attachTo, OSType tag, size_t objectSize);
		MCObjectHandle gsResult = CALL_PROC(NewDataObject)(attachTo, tag, objectSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_NextAuxObject(CALLBACKPTR, MCObjectHandle start, short objectType)
{
	GET_CB_UPP(NextAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*NextAuxObjectPtr)(MCObjectHandle start, CBSignedShort objectType);
		MCObjectHandle gsResult = CALL_PROC(NextAuxObject)(start, objectType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_NextDataObject(CALLBACKPTR, MCObjectHandle start, OSType tag)
{
	GET_CB_UPP(NextDataObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*NextDataObjectPtr)(MCObjectHandle start, OSType tag);
		MCObjectHandle gsResult = CALL_PROC(NextDataObject)(start, tag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_RemoveAuxObject(CALLBACKPTR, MCObjectHandle h, MCObjectHandle owner)
{
	GET_CB_UPP(RemoveAuxObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveAuxObjectPtr)(MCObjectHandle h, MCObjectHandle owner);
		CALL_PROC(RemoveAuxObject)(h, owner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_TaggedDataCreate(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t numDataElements)
{
	GET_CB_UPP(TaggedDataCreate);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataCreatePtr)(MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t numDataElements);
		Boolean gsResult = CALL_PROC(TaggedDataCreate)(inOwnerObj, dataContainer, dataType, dataTag, numDataElements);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TaggedDataGet(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t dataIndex, void* getData)
{
	GET_CB_UPP(TaggedDataGet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataGetPtr)(MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t dataIndex, void* getData);
		Boolean gsResult = CALL_PROC(TaggedDataGet)(inOwnerObj, dataContainer, dataType, dataTag, dataIndex, getData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TaggedDataGetNumElements(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, Sint32* getData)
{
	GET_CB_UPP(TaggedDataGetNumElements);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataGetNumElementsPtr)(MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, Sint32* getData);
		Boolean gsResult = CALL_PROC(TaggedDataGetNumElements)(inOwnerObj, dataContainer, dataType, dataTag, getData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TaggedDataRemoveContainer(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer)
{
	GET_CB_UPP(TaggedDataRemoveContainer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataRemoveContainerPtr)(MCObjectHandle inOwnerObj, OSType dataContainer);
		Boolean gsResult = CALL_PROC(TaggedDataRemoveContainer)(inOwnerObj, dataContainer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TaggedDataRemoveTag(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag)
{
	GET_CB_UPP(TaggedDataRemoveTag);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataRemoveTagPtr)(MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag);
		Boolean gsResult = CALL_PROC(TaggedDataRemoveTag)(inOwnerObj, dataContainer, dataType, dataTag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TaggedDataSet(CALLBACKPTR, MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t dataIndex, const void* data)
{
	GET_CB_UPP(TaggedDataSet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TaggedDataSetPtr)(MCObjectHandle inOwnerObj, OSType dataContainer, Sint32 dataType, Sint32 dataTag, size_t dataIndex, const void* data);
		Boolean gsResult = CALL_PROC(TaggedDataSet)(inOwnerObj, dataContainer, dataType, dataTag, dataIndex, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Coordinate Transformation
///////////////////////////////////////////


void GS_CALLBACK GS_CoordLengthToPageLengthN(CALLBACKPTR, WorldCoord len, double_gs& pageLength)
{
	GET_CB_UPP(CoordLengthToPageLengthN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CoordLengthToPageLengthNPtr)(CBWorldCoord_param len, double_gs& pageLength);
		CALL_PROC(CoordLengthToPageLengthN)(len, pageLength);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


double_gs GS_CALLBACK GS_CoordLengthToPagePoints(CALLBACKPTR, WorldCoord len)
{
	GET_CB_UPP(CoordLengthToPagePoints);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef double_gs (*CoordLengthToPagePointsPtr)(CBWorldCoord_param len);
		double_gs gsResult = CALL_PROC(CoordLengthToPagePoints)(len);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


Boolean GS_CALLBACK GS_CoordLengthToPixelLength(CALLBACKPTR, WorldCoord numCoords, short& numPixels)
{
	GET_CB_UPP(CoordLengthToPixelLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CoordLengthToPixelLengthPtr)(CBWorldCoord_param numCoords, short& numPixels);
		Boolean gsResult = CALL_PROC(CoordLengthToPixelLength)(numCoords, numPixels);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CoordLengthToUnitsLengthN(CALLBACKPTR, WorldCoord len, double_gs& unitsLength)
{
	GET_CB_UPP(CoordLengthToUnitsLengthN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CoordLengthToUnitsLengthNPtr)(CBWorldCoord_param len, double_gs& unitsLength);
		CALL_PROC(CoordLengthToUnitsLengthN)(len, unitsLength);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_CreateOvalN(CALLBACKPTR, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height)
{
	GET_CB_UPP(CreateOvalN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateOvalNPtr)(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		MCObjectHandle gsResult = CALL_PROC(CreateOvalN)(origin, orientation, width, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_DimStringToCoord(CALLBACKPTR, const TXString& s, WorldCoord& c)
{
	GET_CB_UPP(DimStringToCoord);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DimStringToCoordPtr)(const TXString& s, WorldCoord& c);
		Boolean gsResult = CALL_PROC(DimStringToCoord)(s, c);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_FPCoordLengthToPageLength(CALLBACKPTR, double_param coordLen, double_gs& pageLen)
{
	GET_CB_UPP(FPCoordLengthToPageLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*FPCoordLengthToPageLengthPtr)(CBDouble_param coordLen, double_gs& pageLen);
		CALL_PROC(FPCoordLengthToPageLength)(coordLen, pageLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_FPCoordLengthToUnitsLength(CALLBACKPTR, double_param coordLen, double_gs& unitsLen)
{
	GET_CB_UPP(FPCoordLengthToUnitsLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*FPCoordLengthToUnitsLengthPtr)(CBDouble_param coordLen, double_gs& unitsLen);
		CALL_PROC(FPCoordLengthToUnitsLength)(coordLen, unitsLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ModelPt2DToScreenPt(CALLBACKPTR, WorldPt& vertex)
{
	GET_CB_UPP(ModelPt2DToScreenPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ModelPt2DToScreenPtPtr)(WorldPt& vertex);
		CALL_PROC(ModelPt2DToScreenPt)(vertex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ModelVecToScreenVec(CALLBACKPTR, WorldPt& vertex)
{
	GET_CB_UPP(ModelVecToScreenVec);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ModelVecToScreenVecPtr)(WorldPt& vertex);
		CALL_PROC(ModelVecToScreenVec)(vertex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PageLengthToFPCoordLength(CALLBACKPTR, double_param pageLen, double_gs& coordLen)
{
	GET_CB_UPP(PageLengthToFPCoordLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PageLengthToFPCoordLengthPtr)(CBDouble_param pageLen, double_gs& coordLen);
		CALL_PROC(PageLengthToFPCoordLength)(pageLen, coordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


WorldCoord GS_CALLBACK GS_PagePointsToCoordLength(CALLBACKPTR, double_gs& points)
{
	GET_CB_UPP(PagePointsToCoordLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef WorldCoord (*PagePointsToCoordLengthPtr)(double_gs& points);
		WorldCoord gsResult = CALL_PROC(PagePointsToCoordLength)(points);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


void GS_CALLBACK GS_PixelLengthToCoordLength(CALLBACKPTR, short numPixels, WorldCoord& numCoords)
{
	GET_CB_UPP(PixelLengthToCoordLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PixelLengthToCoordLengthPtr)(CBSignedShort numPixels, WorldCoord& numCoords);
		CALL_PROC(PixelLengthToCoordLength)(numPixels, numCoords);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ScreenPtToModelPt2D(CALLBACKPTR, WorldPt& vertex)
{
	GET_CB_UPP(ScreenPtToModelPt2D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ScreenPtToModelPt2DPtr)(WorldPt& vertex);
		CALL_PROC(ScreenPtToModelPt2D)(vertex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ScreenVecToModelVec(CALLBACKPTR, WorldPt& vertex)
{
	GET_CB_UPP(ScreenVecToModelVec);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ScreenVecToModelVecPtr)(WorldPt& vertex);
		CALL_PROC(ScreenVecToModelVec)(vertex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_UnitsLengthToFPCoordLength(CALLBACKPTR, double_param unitsLen, double_gs& coordLen)
{
	GET_CB_UPP(UnitsLengthToFPCoordLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UnitsLengthToFPCoordLengthPtr)(CBDouble_param unitsLen, double_gs& coordLen);
		CALL_PROC(UnitsLengthToFPCoordLength)(unitsLen, coordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


WorldCoord GS_CALLBACK GS_WorldCoordsPerDrawingUnit(CALLBACKPTR)
{
	GET_CB_UPP(WorldCoordsPerDrawingUnit);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef WorldCoord (*WorldCoordsPerDrawingUnitPtr)();
		WorldCoord gsResult = CALL_PROC(WorldCoordsPerDrawingUnit)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0.0;
}


void GS_CALLBACK GS_WrapPageLengthToCoordLengthN(CALLBACKPTR, double_param len, double_gs& outCoordLen)
{
	GET_CB_UPP(WrapPageLengthToCoordLengthN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*WrapPageLengthToCoordLengthNPtr)(CBDouble_param len, double_gs& outCoordLen);
		CALL_PROC(WrapPageLengthToCoordLengthN)(len, outCoordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_WrapUnitsLengthToCoordLengthN(CALLBACKPTR, double_param len, double_gs& outCoordLen)
{
	GET_CB_UPP(WrapUnitsLengthToCoordLengthN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*WrapUnitsLengthToCoordLengthNPtr)(CBDouble_param len, double_gs& outCoordLen);
		CALL_PROC(WrapUnitsLengthToCoordLengthN)(len, outCoordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Creation
///////////////////////////////////////////


short GS_CALLBACK GS_AddSolid(CALLBACKPTR, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
{
	GET_CB_UPP(AddSolid);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*AddSolidPtr)(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		short gsResult = CALL_PROC(AddSolid)(obj1, obj2, newSolid);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_AppendRoofEdge(CALLBACKPTR, MCObjectHandle object, const WorldPt& edgePt, double_param slope, WorldCoord projection, WorldCoord eaveHeight)
{
	GET_CB_UPP(AppendRoofEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AppendRoofEdgePtr)(MCObjectHandle object, const WorldPt& edgePt, CBDouble_param slope, CBWorldCoord_param projection, CBWorldCoord_param eaveHeight);
		Boolean gsResult = CALL_PROC(AppendRoofEdge)(object, edgePt, slope, projection, eaveHeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_Create3DPoly(CALLBACKPTR)
{
	GET_CB_UPP(Create3DPoly);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*Create3DPolyPtr)();
		MCObjectHandle gsResult = CALL_PROC(Create3DPoly)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateAngleDimension(CALLBACKPTR, const WorldPt& center, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset)
{
	GET_CB_UPP(CreateAngleDimension);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateAngleDimensionPtr)(const WorldPt& center, const WorldPt& p1, const WorldPt& p2, CBWorldCoord_param startOffset);
		MCObjectHandle gsResult = CALL_PROC(CreateAngleDimension)(center, p1, p2, startOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateArcN(CALLBACKPTR, const WorldRect& bounds, double_param startAngle, double_param sweepAngle)
{
	GET_CB_UPP(CreateArcN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateArcNPtr)(const WorldRect& bounds, CBDouble_param startAngle, CBDouble_param sweepAngle);
		MCObjectHandle gsResult = CALL_PROC(CreateArcN)(bounds, startAngle, sweepAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_CreateBatDormer(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateBatDormer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateBatDormerPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateBatDormer)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_CreateChainDimension(CALLBACKPTR, MCObjectHandle h1, MCObjectHandle h2)
{
	GET_CB_UPP(CreateChainDimension);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateChainDimensionPtr)(MCObjectHandle h1, MCObjectHandle h2);
		MCObjectHandle gsResult = CALL_PROC(CreateChainDimension)(h1, h2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCombineIntoSurface(CALLBACKPTR, const WorldPt& inPoint)
{
	GET_CB_UPP(CreateCombineIntoSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCombineIntoSurfacePtr)(const WorldPt& inPoint);
		MCObjectHandle gsResult = CALL_PROC(CreateCombineIntoSurface)(inPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCone(CALLBACKPTR, const WorldPt3& center, const WorldPt3 &tip, WorldCoord radius)
{
	GET_CB_UPP(CreateCone);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateConePtr)(const WorldPt3& center, const WorldPt3 &tip, CBWorldCoord_param radius, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateCone)(center, tip, radius, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateContourCurves(CALLBACKPTR, MCObjectHandle h, double_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal)
{
	GET_CB_UPP(CreateContourCurves);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateContourCurvesPtr)(MCObjectHandle h, CBDouble_param delta, WorldPt3 pointOnPlane, WorldPt3 planeNormal, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateContourCurves)(h, delta, pointOnPlane, planeNormal, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCustomDimensionStandard(CALLBACKPTR, const TXString& name)
{
	GET_CB_UPP(CreateCustomDimensionStandard);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCustomDimensionStandardPtr)(const TXString& name);
		MCObjectHandle gsResult = CALL_PROC(CreateCustomDimensionStandard)(name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCustomObject(CALLBACKPTR, const InternalName& name, const WorldPt& location, double_param angle)
{
	GET_CB_UPP(CreateCustomObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCustomObjectPtr)(const InternalName& name, const WorldPt& location, CBDouble_param angle, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateCustomObject)(name, location, angle, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCustomObjectByMatrix(CALLBACKPTR, const InternalName& name, const TransformMatrix& matrix)
{
	GET_CB_UPP(CreateCustomObjectByMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCustomObjectByMatrixPtr)(const InternalName& name, const TransformMatrix& matrix, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateCustomObjectByMatrix)(name, matrix, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCustomObjectDoubleClick(CALLBACKPTR, const InternalName& name)
{
	GET_CB_UPP(CreateCustomObjectDoubleClick);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCustomObjectDoubleClickPtr)(const InternalName& name, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateCustomObjectDoubleClick)(name, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateCustomObjectPath(CALLBACKPTR, const InternalName& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand)
{
	GET_CB_UPP(CreateCustomObjectPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateCustomObjectPathPtr)(const InternalName& name, MCObjectHandle pathHand, MCObjectHandle profileGroupHand, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateCustomObjectPath)(name, pathHand, profileGroupHand, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateExtrude(CALLBACKPTR, WorldCoord bottom, WorldCoord top)
{
	GET_CB_UPP(CreateExtrude);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateExtrudePtr)(CBWorldCoord_param bottom, CBWorldCoord_param top);
		MCObjectHandle gsResult = CALL_PROC(CreateExtrude)(bottom, top);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateExtrudeAlongPath(CALLBACKPTR, MCObjectHandle pathHandle, MCObjectHandle profileHandle)
{
	GET_CB_UPP(CreateExtrudeAlongPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateExtrudeAlongPathPtr)(MCObjectHandle pathHandle, MCObjectHandle profileHandle);
		MCObjectHandle gsResult = CALL_PROC(CreateExtrudeAlongPath)(pathHandle, profileHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_CreateGableDormer(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateGableDormer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateGableDormerPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateGableDormer)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_CreateGroup(CALLBACKPTR)
{
	GET_CB_UPP(CreateGroup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateGroupPtr)();
		MCObjectHandle gsResult = CALL_PROC(CreateGroup)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateHemisphere(CALLBACKPTR, const WorldPt3& center, const WorldPt3 &topPoint)
{
	GET_CB_UPP(CreateHemisphere);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateHemispherePtr)(const WorldPt3& center, const WorldPt3 &topPoint, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateHemisphere)(center, topPoint, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_CreateHipDormer(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateHipDormer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateHipDormerPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateHipDormer)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_CreateImageProp(CALLBACKPTR, TXString&  propName, InternalIndex textureRef, WorldCoord height, WorldCoord width, Boolean enforceImageAspectRatio, Boolean crossedPlanes, Boolean createPlugin, Boolean autoRotate, Boolean createSymbol)
{
	GET_CB_UPP(CreateImageProp);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateImagePropPtr)(TXString&  propName, InternalIndex textureRef, CBWorldCoord_param height, CBWorldCoord_param width, CBBoolean enforceImageAspectRatio, CBBoolean crossedPlanes, CBBoolean createPlugin, CBBoolean autoRotate, CBBoolean createSymbol);
		MCObjectHandle gsResult = CALL_PROC(CreateImageProp)(propName, textureRef, height, width, enforceImageAspectRatio, crossedPlanes, createPlugin, autoRotate, createSymbol);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateInterpolatedSurface(CALLBACKPTR, MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree)
{
	GET_CB_UPP(CreateInterpolatedSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateInterpolatedSurfacePtr)(MCObjectHandle surfaceHandle, Sint32 numUPts, Sint32 numVPts, CBSignedShort uDegree, CBSignedShort vDegree);
		MCObjectHandle gsResult = CALL_PROC(CreateInterpolatedSurface)(surfaceHandle, numUPts, numVPts, uDegree, vDegree);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLayer(CALLBACKPTR, const InternalName& layerName, short layerType)
{
	GET_CB_UPP(CreateLayer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLayerPtr)(const InternalName& layerName, CBSignedShort layerType);
		MCObjectHandle gsResult = CALL_PROC(CreateLayer)(layerName, layerType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLayerN(CALLBACKPTR, const InternalName& name, double_param scale)
{
	GET_CB_UPP(CreateLayerN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLayerNPtr)(const InternalName& name, CBDouble_param scale);
		MCObjectHandle gsResult = CALL_PROC(CreateLayerN)(name, scale);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLightN(CALLBACKPTR, const WorldPt3& pos, short kind, Boolean isOn, double_param brightness, const WorldPt3& color, Boolean castShadows)
{
	GET_CB_UPP(CreateLightN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLightNPtr)(const WorldPt3& pos, CBSignedShort kind, CBBoolean isOn, CBDouble_param brightness, const WorldPt3& color, CBBoolean castShadows, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateLightN)(pos, kind, isOn, brightness, color, castShadows, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLine(CALLBACKPTR, const WorldPt& startPt, const WorldPt& endPt)
{
	GET_CB_UPP(CreateLine);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLinePtr)(const WorldPt& startPt, const WorldPt& endPt);
		MCObjectHandle gsResult = CALL_PROC(CreateLine)(startPt, endPt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLinearDimension(CALLBACKPTR, const WorldPt& p1, const WorldPt& p2, WorldCoord startOffset, WorldCoord textOffset, const Vector2& dir, short dimType)
{
	GET_CB_UPP(CreateLinearDimension);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLinearDimensionPtr)(const WorldPt& p1, const WorldPt& p2, CBWorldCoord_param startOffset, CBWorldCoord_param textOffset, const Vector2& dir, CBSignedShort dimType);
		MCObjectHandle gsResult = CALL_PROC(CreateLinearDimension)(p1, p2, startOffset, textOffset, dir, dimType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLocus(CALLBACKPTR, const WorldPt& location)
{
	GET_CB_UPP(CreateLocus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLocusPtr)(const WorldPt& location);
		MCObjectHandle gsResult = CALL_PROC(CreateLocus)(location);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLocus3D(CALLBACKPTR, const WorldPt3& location)
{
	GET_CB_UPP(CreateLocus3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLocus3DPtr)(const WorldPt3& location, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateLocus3D)(location, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateLoftSurfaces(CALLBACKPTR, MCObjectHandle groupCurvesH, Boolean bRule, Boolean bClose, Boolean bSolid)
{
	GET_CB_UPP(CreateLoftSurfaces);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateLoftSurfacesPtr)(MCObjectHandle groupCurvesH, CBBoolean bRule, CBBoolean bClose, CBBoolean bSolid);
		MCObjectHandle gsResult = CALL_PROC(CreateLoftSurfaces)(groupCurvesH, bRule, bClose, bSolid);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateNurbsCurve(CALLBACKPTR, WorldPt3 firstPt, bool byCtrlPts, short degree)
{
	GET_CB_UPP(CreateNurbsCurve);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateNurbsCurvePtr)(WorldPt3 firstPt, bool byCtrlPts, CBSignedShort degree, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateNurbsCurve)(firstPt, byCtrlPts, degree, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateNurbsSurface(CALLBACKPTR, Sint32 numUPts, Sint32 numVPts, short uDegree, short vDegree)
{
	GET_CB_UPP(CreateNurbsSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateNurbsSurfacePtr)(Sint32 numUPts, Sint32 numVPts, CBSignedShort uDegree, CBSignedShort vDegree);
		MCObjectHandle gsResult = CALL_PROC(CreateNurbsSurface)(numUPts, numVPts, uDegree, vDegree);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateOval(CALLBACKPTR, const WorldRect& bounds)
{
	GET_CB_UPP(CreateOval);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateOvalPtr)(const WorldRect& bounds);
		MCObjectHandle gsResult = CALL_PROC(CreateOval)(bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreatePolyshape(CALLBACKPTR)
{
	GET_CB_UPP(CreatePolyshape);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreatePolyshapePtr)();
		MCObjectHandle gsResult = CALL_PROC(CreatePolyshape)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateQArc(CALLBACKPTR, const WorldRect& bounds, short quadrant)
{
	GET_CB_UPP(CreateQArc);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateQArcPtr)(const WorldRect& bounds, CBSignedShort quadrant);
		MCObjectHandle gsResult = CALL_PROC(CreateQArc)(bounds, quadrant);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRectangle(CALLBACKPTR, const WorldRect& bounds)
{
	GET_CB_UPP(CreateRectangle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRectanglePtr)(const WorldRect& bounds);
		MCObjectHandle gsResult = CALL_PROC(CreateRectangle)(bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRectangleN(CALLBACKPTR, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height)
{
	GET_CB_UPP(CreateRectangleN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRectangleNPtr)(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height);
		MCObjectHandle gsResult = CALL_PROC(CreateRectangleN)(origin, orientation, width, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRoof(CALLBACKPTR, Boolean genGableWall, WorldCoord bearingInset, WorldCoord roofThick, short miterType, WorldCoord vertMiter)
{
	GET_CB_UPP(CreateRoof);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRoofPtr)(CBBoolean genGableWall, CBWorldCoord_param bearingInset, CBWorldCoord_param roofThick, CBSignedShort miterType, CBWorldCoord_param vertMiter);
		MCObjectHandle gsResult = CALL_PROC(CreateRoof)(genGableWall, bearingInset, roofThick, miterType, vertMiter);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRoundWall(CALLBACKPTR, const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, WorldCoord wallThickness)
{
	GET_CB_UPP(CreateRoundWall);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRoundWallPtr)(const WorldPt& startPt, const WorldPt& ptOnArc, const WorldPt& endPt, CBWorldCoord_param wallThickness);
		MCObjectHandle gsResult = CALL_PROC(CreateRoundWall)(startPt, ptOnArc, endPt, wallThickness);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRRectangle(CALLBACKPTR, const WorldRect& bounds, WorldCoord xDiam, WorldCoord yDiam)
{
	GET_CB_UPP(CreateRRectangle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRRectanglePtr)(const WorldRect& bounds, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam);
		MCObjectHandle gsResult = CALL_PROC(CreateRRectangle)(bounds, xDiam, yDiam);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateRRectangleN(CALLBACKPTR, const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, CBBoolean isProportional)
{
	GET_CB_UPP(CreateRRectangleN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateRRectangleNPtr)(const WorldPt& origin, const Vector2 &orientation, CBWorldCoord_param width, CBWorldCoord_param height, CBWorldCoord_param xDiam, CBWorldCoord_param yDiam, CBBoolean isProportional);
		MCObjectHandle gsResult = CALL_PROC(CreateRRectangleN)(origin, orientation, width, height, xDiam, yDiam, isProportional);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_CreateShedDormer(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateShedDormer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateShedDormerPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateShedDormer)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_CreateBasicSlab(CALLBACKPTR, short slabKind)
{
	GET_CB_UPP(CreateBasicSlab);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateBasicSlabPtr)(CBSignedShort slabKind);
		MCObjectHandle gsResult = CALL_PROC(CreateBasicSlab)(slabKind);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateSphere(CALLBACKPTR, const WorldPt3& center, WorldCoord radius)
{
	GET_CB_UPP(CreateSphere);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateSpherePtr)(const WorldPt3& center, CBWorldCoord_param radius, bool bUseLegacyZ);
		MCObjectHandle gsResult = CALL_PROC(CreateSphere)(center, radius, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateStaticHatch(CALLBACKPTR, const InternalName& name, const WorldPt& inOriginPoint, double_param inRotationAngle)
{
	GET_CB_UPP(CreateStaticHatch);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateStaticHatchPtr)(const InternalName& name, const WorldPt& inOriginPoint, CBDouble_param inRotationAngle);
		MCObjectHandle gsResult = CALL_PROC(CreateStaticHatch)(name, inOriginPoint, inRotationAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateStaticHatchFromObject(CALLBACKPTR, MCObjectHandle inObj, const InternalName& name, const WorldPt& inOriginPoint, double_param inRotationAngle)
{
	GET_CB_UPP(CreateStaticHatchFromObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateStaticHatchFromObjectPtr)(MCObjectHandle inObj, const InternalName& name, const WorldPt& inOriginPoint, CBDouble_param inRotationAngle);
		MCObjectHandle gsResult = CALL_PROC(CreateStaticHatchFromObject)(inObj, name, inOriginPoint, inRotationAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_CreateSurfacefromCurvesNetwork(CALLBACKPTR)
{
	GET_CB_UPP(CreateSurfacefromCurvesNetwork);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateSurfacefromCurvesNetworkPtr)();
		Boolean gsResult = CALL_PROC(CreateSurfacefromCurvesNetwork)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_CreateSweepN(CALLBACKPTR, double_param startAngle, double_param arcAngle, double_param incrAngle, WorldCoord screwDist)
{
	GET_CB_UPP(CreateSweepN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateSweepNPtr)(CBDouble_param startAngle, CBDouble_param arcAngle, CBDouble_param incrAngle, CBWorldCoord_param screwDist);
		MCObjectHandle gsResult = CALL_PROC(CreateSweepN)(startAngle, arcAngle, incrAngle, screwDist);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateSymbolDefinition(CALLBACKPTR, const InternalName& name)
{
	GET_CB_UPP(CreateSymbolDefinition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateSymbolDefinitionPtr)(const InternalName& name);
		MCObjectHandle gsResult = CALL_PROC(CreateSymbolDefinition)(name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateSymbolFolder(CALLBACKPTR, const InternalName& name)
{
	GET_CB_UPP(CreateSymbolFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateSymbolFolderPtr)(const InternalName& name);
		MCObjectHandle gsResult = CALL_PROC(CreateSymbolFolder)(name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateTaperedExtrude(CALLBACKPTR, MCObjectHandle profileH, const double_param angle, const double_param height)
{
	GET_CB_UPP(CreateTaperedExtrude);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateTaperedExtrudePtr)(MCObjectHandle profileH, const double_param angle, const double_param height);
		MCObjectHandle gsResult = CALL_PROC(CreateTaperedExtrude)(profileH, angle, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_CreateTrapeziumDormer(CALLBACKPTR, MCObjectHandle object)
{
	GET_CB_UPP(CreateTrapeziumDormer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CreateTrapeziumDormerPtr)(MCObjectHandle object);
		short gsResult = CALL_PROC(CreateTrapeziumDormer)(object);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_CreateViewport(CALLBACKPTR, MCObjectHandle parentHandle)
{
	GET_CB_UPP(CreateViewport);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateViewportPtr)(MCObjectHandle parentHandle);
		MCObjectHandle gsResult = CALL_PROC(CreateViewport)(parentHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateWall(CALLBACKPTR, const WorldPt& startPt, const WorldPt& endPt, WorldCoord thickness)
{
	GET_CB_UPP(CreateWall);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateWallPtr)(const WorldPt& startPt, const WorldPt& endPt, CBWorldCoord_param thickness);
		MCObjectHandle gsResult = CALL_PROC(CreateWall)(startPt, endPt, thickness);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_DefineCustomObject(CALLBACKPTR, const InternalName& name, Byte prefWhen)
{
	GET_CB_UPP(DefineCustomObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*DefineCustomObjectPtr)(const InternalName& name, CBUnsignedByte prefWhen);
		MCObjectHandle gsResult = CALL_PROC(DefineCustomObject)(name, prefWhen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DuplicateSelection(CALLBACKPTR, WorldCoord dx, WorldCoord dy)
{
	GET_CB_UPP(DuplicateSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DuplicateSelectionPtr)(CBWorldCoord_param dx, CBWorldCoord_param dy);
		CALL_PROC(DuplicateSelection)(dx, dy);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_ExtendNurbsCurve(CALLBACKPTR, MCObjectHandle curveHandle, double_param distance, Boolean bStart, Boolean bLinear)
{
	GET_CB_UPP(ExtendNurbsCurve);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ExtendNurbsCurvePtr)(MCObjectHandle curveHandle, CBDouble_param distance, CBBoolean bStart, CBBoolean bLinear);
		MCObjectHandle gsResult = CALL_PROC(ExtendNurbsCurve)(curveHandle, distance, bStart, bLinear);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_ExtendNurbsSurface(CALLBACKPTR, MCObjectHandle surfaceHandle, double_param distance, Boolean bStart, Boolean bLinear, Boolean bUDir)
{
	GET_CB_UPP(ExtendNurbsSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ExtendNurbsSurfacePtr)(MCObjectHandle surfaceHandle, CBDouble_param distance, CBBoolean bStart, CBBoolean bLinear, CBBoolean bUDir);
		MCObjectHandle gsResult = CALL_PROC(ExtendNurbsSurface)(surfaceHandle, distance, bStart, bLinear, bUDir);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GenerateBezierApproximationFromPolygon(CALLBACKPTR, MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic)
{
	GET_CB_UPP(GenerateBezierApproximationFromPolygon);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GenerateBezierApproximationFromPolygonPtr)(MCObjectHandle hPolygonHandle, const WorldCoord approximationTolerance, const double discontinuityAngleTolerance, const unsigned short quadraticsPerCubic);
		MCObjectHandle gsResult = CALL_PROC(GenerateBezierApproximationFromPolygon)(hPolygonHandle, approximationTolerance, discontinuityAngleTolerance, quadraticsPerCubic);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return NULL;
}


MCObjectHandle GS_CALLBACK GS_GroupSelection(CALLBACKPTR)
{
	GET_CB_UPP(GroupSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GroupSelectionPtr)();
		MCObjectHandle gsResult = CALL_PROC(GroupSelection)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_IntersectSolid(CALLBACKPTR, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
{
	GET_CB_UPP(IntersectSolid);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*IntersectSolidPtr)(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		short gsResult = CALL_PROC(IntersectSolid)(obj1, obj2, newSolid);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


MCObjectHandle GS_CALLBACK GS_PlaceSymbolByNameN(CALLBACKPTR, const InternalName& symName, const WorldPt& location, double_param rotation)
{
	GET_CB_UPP(PlaceSymbolByNameN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*PlaceSymbolByNameNPtr)(const InternalName& symName, const WorldPt& location, CBDouble_param rotation);
		MCObjectHandle gsResult = CALL_PROC(PlaceSymbolByNameN)(symName, location, rotation);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_PlaceSymbolN(CALLBACKPTR, MCObjectHandle definition, const WorldPt& location, double_param rotation)
{
	GET_CB_UPP(PlaceSymbolN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*PlaceSymbolNPtr)(MCObjectHandle definition, const WorldPt& location, CBDouble_param rotation);
		MCObjectHandle gsResult = CALL_PROC(PlaceSymbolN)(definition, location, rotation);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_RevolveWithRail(CALLBACKPTR, MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH)
{
	GET_CB_UPP(RevolveWithRail);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*RevolveWithRailPtr)(MCObjectHandle profileH, MCObjectHandle railH, MCObjectHandle axisH);
		MCObjectHandle gsResult = CALL_PROC(RevolveWithRail)(profileH, railH, axisH);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_Split2DObjectByLine(CALLBACKPTR, MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles)
{
	GET_CB_UPP(Split2DObjectByLine);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Split2DObjectByLinePtr)(MCObjectHandle h, const WorldPt& p1, const WorldPt& p2, MCObjectHandle& listHandles);
		CALL_PROC(Split2DObjectByLine)(h, p1, p2, listHandles);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_SubtractSolid(CALLBACKPTR, MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid)
{
	GET_CB_UPP(SubtractSolid);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*SubtractSolidPtr)(MCObjectHandle obj1, MCObjectHandle obj2, MCObjectHandle& newSolid);
		short gsResult = CALL_PROC(SubtractSolid)(obj1, obj2, newSolid);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}




///////////////////////////////////////////
//  Dialogs
///////////////////////////////////////////


void GS_CALLBACK GS_AddChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short nItemIndex)
{
	GET_CB_UPP(AddChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddChoicePtr)(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, CBSignedShort nItemIndex);
		CALL_PROC(AddChoice)(dialogID, itemID, strItemText, nItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_AddListBoxTabStop(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 tabStop)
{
	GET_CB_UPP(AddListBoxTabStop);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddListBoxTabStopPtr)(Sint32 dialogID, Sint32 componentID, Sint32 tabStop);
		CALL_PROC(AddListBoxTabStop)(dialogID, componentID, tabStop);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_AddListBrowserImage(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short resourceType, short resourceID, short resourceIDSelected)
{
	GET_CB_UPP(AddListBrowserImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*AddListBrowserImagePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort resourceType, CBSignedShort resourceID, CBSignedShort resourceIDSelected);
		short gsResult = CALL_PROC(AddListBrowserImage)(dialogID, componentID, resourceType, resourceID, resourceIDSelected);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_AdjustComponentPixelPos(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nHorizontalPixels, Sint32 nVerticalPixels)
{
	GET_CB_UPP(AdjustComponentPixelPos);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AdjustComponentPixelPosPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nHorizontalPixels, Sint32 nVerticalPixels);
		Boolean gsResult = CALL_PROC(AdjustComponentPixelPos)(nDialogID, nComponentID, nHorizontalPixels, nVerticalPixels);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_AlertCritical(CALLBACKPTR, const TXString& text, const TXString& advice)
{
	GET_CB_UPP(AlertCritical);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AlertCriticalPtr)(const TXString& text, const TXString& advice);
		CALL_PROC(AlertCritical)(text, advice);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_AlertInform(CALLBACKPTR, const TXString& text, const TXString& advice, CBBoolean minorAlert, const TXString& category, const TXString& item, const TXString& checkboxOverideText)
{
	GET_CB_UPP(AlertInform);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AlertInformPtr)(const TXString& text, const TXString& advice, CBBoolean minorAlert, const TXString& category, const TXString& item, const TXString& checkboxOverideText);
		CALL_PROC(AlertInform)(text, advice, minorAlert, category, item, checkboxOverideText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_AlertQuestion(CALLBACKPTR, const TXString& question, const TXString& advice, short defaultButton, const TXString& OKOverrideText, const TXString& cancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverideText)
{
	GET_CB_UPP(AlertQuestion);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*AlertQuestionPtr)(const TXString& question, const TXString& advice, CBSignedShort defaultButton, const TXString& OKOverrideText, const TXString& cancelOverrideText, const TXString& customButtonAText, const TXString& customButtonBText, const TXString& category, const TXString& item, const TXString& checkboxOverideText);
		short gsResult = CALL_PROC(AlertQuestion)(question, advice, defaultButton, OKOverrideText, cancelOverrideText, customButtonAText, customButtonBText, category, item, checkboxOverideText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


bool GS_CALLBACK GS_AlignBottomEdge(CALLBACKPTR, Sint32 dialogID, Sint32 srcItemID, short bottomID, short alignMode)
{
	GET_CB_UPP(AlignBottomEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*AlignBottomEdgePtr)(Sint32 dialogID, Sint32 srcItemID, CBSignedShort bottomID, CBSignedShort alignMode);
		bool gsResult = CALL_PROC(AlignBottomEdge)(dialogID, srcItemID, bottomID, alignMode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_AlignLeftEdge(CALLBACKPTR, Sint32 dialogID, Sint32 srcItemID, short leftID, short alignMode)
{
	GET_CB_UPP(AlignLeftEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*AlignLeftEdgePtr)(Sint32 dialogID, Sint32 srcItemID, CBSignedShort leftID, CBSignedShort alignMode);
		bool gsResult = CALL_PROC(AlignLeftEdge)(dialogID, srcItemID, leftID, alignMode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_AlignRightEdge(CALLBACKPTR, Sint32 dialogID, Sint32 srcItemID, short rightID, short alignMode)
{
	GET_CB_UPP(AlignRightEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*AlignRightEdgePtr)(Sint32 dialogID, Sint32 srcItemID, CBSignedShort rightID, CBSignedShort alignMode);
		bool gsResult = CALL_PROC(AlignRightEdge)(dialogID, srcItemID, rightID, alignMode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AreListBrowserColumnLinesEnabled(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(AreListBrowserColumnLinesEnabled);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AreListBrowserColumnLinesEnabledPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(AreListBrowserColumnLinesEnabled)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AreListBrowserRadioColumnLinesEnabled(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(AreListBrowserRadioColumnLinesEnabled);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AreListBrowserRadioColumnLinesEnabledPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		Boolean gsResult = CALL_PROC(AreListBrowserRadioColumnLinesEnabled)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_ClearGradientSliderSegments(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(ClearGradientSliderSegments);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ClearGradientSliderSegmentsPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(ClearGradientSliderSegments)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_Confirm(CALLBACKPTR, const TXString& strNode, Boolean yesOrNo)
{
	GET_CB_UPP(Confirm);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ConfirmPtr)(const TXString& strNode, CBBoolean yesOrNo);
		Boolean gsResult = CALL_PROC(Confirm)(strNode, yesOrNo);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateCenteredStaticText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
{
	GET_CB_UPP(CreateCenteredStaticText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateCenteredStaticTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& text, CBSignedShort widthInStdChar);
		CALL_PROC(CreateCenteredStaticText)(dialogID, itemID, text, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateCheckBox(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& name)
{
	GET_CB_UPP(CreateCheckBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateCheckBoxPtr)(Sint32 dialogID, Sint32 itemID, const TXString& name);
		CALL_PROC(CreateCheckBox)(dialogID, itemID, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateCheckBoxGroupBox(CALLBACKPTR, Sint32 dialogID, short itemID, const TXString& name, bool hasFrame)
{
	GET_CB_UPP(CreateCheckBoxGroupBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateCheckBoxGroupBoxPtr)(Sint32 dialogID, CBSignedShort itemID, const TXString& name, bool hasFrame);
		CALL_PROC(CreateCheckBoxGroupBox)(dialogID, itemID, name, hasFrame);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateClassPullDownMenu(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar)
{
	GET_CB_UPP(CreateClassPullDownMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateClassPullDownMenuPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		Boolean gsResult = CALL_PROC(CreateClassPullDownMenu)(nDialogID, nComponentID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateCMYKColorSwatch(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateCMYKColorSwatch);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateCMYKColorSwatchPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateCMYKColorSwatch)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateColorPopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short widthInStdChar)
{
	GET_CB_UPP(CreateColorPopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateColorPopupPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort widthInStdChar);
		CALL_PROC(CreateColorPopup)(dialogID, itemID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateControl(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data)
{
	GET_CB_UPP(CreateControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateControlPtr)(Sint32 dialogID, Sint32 itemID, Sint32 controlKind, const TXString& name, SintptrT data);
		CALL_PROC(CreateControl)(dialogID, itemID, controlKind, name, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateCustomControl(CALLBACKPTR, Sint32 dlogID, Sint32 controlID, short width, short length)
{
	GET_CB_UPP(CreateCustomControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateCustomControlPtr)(Sint32 dlogID, Sint32 controlID, CBSignedShort width, CBSignedShort length);
		CALL_PROC(CreateCustomControl)(dlogID, controlID, width, length);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateDesignLayerPullDownMenu(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar)
{
	GET_CB_UPP(CreateDesignLayerPullDownMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateDesignLayerPullDownMenuPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		Boolean gsResult = CALL_PROC(CreateDesignLayerPullDownMenu)(nDialogID, nComponentID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateEditInteger(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, short widthInStdChar)
{
	GET_CB_UPP(CreateEditInteger);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateEditIntegerPtr)(Sint32 dialogID, Sint32 itemID, Sint32 defaultValue, CBSignedShort widthInStdChar);
		CALL_PROC(CreateEditInteger)(dialogID, itemID, defaultValue, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateEditReal(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, short widthInStdChar)
{
	GET_CB_UPP(CreateEditReal);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateEditRealPtr)(Sint32 dialogID, Sint32 itemID, Sint32 editRealType, double value, CBSignedShort widthInStdChar);
		CALL_PROC(CreateEditReal)(dialogID, itemID, editRealType, value, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateEditText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& defaultText, short widthInStdChar, short heightInLines)
{
	GET_CB_UPP(CreateEditText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateEditTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& defaultText, CBSignedShort widthInStdChar, CBSignedShort heightInLines);
		CALL_PROC(CreateEditText)(dialogID, itemID, defaultText, widthInStdChar, heightInLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateEnhancedPullDownMenu(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, Boolean bShowIconInMainWindow)
{
	GET_CB_UPP(CreateEnhancedPullDownMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateEnhancedPullDownMenuPtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, CBBoolean bShowIconInMainWindow);
		Boolean gsResult = CALL_PROC(CreateEnhancedPullDownMenu)(liDialogID, liComponentID, widthInStdChar, bShowIconInMainWindow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateGroupBox(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& name, Boolean hasFrame)
{
	GET_CB_UPP(CreateGroupBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateGroupBoxPtr)(Sint32 dialogID, Sint32 itemID, const TXString& name, CBBoolean hasFrame);
		CALL_PROC(CreateGroupBox)(dialogID, itemID, name, hasFrame);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateIconPushButton(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nIconID, Sint32 widthInStdChar)
{
	GET_CB_UPP(CreateIconPushButton);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateIconPushButtonPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nIconID, Sint32 widthInStdChar);
		Boolean gsResult = CALL_PROC(CreateIconPushButton)(nDialogID, nComponentID, nIconID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CreateImageControl(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 iWidthPixels, Sint32 iHeightPixels, MCObjectHandle hImage)
{
	GET_CB_UPP(CreateImageControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateImageControlPtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 iWidthPixels, Sint32 iHeightPixels, MCObjectHandle hImage);
		Boolean gsResult = CALL_PROC(CreateImageControl)(liDialogID, liComponentID, iWidthPixels, iHeightPixels, hImage);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_CreateLayout(CALLBACKPTR, const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName)
{
	GET_CB_UPP(CreateLayout);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*CreateLayoutPtr)(const TXString& dialogTitle, CBBoolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName);
		Sint32 gsResult = CALL_PROC(CreateLayout)(dialogTitle, hasHelp, defaultButtonName, cancelButtonName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_CreateLineAttributePopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateLineAttributePopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateLineAttributePopupPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateLineAttributePopup)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateLineStylePopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateLineStylePopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateLineStylePopupPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateLineStylePopup)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateLineWeightPopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateLineWeightPopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateLineWeightPopupPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateLineWeightPopup)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateListBox(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines)
{
	GET_CB_UPP(CreateListBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateListBoxPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort widthInStdChar, CBSignedShort heightInLines);
		CALL_PROC(CreateListBox)(dialogID, itemID, widthInStdChar, heightInLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateListBoxN(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short widthInStdChar, short heightInLines, Boolean isMultiSel)
{
	GET_CB_UPP(CreateListBoxN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateListBoxNPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort widthInStdChar, CBSignedShort heightInLines, CBBoolean isMultiSel);
		CALL_PROC(CreateListBoxN)(dialogID, itemID, widthInStdChar, heightInLines, isMultiSel);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateListBrowser(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, CBSignedShort widthInStdChar, CBSignedShort heightInLines)
{
	GET_CB_UPP(CreateListBrowser);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateListBrowserPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort widthInStdChar, CBSignedShort heightInLines);
		CALL_PROC(CreateListBrowser)(dialogID, componentID, widthInStdChar, heightInLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateMarkerPopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateMarkerPopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateMarkerPopupPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateMarkerPopup)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreatePatternPopup(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreatePatternPopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreatePatternPopupPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreatePatternPopup)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreatePullDownMenu(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short widthInStdChar)
{
	GET_CB_UPP(CreatePullDownMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreatePullDownMenuPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort widthInStdChar);
		CALL_PROC(CreatePullDownMenu)(dialogID, itemID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreatePullDownMenuGroupBox(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, const TXString& strLabel, Boolean bHasFrame)
{
	GET_CB_UPP(CreatePullDownMenuGroupBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreatePullDownMenuGroupBoxPtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 widthInStdChar, const TXString& strLabel, CBBoolean bHasFrame);
		Boolean gsResult = CALL_PROC(CreatePullDownMenuGroupBox)(liDialogID, liComponentID, widthInStdChar, strLabel, bHasFrame);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreatePushButton(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& buttonName)
{
	GET_CB_UPP(CreatePushButton);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreatePushButtonPtr)(Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		CALL_PROC(CreatePushButton)(dialogID, itemID, buttonName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateRadioButton(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& buttonName)
{
	GET_CB_UPP(CreateRadioButton);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateRadioButtonPtr)(Sint32 dialogID, Sint32 itemID, const TXString& buttonName);
		CALL_PROC(CreateRadioButton)(dialogID, itemID, buttonName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateRadioButtonGroupBox(CALLBACKPTR, Sint32 dialogID, short itemID, const TXString& name, bool hasFrame)
{
	GET_CB_UPP(CreateRadioButtonGroupBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateRadioButtonGroupBoxPtr)(Sint32 dialogID, CBSignedShort itemID, const TXString& name, bool hasFrame);
		CALL_PROC(CreateRadioButtonGroupBox)(dialogID, itemID, name, hasFrame);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_CreateResizableLayout(CALLBACKPTR, const TXString& dialogTitle, Boolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, CBBoolean widthResizable, CBBoolean heightResizable)
{
	GET_CB_UPP(CreateResizableLayout);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*CreateResizableLayoutPtr)(const TXString& dialogTitle, CBBoolean hasHelp, const TXString& defaultButtonName, const TXString& cancelButtonName, CBBoolean widthResizable, CBBoolean heightResizable);
		Sint32 gsResult = CALL_PROC(CreateResizableLayout)(dialogTitle, hasHelp, defaultButtonName, cancelButtonName, widthResizable, heightResizable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_CreateRightStaticText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
{
	GET_CB_UPP(CreateRightStaticText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateRightStaticTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& text, CBSignedShort widthInStdChar);
		CALL_PROC(CreateRightStaticText)(dialogID, itemID, text, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateSeparator(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 iLength)
{
	GET_CB_UPP(CreateSeparator);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateSeparatorPtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 iLength);
		Boolean gsResult = CALL_PROC(CreateSeparator)(liDialogID, liComponentID, iLength);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CreateSheetLayerPullDownMenu(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar)
{
	GET_CB_UPP(CreateSheetLayerPullDownMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateSheetLayerPullDownMenuPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar);
		Boolean gsResult = CALL_PROC(CreateSheetLayerPullDownMenu)(nDialogID, nComponentID, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateStandardIconControl(CALLBACKPTR, Sint32 dialogID, Sint32 iconControlID, Sint32 iconNumber)
{
	GET_CB_UPP(CreateStandardIconControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateStandardIconControlPtr)(Sint32 dialogID, Sint32 iconControlID, Sint32 iconNumber);
		CALL_PROC(CreateStandardIconControl)(dialogID, iconControlID, iconNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateStaticText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& text, short widthInStdChar)
{
	GET_CB_UPP(CreateStaticText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateStaticTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& text, CBSignedShort widthInStdChar);
		CALL_PROC(CreateStaticText)(dialogID, itemID, text, widthInStdChar);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateSwapControl(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(CreateSwapControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateSwapControlPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(CreateSwapControl)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateSwapPane(CALLBACKPTR, Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID)
{
	GET_CB_UPP(CreateSwapPane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateSwapPanePtr)(Sint32 dialogID, Sint32 swapControlID, Sint32 newGroupID);
		CALL_PROC(CreateSwapPane)(dialogID, swapControlID, newGroupID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateTabControl(CALLBACKPTR, Sint32 dialogID, short itemID)
{
	GET_CB_UPP(CreateTabControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateTabControlPtr)(Sint32 dialogID, CBSignedShort itemID);
		CALL_PROC(CreateTabControl)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_CreateTabPane(CALLBACKPTR, Sint32 dialogID, short itemID, short groupID)
{
	GET_CB_UPP(CreateTabPane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateTabPanePtr)(Sint32 dialogID, CBSignedShort itemID, CBSignedShort groupID);
		CALL_PROC(CreateTabPane)(dialogID, itemID, groupID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CreateThreeStateCheckBox(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, const TXString& strName)
{
	GET_CB_UPP(CreateThreeStateCheckBox);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateThreeStateCheckBoxPtr)(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName);
		Boolean gsResult = CALL_PROC(CreateThreeStateCheckBox)(liDialogID, liComponentID, strName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CreateTreeControl(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar, Sint32 heightInLines)
{
	GET_CB_UPP(CreateTreeControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CreateTreeControlPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 widthInStdChar, Sint32 heightInLines);
		Boolean gsResult = CALL_PROC(CreateTreeControl)(nDialogID, nComponentID, widthInStdChar, heightInLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_DeleteAllItems(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(DeleteAllItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteAllItemsPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(DeleteAllItems)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_DeleteAllListBrowserItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(DeleteAllListBrowserItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteAllListBrowserItemsPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(DeleteAllListBrowserItems)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_DeleteListBrowserColumn(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(DeleteListBrowserColumn);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteListBrowserColumnPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		Boolean gsResult = CALL_PROC(DeleteListBrowserColumn)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_DeleteListBrowserItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex)
{
	GET_CB_UPP(DeleteListBrowserItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteListBrowserItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex);
		Boolean gsResult = CALL_PROC(DeleteListBrowserItem)(dialogID, componentID, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_DeselectEditText(CALLBACKPTR, Sint32 dialogID, Sint32 controlID)
{
	GET_CB_UPP(DeselectEditText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeselectEditTextPtr)(Sint32 dialogID, Sint32 controlID);
		CALL_PROC(DeselectEditText)(dialogID, controlID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_DisplayColorPopup(CALLBACKPTR, Sint32 top, Sint32 left, Sint32 bottom, Sint32 right, Boolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass)
{
	GET_CB_UPP(DisplayColorPopup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DisplayColorPopupPtr)(Sint32 top, Sint32 left, Sint32 bottom, Sint32 right, CBBoolean inDisplayByClassOption, ColorRef& ioColorRef, Boolean& ioIsByClass);
		Boolean gsResult = CALL_PROC(DisplayColorPopup)(top, left, bottom, right, inDisplayByClassOption, ioColorRef, ioIsByClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_DisplaySwapPane(CALLBACKPTR, Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber)
{
	GET_CB_UPP(DisplaySwapPane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisplaySwapPanePtr)(Sint32 dialogID, Sint32 swapControlID, Sint32 groupNumber);
		CALL_PROC(DisplaySwapPane)(dialogID, swapControlID, groupNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DisplayTabPane(CALLBACKPTR, Sint32 dialogID, Sint32 controlID, Sint32 groupNumber)
{
	GET_CB_UPP(DisplayTabPane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisplayTabPanePtr)(Sint32 dialogID, Sint32 controlID, Sint32 groupNumber);
		CALL_PROC(DisplayTabPane)(dialogID, controlID, groupNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_EnableItem(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Boolean bEnable)
{
	GET_CB_UPP(EnableItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableItemPtr)(Sint32 dialogID, Sint32 itemID, CBBoolean bEnable);
		CALL_PROC(EnableItem)(dialogID, itemID, bEnable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EnableListBrowser(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean enable)
{
	GET_CB_UPP(EnableListBrowser);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserPtr)(Sint32 dialogID, Sint32 componentID, CBBoolean enable);
		Boolean gsResult = CALL_PROC(EnableListBrowser)(dialogID, componentID, enable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_EnableListBrowserClickAllDataChange(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean enable)
{
	GET_CB_UPP(EnableListBrowserClickAllDataChange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserClickAllDataChangePtr)(Sint32 dialogID, Sint32 componentID, CBBoolean enable);
		Boolean gsResult = CALL_PROC(EnableListBrowserClickAllDataChange)(dialogID, componentID, enable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_EnableListBrowserColumnLines(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean enableColumnLines)
{
	GET_CB_UPP(EnableListBrowserColumnLines);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableListBrowserColumnLinesPtr)(Sint32 dialogID, Sint32 componentID, CBBoolean enableColumnLines);
		CALL_PROC(EnableListBrowserColumnLines)(dialogID, componentID, enableColumnLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_EnableListBrowserColumnTracking(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableColumnTracking)
{
	GET_CB_UPP(EnableListBrowserColumnTracking);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableListBrowserColumnTrackingPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBBoolean enableColumnTracking);
		CALL_PROC(EnableListBrowserColumnTracking)(dialogID, componentID, columnIndex, enableColumnTracking);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EnableListBrowserDragAndDrop(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean bEnable)
{
	GET_CB_UPP(EnableListBrowserDragAndDrop);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserDragAndDropPtr)(Sint32 dialogID, Sint32 componentID, CBBoolean bEnable);
		Boolean gsResult = CALL_PROC(EnableListBrowserDragAndDrop)(dialogID, componentID, bEnable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_EnableListBrowserDropOnIndices(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartIndex, Sint32 iEndIndex, Boolean bEnable)
{
	GET_CB_UPP(EnableListBrowserDropOnIndices);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserDropOnIndicesPtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartIndex, Sint32 iEndIndex, CBBoolean bEnable);
		Boolean gsResult = CALL_PROC(EnableListBrowserDropOnIndices)(liDialogID, liComponentID, iStartIndex, iEndIndex, bEnable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_EnableListBrowserRadioColumnLines(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, Boolean enableRadioColumnLines)
{
	GET_CB_UPP(EnableListBrowserRadioColumnLines);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableListBrowserRadioColumnLinesPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBBoolean enableRadioColumnLines);
		CALL_PROC(EnableListBrowserRadioColumnLines)(dialogID, componentID, columnIndex, enableRadioColumnLines);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EnableListBrowserSingleLineSelection(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean enable)
{
	GET_CB_UPP(EnableListBrowserSingleLineSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserSingleLineSelectionPtr)(Sint32 dialogID, Sint32 componentID, CBBoolean enable);
		Boolean gsResult = CALL_PROC(EnableListBrowserSingleLineSelection)(dialogID, componentID, enable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_EnableListBrowserSorting(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Boolean enableSorting)
{
	GET_CB_UPP(EnableListBrowserSorting);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableListBrowserSortingPtr)(Sint32 dialogID, Sint32 componentID, CBBoolean enableSorting);
		CALL_PROC(EnableListBrowserSorting)(dialogID, componentID, enableSorting);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EnableListBrowserUpdates(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Boolean bEnableUpdates)
{
	GET_CB_UPP(EnableListBrowserUpdates);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnableListBrowserUpdatesPtr)(Sint32 liDialogID, Sint32 liComponentID, CBBoolean bEnableUpdates);
		Boolean gsResult = CALL_PROC(EnableListBrowserUpdates)(liDialogID, liComponentID, bEnableUpdates);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_EnsureListBrowserItemIsVisible(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iIndex)
{
	GET_CB_UPP(EnsureListBrowserItemIsVisible);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EnsureListBrowserItemIsVisiblePtr)(Sint32 dialogID, Sint32 componentID, Sint32 iIndex);
		Boolean gsResult = CALL_PROC(EnsureListBrowserItemIsVisible)(dialogID, componentID, iIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_ExpandTreeControlItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Boolean bExpand)
{
	GET_CB_UPP(ExpandTreeControlItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ExpandTreeControlItemPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, CBBoolean bExpand);
		Boolean gsResult = CALL_PROC(ExpandTreeControlItem)(nDialogID, nComponentID, nItemID, bExpand);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_FindListBrowserColumnDataItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& columnDataItemIndex)
{
	GET_CB_UPP(FindListBrowserColumnDataItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*FindListBrowserColumnDataItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, const TXString& itemString, short& columnDataItemIndex);
		Boolean gsResult = CALL_PROC(FindListBrowserColumnDataItem)(dialogID, componentID, columnIndex, itemString, columnDataItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_FindListBrowserColumnItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short& itemIndex)
{
	GET_CB_UPP(FindListBrowserColumnItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*FindListBrowserColumnItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, const TXString& itemString, short& itemIndex);
		Boolean gsResult = CALL_PROC(FindListBrowserColumnItem)(dialogID, componentID, columnIndex, itemString, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_FormatTextDialog(CALLBACKPTR, FormatTextType& formatTextRec)
{
	GET_CB_UPP(FormatTextDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*FormatTextDialogPtr)(FormatTextType& formatTextRec);
		CALL_PROC(FormatTextDialog)(formatTextRec);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_GetActiveEditItem(CALLBACKPTR, Sint32 dialogID)
{
	GET_CB_UPP(GetActiveEditItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetActiveEditItemPtr)(Sint32 dialogID);
		Sint32 gsResult = CALL_PROC(GetActiveEditItem)(dialogID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Sint32 GS_CALLBACK GS_GetActivePane(CALLBACKPTR, Sint32 dialogID, Sint32 controlID)
{
	GET_CB_UPP(GetActivePane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetActivePanePtr)(Sint32 dialogID, Sint32 controlID);
		Sint32 gsResult = CALL_PROC(GetActivePane)(dialogID, controlID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_GetBooleanItem(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Boolean& state)
{
	GET_CB_UPP(GetBooleanItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetBooleanItemPtr)(Sint32 dialogID, Sint32 itemID, Boolean& state);
		CALL_PROC(GetBooleanItem)(dialogID, itemID, state);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetChoiceCount(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short& numItems)
{
	GET_CB_UPP(GetChoiceCount);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetChoiceCountPtr)(Sint32 dialogID, Sint32 itemID, short& numItems);
		CALL_PROC(GetChoiceCount)(dialogID, itemID, numItems);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetChoiceIndex(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex)
{
	GET_CB_UPP(GetChoiceIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetChoiceIndexPtr)(Sint32 dialogID, Sint32 itemID, const TXString& strItemText, short& nItemIndex);
		CALL_PROC(GetChoiceIndex)(dialogID, itemID, strItemText, nItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetChoiceText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short nItemIndex, TXString& strItemText)
{
	GET_CB_UPP(GetChoiceText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetChoiceTextPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort nItemIndex, TXString& strItemText);
		CALL_PROC(GetChoiceText)(dialogID, itemID, nItemIndex, strItemText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetCMYKColor(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor)
{
	GET_CB_UPP(GetCMYKColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetCMYKColorPtr)(Sint32 dialogID, Sint32 itemID, TGSColorV2 &outColor);
		CALL_PROC(GetCMYKColor)(dialogID, itemID, outColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetColorButton(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, RGBColor& rgb)
{
	GET_CB_UPP(GetColorButton);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetColorButtonPtr)(Sint32 dialogID, Sint32 itemID, RGBColor& rgb);
		CALL_PROC(GetColorButton)(dialogID, itemID, rgb);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetColorChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short& colorIndex)
{
	GET_CB_UPP(GetColorChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetColorChoicePtr)(Sint32 dialogID, Sint32 itemID, short& colorIndex);
		CALL_PROC(GetColorChoice)(dialogID, itemID, colorIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetComponentRect(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32& nLeft, Sint32& nTop, Sint32& nRight, Sint32& nBottom)
{
	GET_CB_UPP(GetComponentRect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentRectPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32& nLeft, Sint32& nTop, Sint32& nRight, Sint32& nBottom);
		Boolean gsResult = CALL_PROC(GetComponentRect)(nDialogID, nComponentID, nLeft, nTop, nRight, nBottom);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetComponentTextWidth(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32& nWidthInLMUnits)
{
	GET_CB_UPP(GetComponentTextWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentTextWidthPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32& nWidthInLMUnits);
		Boolean gsResult = CALL_PROC(GetComponentTextWidth)(nDialogID, nComponentID, nWidthInLMUnits);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetControlData(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, SControlDataBase& data)
{
	GET_CB_UPP(GetControlData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetControlDataPtr)(Sint32 dialogID, Sint32 itemID, SControlDataBase& data);
		CALL_PROC(GetControlData)(dialogID, itemID, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetCustomControlScrollArea(CALLBACKPTR, Sint32 dialogID, Sint32 component, Sint32 *leftStart, Sint32 *topStart)
{
	GET_CB_UPP(GetCustomControlScrollArea);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetCustomControlScrollAreaPtr)(Sint32 dialogID, Sint32 component, Sint32 *leftStart, Sint32 *topStart);
		CALL_PROC(GetCustomControlScrollArea)(dialogID, component, leftStart, topStart);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


bool GS_CALLBACK GS_GetEditInteger(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32& value)
{
	GET_CB_UPP(GetEditInteger);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*GetEditIntegerPtr)(Sint32 dialogID, Sint32 componentID, Sint32& value);
		bool gsResult = CALL_PROC(GetEditInteger)(dialogID, componentID, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_GetEditReal(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short editRealType, double& value)
{
	GET_CB_UPP(GetEditReal);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*GetEditRealPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort editRealType, double& value);
		bool gsResult = CALL_PROC(GetEditReal)(dialogID, componentID, editRealType, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetGradientSliderData(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color)
{
	GET_CB_UPP(GetGradientSliderData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGradientSliderDataPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		Boolean gsResult = CALL_PROC(GetGradientSliderData)(dialogID, componentID, segmentIndex, spotPosition, midpointPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetGradientSliderSelectedMarker(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType)
{
	GET_CB_UPP(GetGradientSliderSelectedMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGradientSliderSelectedMarkerPtr)(Sint32 dialogID, Sint32 componentID, short& segmentIndex, short& markerType);
		Boolean gsResult = CALL_PROC(GetGradientSliderSelectedMarker)(dialogID, componentID, segmentIndex, markerType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetIconPushButtonState(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed)
{
	GET_CB_UPP(GetIconPushButtonState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetIconPushButtonStatePtr)(Sint32 nDialogID, Sint32 nComponentID, Boolean& bPressed);
		Boolean gsResult = CALL_PROC(GetIconPushButtonState)(nDialogID, nComponentID, bPressed);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetImagePopupObject(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex)
{
	GET_CB_UPP(GetImagePopupObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetImagePopupObjectPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex);
		InternalIndex gsResult = CALL_PROC(GetImagePopupObject)(dialogID, componentID, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetImagePopupObjectItemIndex(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
{
	GET_CB_UPP(GetImagePopupObjectItemIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetImagePopupObjectItemIndexPtr)(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		short gsResult = CALL_PROC(GetImagePopupObjectItemIndex)(dialogID, componentID, objectIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetImagePopupSelectedItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetImagePopupSelectedItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetImagePopupSelectedItemPtr)(Sint32 dialogID, Sint32 componentID);
		short gsResult = CALL_PROC(GetImagePopupSelectedItem)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetItemText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, TXString& strCurrentText)
{
	GET_CB_UPP(GetItemText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetItemTextPtr)(Sint32 dialogID, Sint32 itemID, TXString& strCurrentText);
		CALL_PROC(GetItemText)(dialogID, itemID, strCurrentText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetLayoutDialogPosition(CALLBACKPTR, Sint32 dialogID, short& left, short& top, short& right, short& bottom)
{
	GET_CB_UPP(GetLayoutDialogPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLayoutDialogPositionPtr)(Sint32 dialogID, short& left, short& top, short& right, short& bottom);
		Boolean gsResult = CALL_PROC(GetLayoutDialogPosition)(dialogID, left, top, right, bottom);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetLayoutDialogSize(CALLBACKPTR, Sint32 dialogID, short& width, short& height)
{
	GET_CB_UPP(GetLayoutDialogSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetLayoutDialogSizePtr)(Sint32 dialogID, short& width, short& height);
		CALL_PROC(GetLayoutDialogSize)(dialogID, width, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}

#if _MINICAD_
#define DEFAULTVWRIDENTIFIER "Vectorworks"
#else
#define DEFAULTVWRIDENTIFIER DefaultPluginVWRIdentifier()
#endif

Sint32 GS_CALLBACK GS_GetLayoutFromRsrc(CALLBACKPTR, short textRsrcID)
{
	const char *vwr = DEFAULTVWRIDENTIFIER; 
	gSDK->Kludge(3602, (void *)vwr, NULL); 
	char resID[128]; 
	sprintf(resID, "%s/DialogLayout/%d *", vwr, textRsrcID); 
	return gSDK->CreateLayoutDialogFromVWResource(resID);
}


Sint32 GS_CALLBACK GS_GetLBHeaderTextWidth(CALLBACKPTR, const TXString& str, bool allowForSortingTriangle)
{
	GET_CB_UPP(GetLBHeaderTextWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetLBHeaderTextWidthPtr)(const TXString& str, bool allowForSortingTriangle);
		Sint32 gsResult = CALL_PROC(GetLBHeaderTextWidth)(str, allowForSortingTriangle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}



void GS_CALLBACK GS_GetLineWeightChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short& lineWeight)
{
	GET_CB_UPP(GetLineWeightChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetLineWeightChoicePtr)(Sint32 dialogID, Sint32 itemID, short& lineWeight);
		CALL_PROC(GetLineWeightChoice)(dialogID, itemID, lineWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetListBrowserColumnWidth(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short& width)
{
	GET_CB_UPP(GetListBrowserColumnWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserColumnWidthPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, short& width);
		Boolean gsResult = CALL_PROC(GetListBrowserColumnWidth)(dialogID, componentID, columnIndex, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserColumnDataItemInfo(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex, TXString&  itemString, short &imageOn, short &imageOff, Sint32 &itemData)
{
	GET_CB_UPP(GetListBrowserColumnDataItemInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserColumnDataItemInfoPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBSignedShort columnDataItemIndex, TXString&  itemString, short &imageOn, short &imageOff, Sint32 &itemData);
		Boolean gsResult = CALL_PROC(GetListBrowserColumnDataItemInfo)(dialogID, componentID, columnIndex, columnDataItemIndex, itemString, imageOn, imageOff, itemData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_GetListBrowserColumnSortState(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 columnIndex)
{
	GET_CB_UPP(GetListBrowserColumnSortState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetListBrowserColumnSortStatePtr)(Sint32 dialogID, Sint32 componentID, Sint32 columnIndex);
		Sint32 gsResult = CALL_PROC(GetListBrowserColumnSortState)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_GetListBrowserColumnOwnerDrawnType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 &iOwnerDrawnType)
{
	GET_CB_UPP(GetListBrowserColumnOwnerDrawnType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserColumnOwnerDrawnTypePtr)(Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 &iOwnerDrawnType);
		Boolean gsResult = CALL_PROC(GetListBrowserColumnOwnerDrawnType)(dialogID, componentID, iIndex, iSubIndex, iOwnerDrawnType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserColumnHeaderToolTip(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText)
{
	GET_CB_UPP(GetListBrowserColumnHeaderToolTip);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserColumnHeaderToolTipPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, TXString& strToolTipPrimaryText, TXString& strToolTipSubText);
		Boolean gsResult = CALL_PROC(GetListBrowserColumnHeaderToolTip)(dialogID, componentID, iColumnIndex, strToolTipPrimaryText, strToolTipSubText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserColumnHeaderJust(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 &iJustification)
{
	GET_CB_UPP(GetListBrowserColumnHeaderJust);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserColumnHeaderJustPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 &iJustification);
		Boolean gsResult = CALL_PROC(GetListBrowserColumnHeaderJust)(dialogID, componentID, iColumnIndex, iJustification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_GetListBrowserControlType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(GetListBrowserControlType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetListBrowserControlTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		short gsResult = CALL_PROC(GetListBrowserControlType)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetListBrowserEditDisplayType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(GetListBrowserEditDisplayType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetListBrowserEditDisplayTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		short gsResult = CALL_PROC(GetListBrowserEditDisplayType)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetListBrowserEventInfo(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32& iEventType, Sint32& iRowIndex, Sint32& iColumnIndex)
{
	GET_CB_UPP(GetListBrowserEventInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserEventInfoPtr)(Sint32 dialogID, Sint32 componentID, Sint32& iEventType, Sint32& iRowIndex, Sint32& iColumnIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserEventInfo)(dialogID, componentID, iEventType, iRowIndex, iColumnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_GetListBrowserItemData(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32& nUserData)
{
	GET_CB_UPP(GetListBrowserItemData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemDataPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32& nUserData);
		Boolean gsResult = CALL_PROC(GetListBrowserItemData)(nDialogID, nComponentID, nItemIndex, nSubItemIndex, nUserData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_GetListBrowserItemDisplayType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(GetListBrowserItemDisplayType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetListBrowserItemDisplayTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		short gsResult = CALL_PROC(GetListBrowserItemDisplayType)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetListBrowserItemFillForeColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex)
{
	GET_CB_UPP(GetListBrowserItemFillForeColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemFillForeColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemFillForeColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemFillBackColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex)
{
	GET_CB_UPP(GetListBrowserItemFillBackColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemFillBackColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemFillBackColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemGradientOrImageRefNumber(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &liRefNumber)
{
	GET_CB_UPP(GetListBrowserItemGradientOrImageRefNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemGradientOrImageRefNumberPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &liRefNumber);
		Boolean gsResult = CALL_PROC(GetListBrowserItemGradientOrImageRefNumber)(dialogID, componentID, iItemIndex, iSubItemIndex, liRefNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemInfo(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, TXString&  itemString, short& imageIndex)
{
	GET_CB_UPP(GetListBrowserItemInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemInfoPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex, CBSignedShort subItemIndex, TXString&  itemString, short& imageIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemInfo)(dialogID, componentID, itemIndex, subItemIndex, itemString, imageIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


#if _WINDOWS
Boolean GS_CALLBACK GS_GetListBrowserItemPatternIndex(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iPatternIndex)
{
	GET_CB_UPP(GetListBrowserItemPatternIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemPatternIndexPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iPatternIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemPatternIndex)(dialogID, componentID, iItemIndex, iSubItemIndex, iPatternIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}
#endif


#if !_WIN_EXTERNAL_ && !_GSWINSDK_
Boolean GS_CALLBACK GS_GetListBrowserItemPattern(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* &pPattern)
{
	GET_CB_UPP(GetListBrowserItemPattern);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemPatternPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* &pPattern);
		Boolean gsResult = CALL_PROC(GetListBrowserItemPattern)(dialogID, componentID, iItemIndex, iSubItemIndex, pPattern);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}
#endif


Boolean GS_CALLBACK GS_GetListBrowserItemPenForeColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex)
{
	GET_CB_UPP(GetListBrowserItemPenForeColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemPenForeColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemPenForeColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemPenBackColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex)
{
	GET_CB_UPP(GetListBrowserItemPenBackColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemPenBackColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 &iRedIndex, Sint32 &iGreenIndex, Sint32 &iBlueIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemPenBackColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemTextJust(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &justification)
{
	GET_CB_UPP(GetListBrowserItemTextJust);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemTextJustPtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &justification);
		Boolean gsResult = CALL_PROC(GetListBrowserItemTextJust)(dialogID, componentID, itemIndex, subItemIndex, justification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemTextStyle(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char &textStyle)
{
	GET_CB_UPP(GetListBrowserItemTextStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemTextStylePtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char &textStyle);
		Boolean gsResult = CALL_PROC(GetListBrowserItemTextStyle)(dialogID, componentID, itemIndex, subItemIndex, textStyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetListBrowserItemTextColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &redIndex, Sint32 &greenIndex, Sint32 &blueIndex)
{
	GET_CB_UPP(GetListBrowserItemTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetListBrowserItemTextColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 &redIndex, Sint32 &greenIndex, Sint32 &blueIndex);
		Boolean gsResult = CALL_PROC(GetListBrowserItemTextColor)(dialogID, componentID, itemIndex, subItemIndex, redIndex, greenIndex, blueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Boolean GS_CALLBACK GS_GetListBrowserMultImageIndexes(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32& iImageIndex0, Sint32& iImageIndex1, Sint32& iImageIndex2)
{
	GET_CB_UPP(Deprecated481);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef CBBoolean (*Deprecated481Ptr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32& iImageIndex0, Sint32& iImageIndex1, Sint32& iImageIndex2);
		Boolean gsResult = CALL_PROC(Deprecated481)(dialogID, componentID, iItemIndex, iSubItemIndex, iImageIndex0, iImageIndex1, iImageIndex2);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Sint32 GS_CALLBACK GS_GetListBrowserSortColumn(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetListBrowserSortColumn);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetListBrowserSortColumnPtr)(Sint32 dialogID, Sint32 componentID);
		Sint32 gsResult = CALL_PROC(GetListBrowserSortColumn)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_GetMarkerChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, MarkerType& style, CBSignedByte& angle, double& size, double& width, CBUnsignedByte& thicknessBasis, double& thickness)
{
	GET_CB_UPP(GetMarkerChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetMarkerChoicePtr)(Sint32 dialogID, Sint32 itemID, MarkerType& style, CBSignedByte& angle, double& size, double& width, CBUnsignedByte& thicknessBasis, double& thickness);
		CALL_PROC(GetMarkerChoice)(dialogID, itemID, style, angle, size, width, thicknessBasis, thickness);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetMarkerPopupSelectedItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size)
{
	GET_CB_UPP(GetMarkerPopupSelectedItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetMarkerPopupSelectedItemPtr)(Sint32 dialogID, Sint32 componentID, char& style, char& angle, short& size);
		short gsResult = CALL_PROC(GetMarkerPopupSelectedItem)(dialogID, componentID, style, angle, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


GSHandle GS_CALLBACK GS_GetMultilineText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(GetMultilineText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSHandle (*GetMultilineTextPtr)(Sint32 dialogID, Sint32 itemID);
		GSHandle gsResult = CALL_PROC(GetMultilineText)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_GetNumGradientSliderSegments(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetNumGradientSliderSegments);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumGradientSliderSegmentsPtr)(Sint32 dialogID, Sint32 componentID);
		short gsResult = CALL_PROC(GetNumGradientSliderSegments)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetNumImagePopupItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetNumImagePopupItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumImagePopupItemsPtr)(Sint32 dialogID, Sint32 componentID);
		short gsResult = CALL_PROC(GetNumImagePopupItems)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetNumListBrowserColumns(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetNumListBrowserColumns);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumListBrowserColumnsPtr)(Sint32 dialogID, Sint32 componentID);
		short gsResult = CALL_PROC(GetNumListBrowserColumns)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetNumListBrowserColumnDataItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(GetNumListBrowserColumnDataItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumListBrowserColumnDataItemsPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		short gsResult = CALL_PROC(GetNumListBrowserColumnDataItems)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetNumListBrowserItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetNumListBrowserItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumListBrowserItemsPtr)(Sint32 dialogID, Sint32 componentID);
		short gsResult = CALL_PROC(GetNumListBrowserItems)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Sint32 GS_CALLBACK GS_GetNumSelectedListBrowserItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(GetNumSelectedListBrowserItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetNumSelectedListBrowserItemsPtr)(Sint32 dialogID, Sint32 componentID);
		Sint32 gsResult = CALL_PROC(GetNumSelectedListBrowserItems)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_GetPatternData(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor)
{
	GET_CB_UPP(GetPatternData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetPatternDataPtr)(Sint32 dialogID, Sint32 itemID, short& patternIndex, short& foreColor, short& backColor);
		CALL_PROC(GetPatternData)(dialogID, itemID, patternIndex, foreColor, backColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetSelChoiceIndex(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short inStartIndex, short& outSelectedIndex)
{
	GET_CB_UPP(GetSelChoiceIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSelChoiceIndexPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort inStartIndex, short& outSelectedIndex);
		CALL_PROC(GetSelChoiceIndex)(dialogID, itemID, inStartIndex, outSelectedIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetSelectedChoiceIndex(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short& nItemIndex)
{
	GET_CB_UPP(GetSelectedChoiceIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSelectedChoiceIndexPtr)(Sint32 dialogID, Sint32 itemID, short& nItemIndex);
		CALL_PROC(GetSelectedChoiceIndex)(dialogID, itemID, nItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetSelectionRange(CALLBACKPTR, Sint32 dialogID, Sint32 controlID, Sint32& startPos, Sint32& endPos)
{
	GET_CB_UPP(GetSelectionRange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSelectionRangePtr)(Sint32 dialogID, Sint32 controlID, Sint32& startPos, Sint32& endPos);
		CALL_PROC(GetSelectionRange)(dialogID, controlID, startPos, endPos);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetThreeStateCheckBoxState(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32& iState)
{
	GET_CB_UPP(GetThreeStateCheckBoxState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetThreeStateCheckBoxStatePtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32& iState);
		Boolean gsResult = CALL_PROC(GetThreeStateCheckBoxState)(liDialogID, liComponentID, iState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetTreeControlItemData(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData)
{
	GET_CB_UPP(GetTreeControlItemData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetTreeControlItemDataPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, SintptrT& nItemData);
		Boolean gsResult = CALL_PROC(GetTreeControlItemData)(nDialogID, nComponentID, nItemID, nItemData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetTreeControlSelectedItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32& nItemID)
{
	GET_CB_UPP(GetTreeControlSelectedItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetTreeControlSelectedItemPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32& nItemID);
		Boolean gsResult = CALL_PROC(GetTreeControlSelectedItem)(nDialogID, nComponentID, nItemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Sint32 GS_CALLBACK GS_InsertEnhancedPullDownMenuItem(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, const TXString& strName, Sint32 iIconID)
{
	GET_CB_UPP(InsertEnhancedPullDownMenuItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*InsertEnhancedPullDownMenuItemPtr)(Sint32 liDialogID, Sint32 liComponentID, const TXString& strName, Sint32 iIconID);
		Sint32 gsResult = CALL_PROC(InsertEnhancedPullDownMenuItem)(liDialogID, liComponentID, strName, iIconID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_InsertGradientSliderSegment(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, double_param spotPosition, const WorldPt3& color)
{
	GET_CB_UPP(InsertGradientSliderSegment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertGradientSliderSegmentPtr)(Sint32 dialogID, Sint32 componentID, CBDouble_param spotPosition, const WorldPt3& color);
		short gsResult = CALL_PROC(InsertGradientSliderSegment)(dialogID, componentID, spotPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_InsertImagePopupObjectItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex)
{
	GET_CB_UPP(InsertImagePopupObjectItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertImagePopupObjectItemPtr)(Sint32 dialogID, Sint32 componentID, InternalIndex objectIndex);
		short gsResult = CALL_PROC(InsertImagePopupObjectItem)(dialogID, componentID, objectIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Sint32 GS_CALLBACK GS_InsertImagePopupResource(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index)
{
	GET_CB_UPP(InsertImagePopupResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*InsertImagePopupResourcePtr)(Sint32 dialogID, Sint32 componentID, Sint32 listID, Sint32 index);
		Sint32 gsResult = CALL_PROC(InsertImagePopupResource)(dialogID, componentID, listID, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Sint32 GS_CALLBACK GS_InsertImagePopupSeparator(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel)
{
	GET_CB_UPP(InsertImagePopupSeparator);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*InsertImagePopupSeparatorPtr)(Sint32 liDialogID, Sint32 liComponentID, const TXString& strLabel);
		Sint32 gsResult = CALL_PROC(InsertImagePopupSeparator)(liDialogID, liComponentID, strLabel);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_InsertListBrowserColumn(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& headerString, short width)
{
	GET_CB_UPP(InsertListBrowserColumn);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertListBrowserColumnPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, const TXString& headerString, CBSignedShort width);
		short gsResult = CALL_PROC(InsertListBrowserColumn)(dialogID, componentID, columnIndex, headerString, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_InsertListBrowserColumnDataItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, const TXString& itemString, short imageOn, short imageOff, Sint32 itemData)
{
	GET_CB_UPP(InsertListBrowserColumnDataItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertListBrowserColumnDataItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, const TXString& itemString, CBSignedShort imageOn, CBSignedShort imageOff, Sint32 itemData);
		short gsResult = CALL_PROC(InsertListBrowserColumnDataItem)(dialogID, componentID, columnIndex, itemString, imageOn, imageOff, itemData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_InsertListBrowserItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex, const TXString& itemString)
{
	GET_CB_UPP(InsertListBrowserItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertListBrowserItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex, const TXString& itemString);
		short gsResult = CALL_PROC(InsertListBrowserItem)(dialogID, componentID, itemIndex, itemString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_InsertProposedClassOrLayerItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, Sint32 nIconIndex)
{
	GET_CB_UPP(InsertProposedClassOrLayerItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*InsertProposedClassOrLayerItemPtr)(Sint32 nDialogID, Sint32 nComponentID, const TXString& strLabel, Sint32 nIconIndex);
		Boolean gsResult = CALL_PROC(InsertProposedClassOrLayerItem)(nDialogID, nComponentID, strLabel, nIconIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_InsertTreeControlItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, Sint32 nParentID, Sint32 nAfterID)
{
	GET_CB_UPP(InsertTreeControlItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*InsertTreeControlItemPtr)(Sint32 nDialogID, Sint32 nComponentID, const TXString& strItemLabel, Sint32 nParentID, Sint32 nAfterID);
		Sint32 gsResult = CALL_PROC(InsertTreeControlItem)(nDialogID, nComponentID, strItemLabel, nParentID, nAfterID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_IsItemEnabled(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID)
{
	GET_CB_UPP(IsItemEnabled);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsItemEnabledPtr)(Sint32 nDialogID, Sint32 nComponentID);
		Boolean gsResult = CALL_PROC(IsItemEnabled)(nDialogID, nComponentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsItemVisible(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID)
{
	GET_CB_UPP(IsItemVisible);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsItemVisiblePtr)(Sint32 nDialogID, Sint32 nComponentID);
		Boolean gsResult = CALL_PROC(IsItemVisible)(nDialogID, nComponentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsListBrowserColumnTrackingEnabled(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(IsListBrowserColumnTrackingEnabled);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsListBrowserColumnTrackingEnabledPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		Boolean gsResult = CALL_PROC(IsListBrowserColumnTrackingEnabled)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsListBrowserItemSelected(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex)
{
	GET_CB_UPP(IsListBrowserItemSelected);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsListBrowserItemSelectedPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex);
		Boolean gsResult = CALL_PROC(IsListBrowserItemSelected)(dialogID, componentID, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsListBrowserSortingEnabled(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(IsListBrowserSortingEnabled);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsListBrowserSortingEnabledPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(IsListBrowserSortingEnabled)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_NotifyPullDownClicked(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID)
{
	GET_CB_UPP(NotifyPullDownClicked);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NotifyPullDownClickedPtr)(Sint32 nDialogID, Sint32 nComponentID);
		Boolean gsResult = CALL_PROC(NotifyPullDownClicked)(nDialogID, nComponentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


VoidPtr GS_CALLBACK GS_OverrideControl(CALLBACKPTR, Sint32 dlogID, Sint32 controlID, VoidPtr vp)
{
	GET_CB_UPP(OverrideControl);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef VoidPtr (*OverrideControlPtr)(Sint32 dlogID, Sint32 controlID, VoidPtr vp);
		VoidPtr gsResult = CALL_PROC(OverrideControl)(dlogID, controlID, vp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_PostMinorNoteAlert(CALLBACKPTR, const TXString& strNode)
{
	GET_CB_UPP(PostMinorNoteAlert);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PostMinorNoteAlertPtr)(const TXString& strNode);
		CALL_PROC(PostMinorNoteAlert)(strNode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PostMinorStopAlert(CALLBACKPTR, const TXString& strNode)
{
	GET_CB_UPP(PostMinorStopAlert);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PostMinorStopAlertPtr)(const TXString& strNode);
		CALL_PROC(PostMinorStopAlert)(strNode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PostNoteAlert(CALLBACKPTR,  const TXString& strNode)
{
	GET_CB_UPP(PostNoteAlert);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PostNoteAlertPtr)(const TXString& strNode);
		CALL_PROC(PostNoteAlert)(strNode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PostStopAlert(CALLBACKPTR, const TXString& strNode)
{
	GET_CB_UPP(PostStopAlert);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PostStopAlertPtr)(const TXString& strNode);
		CALL_PROC(PostStopAlert)(strNode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_RefreshItem(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID)
{
	GET_CB_UPP(RefreshItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RefreshItemPtr)(Sint32 liDialogID, Sint32 liComponentID);
		Boolean gsResult = CALL_PROC(RefreshItem)(liDialogID, liComponentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RefreshListBrowser(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(RefreshListBrowser);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RefreshListBrowserPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(RefreshListBrowser)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RemoveAllImagePopupItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(RemoveAllImagePopupItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveAllImagePopupItemsPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(RemoveAllImagePopupItems)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_RemoveAllListBrowserColumnDataItems(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex)
{
	GET_CB_UPP(RemoveAllListBrowserColumnDataItems);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveAllListBrowserColumnDataItemsPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex);
		CALL_PROC(RemoveAllListBrowserColumnDataItems)(dialogID, componentID, columnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RemoveChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short itemIndexToRemove)
{
	GET_CB_UPP(RemoveChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveChoicePtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort itemIndexToRemove);
		CALL_PROC(RemoveChoice)(dialogID, itemID, itemIndexToRemove);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_RemoveEnhancedPullDownMenuItemRange(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartItemIndexToRemove, Sint32 iEndItemIndexToRemove)
{
	GET_CB_UPP(RemoveEnhancedPullDownMenuItemRange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveEnhancedPullDownMenuItemRangePtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 iStartItemIndexToRemove, Sint32 iEndItemIndexToRemove);
		Boolean gsResult = CALL_PROC(RemoveEnhancedPullDownMenuItemRange)(liDialogID, liComponentID, iStartItemIndexToRemove, iEndItemIndexToRemove);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RemoveGradientSliderSegment(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short segmentIndex)
{
	GET_CB_UPP(RemoveGradientSliderSegment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveGradientSliderSegmentPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort segmentIndex);
		Boolean gsResult = CALL_PROC(RemoveGradientSliderSegment)(dialogID, componentID, segmentIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RemoveImagePopupItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex)
{
	GET_CB_UPP(RemoveImagePopupItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveImagePopupItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex);
		Boolean gsResult = CALL_PROC(RemoveImagePopupItem)(dialogID, componentID, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_RemoveListBoxTabStop(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(RemoveListBoxTabStop);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveListBoxTabStopPtr)(Sint32 dialogID, Sint32 componentID);
		CALL_PROC(RemoveListBoxTabStop)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_RemoveListBrowserColumnDataItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short columnDataItemIndex)
{
	GET_CB_UPP(RemoveListBrowserColumnDataItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveListBrowserColumnDataItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBSignedShort columnDataItemIndex);
		Boolean gsResult = CALL_PROC(RemoveListBrowserColumnDataItem)(dialogID, componentID, columnIndex, columnDataItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RemoveTreeControlItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID)
{
	GET_CB_UPP(RemoveTreeControlItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveTreeControlItemPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID);
		Boolean gsResult = CALL_PROC(RemoveTreeControlItem)(nDialogID, nComponentID, nItemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_RunLayoutDialog(CALLBACKPTR, Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& universalName)
{
	GET_CB_UPP(RunLayoutDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*RunLayoutDialogPtr)(Sint32 dialogID, GS_EventHandlerProcPtr handleEvent, void* env, const TXString& universalName);
		Sint32 gsResult = CALL_PROC(RunLayoutDialog)(dialogID, handleEvent, env, universalName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_SelectChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short nItemIndex, Boolean bSelect)
{
	GET_CB_UPP(SelectChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SelectChoicePtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort nItemIndex, CBBoolean bSelect);
		CALL_PROC(SelectChoice)(dialogID, itemID, nItemIndex, bSelect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SelectEditText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID)
{
	GET_CB_UPP(SelectEditText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SelectEditTextPtr)(Sint32 dialogID, Sint32 itemID);
		CALL_PROC(SelectEditText)(dialogID, itemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SelectTreeControlItem(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID)
{
	GET_CB_UPP(SelectTreeControlItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SelectTreeControlItemPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID);
		Boolean gsResult = CALL_PROC(SelectTreeControlItem)(nDialogID, nComponentID, nItemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_SetBelowItem(CALLBACKPTR, Sint32 dialogID, Sint32 srcItemID, Sint32 belowItemID, short indent, short lineSpacing)
{
	GET_CB_UPP(SetBelowItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*SetBelowItemPtr)(Sint32 dialogID, Sint32 srcItemID, Sint32 belowItemID, CBSignedShort indent, CBSignedShort lineSpacing);
		bool gsResult = CALL_PROC(SetBelowItem)(dialogID, srcItemID, belowItemID, indent, lineSpacing);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetBooleanItem(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Boolean bSelect)
{
	GET_CB_UPP(SetBooleanItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetBooleanItemPtr)(Sint32 dialogID, Sint32 itemID, CBBoolean bSelect);
		CALL_PROC(SetBooleanItem)(dialogID, itemID, bSelect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetCMYKColor(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor)
{
	GET_CB_UPP(SetCMYKColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetCMYKColorPtr)(Sint32 dialogID, Sint32 itemID, TGSColorV2 &inColor);
		CALL_PROC(SetCMYKColor)(dialogID, itemID, inColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetColorButton(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const RGBColor& rgb)
{
	GET_CB_UPP(SetColorButton);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetColorButtonPtr)(Sint32 dialogID, Sint32 itemID, const RGBColor& rgb);
		CALL_PROC(SetColorButton)(dialogID, itemID, rgb);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetColorChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short colorIndex)
{
	GET_CB_UPP(SetColorChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetColorChoicePtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort colorIndex);
		CALL_PROC(SetColorChoice)(dialogID, itemID, colorIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetComponentIndeterminate(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Boolean bIndeterminateState)
{
	GET_CB_UPP(SetComponentIndeterminate);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentIndeterminatePtr)(Sint32 nDialogID, Sint32 nComponentID, CBBoolean bIndeterminateState);
		Boolean gsResult = CALL_PROC(SetComponentIndeterminate)(nDialogID, nComponentID, bIndeterminateState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetComponentSize(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nWidthPixels, Sint32 nHeightPixels)
{
	GET_CB_UPP(SetComponentSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentSizePtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nWidthPixels, Sint32 nHeightPixels);
		Boolean gsResult = CALL_PROC(SetComponentSize)(nDialogID, nComponentID, nWidthPixels, nHeightPixels);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetControlData(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const SControlDataBase& data)
{
	GET_CB_UPP(SetControlData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetControlDataPtr)(Sint32 dialogID, Sint32 itemID, const SControlDataBase& data);
		CALL_PROC(SetControlData)(dialogID, itemID, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetEdgeBinding(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, CBBoolean boundToLeft, CBBoolean boundToRight, CBBoolean boundToTop, CBBoolean boundToBottom)
{
	GET_CB_UPP(SetEdgeBinding);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetEdgeBindingPtr)(Sint32 dialogID, Sint32 itemID, CBBoolean boundToLeft, CBBoolean boundToRight, CBBoolean boundToTop, CBBoolean boundToBottom);
		CALL_PROC(SetEdgeBinding)(dialogID, itemID, boundToLeft, boundToRight, boundToTop, boundToBottom);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetEditInteger(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 value)
{
	GET_CB_UPP(SetEditInteger);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetEditIntegerPtr)(Sint32 dialogID, Sint32 componentID, Sint32 value);
		CALL_PROC(SetEditInteger)(dialogID, componentID, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetEditReal(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short editRealType, double value)
{
	GET_CB_UPP(SetEditReal);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetEditRealPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort editRealType, double value);
		CALL_PROC(SetEditReal)(dialogID, componentID, editRealType, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


bool GS_CALLBACK GS_SetFirstGroupItem(CALLBACKPTR, Sint32 dialogID, Sint32 groupID, Sint32 firstItemID)
{
	GET_CB_UPP(SetFirstGroupItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*SetFirstGroupItemPtr)(Sint32 dialogID, Sint32 groupID, Sint32 firstItemID);
		bool gsResult = CALL_PROC(SetFirstGroupItem)(dialogID, groupID, firstItemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_SetFirstLayoutItem(CALLBACKPTR, Sint32 dialogID, Sint32 firstItemID)
{
	GET_CB_UPP(SetFirstLayoutItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*SetFirstLayoutItemPtr)(Sint32 dialogID, Sint32 firstItemID);
		bool gsResult = CALL_PROC(SetFirstLayoutItem)(dialogID, firstItemID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetFocusOnItem(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID)
{
	GET_CB_UPP(SetFocusOnItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetFocusOnItemPtr)(Sint32 liDialogID, Sint32 liComponentID);
		Boolean gsResult = CALL_PROC(SetFocusOnItem)(liDialogID, liComponentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetFocusOnListBrowser(CALLBACKPTR, Sint32 dialogID, Sint32 componentID)
{
	GET_CB_UPP(SetFocusOnListBrowser);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetFocusOnListBrowserPtr)(Sint32 dialogID, Sint32 componentID);
		Boolean gsResult = CALL_PROC(SetFocusOnListBrowser)(dialogID, componentID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetGradientSliderData(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
{
	GET_CB_UPP(SetGradientSliderData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientSliderDataPtr)(Sint32 dialogID, Sint32 componentID, short& segmentIndex, CBDouble_param spotPosition, CBDouble_param midpointPosition, const WorldPt3& color);
		Boolean gsResult = CALL_PROC(SetGradientSliderData)(dialogID, componentID, segmentIndex, spotPosition, midpointPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetGradientSliderSelectedMarker(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short segmentIndex, short markerType)
{
	GET_CB_UPP(SetGradientSliderSelectedMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientSliderSelectedMarkerPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort segmentIndex, CBSignedShort markerType);
		Boolean gsResult = CALL_PROC(SetGradientSliderSelectedMarker)(dialogID, componentID, segmentIndex, markerType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetHelpText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& helpText)
{
	GET_CB_UPP(SetHelpText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetHelpTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& helpText);
		CALL_PROC(SetHelpText)(dialogID, itemID, helpText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetIconPushButtonState(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Boolean bPressed)
{
	GET_CB_UPP(SetIconPushButtonState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetIconPushButtonStatePtr)(Sint32 nDialogID, Sint32 nComponentID, CBBoolean bPressed);
		Boolean gsResult = CALL_PROC(SetIconPushButtonState)(nDialogID, nComponentID, bPressed);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetImageControlHandle(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage)
{
	GET_CB_UPP(SetImageControlHandle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetImageControlHandlePtr)(Sint32 liDialogID, Sint32 liComponentID, MCObjectHandle hImage);
		Boolean gsResult = CALL_PROC(SetImageControlHandle)(liDialogID, liComponentID, hImage);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetImageControlPath(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath)
{
	GET_CB_UPP(SetImageControlPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetImageControlPathPtr)(Sint32 nDialogID, Sint32 nComponentID, const TXString& strPath);
		Boolean gsResult = CALL_PROC(SetImageControlPath)(nDialogID, nComponentID, strPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetImagePopupSelectedItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex)
{
	GET_CB_UPP(SetImagePopupSelectedItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetImagePopupSelectedItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex);
		Boolean gsResult = CALL_PROC(SetImagePopupSelectedItem)(dialogID, componentID, itemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetItemText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, const TXString& strNewText)
{
	GET_CB_UPP(SetItemText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetItemTextPtr)(Sint32 dialogID, Sint32 itemID, const TXString& strNewText);
		CALL_PROC(SetItemText)(dialogID, itemID, strNewText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetItemToolTipText(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, Sint32 nIndex, Sint32 nSubIndex)
{
	GET_CB_UPP(SetItemToolTipText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetItemToolTipTextPtr)(Sint32 nDialogID, Sint32 nComponentID, const TXString& strToolTip, const TXString& strSubToolTip, Sint32 nIndex, Sint32 nSubIndex);
		Boolean gsResult = CALL_PROC(SetItemToolTipText)(nDialogID, nComponentID, strToolTip, strSubToolTip, nIndex, nSubIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetLayoutDialogPosition(CALLBACKPTR, Sint32 dialogID, short left, short top)
{
	GET_CB_UPP(SetLayoutDialogPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLayoutDialogPositionPtr)(Sint32 dialogID, CBSignedShort left, CBSignedShort top);
		Boolean gsResult = CALL_PROC(SetLayoutDialogPosition)(dialogID, left, top);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetLayoutDialogSize(CALLBACKPTR, Sint32 dialogID, short width, short height)
{
	GET_CB_UPP(SetLayoutDialogSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLayoutDialogSizePtr)(Sint32 dialogID, CBSignedShort width, CBSignedShort height);
		CALL_PROC(SetLayoutDialogSize)(dialogID, width, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetLayoutOption(CALLBACKPTR, Sint32 dialogID, short option, Sint32 value)
{
	GET_CB_UPP(SetLayoutOption);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLayoutOptionPtr)(Sint32 dialogID, CBSignedShort option, Sint32 value);
		Boolean gsResult = CALL_PROC(SetLayoutOption)(dialogID, option, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



void GS_CALLBACK GS_SetLineWeightChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short lineWeight)
{
	GET_CB_UPP(SetLineWeightChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLineWeightChoicePtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort lineWeight);
		CALL_PROC(SetLineWeightChoice)(dialogID, itemID, lineWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetListBrowserColumnWidth(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short fromColumn, short toColumn, short width)
{
	GET_CB_UPP(SetListBrowserColumnWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserColumnWidthPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort fromColumn, CBSignedShort toColumn, CBSignedShort width);
		Boolean gsResult = CALL_PROC(SetListBrowserColumnWidth)(dialogID, componentID, fromColumn, toColumn, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserColumnOwnerDrawnType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 iOwnerDrawnType)
{
	GET_CB_UPP(SetListBrowserColumnOwnerDrawnType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserColumnOwnerDrawnTypePtr)(Sint32 dialogID, Sint32 componentID, Sint32 iIndex, Sint32 iSubIndex, Sint32 iOwnerDrawnType);
		Boolean gsResult = CALL_PROC(SetListBrowserColumnOwnerDrawnType)(dialogID, componentID, iIndex, iSubIndex, iOwnerDrawnType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserColumnHeaderToolTip(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText)
{
	GET_CB_UPP(SetListBrowserColumnHeaderToolTip);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserColumnHeaderToolTipPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, const TXString& strToolTipPrimaryText, const TXString& strToolTipSubText);
		Boolean gsResult = CALL_PROC(SetListBrowserColumnHeaderToolTip)(dialogID, componentID, iColumnIndex, strToolTipPrimaryText, strToolTipSubText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserColumnHeaderJust(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 iJustification)
{
	GET_CB_UPP(SetListBrowserColumnHeaderJust);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserColumnHeaderJustPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex, Sint32 iJustification);
		Boolean gsResult = CALL_PROC(SetListBrowserColumnHeaderJust)(dialogID, componentID, iColumnIndex, iJustification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserColumnImage(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nColumnIndex, Sint32 nImageIndex)
{
	GET_CB_UPP(SetListBrowserColumnImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserColumnImagePtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nColumnIndex, Sint32 nImageIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserColumnImage)(nDialogID, nComponentID, nColumnIndex, nImageIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserControlType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short controlType)
{
	GET_CB_UPP(SetListBrowserControlType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserControlTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBSignedShort controlType);
		Boolean gsResult = CALL_PROC(SetListBrowserControlType)(dialogID, componentID, columnIndex, controlType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserDragAndDropColumn(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex)
{
	GET_CB_UPP(SetListBrowserDragAndDropColumn);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserDragAndDropColumnPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iColumnIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserDragAndDropColumn)(dialogID, componentID, iColumnIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserEditDisplayType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType)
{
	GET_CB_UPP(SetListBrowserEditDisplayType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserEditDisplayTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBSignedShort displayType);
		Boolean gsResult = CALL_PROC(SetListBrowserEditDisplayType)(dialogID, componentID, columnIndex, displayType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_SetListBrowserItemData(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32 nUserData)
{
	GET_CB_UPP(SetListBrowserItemData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemDataPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemIndex, Sint32 nSubItemIndex, Sint32 nUserData);
		Boolean gsResult = CALL_PROC(SetListBrowserItemData)(nDialogID, nComponentID, nItemIndex, nSubItemIndex, nUserData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemDisplayType(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short columnIndex, short displayType)
{
	GET_CB_UPP(SetListBrowserItemDisplayType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemDisplayTypePtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort columnIndex, CBSignedShort displayType);
		Boolean gsResult = CALL_PROC(SetListBrowserItemDisplayType)(dialogID, componentID, columnIndex, displayType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemFillForeColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex)
{
	GET_CB_UPP(SetListBrowserItemFillForeColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemFillForeColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemFillForeColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemFillBackColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex)
{
	GET_CB_UPP(SetListBrowserItemFillBackColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemFillBackColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemFillBackColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemGradientOrImageRefNumber(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, Sint32 liRefNumber)
{
	GET_CB_UPP(SetListBrowserItemGradientOrImageRefNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemGradientOrImageRefNumberPtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 iSubItemIndex, Sint32 liRefNumber);
		Boolean gsResult = CALL_PROC(SetListBrowserItemGradientOrImageRefNumber)(dialogID, componentID, itemIndex, iSubItemIndex, liRefNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemInfo(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, const TXString& itemString, short imageIndex)
{
	GET_CB_UPP(SetListBrowserItemInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemInfoPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex, CBSignedShort subItemIndex, const TXString& itemString, CBSignedShort imageIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemInfo)(dialogID, componentID, itemIndex, subItemIndex, itemString, imageIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


#if _WINDOWS
Boolean GS_CALLBACK GS_SetListBrowserItemPatternIndex(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iPatternIndex)
{
	GET_CB_UPP(SetListBrowserItemPatternIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemPatternIndexPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iPatternIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemPatternIndex)(dialogID, componentID, iItemIndex, iSubItemIndex, iPatternIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}
#endif


#if !_WIN_EXTERNAL_ && !_GSWINSDK_
Boolean GS_CALLBACK GS_SetListBrowserItemPattern(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* pPattern)
{
	GET_CB_UPP(SetListBrowserItemPattern);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemPatternPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Pattern* pPattern);
		Boolean gsResult = CALL_PROC(SetListBrowserItemPattern)(dialogID, componentID, iItemIndex, iSubItemIndex, pPattern);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}
#endif


Boolean GS_CALLBACK GS_SetListBrowserItemPenForeColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex)
{
	GET_CB_UPP(SetListBrowserItemPenForeColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemPenForeColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemPenForeColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemPenBackColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex)
{
	GET_CB_UPP(SetListBrowserItemPenBackColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemPenBackColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iRedIndex, Sint32 iGreenIndex, Sint32 iBlueIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemPenBackColor)(dialogID, componentID, iItemIndex, iSubItemIndex, iRedIndex, iGreenIndex, iBlueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemTextJust(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 justification)
{
	GET_CB_UPP(SetListBrowserItemTextJust);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemTextJustPtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 justification);
		Boolean gsResult = CALL_PROC(SetListBrowserItemTextJust)(dialogID, componentID, itemIndex, subItemIndex, justification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemTextStyle(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, unsigned char textStyle)
{
	GET_CB_UPP(SetListBrowserItemTextStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemTextStylePtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, CBUnsignedByte textStyle);
		Boolean gsResult = CALL_PROC(SetListBrowserItemTextStyle)(dialogID, componentID, itemIndex, subItemIndex, textStyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemTextColor(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 redIndex, Sint32 greenIndex, Sint32 blueIndex)
{
	GET_CB_UPP(SetListBrowserItemTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemTextColorPtr)(Sint32 dialogID, Sint32 componentID, Sint32 itemIndex, Sint32 subItemIndex, Sint32 redIndex, Sint32 greenIndex, Sint32 blueIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemTextColor)(dialogID, componentID, itemIndex, subItemIndex, redIndex, greenIndex, blueIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetListBrowserItemUsingColumnDataItem(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short itemIndex, short subItemIndex, short columnDataItemIndex)
{
	GET_CB_UPP(SetListBrowserItemUsingColumnDataItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserItemUsingColumnDataItemPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort itemIndex, CBSignedShort subItemIndex, CBSignedShort columnDataItemIndex);
		Boolean gsResult = CALL_PROC(SetListBrowserItemUsingColumnDataItem)(dialogID, componentID, itemIndex, subItemIndex, columnDataItemIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Boolean GS_CALLBACK GS_SetListBrowserMultImageIndexes(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iImageIndex0, Sint32 iImageIndex1, Sint32 iImageIndex2)
{
	GET_CB_UPP(Deprecated590);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef CBBoolean (*Deprecated590Ptr)(Sint32 dialogID, Sint32 componentID, Sint32 iItemIndex, Sint32 iSubItemIndex, Sint32 iImageIndex0, Sint32 iImageIndex1, Sint32 iImageIndex2);
		Boolean gsResult = CALL_PROC(Deprecated590)(dialogID, componentID, iItemIndex, iSubItemIndex, iImageIndex0, iImageIndex1, iImageIndex2);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Boolean GS_CALLBACK GS_SetListBrowserSelection(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, short firstItemIndex, short lastItemIndex, Boolean select)
{
	GET_CB_UPP(SetListBrowserSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetListBrowserSelectionPtr)(Sint32 dialogID, Sint32 componentID, CBSignedShort firstItemIndex, CBSignedShort lastItemIndex, CBBoolean select);
		Boolean gsResult = CALL_PROC(SetListBrowserSelection)(dialogID, componentID, firstItemIndex, lastItemIndex, select);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetListBrowserSortColumn(CALLBACKPTR, Sint32 dialogID, Sint32 componentID, Sint32 columnIndex, Boolean isAscending)
{
	GET_CB_UPP(SetListBrowserSortColumn);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetListBrowserSortColumnPtr)(Sint32 dialogID, Sint32 componentID, Sint32 columnIndex, CBBoolean isAscending);
		CALL_PROC(SetListBrowserSortColumn)(dialogID, componentID, columnIndex, isAscending);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetMarkerChoice(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, MarkerType style, CBSignedByte angle, double size, double width, CBUnsignedByte thicknessBasis, double thickness)
{
	GET_CB_UPP(SetMarkerChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetMarkerChoicePtr)(Sint32 dialogID, Sint32 itemID, MarkerType style, CBSignedByte angle, double size, double width, CBUnsignedByte thicknessBasis, double thickness);
		CALL_PROC(SetMarkerChoice)(dialogID, itemID, style, angle, size, width, thicknessBasis, thickness);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetMultilineText(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, GSHandle text)
{
	GET_CB_UPP(SetMultilineText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetMultilineTextPtr)(Sint32 dialogID, Sint32 itemID, GSHandle text);
		CALL_PROC(SetMultilineText)(dialogID, itemID, text);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetPatternData(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, short patternIndex, short foreColor, short backColor)
{
	GET_CB_UPP(SetPatternData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPatternDataPtr)(Sint32 dialogID, Sint32 itemID, CBSignedShort patternIndex, CBSignedShort foreColor, CBSignedShort backColor);
		CALL_PROC(SetPatternData)(dialogID, itemID, patternIndex, foreColor, backColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetProportionalBinding(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, CBBoolean leftProportional, CBBoolean rightProportional, CBBoolean topProportional, CBBoolean bottomProportional)
{
	GET_CB_UPP(SetProportionalBinding);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetProportionalBindingPtr)(Sint32 dialogID, Sint32 itemID, CBBoolean leftProportional, CBBoolean rightProportional, CBBoolean topProportional, CBBoolean bottomProportional);
		CALL_PROC(SetProportionalBinding)(dialogID, itemID, leftProportional, rightProportional, topProportional, bottomProportional);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


bool GS_CALLBACK GS_SetRightItem(CALLBACKPTR, Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, short indent, short lineSpacing)
{
	GET_CB_UPP(SetRightItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*SetRightItemPtr)(Sint32 dialogID, Sint32 srcItemID, Sint32 rightItemID, CBSignedShort indent, CBSignedShort lineSpacing);
		bool gsResult = CALL_PROC(SetRightItem)(dialogID, srcItemID, rightItemID, indent, lineSpacing);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetSelectionRange(CALLBACKPTR, Sint32 dialogID, Sint32 controlID, Sint32 startPos, Sint32 endPos)
{
	GET_CB_UPP(SetSelectionRange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetSelectionRangePtr)(Sint32 dialogID, Sint32 controlID, Sint32 startPos, Sint32 endPos);
		CALL_PROC(SetSelectionRange)(dialogID, controlID, startPos, endPos);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextEditable(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Boolean editable)
{
	GET_CB_UPP(SetTextEditable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextEditablePtr)(Sint32 dialogID, Sint32 itemID, CBBoolean editable);
		CALL_PROC(SetTextEditable)(dialogID, itemID, editable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetThreeStateCheckBoxState(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Sint32 iState)
{
	GET_CB_UPP(SetThreeStateCheckBoxState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetThreeStateCheckBoxStatePtr)(Sint32 liDialogID, Sint32 liComponentID, Sint32 iState);
		Boolean gsResult = CALL_PROC(SetThreeStateCheckBoxState)(liDialogID, liComponentID, iState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetTreeControlItemData(CALLBACKPTR, Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Sint32 nItemData)
{
	GET_CB_UPP(SetTreeControlItemData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetTreeControlItemDataPtr)(Sint32 nDialogID, Sint32 nComponentID, Sint32 nItemID, Sint32 nItemData);
		Boolean gsResult = CALL_PROC(SetTreeControlItemData)(nDialogID, nComponentID, nItemID, nItemData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_ShowEnhancedPullDownMenuGroupIcon(CALLBACKPTR, Sint32 liDialogID, Sint32 liComponentID, Boolean bShowGroupIcon)
{
	GET_CB_UPP(ShowEnhancedPullDownMenuGroupIcon);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ShowEnhancedPullDownMenuGroupIconPtr)(Sint32 liDialogID, Sint32 liComponentID, CBBoolean bShowGroupIcon);
		Boolean gsResult = CALL_PROC(ShowEnhancedPullDownMenuGroupIcon)(liDialogID, liComponentID, bShowGroupIcon);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ShowItem(CALLBACKPTR, Sint32 dialogID, Sint32 itemID, Boolean bShow)
{
	GET_CB_UPP(ShowItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ShowItemPtr)(Sint32 dialogID, Sint32 itemID, CBBoolean bShow);
		CALL_PROC(ShowItem)(dialogID, itemID, bShow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_UpdateCustomControlScrollArea(CALLBACKPTR, Sint32 dialogID, Sint32 component, Sint32 width, Sint32 height, Sint32 leftStart, Sint32 topStart, Sint32 stepSize, bool liveUpdate, bool alwaysShowHoriz, bool alwaysShowVert)
{
	GET_CB_UPP(UpdateCustomControlScrollArea);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UpdateCustomControlScrollAreaPtr)(Sint32 dialogID, Sint32 component, Sint32 width, Sint32 height, Sint32 leftStart, Sint32 topStart, Sint32 stepSize, bool liveUpdate, bool alwaysShowHoriz, bool alwaysShowVert);
		CALL_PROC(UpdateCustomControlScrollArea)(dialogID, component, width, height, leftStart, topStart, stepSize, liveUpdate, alwaysShowHoriz, alwaysShowVert);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



bool GS_CALLBACK GS_VerifyLayout(CALLBACKPTR, Sint32 dialogID)
{
	GET_CB_UPP(VerifyLayout);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*VerifyLayoutPtr)(Sint32 dialogID);
		bool gsResult = CALL_PROC(VerifyLayout)(dialogID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Document
///////////////////////////////////////////


InternalIndex GS_CALLBACK GS_AddClass(CALLBACKPTR, const InternalName& className)
{
	GET_CB_UPP(AddClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*AddClassPtr)(const InternalName& className);
		InternalIndex gsResult = CALL_PROC(AddClass)(className);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}



InternalIndex GS_CALLBACK GS_AddGuidesClass(CALLBACKPTR)
{
	GET_CB_UPP(AddGuidesClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*AddGuidesClassPtr)();
		InternalIndex gsResult = CALL_PROC(AddGuidesClass)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_ColorIndexToName(CALLBACKPTR, const ColorRef& inColorRef, TXString& outColorName)
{
	GET_CB_UPP(ColorIndexToName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ColorIndexToNamePtr)(const ColorRef& inColorRef, TXString& outColorName);
		CALL_PROC(ColorIndexToName)(inColorRef, outColorName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ColorIndexToRGB(CALLBACKPTR, ColorRef colorIndex, RGBColor& rgb)
{
	GET_CB_UPP(ColorIndexToRGB);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ColorIndexToRGBPtr)(ColorRef colorIndex, RGBColor& rgb);
		CALL_PROC(ColorIndexToRGB)(colorIndex, rgb);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CopySymbol(CALLBACKPTR, const TXString& inFilePath, const InternalName& symName)
{
	GET_CB_UPP(CopySymbol);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CopySymbolPtr)(const TXString& inFilePath, const InternalName& symName);
		Boolean gsResult = CALL_PROC(CopySymbol)(inFilePath, symName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_CreateGradient(CALLBACKPTR, const InternalName& name)
{
	GET_CB_UPP(CreateGradient);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateGradientPtr)(const InternalName& name);
		MCObjectHandle gsResult = CALL_PROC(CreateGradient)(name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateHatch(CALLBACKPTR, const InternalName& inName, CBBoolean inUsePageUnits, CBBoolean inRotateInWalls, CBBoolean inRotateInSymbols, CBBoolean inTransparent, ColorRef inFillColorIndex)
{
	GET_CB_UPP(CreateHatch);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateHatchPtr)(const InternalName& inName, CBBoolean inUsePageUnits, CBBoolean inRotateInWalls, CBBoolean inRotateInSymbols, CBBoolean inTransparent, ColorRef inFillColorIndex);
		MCObjectHandle gsResult = CALL_PROC(CreateHatch)(inName, inUsePageUnits, inRotateInWalls, inRotateInSymbols, inTransparent, inFillColorIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateImageFromPaint(CALLBACKPTR, MCObjectHandle paint, const InternalName& imageName)
{
	GET_CB_UPP(CreateImageFromPaint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateImageFromPaintPtr)(MCObjectHandle paint, const InternalName& imageName);
		MCObjectHandle gsResult = CALL_PROC(CreateImageFromPaint)(paint, imageName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreatePaintFromImage(CALLBACKPTR, MCObjectHandle image)
{
	GET_CB_UPP(CreatePaintFromImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreatePaintFromImagePtr)(MCObjectHandle image);
		MCObjectHandle gsResult = CALL_PROC(CreatePaintFromImage)(image);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateWallStyle(CALLBACKPTR, const InternalName& wallStyleName)
{
	GET_CB_UPP(CreateWallStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateWallStylePtr)(const InternalName& wallStyleName);
		MCObjectHandle gsResult = CALL_PROC(CreateWallStyle)(wallStyleName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DeleteClass(CALLBACKPTR, const InternalName& className)
{
	GET_CB_UPP(DeleteClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteClassPtr)(const InternalName& className);
		CALL_PROC(DeleteClass)(className);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



void GS_CALLBACK GS_DeselectAll(CALLBACKPTR)
{
	GET_CB_UPP(DeselectAll);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeselectAllPtr)();
		CALL_PROC(DeselectAll)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetActiveSymbolDef(CALLBACKPTR)
{
	GET_CB_UPP(GetActiveSymbolDef);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetActiveSymbolDefPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetActiveSymbolDef)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_GetClassVisibility(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClassVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetClassVisibilityPtr)(InternalIndex index);
		Boolean gsResult = CALL_PROC(GetClassVisibility)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_GetCurrentLayer(CALLBACKPTR)
{
	GET_CB_UPP(GetCurrentLayer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetCurrentLayerPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetCurrentLayer)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


short GS_CALLBACK GS_GetCurrentView(CALLBACKPTR)
{
	GET_CB_UPP(GetCurrentView);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetCurrentViewPtr)();
		short gsResult = CALL_PROC(GetCurrentView)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}




InternalIndex GS_CALLBACK GS_GetDimensionClassID(CALLBACKPTR)
{
	GET_CB_UPP(GetDimensionClassID);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetDimensionClassIDPtr)();
		InternalIndex gsResult = CALL_PROC(GetDimensionClassID)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_GetGradientData(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color)
{
	GET_CB_UPP(GetGradientData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGradientDataPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, double& spotPosition, double& midpointPosition, WorldPt3& color);
		Boolean gsResult = CALL_PROC(GetGradientData)(gradient, segmentIndex, spotPosition, midpointPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetGradientMidpointPosition(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, double& position)
{
	GET_CB_UPP(GetGradientMidpointPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGradientMidpointPositionPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, double& position);
		Boolean gsResult = CALL_PROC(GetGradientMidpointPosition)(gradient, segmentIndex, position);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetGradientSpotColor(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, WorldPt3& color)
{
	GET_CB_UPP(GetGradientSpotColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetGradientSpotColorPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, WorldPt3& color);
		CALL_PROC(GetGradientSpotColor)(gradient, segmentIndex, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetGradientSpotPosition(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, double& position)
{
	GET_CB_UPP(GetGradientSpotPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetGradientSpotPositionPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, double& position);
		Boolean gsResult = CALL_PROC(GetGradientSpotPosition)(gradient, segmentIndex, position);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetGridUnits(CALLBACKPTR, WorldCoord& x, WorldCoord& y)
{
	GET_CB_UPP(GetGridUnits);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetGridUnitsPtr)(WorldCoord& x, WorldCoord& y);
		CALL_PROC(GetGridUnits)(x, y);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetHatchLevel(CALLBACKPTR, MCObjectHandle inHatchDef, short inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight)
{
	GET_CB_UPP(GetHatchLevel);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetHatchLevelPtr)(MCObjectHandle inHatchDef, CBSignedShort inLevel, WorldPt& outStartPt, WorldPt& outRepeatVec, double& outDashFactor, WorldPt& outOffsetVec, ColorRef& outColorIndex, short& outMilsLineWeight);
		CBBoolean gsResult = CALL_PROC(GetHatchLevel)(inHatchDef, inLevel, outStartPt, outRepeatVec, outDashFactor, outOffsetVec, outColorIndex, outMilsLineWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetLayerScaleN(CALLBACKPTR, MCObjectHandle h, double_gs& scale)
{
	GET_CB_UPP(GetLayerScaleN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetLayerScaleNPtr)(MCObjectHandle h, double_gs& scale);
		CALL_PROC(GetLayerScaleN)(h, scale);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetNamedLayer(CALLBACKPTR, const InternalName& layerName)
{
	GET_CB_UPP(GetNamedLayer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetNamedLayerPtr)(const InternalName& layerName);
		MCObjectHandle gsResult = CALL_PROC(GetNamedLayer)(layerName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


InternalIndex GS_CALLBACK GS_GetNoneClassID(CALLBACKPTR)
{
	GET_CB_UPP(GetNoneClassID);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetNoneClassIDPtr)();
		InternalIndex gsResult = CALL_PROC(GetNoneClassID)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}



short GS_CALLBACK GS_GetNumGradientSegments(CALLBACKPTR, MCObjectHandle gradient)
{
	GET_CB_UPP(GetNumGradientSegments);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetNumGradientSegmentsPtr)(MCObjectHandle gradient);
		short gsResult = CALL_PROC(GetNumGradientSegments)(gradient);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_GetPageBounds(CALLBACKPTR, WorldRect& bounds)
{
	GET_CB_UPP(GetPageBounds);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetPageBoundsPtr)(WorldRect& bounds);
		CALL_PROC(GetPageBounds)(bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetPatternBits(CALLBACKPTR, short inIndex, CBUnsignedByte outPattern[8])
{
	GET_CB_UPP(GetPatternBits);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPatternBitsPtr)(CBSignedShort inIndex, CBUnsignedByte outPattern[8]);
		CBBoolean gsResult = CALL_PROC(GetPatternBits)(inIndex, outPattern);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetSheetLayerUserOrigin(CALLBACKPTR, MCObjectHandle layerHandle, WorldPt& origin)
{
	GET_CB_UPP(GetSheetLayerUserOrigin);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetSheetLayerUserOriginPtr)(MCObjectHandle layerHandle, WorldPt& origin);
		Boolean gsResult = CALL_PROC(GetSheetLayerUserOrigin)(layerHandle, origin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetUnits(CALLBACKPTR, UnitsType& currentUnits)
{
	GET_CB_UPP(GetUnits);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetUnitsPtr)(UnitsType& currentUnits);
		CALL_PROC(GetUnits)(currentUnits);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetUserOrigin(CALLBACKPTR, WorldPt& origin)
{
	GET_CB_UPP(GetUserOrigin);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetUserOriginPtr)(WorldPt& origin);
		CALL_PROC(GetUserOrigin)(origin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetUserOriginFP(CALLBACKPTR, WorldPt& outOrigin)
{
	GET_CB_UPP(GetUserOriginFP);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetUserOriginFPPtr)(WorldPt& outOrigin);
		Boolean gsResult = CALL_PROC(GetUserOriginFP)(outOrigin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_InsertGradientSegment(CALLBACKPTR, MCObjectHandle gradient, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
{
	GET_CB_UPP(InsertGradientSegment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*InsertGradientSegmentPtr)(MCObjectHandle gradient, CBDouble_param spotPosition, CBDouble_param midpointPosition, const WorldPt3& color);
		short gsResult = CALL_PROC(InsertGradientSegment)(gradient, spotPosition, midpointPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_MarkCurrentDocChanged(CALLBACKPTR)
{
	GET_CB_UPP(MarkCurrentDocChanged);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MarkCurrentDocChangedPtr)();
		CALL_PROC(MarkCurrentDocChanged)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_NumSelectedObjects(CALLBACKPTR)
{
	GET_CB_UPP(NumSelectedObjects);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*NumSelectedObjectsPtr)();
		Sint32 gsResult = CALL_PROC(NumSelectedObjects)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_RemoveGradientSegment(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex)
{
	GET_CB_UPP(RemoveGradientSegment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveGradientSegmentPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex);
		Boolean gsResult = CALL_PROC(RemoveGradientSegment)(gradient, segmentIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ResetAllObjectsVisibility(CALLBACKPTR)
{
	GET_CB_UPP(ResetAllObjectsVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ResetAllObjectsVisibilityPtr)();
		CALL_PROC(ResetAllObjectsVisibility)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RGBToColorIndex(CALLBACKPTR, const RGBColor& rgb, ColorRef& colorIndex)
{
	GET_CB_UPP(RGBToColorIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RGBToColorIndexPtr)(const RGBColor& rgb, ColorRef& colorIndex);
		CALL_PROC(RGBToColorIndex)(rgb, colorIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SelectAll(CALLBACKPTR)
{
	GET_CB_UPP(SelectAll);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SelectAllPtr)();
		CALL_PROC(SelectAll)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetActiveSymbolDef(CALLBACKPTR, MCObjectHandle aSymDef)
{
	GET_CB_UPP(SetActiveSymbolDef);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetActiveSymbolDefPtr)(MCObjectHandle aSymDef);
		CALL_PROC(SetActiveSymbolDef)(aSymDef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClassVisibility(CALLBACKPTR, InternalIndex index, Boolean visible)
{
	GET_CB_UPP(SetClassVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClassVisibilityPtr)(InternalIndex index, CBBoolean visible);
		CALL_PROC(SetClassVisibility)(index, visible);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetCurrentLayer(CALLBACKPTR, MCObjectHandle theLayer)
{
	GET_CB_UPP(SetCurrentLayer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetCurrentLayerPtr)(MCObjectHandle theLayer);
		CALL_PROC(SetCurrentLayer)(theLayer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




Boolean GS_CALLBACK GS_SetGradientData(CALLBACKPTR, MCObjectHandle gradient, short& segmentIndex, double_param spotPosition, double_param midpointPosition, const WorldPt3& color)
{
	GET_CB_UPP(SetGradientData);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientDataPtr)(MCObjectHandle gradient, short& segmentIndex, CBDouble_param spotPosition, CBDouble_param midpointPosition, const WorldPt3& color);
		Boolean gsResult = CALL_PROC(SetGradientData)(gradient, segmentIndex, spotPosition, midpointPosition, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetGradientMidpointPosition(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, double_param position)
{
	GET_CB_UPP(SetGradientMidpointPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientMidpointPositionPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, CBDouble_param position);
		Boolean gsResult = CALL_PROC(SetGradientMidpointPosition)(gradient, segmentIndex, position);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetGradientSpotColor(CALLBACKPTR, MCObjectHandle gradient, short segmentIndex, const WorldPt3& color)
{
	GET_CB_UPP(SetGradientSpotColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientSpotColorPtr)(MCObjectHandle gradient, CBSignedShort segmentIndex, const WorldPt3& color);
		Boolean gsResult = CALL_PROC(SetGradientSpotColor)(gradient, segmentIndex, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetGradientSpotPosition(CALLBACKPTR, MCObjectHandle gradient, short& segmentIndex, double_param position)
{
	GET_CB_UPP(SetGradientSpotPosition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetGradientSpotPositionPtr)(MCObjectHandle gradient, short& segmentIndex, CBDouble_param position);
		Boolean gsResult = CALL_PROC(SetGradientSpotPosition)(gradient, segmentIndex, position);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetHatchLevel(CALLBACKPTR, MCObjectHandle inHatchDef, short inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, double_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, short inMilsLineWeight)
{
	GET_CB_UPP(SetHatchLevel);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetHatchLevelPtr)(MCObjectHandle inHatchDef, CBSignedShort inLevel, const WorldPt& inStartPt, const WorldPt& inRepeatVec, CBDouble_param inDashFactor, const WorldPt& inOffsetVec, ColorRef inColorIndex, CBSignedShort inMilsLineWeight);
		CBBoolean gsResult = CALL_PROC(SetHatchLevel)(inHatchDef, inLevel, inStartPt, inRepeatVec, inDashFactor, inOffsetVec, inColorIndex, inMilsLineWeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetLayerScaleN(CALLBACKPTR, MCObjectHandle theLayer, double_param newScale)
{
	GET_CB_UPP(SetLayerScaleN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetLayerScaleNPtr)(MCObjectHandle theLayer, CBDouble_param newScale);
		CALL_PROC(SetLayerScaleN)(theLayer, newScale);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetMarker(CALLBACKPTR, MCObjectHandle obj, MarkerType style, short size, short angle, Boolean start, Boolean end)
{
	GET_CB_UPP(SetMarker);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetMarkerPtr)(MCObjectHandle obj, MarkerType style, CBSignedShort size, CBSignedShort angle, CBBoolean start, CBBoolean end);
		CALL_PROC(SetMarker)(obj, style, size, angle, start, end);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetProjection(CALLBACKPTR, MCObjectHandle theLayer, short newProj, Boolean confirmWithUser, Boolean doProgress)
{
	GET_CB_UPP(SetProjection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetProjectionPtr)(MCObjectHandle theLayer, CBSignedShort newProj, CBBoolean confirmWithUser, CBBoolean doProgress);
		CALL_PROC(SetProjection)(theLayer, newProj, confirmWithUser, doProgress);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetRenderMode(CALLBACKPTR, MCObjectHandle theLayer, short newRenderMode, Boolean immediate, Boolean doProgress)
{
	GET_CB_UPP(SetRenderMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetRenderModePtr)(MCObjectHandle theLayer, CBSignedShort newRenderMode, CBBoolean immediate, CBBoolean doProgress);
		Boolean gsResult = CALL_PROC(SetRenderMode)(theLayer, newRenderMode, immediate, doProgress);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetSheetLayerUserOrigin(CALLBACKPTR, MCObjectHandle layerHandle, const WorldPt& origin)
{
	GET_CB_UPP(SetSheetLayerUserOrigin);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetSheetLayerUserOriginPtr)(MCObjectHandle layerHandle, const WorldPt& origin);
		Boolean gsResult = CALL_PROC(SetSheetLayerUserOrigin)(layerHandle, origin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetUserOrigin(CALLBACKPTR, const WorldPt& origin)
{
	GET_CB_UPP(SetUserOrigin);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetUserOriginPtr)(const WorldPt& origin);
		CALL_PROC(SetUserOrigin)(origin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetUserOriginFP(CALLBACKPTR, const WorldPt& inOrigin)
{
	GET_CB_UPP(SetUserOriginFP);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetUserOriginFPPtr)(const WorldPt& inOrigin);
		Boolean gsResult = CALL_PROC(SetUserOriginFP)(inOrigin);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_ShowCreateImageDialog(CALLBACKPTR)
{
	GET_CB_UPP(ShowCreateImageDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ShowCreateImageDialogPtr)();
		MCObjectHandle gsResult = CALL_PROC(ShowCreateImageDialog)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_ShowGradientEditorDialog(CALLBACKPTR, MCObjectHandle& gradient)
{
	GET_CB_UPP(ShowGradientEditorDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ShowGradientEditorDialogPtr)(MCObjectHandle& gradient);
		Boolean gsResult = CALL_PROC(ShowGradientEditorDialog)(gradient);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_ValidClass(CALLBACKPTR, InternalIndex classID)
{
	GET_CB_UPP(ValidClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ValidClassPtr)(InternalIndex classID);
		Boolean gsResult = CALL_PROC(ValidClass)(classID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Files and Directories
///////////////////////////////////////////


TTesselator GS_CALLBACK GS_CreateTessellator(CALLBACKPTR, short convertRes3D)
{
	GET_CB_UPP(CreateTessellator);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef TTesselator (*CreateTessellatorPtr)(CBSignedShort convertRes3D);
		TTesselator gsResult = CALL_PROC(CreateTessellator)(convertRes3D);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return NULL;
}


void GS_CALLBACK GS_DeleteTessellator(CALLBACKPTR, TTesselator pTess)
{
	GET_CB_UPP(DeleteTessellator);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteTessellatorPtr)(TTesselator pTess);
		CALL_PROC(DeleteTessellator)(pTess);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EncryptVSPluginFilePath(CALLBACKPTR, const TXString & inFullPath, Boolean doObfuscation, const TXString & testOutputFolder)
{
	GET_CB_UPP(EncryptVSPluginFilePath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EncryptVSPluginFilePathPtr)(const TXString& inFullPath, CBBoolean doObfuscation, const TXString & testOutputFolder);
		Boolean gsResult = CALL_PROC(EncryptVSPluginFilePath)(inFullPath, doObfuscation, testOutputFolder);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_FindFileInPluginFolderN(CALLBACKPTR, const TXString& fileName, TXString& outFullPath)
{
	GET_CB_UPP(FindFileInPluginFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*FindFileInPluginFolderNPtr)(const TXString& fileName, TXString& outFullPath);
		Boolean gsResult = CALL_PROC(FindFileInPluginFolderN)(fileName, outFullPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}





EForEachFileResult GS_CALLBACK GS_ForEachFileInStandardFolder(CallBackPtr cbp, GS_ForEachFilePathProcPtr processFile, Sint32 folderSpec, void* env)
{
	GET_CB_UPP(ForEachFileInStandardFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef EForEachFileResult (*ForEachFileInStandardFolderPtr)(GS_ForEachFilePathProcPtr processFile, Sint32 folderSpec, void* env, CallBackPtr cbp);
		EForEachFileResult gsResult = CALL_PROC(ForEachFileInStandardFolder)(processFile, folderSpec, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFolderNotFoundError;
}



EForEachFileResult GS_CALLBACK GS_ForEachFilePathInFolderN(CallBackPtr cbp, GS_ForEachFilePathNProcPtr processFile, const TXString& inStartDirectory, Boolean doRecursive, void* env)
{
	GET_CB_UPP(ForEachFilePathInFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef EForEachFileResult (*ForEachFilePathInFolderNPtr)(GS_ForEachFilePathNProcPtr processFile, const TXString& inStartDirectory, CBBoolean doRecursive, void* env, CallBackPtr cbp);
		EForEachFileResult gsResult = CALL_PROC(ForEachFilePathInFolderN)(processFile, inStartDirectory, doRecursive, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFolderNotFoundError;
}


EForEachFileResult GS_CALLBACK GS_ForEachFilePathInPluginFolder(CallBackPtr cbp, GS_ForEachFilePathNProcPtr processFile, void* env)
{
	GET_CB_UPP(ForEachFilePathInPluginFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef EForEachFileResult (*ForEachFilePathInPluginFolderPtr)(GS_ForEachFilePathNProcPtr processFile, void* env, CallBackPtr cbp);
		EForEachFileResult gsResult = CALL_PROC(ForEachFilePathInPluginFolder)(processFile, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFolderNotFoundError;
}


EForEachFileResult GS_CALLBACK GS_ForEachFilePathInStandardFolder(CallBackPtr cbp, GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env)
{
	GET_CB_UPP(ForEachFilePathInStandardFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef EForEachFileResult (*ForEachFilePathInStandardFolderPtr)(GS_ForEachFilePathProcPtr processFile, FolderSpecifier folderSpec, void* env, CallBackPtr cbp);
		EForEachFileResult gsResult = CALL_PROC(ForEachFilePathInStandardFolder)(processFile, folderSpec, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFolderNotFoundError;
}


Boolean GS_CALLBACK GS_GetActiveDocumentN(CALLBACKPTR, TXString& activeDocumentPath, Boolean& saved)
{
	GET_CB_UPP(GetActiveDocumentN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetActiveDocumentNPtr)(TXString& activeDocumentPath, Boolean& saved);
		Boolean gsResult = CALL_PROC(GetActiveDocumentN)(activeDocumentPath, saved);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_GetFilePathInStandardFolder(CALLBACKPTR, Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists)
{
	GET_CB_UPP(GetFilePathInStandardFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFilePathInStandardFolderPtr)(Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists);
		Boolean gsResult = CALL_PROC(GetFilePathInStandardFolder)(folderClass, fileName, outFilePath, exists);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFilePathInStandardFolderN(CALLBACKPTR, Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists)
{
	GET_CB_UPP(GetFilePathInStandardFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFilePathInStandardFolderNPtr)(Sint32 folderClass, const TXString& fileName, TXString& outFilePath, Boolean& exists);
		Boolean gsResult = CALL_PROC(GetFilePathInStandardFolderN)(folderClass, fileName, outFilePath, exists);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFilePathInUserRoot(CALLBACKPTR, FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath)
{
	GET_CB_UPP(GetFilePathInUserRoot);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFilePathInUserRootPtr)(FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath);
		Boolean gsResult = CALL_PROC(GetFilePathInUserRoot)(folderClass, fileName, outFilePath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFilePathInUserRootN(CALLBACKPTR, FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath)
{
	GET_CB_UPP(GetFilePathInUserRootN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFilePathInUserRootNPtr)(FolderSpecifier folderClass, const TXString& fileName, TXString& outFilePath);
		Boolean gsResult = CALL_PROC(GetFilePathInUserRootN)(folderClass, fileName, outFilePath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetFolderN(CALLBACKPTR, FolderSpecifier inWhichFolder, TXString& outPath, Boolean inCreateIfMissing)
{
	GET_CB_UPP(GetFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetFolderNPtr)(FolderSpecifier inWhichFolder, TXString& outPath, CBBoolean inCreateIfMissing);
		Boolean gsResult = CALL_PROC(GetFolderN)(inWhichFolder, outPath, inCreateIfMissing);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




Boolean GS_CALLBACK GS_GetNamedSubFolderN(CALLBACKPTR, const TXString& parentPath, const TXString& partialPath, TXString& outFolderPath)
{
	GET_CB_UPP(GetNamedSubFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetNamedSubFolderNPtr)(const TXString& parentPath, const TXString& partialPath, TXString& outFolderPath);
		Boolean gsResult = CALL_PROC(GetNamedSubFolderN)(parentPath, partialPath, outFolderPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetNumFilesInStandardFolder(CALLBACKPTR, FolderSpecifier folderClass, Uint32& numFiles)
{
	GET_CB_UPP(GetNumFilesInStandardFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetNumFilesInStandardFolderPtr)(FolderSpecifier folderClass, Uint32& numFiles);
		Boolean gsResult = CALL_PROC(GetNumFilesInStandardFolder)(folderClass, numFiles);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


short GS_CALLBACK GS_ImportDXF(CALLBACKPTR, const TXString& inFilePath)
{
	GET_CB_UPP(ImportDXF);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*ImportDXFPtr)(const TXString& inFilePath);
		short gsResult = CALL_PROC(ImportDXF)(inFilePath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_IsInStandardFolder(CALLBACKPTR, FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath)
{
	GET_CB_UPP(IsInStandardFolder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsInStandardFolderPtr)(FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath);
		Boolean gsResult = CALL_PROC(IsInStandardFolder)(folderClass, filePath, outFolderPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsInStandardFolderN(CALLBACKPTR, FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath)
{
	GET_CB_UPP(IsInStandardFolderN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsInStandardFolderNPtr)(FolderSpecifier folderClass, const TXString& filePath, TXString& outFolderPath);
		Boolean gsResult = CALL_PROC(IsInStandardFolderN)(folderClass, filePath, outFolderPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_OpenDocumentPath(CALLBACKPTR, const TXString& inPath, CBBoolean inShowErrorMessages)
{
	GET_CB_UPP(OpenDocumentPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*OpenDocumentPathPtr)(const TXString& inPath, CBBoolean inShowErrorMessages);
		CBBoolean gsResult = CALL_PROC(OpenDocumentPath)(inPath, inShowErrorMessages);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}

Boolean GS_CALLBACK GS_ReadVSExternalFilePath(CALLBACKPTR, const TXString& inFilePath, TMPExternalDataForWorkspace& outData)
{
	GET_CB_UPP(ReadVSExternalFilePath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef CBBoolean (*ReadVSExternalFilePathPtr)(const TXString& inFilePath, TMPExternalDataForWorkspace& outData);
		Boolean gsResult = CALL_PROC(ReadVSExternalFilePath)(inFilePath, outData);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


GSError GS_CALLBACK GS_SaveActiveDocumentPath(CALLBACKPTR, const TXString& activeDocumentPath)
{
	GET_CB_UPP(SaveActiveDocumentPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSError (*SaveActiveDocumentPathPtr)(const TXString& activeDocumentPath);
		GSError gsResult = CALL_PROC(SaveActiveDocumentPath)(activeDocumentPath);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 1;
}


bool GS_CALLBACK GS_TesselateObject(CALLBACKPTR, TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv)
{
	GET_CB_UPP(TesselateObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*TesselateObjectPtr)(TTesselator pTess, MCObjectHandle h, GS_TessellateIteratorProcPtr proc, void* pEnv);
		bool gsResult = CALL_PROC(TesselateObject)(pTess, h, proc, pEnv);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


bool GS_CALLBACK GS_WriteMaterialImageFile(CALLBACKPTR, const TXString& szFullPathName, MCObjectHandle hMaterial, Sint32 type)
{
	GET_CB_UPP(WriteMaterialImageFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef bool (*WriteMaterialImageFilePtr)(const TXString& szFullPathName, MCObjectHandle hMaterial, Sint32 type);
		bool gsResult = CALL_PROC(WriteMaterialImageFile)(szFullPathName, hMaterial, type);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Image Manipulation
///////////////////////////////////////////


#if _WINDOWS
HBITMAP GS_CALLBACK GS_CreateDIBFromPaintNode(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(CreateDIBFromPaintNode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef HBITMAP (*CreateDIBFromPaintNodePtr)(MCObjectHandle h);
		HBITMAP gsResult = CALL_PROC(CreateDIBFromPaintNode)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}
#endif


#if _WINDOWS
HBITMAP GS_CALLBACK GS_CreateDIBFromPreview(CALLBACKPTR, InternalIndex &inIndex, short pixelWidth, short pixelHeight)
{
	GET_CB_UPP(CreateDIBFromPreview);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef HBITMAP (*CreateDIBFromPreviewPtr)(InternalIndex &inIndex, CBSignedShort pixelWidth, CBSignedShort pixelHeight);
		HBITMAP gsResult = CALL_PROC(CreateDIBFromPreview)(inIndex, pixelWidth, pixelHeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}
#endif


#if _WINDOWS
MCObjectHandle GS_CALLBACK GS_CreatePaintNodeFromDIB(CALLBACKPTR, HBITMAP hBitmap)
{
	GET_CB_UPP(CreatePaintNodeFromDIB);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreatePaintNodeFromDIBPtr)(HBITMAP hBitmap);
		MCObjectHandle gsResult = CALL_PROC(CreatePaintNodeFromDIB)(hBitmap);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}
#endif


#if _WINDOWS
void GS_CALLBACK GS_DisposeDIB(CALLBACKPTR, HBITMAP hBitmap)
{
	GET_CB_UPP(DisposeDIB);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisposeDIBPtr)(HBITMAP hBitmap);
		CALL_PROC(DisposeDIB)(hBitmap);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}
#endif


Boolean GS_CALLBACK GS_UpdateThumbnailPreview(CALLBACKPTR, InternalIndex inIndex)
{
	GET_CB_UPP(UpdateThumbnailPreview);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*UpdateThumbnailPreviewPtr)(InternalIndex inIndex);
		Boolean gsResult = CALL_PROC(UpdateThumbnailPreview)(inIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Internal use
///////////////////////////////////////////


void GS_CALLBACK GS_CloseXCode(CALLBACKPTR, Sint32 extCodeInfoID)
{
	GET_CB_UPP(CloseXCode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CloseXCodePtr)(Sint32 extCodeInfoID);
		CALL_PROC(CloseXCode)(extCodeInfoID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


GenericFunctionPtr GS_CALLBACK GS_OpenXCode(CALLBACKPTR, Sint32 extCodeInfoID, Boolean needsResourceFileOpen)
{
	GET_CB_UPP(OpenXCode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GenericFunctionPtr (*OpenXCodePtr)(Sint32 extCodeInfoID, CBBoolean needsResourceFileOpen);
		GenericFunctionPtr gsResult = CALL_PROC(OpenXCode)(extCodeInfoID, needsResourceFileOpen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}




///////////////////////////////////////////
//  Memory Allocation
///////////////////////////////////////////


void GS_CALLBACK GS_DisposeHandle(CALLBACKPTR, GSHandle handle)
{
	GET_CB_UPP(DisposeHandle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisposeHandlePtr)(GSHandle handle);
		CALL_PROC(DisposeHandle)(handle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DisposePtr(CALLBACKPTR, void* p)
{
	GET_CB_UPP(DisposePtr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisposePtrPtr)(void* p);
		CALL_PROC(DisposePtr)(p);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetHandleSize(CALLBACKPTR, GSHandle handle, size_t& size)
{
	GET_CB_UPP(GetHandleSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetHandleSizePtr)(GSHandle handle, size_t& size);
		CALL_PROC(GetHandleSize)(handle, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetHandleState(CALLBACKPTR, GSHandle handle, Boolean& isLocked)
{
	GET_CB_UPP(GetHandleState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetHandleStatePtr)(GSHandle handle, Boolean& isLocked);
		CALL_PROC(GetHandleState)(handle, isLocked);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


GSHandle GS_CALLBACK GS_NewHandle(CALLBACKPTR, size_t size)
{
	GET_CB_UPP(NewHandle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSHandle (*NewHandlePtr)(size_t size);
		GSHandle gsResult = CALL_PROC(NewHandle)(size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


VoidPtr GS_CALLBACK GS_NewPtr(CALLBACKPTR, size_t size)
{
	GET_CB_UPP(NewPtr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef VoidPtr (*NewPtrPtr)(size_t size);
		VoidPtr gsResult = CALL_PROC(NewPtr)(size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_ReduceHandleSize(CALLBACKPTR, GSHandle handle, size_t size)
{
	GET_CB_UPP(ReduceHandleSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ReduceHandleSizePtr)(GSHandle handle, size_t size);
		CALL_PROC(ReduceHandleSize)(handle, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetHandleSize(CALLBACKPTR, GSHandle handle, size_t size)
{
	GET_CB_UPP(SetHandleSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetHandleSizePtr)(GSHandle handle, size_t size);
		Boolean gsResult = CALL_PROC(SetHandleSize)(handle, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetHandleState(CALLBACKPTR, GSHandle handle, Boolean isLocked)
{
	GET_CB_UPP(SetHandleState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetHandleStatePtr)(GSHandle handle, CBBoolean isLocked);
		CALL_PROC(SetHandleState)(handle, isLocked);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


VoidPtr GS_CALLBACK GS_SetPtrSize(CALLBACKPTR, void* p, size_t size)
{
	GET_CB_UPP(SetPtrSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef VoidPtr (*SetPtrSizePtr)(void* p, size_t size);
		VoidPtr gsResult = CALL_PROC(SetPtrSize)(p, size);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}




///////////////////////////////////////////
//  Menus
///////////////////////////////////////////


Sint32 GS_CALLBACK GS_AddResourceToList(CALLBACKPTR, Sint32 listID, MCObjectHandle resource)
{
	GET_CB_UPP(AddResourceToList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*AddResourceToListPtr)(Sint32 listID, MCObjectHandle resource);
		Sint32 gsResult = CALL_PROC(AddResourceToList)(listID, resource);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Sint32 GS_CALLBACK GS_BuildResourceList(CALLBACKPTR, short objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems)
{
	GET_CB_UPP(BuildResourceList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*BuildResourceListPtr)(CBSignedShort objectType, FolderSpecifier folderIndex, const TXString& subFolderName, Sint32& numItems, bool sort);
		Sint32 gsResult = CALL_PROC(BuildResourceList)(objectType, folderIndex, subFolderName, numItems, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_DeleteResourceFromList(CALLBACKPTR, Sint32 listID, Sint32 index)
{
	GET_CB_UPP(DeleteResourceFromList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteResourceFromListPtr)(Sint32 listID, Sint32 index);
		CALL_PROC(DeleteResourceFromList)(listID, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DisposeResourceList(CALLBACKPTR, Sint32 listID)
{
	GET_CB_UPP(DisposeResourceList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisposeResourceListPtr)(Sint32 listID);
		CALL_PROC(DisposeResourceList)(listID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetActualNameFromResourceList(CALLBACKPTR, Sint32 listID, Sint32 index, TXString&  name)
{
	GET_CB_UPP(GetActualNameFromResourceList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetActualNameFromResourceListPtr)(Sint32 listID, Sint32 index, TXString&  name);
		CALL_PROC(GetActualNameFromResourceList)(listID, index, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetMyMenuCommandIndex(CALLBACKPTR)
{
	GET_CB_UPP(GetMyMenuCommandIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetMyMenuCommandIndexPtr)();
		short gsResult = CALL_PROC(GetMyMenuCommandIndex)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetNameFromResourceList(CALLBACKPTR, Sint32 listID, Sint32 index, TXString&  name)
{
	GET_CB_UPP(GetNameFromResourceList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetNameFromResourceListPtr)(Sint32 listID, Sint32 index, TXString&  name);
		CALL_PROC(GetNameFromResourceList)(listID, index, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetResourceFromList(CALLBACKPTR, Sint32 listID, Sint32 index)
{
	GET_CB_UPP(GetResourceFromList);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetResourceFromListPtr)(Sint32 listID, Sint32 index);
		MCObjectHandle gsResult = CALL_PROC(GetResourceFromList)(listID, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


MCObjectHandle GS_CALLBACK GS_ImportResourceToCurrentFile(CALLBACKPTR, Sint32 listID, Sint32 index)
{
	GET_CB_UPP(ImportResourceToCurrentFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ImportResourceToCurrentFilePtr)(Sint32 listID, Sint32 index);
		MCObjectHandle gsResult = CALL_PROC(ImportResourceToCurrentFile)(listID, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_RegisterMenuForCallback(CALLBACKPTR, short menuIndex, OSType whichChange)
{
	GET_CB_UPP(RegisterMenuForCallback);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RegisterMenuForCallbackPtr)(CBSignedShort menuIndex, OSType whichChange);
		Boolean gsResult = CALL_PROC(RegisterMenuForCallback)(menuIndex, whichChange);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_ResourceListSize(CALLBACKPTR, Sint32 listID)
{
	GET_CB_UPP(ResourceListSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*ResourceListSizePtr)(Sint32 listID);
		Sint32 gsResult = CALL_PROC(ResourceListSize)(listID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_UnregisterMenuForCallback(CALLBACKPTR, short menuIndex, OSType whichChange)
{
	GET_CB_UPP(UnregisterMenuForCallback);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UnregisterMenuForCallbackPtr)(CBSignedShort menuIndex, OSType whichChange);
		CALL_PROC(UnregisterMenuForCallback)(menuIndex, whichChange);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Mode Bar
///////////////////////////////////////////

void GS_CALLBACK GS_Deprecated35L(CALLBACKPTR, short iconID)
{
	GET_CB_UPP(Deprecated35L);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef void (*Deprecated35LPtr)(CBSignedShort iconID);
		CALL_PROC(Deprecated35L)(iconID);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_Deprecated36L(CALLBACKPTR, short initialSetting, short iconID)
{
	GET_CB_UPP(Deprecated36L);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef void (*Deprecated36LPtr)(CBSignedShort initialSetting, CBSignedShort iconID);
		CALL_PROC(Deprecated36L)(initialSetting, iconID);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_AddPullDownMenuItem(CALLBACKPTR, short group, const TXString& item)
{
	GET_CB_UPP(AddPullDownMenuItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddPullDownMenuItemPtr)(CBSignedShort group, const TXString& item);
		CALL_PROC(AddPullDownMenuItem)(group, item);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_AddPullDownMenuMode(CALLBACKPTR, const TXString& label)
{
	GET_CB_UPP(AddPullDownMenuMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddPullDownMenuModePtr)(const TXString& label);
		CALL_PROC(AddPullDownMenuMode)(label);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_Deprecated37L(CALLBACKPTR, short initialSetting, short numButtons, short id1, short id2, short id3, short id4, short id5, short id6)
{
	GET_CB_UPP(Deprecated37L);
	if (f) {
		CallBackPtr saveCBP = gCBP;
#if GS_USE_D0_RETURNS
#pragma pointers_in_D0
#endif
		typedef void (*Deprecated37LPtr)(CBSignedShort initialSetting, CBSignedShort numButtons, CBSignedShort id1, CBSignedShort id2, CBSignedShort id3, CBSignedShort id4, CBSignedShort id5, CBSignedShort id6);
		CALL_PROC(Deprecated37L)(initialSetting, numButtons, id1, id2, id3, id4, id5, id6);
#if GS_USE_D0_RETURNS
#pragma pointers_in_A0
#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_AddTxtBtnMode(CALLBACKPTR, const TXString& theText)
{
	GET_CB_UPP(AddTxtBtnMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddTxtBtnModePtr)(const TXString& theText);
		CALL_PROC(AddTxtBtnMode)(theText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_EnableMode(CALLBACKPTR, short modeNum, Boolean enable)
{
	GET_CB_UPP(EnableMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableModePtr)(CBSignedShort modeNum, CBBoolean enable);
		CALL_PROC(EnableMode)(modeNum, enable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetModeValue(CALLBACKPTR, short modeNum)
{
	GET_CB_UPP(GetModeValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetModeValuePtr)(CBSignedShort modeNum);
		short gsResult = CALL_PROC(GetModeValue)(modeNum);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_SetHelpString(CALLBACKPTR, const TXString& helpMessage)
{
	GET_CB_UPP(SetHelpString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetHelpStringPtr)(const TXString& helpMessage);
		CALL_PROC(SetHelpString)(helpMessage);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetModeValue(CALLBACKPTR, short modeNum, short theValue)
{
	GET_CB_UPP(SetModeValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetModeValuePtr)(CBSignedShort modeNum, CBSignedShort theValue);
		CALL_PROC(SetModeValue)(modeNum, theValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetPullDownMenuSelection(CALLBACKPTR, short group, short selectedItem)
{
	GET_CB_UPP(SetPullDownMenuSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPullDownMenuSelectionPtr)(CBSignedShort group, CBSignedShort selectedItem);
		CALL_PROC(SetPullDownMenuSelection)(group, selectedItem);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Name Translation
///////////////////////////////////////////


void GS_CALLBACK GS_ClassIDToName(CALLBACKPTR, InternalIndex classID, InternalName& className)
{
	GET_CB_UPP(ClassIDToName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ClassIDToNamePtr)(InternalIndex classID, InternalName& className);
		CALL_PROC(ClassIDToName)(classID, className);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


InternalIndex GS_CALLBACK GS_ClassNameToID(CALLBACKPTR, const InternalName& className)
{
	GET_CB_UPP(ClassNameToID);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*ClassNameToIDPtr)(const InternalName& className);
		InternalIndex gsResult = CALL_PROC(ClassNameToID)(className);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


MCObjectHandle GS_CALLBACK GS_InternalIndexToHandle(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(InternalIndexToHandle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*InternalIndexToHandlePtr)(InternalIndex index);
		MCObjectHandle gsResult = CALL_PROC(InternalIndexToHandle)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_InternalIndexToNameN(CALLBACKPTR, InternalIndex index, InternalName& name)
{
	GET_CB_UPP(InternalIndexToNameN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InternalIndexToNameNPtr)(InternalIndex index, InternalName& name);
		CALL_PROC(InternalIndexToNameN)(index, name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


InternalIndex GS_CALLBACK GS_MaxClassID(CALLBACKPTR)
{
	GET_CB_UPP(MaxClassID);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*MaxClassIDPtr)();
		InternalIndex gsResult = CALL_PROC(MaxClassID)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_NameToInternalIndexN(CALLBACKPTR, const TXString& name, InternalIndex& index)
{
	GET_CB_UPP(NameToInternalIndexN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NameToInternalIndexNPtr)(const TXString& name, InternalIndex& index);
		Boolean gsResult = CALL_PROC(NameToInternalIndexN)(name, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetPolyVertexLoopDirection(CALLBACKPTR, MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec)
{
	GET_CB_UPP(SetPolyVertexLoopDirection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetPolyVertexLoopDirectionPtr)(MCObjectHandle ioPolyToSet, PolyDirectionSpecType inPolyDirectionSpec);
		Boolean gsResult = CALL_PROC(SetPolyVertexLoopDirection)(ioPolyToSet, inPolyDirectionSpec);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Object Manipulation
///////////////////////////////////////////


void GS_CALLBACK GS_AddToConstraintModel(CALLBACKPTR, MCObjectHandle obj)
{
	GET_CB_UPP(AddToConstraintModel);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddToConstraintModelPtr)(MCObjectHandle obj);
		CALL_PROC(AddToConstraintModel)(obj);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_AddViewportAnnotationObject(CALLBACKPTR, MCObjectHandle viewportHandle, MCObjectHandle annotationHandle)
{
	GET_CB_UPP(AddViewportAnnotationObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddViewportAnnotationObjectPtr)(MCObjectHandle viewportHandle, MCObjectHandle annotationHandle);
		Boolean gsResult = CALL_PROC(AddViewportAnnotationObject)(viewportHandle, annotationHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AppendParameterWidget(CALLBACKPTR, Sint32 ObjectID, Sint32 parameterID, const TXString& text, Sint32 data)
{
	GET_CB_UPP(AppendParameterWidget);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AppendParameterWidgetPtr)(Sint32 ObjectID, Sint32 parameterID, const TXString& text, Sint32 data);
		Boolean gsResult = CALL_PROC(AppendParameterWidget)(ObjectID, parameterID, text, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AppendWidget(CALLBACKPTR, Sint32 ObjectID, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data)
{
	GET_CB_UPP(AppendWidget);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AppendWidgetPtr)(Sint32 ObjectID, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data);
		Boolean gsResult = CALL_PROC(AppendWidget)(ObjectID, widgetType, eventID, text, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_ConvertTo3DPolygons(CALLBACKPTR, MCObjectHandle h, Boolean preserveOriginal)
{
	GET_CB_UPP(ConvertTo3DPolygons);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ConvertTo3DPolygonsPtr)(MCObjectHandle h, CBBoolean preserveOriginal);
		MCObjectHandle gsResult = CALL_PROC(ConvertTo3DPolygons)(h, preserveOriginal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle  GS_CALLBACK GS_ConvertToNURBS(CALLBACKPTR, MCObjectHandle h, Boolean keepOrig)
{
	GET_CB_UPP(ConvertToNURBS);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle  (*ConvertToNURBSPtr)(MCObjectHandle h, CBBoolean keepOrig);
		MCObjectHandle  gsResult = CALL_PROC(ConvertToNURBS)(h, keepOrig);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_ConvertToPolygon(CALLBACKPTR, MCObjectHandle h, Boolean preserveOriginal)
{
	GET_CB_UPP(ConvertToPolygon);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ConvertToPolygonPtr)(MCObjectHandle h, CBBoolean preserveOriginal);
		MCObjectHandle gsResult = CALL_PROC(ConvertToPolygon)(h, preserveOriginal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_ConvertToPolygonN(CALLBACKPTR, MCObjectHandle h, Boolean preserveOriginal, short conversionResolution)
{
	GET_CB_UPP(ConvertToPolygonN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ConvertToPolygonNPtr)(MCObjectHandle h, CBBoolean preserveOriginal, CBSignedShort conversionResolution);
		MCObjectHandle gsResult = CALL_PROC(ConvertToPolygonN)(h, preserveOriginal, conversionResolution);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_ConvertToPolyline(CALLBACKPTR, MCObjectHandle h, Boolean preserveOriginal)
{
	GET_CB_UPP(ConvertToPolyline);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ConvertToPolylinePtr)(MCObjectHandle h, CBBoolean preserveOriginal);
		MCObjectHandle gsResult = CALL_PROC(ConvertToPolyline)(h, preserveOriginal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_ConvertToUnstyledWall(CALLBACKPTR, MCObjectHandle theWall)
{
	GET_CB_UPP(ConvertToUnstyledWall);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ConvertToUnstyledWallPtr)(MCObjectHandle theWall);
		Boolean gsResult = CALL_PROC(ConvertToUnstyledWall)(theWall);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_CreateConstraintModel(CALLBACKPTR, MCObjectHandle obj, Boolean useSelection)
{
	GET_CB_UPP(CreateConstraintModel);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CreateConstraintModelPtr)(MCObjectHandle obj, CBBoolean useSelection);
		CALL_PROC(CreateConstraintModel)(obj, useSelection);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_CreateOffsetNurbsObjectHandle(CALLBACKPTR, MCObjectHandle h, double offset)
{
	GET_CB_UPP(CreateOffsetNurbsObjectHandle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateOffsetNurbsObjectHandlePtr)(MCObjectHandle h, double offset);
		MCObjectHandle gsResult = CALL_PROC(CreateOffsetNurbsObjectHandle)(h, offset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_CustomObjectControlPtsCreate(CallBackPtr cbp, MCObjectHandle inOwnerObj, Sint32 numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc, void* env)
{
	GET_CB_UPP(CustomObjectControlPtsCreate);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomObjectControlPtsCreatePtr)(MCObjectHandle inOwnerObj, Sint32 numDataElements, GS_CustomObjectControlPtsInitProcPtr initProc, void* env, CallBackPtr cbp);
		Boolean gsResult = CALL_PROC(CustomObjectControlPtsCreate)(inOwnerObj, numDataElements, initProc, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomObjectControlPtsRemove(CALLBACKPTR, MCObjectHandle inOwnerObj)
{
	GET_CB_UPP(CustomObjectControlPtsRemove);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomObjectControlPtsRemovePtr)(MCObjectHandle inOwnerObj);
		Boolean gsResult = CALL_PROC(CustomObjectControlPtsRemove)(inOwnerObj);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomObjectControlPtSet(CALLBACKPTR, MCObjectHandle inOwnerObj, Sint32 dataIndex, const WorldPt3& pt, Boolean is2DOnly, Boolean isHidden, Sint32 inClientID)
{
	GET_CB_UPP(CustomObjectControlPtSet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomObjectControlPtSetPtr)(MCObjectHandle inOwnerObj, Sint32 dataIndex, const WorldPt3& pt, CBBoolean is2DOnly, CBBoolean isHidden, Sint32 inClientID);
		Boolean gsResult = CALL_PROC(CustomObjectControlPtSet)(inOwnerObj, dataIndex, pt, is2DOnly, isHidden, inClientID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_CustomObjectGetSurfaceProxy(CALLBACKPTR, MCObjectHandle inPathObject)
{
	GET_CB_UPP(CustomObjectGetSurfaceProxy);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CustomObjectGetSurfaceProxyPtr)(MCObjectHandle inPathObject);
		MCObjectHandle gsResult = CALL_PROC(CustomObjectGetSurfaceProxy)(inPathObject);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_CustomObjectReplacePath(CALLBACKPTR, MCObjectHandle inPathObject, MCObjectHandle pathPolyline)
{
	GET_CB_UPP(CustomObjectReplacePath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomObjectReplacePathPtr)(MCObjectHandle inPathObject, MCObjectHandle pathPolyline);
		Boolean gsResult = CALL_PROC(CustomObjectReplacePath)(inPathObject, pathPolyline);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_DeleteAllComponents(CALLBACKPTR, MCObjectHandle wall)
{
	GET_CB_UPP(DeleteAllComponents);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteAllComponentsPtr)(MCObjectHandle wall);
		CBBoolean gsResult = CALL_PROC(DeleteAllComponents)(wall);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_DeleteComponent(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index)
{
	GET_CB_UPP(DeleteComponent);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DeleteComponentPtr)(MCObjectHandle wall, CBSignedShort index);
		CBBoolean gsResult = CALL_PROC(DeleteComponent)(wall, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_DeleteConstraint(CALLBACKPTR, MCObjectHandle obj, MCObjectHandle constraint)
{
	GET_CB_UPP(DeleteConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteConstraintPtr)(MCObjectHandle obj, MCObjectHandle constraint);
		CALL_PROC(DeleteConstraint)(obj, constraint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_DuplicateObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(DuplicateObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*DuplicateObjectPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(DuplicateObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_EnableParameter(CALLBACKPTR, MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetEnabled)
{
	GET_CB_UPP(EnableParameter);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnableParameterPtr)(MCObjectHandle inCustomObject, CBSignedShort inParameterIndex, CBBoolean inSetEnabled);
		CALL_PROC(EnableParameter)(inCustomObject, inParameterIndex, inSetEnabled);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EvaluateNurbsSurfacePointAndNormal(CALLBACKPTR, MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point, WorldPt3& normal)
{
	GET_CB_UPP(EvaluateNurbsSurfacePointAndNormal);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EvaluateNurbsSurfacePointAndNormalPtr)(MCObjectHandle surfaceHandle, double u, double v, WorldPt3& point, WorldPt3& normal, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(EvaluateNurbsSurfacePointAndNormal)(surfaceHandle, u, v, point, normal, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFalse;
}


void GS_CALLBACK GS_ForEachLayer(CallBackPtr cbp, GS_ForEachObjectProcPtr action, void *actionEnv)
{
	GET_CB_UPP(ForEachLayer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ForEachLayerPtr)(GS_ForEachObjectProcPtr action, void *actionEnv, CallBackPtr cbp);
		CALL_PROC(ForEachLayer)(action, actionEnv, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ForEachObject(CallBackPtr cbp, short traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv)
{
	GET_CB_UPP(ForEachObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ForEachObjectPtr)(CBSignedShort traverseWhat, GS_ForEachObjectProcPtr action, void *actionEnv, CallBackPtr cbp);
		CALL_PROC(ForEachObject)(traverseWhat, action, actionEnv, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Get2DPt(CALLBACKPTR, MCObjectHandle obj, short index, WorldPt& loc)
{
	GET_CB_UPP(Get2DPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Get2DPtPtr)(MCObjectHandle obj, CBSignedShort index, WorldPt& loc);
		CALL_PROC(Get2DPt)(obj, index, loc);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetBinaryConstraint(CALLBACKPTR, short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2)
{
	GET_CB_UPP(GetBinaryConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetBinaryConstraintPtr)(CBSignedShort type, MCObjectHandle obj1, MCObjectHandle obj2, CBSignedShort obj1VertexA, CBSignedShort obj1VertexB, CBSignedShort obj2VertexA, CBSignedShort obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		MCObjectHandle gsResult = CALL_PROC(GetBinaryConstraint)(type, obj1, obj2, obj1VertexA, obj1VertexB, obj2VertexA, obj2VertexB, containedObj1, containedObj2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetClosestPt(CALLBACKPTR, MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj)
{
	GET_CB_UPP(GetClosestPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClosestPtPtr)(MCObjectHandle& obj, const WorldPt& pt, short& index, Sint32& containedObj);
		CALL_PROC(GetClosestPt)(obj, pt, index, containedObj);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetClosestSide(CALLBACKPTR, MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB)
{
	GET_CB_UPP(GetClosestSide);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClosestSidePtr)(MCObjectHandle obj, const WorldPt& pt, short& indexA, short& indexB);
		CALL_PROC(GetClosestSide)(obj, pt, indexA, indexB);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_GetComponentClass(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, Sint32 &componentClass)
{
	GET_CB_UPP(GetComponentClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentClassPtr)(MCObjectHandle wall, CBSignedShort index, Sint32 &componentClass);
		CBBoolean gsResult = CALL_PROC(GetComponentClass)(wall, index, componentClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentFill(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, Sint32 &fill)
{
	GET_CB_UPP(GetComponentFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentFillPtr)(MCObjectHandle wall, CBSignedShort index, Sint32 &fill);
		CBBoolean gsResult = CALL_PROC(GetComponentFill)(wall, index, fill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentFillColors(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor)
{
	GET_CB_UPP(GetComponentFillColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentFillColorsPtr)(MCObjectHandle wall, CBSignedShort index, ColorRef &fillForeColor, ColorRef &fillBackColor);
		CBBoolean gsResult = CALL_PROC(GetComponentFillColors)(wall, index, fillForeColor, fillBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentName(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, InternalName &componentName)
{
	GET_CB_UPP(GetComponentName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentNamePtr)(MCObjectHandle wall, CBSignedShort index, InternalName &componentName);
		CBBoolean gsResult = CALL_PROC(GetComponentName)(wall, index, componentName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentPenColors(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor)
{
	GET_CB_UPP(GetComponentPenColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentPenColorsPtr)(MCObjectHandle wall, CBSignedShort index, ColorRef &leftPenForeColor, ColorRef &leftPenBackColor, ColorRef &rightPenForeColor, ColorRef &rightPenBackColor);
		CBBoolean gsResult = CALL_PROC(GetComponentPenColors)(wall, index, leftPenForeColor, leftPenBackColor, rightPenForeColor, rightPenBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




CBBoolean GS_CALLBACK GS_GetComponentPenWeights(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight)
{
	GET_CB_UPP(GetComponentPenWeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentPenWeightsPtr)(MCObjectHandle wall, CBSignedShort index, CBUnsignedByte &penWeightLeft, CBUnsignedByte &penWeightRight);
		CBBoolean gsResult = CALL_PROC(GetComponentPenWeights)(wall, index, penWeightLeft, penWeightRight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentUseFillClassAttr(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBBoolean &useClassAttr)
{
	GET_CB_UPP(GetComponentUseFillClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentUseFillClassAttrPtr)(MCObjectHandle wall, CBSignedShort index, CBBoolean &useClassAttr);
		CBBoolean gsResult = CALL_PROC(GetComponentUseFillClassAttr)(wall, index, useClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentUsePenClassAttr(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr)
{
	GET_CB_UPP(GetComponentUsePenClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentUsePenClassAttrPtr)(MCObjectHandle wall, CBSignedShort index, CBBoolean &leftPenUseClassAttr, CBBoolean &rightPenUseClassAttr);
		CBBoolean gsResult = CALL_PROC(GetComponentUsePenClassAttr)(wall, index, leftPenUseClassAttr, rightPenUseClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetComponentWidth(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, WorldCoord &width)
{
	GET_CB_UPP(GetComponentWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetComponentWidthPtr)(MCObjectHandle wall, CBSignedShort index, WorldCoord &width);
		CBBoolean gsResult = CALL_PROC(GetComponentWidth)(wall, index, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetCustomObjectColor(CALLBACKPTR, MCObjectHandle objectHand, Sint32 iTagID, ColorRef& ioColorRef)
{
	GET_CB_UPP(GetCustomObjectColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetCustomObjectColorPtr)(MCObjectHandle objectHand, Sint32 iTagID, ColorRef& ioColorRef);
		Boolean gsResult = CALL_PROC(GetCustomObjectColor)(objectHand, iTagID, ioColorRef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_GetCustomObjectPath(CALLBACKPTR, MCObjectHandle objectHand)
{
	GET_CB_UPP(GetCustomObjectPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetCustomObjectPathPtr)(MCObjectHandle objectHand);
		MCObjectHandle gsResult = CALL_PROC(GetCustomObjectPath)(objectHand);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetCustomObjectProfileGroup(CALLBACKPTR, MCObjectHandle objectHand)
{
	GET_CB_UPP(GetCustomObjectProfileGroup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetCustomObjectProfileGroupPtr)(MCObjectHandle objectHand, bool bForceSearchInAux);
		MCObjectHandle gsResult = CALL_PROC(GetCustomObjectProfileGroup)(objectHand, false);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_GetDimensionStandardVariable(CALLBACKPTR, short dimensionIndex, short fieldSelector, TVariableBlock& value)
{
	GET_CB_UPP(GetDimensionStandardVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDimensionStandardVariablePtr)(CBSignedShort dimensionIndex, CBSignedShort fieldSelector, TVariableBlock& value);
		Boolean gsResult = CALL_PROC(GetDimensionStandardVariable)(dimensionIndex, fieldSelector, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetDistanceAlongNurbsCurve(CALLBACKPTR, MCObjectHandle inNurbsCurve, double_param inParameter1, Sint32 inParameter1CurveIndex, double_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance)
{
	GET_CB_UPP(GetDistanceAlongNurbsCurve);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetDistanceAlongNurbsCurvePtr)(MCObjectHandle inNurbsCurve, CBDouble_param inParameter1, Sint32 inParameter1CurveIndex, CBDouble_param inParameter2, Sint32 inParameter2CurveIndex, double_gs& outDistance);
		Boolean gsResult = CALL_PROC(GetDistanceAlongNurbsCurve)(inNurbsCurve, inParameter1, inParameter1CurveIndex, inParameter2, inParameter2CurveIndex, outDistance);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetLocalizedPluginChoice(CALLBACKPTR, const InternalName& pluginName, const TXString& parameterName, Sint32 choiceIndex, TXString&  localizedChoice)
{
	GET_CB_UPP(GetLocalizedPluginChoice);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLocalizedPluginChoicePtr)(const InternalName& pluginName, const TXString& parameterName, Sint32 choiceIndex, TXString&  localizedChoice);
		Boolean gsResult = CALL_PROC(GetLocalizedPluginChoice)(pluginName, parameterName, choiceIndex, localizedChoice);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetLocalizedPluginName(CALLBACKPTR, const InternalName& pluginName, InternalName& localizedName)
{
	GET_CB_UPP(GetLocalizedPluginName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLocalizedPluginNamePtr)(const InternalName& pluginName, InternalName& localizedName);
		Boolean gsResult = CALL_PROC(GetLocalizedPluginName)(pluginName, localizedName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetLocalizedPluginParameter(CALLBACKPTR, const InternalName& pluginName, const TXString& parameterName, TXString&  localizedParameterName)
{
	GET_CB_UPP(GetLocalizedPluginParameter);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLocalizedPluginParameterPtr)(const InternalName& pluginName, const TXString& parameterName, TXString&  localizedParameterName);
		Boolean gsResult = CALL_PROC(GetLocalizedPluginParameter)(pluginName, parameterName, localizedParameterName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_GetNumberOfComponents(CALLBACKPTR, MCObjectHandle wall, short& numComponents)
{
	GET_CB_UPP(GetNumberOfComponents);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetNumberOfComponentsPtr)(MCObjectHandle wall, short& numComponents);
		CBBoolean gsResult = CALL_PROC(GetNumberOfComponents)(wall, numComponents);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetNurbsObjectDistanceFromPoint(CALLBACKPTR, MCObjectHandle h, const WorldPt& point, double& distance)
{
	GET_CB_UPP(GetNurbsObjectDistanceFromPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetNurbsObjectDistanceFromPointPtr)(MCObjectHandle h, const WorldPt& point, double& distance);
		Boolean gsResult = CALL_PROC(GetNurbsObjectDistanceFromPoint)(h, point, distance);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetObjectProperty(CALLBACKPTR, MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue)
{
	GET_CB_UPP(GetObjectProperty);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjectPropertyPtr)(MCObjectHandle hObject, Sint32 inPropID, Boolean& outValue);
		Boolean gsResult = CALL_PROC(GetObjectProperty)(hObject, inPropID, outValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetObjectPropertyChar(CALLBACKPTR, MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue)
{
	GET_CB_UPP(GetObjectPropertyChar);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjectPropertyCharPtr)(MCObjectHandle hObject, Sint32 inPropID, unsigned char& outValue);
		Boolean gsResult = CALL_PROC(GetObjectPropertyChar)(hObject, inPropID, outValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetObjectVariable(CALLBACKPTR, MCObjectHandle theObject, short setSelector, TVariableBlock& value)
{
	GET_CB_UPP(GetObjectVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetObjectVariablePtr)(MCObjectHandle theObject, CBSignedShort setSelector, TVariableBlock& value, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(GetObjectVariable)(theObject, setSelector, value, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetParameterOnNurbsCurve(CALLBACKPTR, MCObjectHandle h, const WorldPt3& point, double& parameter, Sint32& index)
{
	GET_CB_UPP(GetParameterOnNurbsCurve);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetParameterOnNurbsCurvePtr)(MCObjectHandle h, const WorldPt3& point, double& parameter, Sint32& index, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(GetParameterOnNurbsCurve)(h, point, parameter, index, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetPointAndParameterOnNurbsCurveAtGivenLength(CALLBACKPTR, MCObjectHandle inNurbCurve, double_param inPercentOfLength, WorldPt3& outPointOnCurve, double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex)
{
	GET_CB_UPP(GetPointAndParameterOnNurbsCurveAtGivenLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetPointAndParameterOnNurbsCurveAtGivenLengthPtr)(MCObjectHandle inNurbCurve, CBDouble_param inPercentOfLength, WorldPt3& outPointOnCurve, double_gs& outParametricParameter, Sint32& outPiecewiseCurveIndex);
		Boolean gsResult = CALL_PROC(GetPointAndParameterOnNurbsCurveAtGivenLength)(inNurbCurve, inPercentOfLength, outPointOnCurve, outParametricParameter, outPiecewiseCurveIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetRoofEdge(CALLBACKPTR, MCObjectHandle object, short index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight)
{
	GET_CB_UPP(GetRoofEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetRoofEdgePtr)(MCObjectHandle object, CBSignedShort index, WorldPt& vertexPt, double_gs& slope, WorldCoord& projection, WorldCoord& eaveHeight);
		Boolean gsResult = CALL_PROC(GetRoofEdge)(object, index, vertexPt, slope, projection, eaveHeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_GetSingularConstraint(CALLBACKPTR, short type, MCObjectHandle obj, short vertexA, short vertexB)
{
	GET_CB_UPP(GetSingularConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetSingularConstraintPtr)(CBSignedShort type, MCObjectHandle obj, CBSignedShort vertexA, CBSignedShort vertexB);
		MCObjectHandle gsResult = CALL_PROC(GetSingularConstraint)(type, obj, vertexA, vertexB);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetViewportClassVisibility(CALLBACKPTR, MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType)
{
	GET_CB_UPP(GetViewportClassVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetViewportClassVisibilityPtr)(MCObjectHandle viewportHandle, InternalIndex classIndex, short& visibilityType);
		Boolean gsResult = CALL_PROC(GetViewportClassVisibility)(viewportHandle, classIndex, visibilityType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_GetViewportCropObject(CALLBACKPTR, MCObjectHandle viewportHandle)
{
	GET_CB_UPP(GetViewportCropObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetViewportCropObjectPtr)(MCObjectHandle viewportHandle);
		MCObjectHandle gsResult = CALL_PROC(GetViewportCropObject)(viewportHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetViewportGroup(CALLBACKPTR, MCObjectHandle viewportHandle, short groupType)
{
	GET_CB_UPP(GetViewportGroup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetViewportGroupPtr)(MCObjectHandle viewportHandle, CBSignedShort groupType);
		MCObjectHandle gsResult = CALL_PROC(GetViewportGroup)(viewportHandle, groupType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetViewportGroupParent(CALLBACKPTR, MCObjectHandle groupHandle)
{
	GET_CB_UPP(GetViewportGroupParent);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetViewportGroupParentPtr)(MCObjectHandle groupHandle);
		MCObjectHandle gsResult = CALL_PROC(GetViewportGroupParent)(groupHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_GetViewportLayerVisibility(CALLBACKPTR, MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType)
{
	GET_CB_UPP(GetViewportLayerVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetViewportLayerVisibilityPtr)(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short& visibilityType);
		Boolean gsResult = CALL_PROC(GetViewportLayerVisibility)(viewportHandle, layerHandle, visibilityType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MeshErrorType GS_CALLBACK GS_GroupToMesh(CALLBACKPTR, MCObjectHandle theMesh)
{
	GET_CB_UPP(GroupToMesh);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MeshErrorType (*GroupToMeshPtr)(MCObjectHandle theMesh);
		MeshErrorType gsResult = CALL_PROC(GroupToMesh)(theMesh);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return (MeshErrorType) -3;
}


Boolean GS_CALLBACK GS_HasConstraint(CALLBACKPTR, MCObjectHandle obj)
{
	GET_CB_UPP(HasConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*HasConstraintPtr)(MCObjectHandle obj);
		Boolean gsResult = CALL_PROC(HasConstraint)(obj);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_InsertAllParametersAsWidgets(CALLBACKPTR, Sint32 inObjectID)
{
	GET_CB_UPP(InsertAllParametersAsWidgets);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*InsertAllParametersAsWidgetsPtr)(Sint32 inObjectID);
		Boolean gsResult = CALL_PROC(InsertAllParametersAsWidgets)(inObjectID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}



Boolean GS_CALLBACK GS_InsertParameterWidget(CALLBACKPTR, Sint32 ObjectID, Sint32 position, Sint32 parameterID, const TXString& text, Sint32 data)
{
	GET_CB_UPP(InsertParameterWidget);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*InsertParameterWidgetPtr)(Sint32 ObjectID, Sint32 position, Sint32 parameterID, const TXString& text, Sint32 data);
		Boolean gsResult = CALL_PROC(InsertParameterWidget)(ObjectID, position, parameterID, text, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_InsertWidget(CALLBACKPTR, Sint32 ObjectID, Sint32 position, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data)
{
	GET_CB_UPP(InsertWidget);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*InsertWidgetPtr)(Sint32 ObjectID, Sint32 position, Sint32 widgetType, Sint32 eventID, const TXString& text, Sint32 data);
		Boolean gsResult = CALL_PROC(InsertWidget)(ObjectID, position, widgetType, eventID, text, data);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsObjectFromReferencedFile(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(IsObjectFromReferencedFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsObjectFromReferencedFilePtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(IsObjectFromReferencedFile)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsViewportGroupContainedObject(CALLBACKPTR, MCObjectHandle objectHandle, short groupType)
{
	GET_CB_UPP(IsViewportGroupContainedObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsViewportGroupContainedObjectPtr)(MCObjectHandle objectHandle, CBSignedShort groupType);
		Boolean gsResult = CALL_PROC(IsViewportGroupContainedObject)(objectHandle, groupType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_MakePolyshapeValid(CALLBACKPTR, MCObjectHandle thePoly)
{
	GET_CB_UPP(MakePolyshapeValid);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MakePolyshapeValidPtr)(MCObjectHandle thePoly);
		CALL_PROC(MakePolyshapeValid)(thePoly);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MeshErrorType GS_CALLBACK GS_MeshToGroup(CALLBACKPTR, MCObjectHandle theMesh)
{
	GET_CB_UPP(MeshToGroup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MeshErrorType (*MeshToGroupPtr)(MCObjectHandle theMesh);
		MeshErrorType gsResult = CALL_PROC(MeshToGroup)(theMesh);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return (MeshErrorType) -3;
}


void GS_CALLBACK GS_MoveObject(CALLBACKPTR, MCObjectHandle h, WorldCoord dx, WorldCoord dy)
{
	GET_CB_UPP(MoveObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MoveObjectPtr)(MCObjectHandle h, CBWorldCoord_param dx, CBWorldCoord_param dy);
		CALL_PROC(MoveObject)(h, dx, dy);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_MoveObject3D(CALLBACKPTR, MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz, bool inMoveScreenObjectsWith3D )
{
	GET_CB_UPP(MoveObject3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MoveObject3DPtr)(MCObjectHandle h, CBWorldCoord_param dx, CBWorldCoord_param dy, CBWorldCoord_param dz, bool inMoveScreenObjectsWith3D);
		CALL_PROC(MoveObject3D)(h, dx, dy, dz, inMoveScreenObjectsWith3D);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_NotifyLayerChange(CALLBACKPTR, StatusData liAdditionalData)
{
	GET_CB_UPP(NotifyLayerChange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*NotifyLayerChangePtr)(StatusData liAdditionalData);
		CALL_PROC(NotifyLayerChange)(liAdditionalData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_RemoveCustomObjectColor(CALLBACKPTR, MCObjectHandle objectHand, Sint32 iTagID)
{
	GET_CB_UPP(RemoveCustomObjectColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveCustomObjectColorPtr)(MCObjectHandle objectHand, Sint32 iTagID);
		Boolean gsResult = CALL_PROC(RemoveCustomObjectColor)(objectHand, iTagID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_RemoveRoofEdge(CALLBACKPTR, MCObjectHandle object, short index)
{
	GET_CB_UPP(RemoveRoofEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RemoveRoofEdgePtr)(MCObjectHandle object, CBSignedShort index);
		Boolean gsResult = CALL_PROC(RemoveRoofEdge)(object, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ResetObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(ResetObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ResetObjectPtr)(MCObjectHandle h);
		CALL_PROC(ResetObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RotateObjectN(CALLBACKPTR, MCObjectHandle& h, const WorldPt& rotCenter, double_param angle)
{
	GET_CB_UPP(RotateObjectN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RotateObjectNPtr)(MCObjectHandle& h, const WorldPt& rotCenter, CBDouble_param angle);
		CALL_PROC(RotateObjectN)(h, rotCenter, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_ScaleObject3D(CALLBACKPTR, MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector)
{
	GET_CB_UPP(ScaleObject3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ScaleObject3DPtr)(MCObjectHandle ioObject, const WorldPt3& scaleCen, const Vector& scaleVector, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(ScaleObject3D)(ioObject, scaleCen, scaleVector, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ScaleObjectN(CALLBACKPTR, MCObjectHandle h, const WorldPt& scaleCen, double_param scaleX, double_param scaleY)
{
	GET_CB_UPP(ScaleObjectN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ScaleObjectNPtr)(MCObjectHandle h, const WorldPt& scaleCen, CBDouble_param scaleX, CBDouble_param scaleY);
		CALL_PROC(ScaleObjectN)(h, scaleCen, scaleX, scaleY);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetBinaryConstraint(CALLBACKPTR, short type, MCObjectHandle obj1, MCObjectHandle obj2, short obj1VertexA, short obj1VertexB, short obj2VertexA, short obj2VertexB, Sint32 containedObj1, Sint32 containedObj2)
{
	GET_CB_UPP(SetBinaryConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetBinaryConstraintPtr)(CBSignedShort type, MCObjectHandle obj1, MCObjectHandle obj2, CBSignedShort obj1VertexA, CBSignedShort obj1VertexB, CBSignedShort obj2VertexA, CBSignedShort obj2VertexB, Sint32 containedObj1, Sint32 containedObj2);
		Boolean gsResult = CALL_PROC(SetBinaryConstraint)(type, obj1, obj2, obj1VertexA, obj1VertexB, obj2VertexA, obj2VertexB, containedObj1, containedObj2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_SetComponentClass(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, Sint32 componentClass)
{
	GET_CB_UPP(SetComponentClass);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentClassPtr)(MCObjectHandle wall, CBSignedShort index, Sint32 componentClass);
		CBBoolean gsResult = CALL_PROC(SetComponentClass)(wall, index, componentClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentFill(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, Sint32 fill)
{
	GET_CB_UPP(SetComponentFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentFillPtr)(MCObjectHandle wall, CBSignedShort index, Sint32 fill);
		CBBoolean gsResult = CALL_PROC(SetComponentFill)(wall, index, fill);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentFillColors(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor)
{
	GET_CB_UPP(SetComponentFillColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentFillColorsPtr)(MCObjectHandle wall, CBSignedShort index, ColorRef fillForeColor, ColorRef fillBackColor);
		CBBoolean gsResult = CALL_PROC(SetComponentFillColors)(wall, index, fillForeColor, fillBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentName(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, const InternalName& componentName)
{
	GET_CB_UPP(SetComponentName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentNamePtr)(MCObjectHandle wall, CBSignedShort index, const InternalName& componentName);
		CBBoolean gsResult = CALL_PROC(SetComponentName)(wall, index, componentName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentPenColors(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor)
{
	GET_CB_UPP(SetComponentPenColors);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentPenColorsPtr)(MCObjectHandle wall, CBSignedShort index, ColorRef leftPenForeColor, ColorRef leftPenBackColor, ColorRef rightPenForeColor, ColorRef rightPenBackColor);
		CBBoolean gsResult = CALL_PROC(SetComponentPenColors)(wall, index, leftPenForeColor, leftPenBackColor, rightPenForeColor, rightPenBackColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




CBBoolean GS_CALLBACK GS_SetComponentPenWeights(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight)
{
	GET_CB_UPP(SetComponentPenWeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentPenWeightsPtr)(MCObjectHandle wall, CBSignedShort index, CBUnsignedByte penWeightLeft, CBUnsignedByte penWeightRight);
		CBBoolean gsResult = CALL_PROC(SetComponentPenWeights)(wall, index, penWeightLeft, penWeightRight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentUseFillClassAttr(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBBoolean useClassAttr)
{
	GET_CB_UPP(SetComponentUseFillClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentUseFillClassAttrPtr)(MCObjectHandle wall, CBSignedShort index, CBBoolean useClassAttr);
		CBBoolean gsResult = CALL_PROC(SetComponentUseFillClassAttr)(wall, index, useClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentUsePenClassAttr(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr)
{
	GET_CB_UPP(SetComponentUsePenClassAttr);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentUsePenClassAttrPtr)(MCObjectHandle wall, CBSignedShort index, CBBoolean leftPenUseClassAttr, CBBoolean rightPenUseClassAttr);
		CBBoolean gsResult = CALL_PROC(SetComponentUsePenClassAttr)(wall, index, leftPenUseClassAttr, rightPenUseClassAttr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetComponentWidth(CALLBACKPTR, MCObjectHandle wall, CBSignedShort index, WorldCoord width)
{
	GET_CB_UPP(SetComponentWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetComponentWidthPtr)(MCObjectHandle wall, CBSignedShort index, CBWorldCoord_param width);
		CBBoolean gsResult = CALL_PROC(SetComponentWidth)(wall, index, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetConstraintValue(CALLBACKPTR, MCObjectHandle constraint, double_param value)
{
	GET_CB_UPP(SetConstraintValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetConstraintValuePtr)(MCObjectHandle constraint, CBDouble_param value);
		CALL_PROC(SetConstraintValue)(constraint, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetCustomDimensionStandardVariable(CALLBACKPTR, short dimensionIndex, short fieldSelector, const TVariableBlock& value)
{
	GET_CB_UPP(SetCustomDimensionStandardVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetCustomDimensionStandardVariablePtr)(CBSignedShort dimensionIndex, CBSignedShort fieldSelector, const TVariableBlock& value);
		Boolean gsResult = CALL_PROC(SetCustomDimensionStandardVariable)(dimensionIndex, fieldSelector, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetCustomObjectColor(CALLBACKPTR, MCObjectHandle objectHand, Sint32 iTagID, ColorRef inColorRef)
{
	GET_CB_UPP(SetCustomObjectColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetCustomObjectColorPtr)(MCObjectHandle objectHand, Sint32 iTagID, ColorRef inColorRef);
		Boolean gsResult = CALL_PROC(SetCustomObjectColor)(objectHand, iTagID, inColorRef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetCustomObjectControlPointVisibility(CALLBACKPTR, MCObjectHandle objectHand, short controlPtIndex, Boolean setVisible)
{
	GET_CB_UPP(SetCustomObjectControlPointVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetCustomObjectControlPointVisibilityPtr)(MCObjectHandle objectHand, CBSignedShort controlPtIndex, CBBoolean setVisible);
		Boolean gsResult = CALL_PROC(SetCustomObjectControlPointVisibility)(objectHand, controlPtIndex, setVisible);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetCustomObjectPath(CALLBACKPTR, MCObjectHandle objectHand, MCObjectHandle pathHand)
{
	GET_CB_UPP(SetCustomObjectPath);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetCustomObjectPathPtr)(MCObjectHandle objectHand, MCObjectHandle pathHand);
		Boolean gsResult = CALL_PROC(SetCustomObjectPath)(objectHand, pathHand);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetCustomObjectProfileGroup(CALLBACKPTR, MCObjectHandle objectHand, MCObjectHandle profileGroupHand)
{
	GET_CB_UPP(SetCustomObjectProfileGroup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetCustomObjectProfileGroupPtr)(MCObjectHandle objectHand, MCObjectHandle profileGroupHand);
		Boolean gsResult = CALL_PROC(SetCustomObjectProfileGroup)(objectHand, profileGroupHand);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetDefinition(CALLBACKPTR, MCObjectHandle h, MCObjectHandle newDef)
{
	GET_CB_UPP(SetDefinition);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefinitionPtr)(MCObjectHandle h, MCObjectHandle newDef);
		CALL_PROC(SetDefinition)(h, newDef);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetObjectProperty(CALLBACKPTR, Sint32 inCodeRefID, Sint32 inPropID, Boolean inValue)
{
	GET_CB_UPP(SetObjectProperty);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetObjectPropertyPtr)(Sint32 inCodeRefID, Sint32 inPropID, CBBoolean inValue);
		Boolean gsResult = CALL_PROC(SetObjectProperty)(inCodeRefID, inPropID, inValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetObjectPropertyChar(CALLBACKPTR, Sint32 inCodeRefID, Sint32 inPropID, unsigned char inValue)
{
	GET_CB_UPP(SetObjectPropertyChar);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetObjectPropertyCharPtr)(Sint32 inCodeRefID, Sint32 inPropID, CBUnsignedByte inValue);
		Boolean gsResult = CALL_PROC(SetObjectPropertyChar)(inCodeRefID, inPropID, inValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetObjectVariable(CALLBACKPTR, MCObjectHandle theObject, short setSelector, const TVariableBlock& value)
{
	GET_CB_UPP(SetObjectVariable);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetObjectVariablePtr)(MCObjectHandle theObject, CBSignedShort setSelector, const TVariableBlock& value, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(SetObjectVariable)(theObject, setSelector, value, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetParameterVisibility(CALLBACKPTR, MCObjectHandle inCustomObject, short inParameterIndex, Boolean inSetVisible)
{
	GET_CB_UPP(SetParameterVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetParameterVisibilityPtr)(MCObjectHandle inCustomObject, CBSignedShort inParameterIndex, CBBoolean inSetVisible);
		CALL_PROC(SetParameterVisibility)(inCustomObject, inParameterIndex, inSetVisible);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetRoofEdge(CALLBACKPTR, MCObjectHandle object, short index, const WorldPt& vertexPt, double_param slope, WorldCoord projection, WorldCoord eaveHeight)
{
	GET_CB_UPP(SetRoofEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetRoofEdgePtr)(MCObjectHandle object, CBSignedShort index, const WorldPt& vertexPt, CBDouble_param slope, CBWorldCoord_param projection, CBWorldCoord_param eaveHeight);
		CALL_PROC(SetRoofEdge)(object, index, vertexPt, slope, projection, eaveHeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetSingularConstraint(CALLBACKPTR, short type, MCObjectHandle obj, short vertexA, short vertexB)
{
	GET_CB_UPP(SetSingularConstraint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetSingularConstraintPtr)(CBSignedShort type, MCObjectHandle obj, CBSignedShort vertexA, CBSignedShort vertexB);
		Boolean gsResult = CALL_PROC(SetSingularConstraint)(type, obj, vertexA, vertexB);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_SetViewportClassVisibility(CALLBACKPTR, MCObjectHandle viewportHandle, InternalIndex classIndex, short visibilityType)
{
	GET_CB_UPP(SetViewportClassVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetViewportClassVisibilityPtr)(MCObjectHandle viewportHandle, InternalIndex classIndex, CBSignedShort visibilityType);
		Boolean gsResult = CALL_PROC(SetViewportClassVisibility)(viewportHandle, classIndex, visibilityType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetViewportCropObject(CALLBACKPTR, MCObjectHandle viewportHandle, MCObjectHandle cropHandle)
{
	GET_CB_UPP(SetViewportCropObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetViewportCropObjectPtr)(MCObjectHandle viewportHandle, MCObjectHandle cropHandle);
		Boolean gsResult = CALL_PROC(SetViewportCropObject)(viewportHandle, cropHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetViewportLayerVisibility(CALLBACKPTR, MCObjectHandle viewportHandle, MCObjectHandle layerHandle, short visibilityType)
{
	GET_CB_UPP(SetViewportLayerVisibility);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetViewportLayerVisibilityPtr)(MCObjectHandle viewportHandle, MCObjectHandle layerHandle, CBSignedShort visibilityType);
		Boolean gsResult = CALL_PROC(SetViewportLayerVisibility)(viewportHandle, layerHandle, visibilityType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_TrimToSelectedObjects(CALLBACKPTR, MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2)
{
	GET_CB_UPP(TrimToSelectedObjects);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*TrimToSelectedObjectsPtr)(MCObjectHandle sourceObject, const WorldPt& pickPt, MCObjectHandle& result1, MCObjectHandle& result2);
		Boolean gsResult = CALL_PROC(TrimToSelectedObjects)(sourceObject, pickPt, result1, result2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_UpdateConstraintModel(CALLBACKPTR)
{
	GET_CB_UPP(UpdateConstraintModel);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*UpdateConstraintModelPtr)();
		Boolean gsResult = CALL_PROC(UpdateConstraintModel)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_UpdateViewport(CALLBACKPTR, MCObjectHandle viewportHandle)
{
	GET_CB_UPP(UpdateViewport);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UpdateViewportPtr)(MCObjectHandle viewportHandle);
		CALL_PROC(UpdateViewport)(viewportHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_ViewportHasCropObject(CALLBACKPTR, MCObjectHandle viewportHandle)
{
	GET_CB_UPP(ViewportHasCropObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ViewportHasCropObjectPtr)(MCObjectHandle viewportHandle);
		Boolean gsResult = CALL_PROC(ViewportHasCropObject)(viewportHandle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Resources
///////////////////////////////////////////


short GS_CALLBACK GS_CountResources(CALLBACKPTR, OSType inType, Boolean lookOnlyInCurrentFile)
{
	GET_CB_UPP(CountResources);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CountResourcesPtr)(OSType inType, CBBoolean lookOnlyInCurrentFile);
		short gsResult = CALL_PROC(CountResources)(inType, lookOnlyInCurrentFile);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


short GS_CALLBACK GS_GetApplicationResFile(CALLBACKPTR, short selector)
{
	GET_CB_UPP(GetApplicationResFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetApplicationResFilePtr)(CBSignedShort selector);
		short gsResult = CALL_PROC(GetApplicationResFile)(selector);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetCurrentResFile(CALLBACKPTR)
{
	GET_CB_UPP(GetCurrentResFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetCurrentResFilePtr)();
		short gsResult = CALL_PROC(GetCurrentResFile)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


GSHandle GS_CALLBACK GS_GetIndResource(CALLBACKPTR, OSType inType, short inIndex, short& outID, Boolean lookOnlyInCurrentFile)
{
	GET_CB_UPP(GetIndResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSHandle (*GetIndResourcePtr)(OSType inType, CBSignedShort inIndex, short& outID, CBBoolean lookOnlyInCurrentFile);
		GSHandle gsResult = CALL_PROC(GetIndResource)(inType, inIndex, outID, lookOnlyInCurrentFile);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


GSHandle GS_CALLBACK GS_GetResource(CALLBACKPTR, OSType type, short id, Boolean lookOnlyInCurrentFile)
{
	GET_CB_UPP(GetResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef GSHandle (*GetResourcePtr)(OSType type, CBSignedShort id, CBBoolean lookOnlyInCurrentFile);
		GSHandle gsResult = CALL_PROC(GetResource)(type, id, lookOnlyInCurrentFile);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_GetResourceName(CALLBACKPTR, OSType inType, short inID, TXString&  outName, Boolean lookOnlyInCurrentFile)
{
	GET_CB_UPP(GetResourceName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetResourceNamePtr)(OSType inType, CBSignedShort inID, TXString&  outName, CBBoolean lookOnlyInCurrentFile);
		CALL_PROC(GetResourceName)(inType, inID, outName, lookOnlyInCurrentFile);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_ReleaseResource(CALLBACKPTR, GSHandle theResource)
{
	GET_CB_UPP(ReleaseResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ReleaseResourcePtr)(GSHandle theResource);
		CALL_PROC(ReleaseResource)(theResource);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RemoveResource(CALLBACKPTR, OSType inType, short inID)
{
	GET_CB_UPP(RemoveResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveResourcePtr)(OSType inType, CBSignedShort inID);
		CALL_PROC(RemoveResource)(inType, inID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetResourceName(CALLBACKPTR, OSType inType, short inID, const TXString& inName, Boolean lookOnlyInCurrentFile)
{
	GET_CB_UPP(SetResourceName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetResourceNamePtr)(OSType inType, CBSignedShort inID, const TXString& inName, CBBoolean lookOnlyInCurrentFile);
		CALL_PROC(SetResourceName)(inType, inID, inName, lookOnlyInCurrentFile);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_UseResFile(CALLBACKPTR, short inFileID)
{
	GET_CB_UPP(UseResFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UseResFilePtr)(CBSignedShort inFileID);
		CALL_PROC(UseResFile)(inFileID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_WriteResource(CALLBACKPTR, GSHandle inResource, OSType inType, short inID)
{
	GET_CB_UPP(WriteResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WriteResourcePtr)(GSHandle inResource, OSType inType, CBSignedShort inID);
		Boolean gsResult = CALL_PROC(WriteResource)(inResource, inType, inID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Selection Manipulation
///////////////////////////////////////////


MCObjectHandle GS_CALLBACK GS_FirstSelectedObject(CALLBACKPTR)
{
	GET_CB_UPP(FirstSelectedObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*FirstSelectedObjectPtr)();
		MCObjectHandle gsResult = CALL_PROC(FirstSelectedObject)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_GetSelectionBounds(CALLBACKPTR, WorldRect& bounds, BoundsType type)
{
	GET_CB_UPP(GetSelectionBounds);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetSelectionBoundsPtr)(WorldRect& bounds, BoundsType type);
		CALL_PROC(GetSelectionBounds)(bounds, type);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_GetSelectionBoundsCube(CALLBACKPTR, WorldCube &theCube)
{
	GET_CB_UPP(GetSelectionBoundsCube);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetSelectionBoundsCubePtr)(WorldCube &theCube, bool bUseLegacyZ);
		Sint32 gsResult = CALL_PROC(GetSelectionBoundsCube)(theCube, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_MoveSelection(CALLBACKPTR, WorldCoord dx, WorldCoord dy)
{
	GET_CB_UPP(MoveSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MoveSelectionPtr)(CBWorldCoord_param dx, CBWorldCoord_param dy);
		CALL_PROC(MoveSelection)(dx, dy);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_MoveSelection3D(CALLBACKPTR, WorldCoord dx, WorldCoord dy, WorldCoord dz)
{
	GET_CB_UPP(MoveSelection3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MoveSelection3DPtr)(CBWorldCoord_param dx, CBWorldCoord_param dy, CBWorldCoord_param dz);
		CALL_PROC(MoveSelection3D)(dx, dy, dz);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RotateSelectionN(CALLBACKPTR, const WorldPt& rotCen, double_param rotAngle)
{
	GET_CB_UPP(RotateSelectionN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RotateSelectionNPtr)(const WorldPt& rotCen, CBDouble_param rotAngle);
		CALL_PROC(RotateSelectionN)(rotCen, rotAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ScaleSelectionN(CALLBACKPTR, const WorldPt& scaleCen, double_param scaleX, double_param scaleY)
{
	GET_CB_UPP(ScaleSelectionN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ScaleSelectionNPtr)(const WorldPt& scaleCen, CBDouble_param scaleX, CBDouble_param scaleY);
		CALL_PROC(ScaleSelectionN)(scaleCen, scaleX, scaleY);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Text Block Objects
///////////////////////////////////////////


Boolean GS_CALLBACK GS_AddText(CALLBACKPTR, MCObjectHandle textBlock, Sint32 beforeChar, Handle newText)
{
	GET_CB_UPP(AddText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddTextPtr)(MCObjectHandle textBlock, Sint32 beforeChar, Handle newText);
		Boolean gsResult = CALL_PROC(AddText)(textBlock, beforeChar, newText);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddTextFromBuffer(CALLBACKPTR, MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize)
{
	GET_CB_UPP(AddTextFromBuffer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddTextFromBufferPtr)(MCObjectHandle textBlock, Sint32 beforeChar, const UCChar* buffer, Sint32 bufferSize);
		Boolean gsResult = CALL_PROC(AddTextFromBuffer)(textBlock, beforeChar, buffer, bufferSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_CreateTextBlock(CALLBACKPTR, const TXString& textStr, const WorldPt& textOrigin, Boolean fixedSize, WorldCoord width)
{
	GET_CB_UPP(CreateTextBlock);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateTextBlockPtr)(const TXString& textStr, const WorldPt& textOrigin, CBBoolean fixedSize, CBWorldCoord_param width);
		MCObjectHandle gsResult = CALL_PROC(CreateTextBlock)(textStr, textOrigin, fixedSize, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DeleteText(CALLBACKPTR, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars)
{
	GET_CB_UPP(DeleteText);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteTextPtr)(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars);
		CALL_PROC(DeleteText)(textBlock, firstChar, numChars);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_GetCharNumFromPoint(CALLBACKPTR, MCObjectHandle textBlock, const WorldPt& pt)
{
	GET_CB_UPP(GetCharNumFromPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetCharNumFromPointPtr)(MCObjectHandle textBlock, const WorldPt& pt);
		Sint32 gsResult = CALL_PROC(GetCharNumFromPoint)(textBlock, pt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}

\

void GS_CALLBACK GS_GetTextColor(CALLBACKPTR, MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor)
{
	GET_CB_UPP(GetTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextColorPtr)(MCObjectHandle textBlock, Sint32 charNum, ColorRef& charColor);
		CALL_PROC(GetTextColor)(textBlock, charNum, charColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextFontIndex(CALLBACKPTR, MCObjectHandle textBlock, Sint32 charNum, short& fontIndex)
{
	GET_CB_UPP(GetTextFontIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextFontIndexPtr)(MCObjectHandle textBlock, Sint32 charNum, short& fontIndex);
		CALL_PROC(GetTextFontIndex)(textBlock, charNum, fontIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextJustification(CALLBACKPTR, MCObjectHandle textBlock, short& justification)
{
	GET_CB_UPP(GetTextJustification);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextJustificationPtr)(MCObjectHandle textBlock, short& justification);
		CALL_PROC(GetTextJustification)(textBlock, justification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_GetTextLength(CALLBACKPTR, MCObjectHandle textBlock)
{
	GET_CB_UPP(GetTextLength);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetTextLengthPtr)(MCObjectHandle textBlock);
		Sint32 gsResult = CALL_PROC(GetTextLength)(textBlock);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetTextLineHeight(CALLBACKPTR, MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height)
{
	GET_CB_UPP(GetTextLineHeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextLineHeightPtr)(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& height);
		CALL_PROC(GetTextLineHeight)(textBlock, charNum, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextOrientationN(CALLBACKPTR, MCObjectHandle h, double_gs& angle, short& flipState)
{
	GET_CB_UPP(GetTextOrientationN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextOrientationNPtr)(MCObjectHandle h, double_gs& angle, short& flipState);
		CALL_PROC(GetTextOrientationN)(h, angle, flipState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextSize(CALLBACKPTR, MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize)
{
	GET_CB_UPP(GetTextSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextSizePtr)(MCObjectHandle textBlock, Sint32 charNum, WorldCoord& charSize);
		CALL_PROC(GetTextSize)(textBlock, charNum, charSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextStyle(CALLBACKPTR, MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle)
{
	GET_CB_UPP(GetTextStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextStylePtr)(MCObjectHandle textBlock, Sint32 charNum, unsigned char& charStyle);
		CALL_PROC(GetTextStyle)(textBlock, charNum, charStyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextVerticalAlignment(CALLBACKPTR, MCObjectHandle textBlock, short& verticalAlignment)
{
	GET_CB_UPP(GetTextVerticalAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextVerticalAlignmentPtr)(MCObjectHandle textBlock, short& verticalAlignment);
		CALL_PROC(GetTextVerticalAlignment)(textBlock, verticalAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetTextVerticalSpacing(CALLBACKPTR, MCObjectHandle textBlock, short& spacing, WorldCoord& height)
{
	GET_CB_UPP(GetTextVerticalSpacing);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTextVerticalSpacingPtr)(MCObjectHandle textBlock, short& spacing, WorldCoord& height);
		CALL_PROC(GetTextVerticalSpacing)(textBlock, spacing, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetTextWidth(CALLBACKPTR, MCObjectHandle textBlock, WorldCoord& width)
{
	GET_CB_UPP(GetTextWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetTextWidthPtr)(MCObjectHandle textBlock, WorldCoord& width);
		Boolean gsResult = CALL_PROC(GetTextWidth)(textBlock, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetTextWrap(CALLBACKPTR, MCObjectHandle textBlock, Boolean& wrapped)
{
	GET_CB_UPP(GetTextWrap);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetTextWrapPtr)(MCObjectHandle textBlock, Boolean& wrapped);
		Boolean gsResult = CALL_PROC(GetTextWrap)(textBlock, wrapped);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetTextColor(CALLBACKPTR, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor)
{
	GET_CB_UPP(SetTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextColorPtr)(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, ColorRef charColor);
		CALL_PROC(SetTextColor)(textBlock, firstChar, numChars, charColor);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextFontIndex(CALLBACKPTR, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, short fontIndex)
{
	GET_CB_UPP(SetTextFontIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextFontIndexPtr)(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, CBSignedShort fontIndex);
		CALL_PROC(SetTextFontIndex)(textBlock, firstChar, numChars, fontIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextJustification(CALLBACKPTR, MCObjectHandle textBlock, short justification)
{
	GET_CB_UPP(SetTextJustification);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextJustificationPtr)(MCObjectHandle textBlock, CBSignedShort justification);
		CALL_PROC(SetTextJustification)(textBlock, justification);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextOrientationN(CALLBACKPTR, MCObjectHandle h, double_param angle, short flipState)
{
	GET_CB_UPP(SetTextOrientationN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextOrientationNPtr)(MCObjectHandle h, CBDouble_param angle, CBSignedShort flipState);
		CALL_PROC(SetTextOrientationN)(h, angle, flipState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextSize(CALLBACKPTR, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, WorldCoord charSize)
{
	GET_CB_UPP(SetTextSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextSizePtr)(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, CBWorldCoord_param charSize);
		CALL_PROC(SetTextSize)(textBlock, firstChar, numChars, charSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextStyle(CALLBACKPTR, MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, unsigned char charStyle)
{
	GET_CB_UPP(SetTextStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextStylePtr)(MCObjectHandle textBlock, Sint32 firstChar, Sint32 numChars, CBUnsignedByte charStyle);
		CALL_PROC(SetTextStyle)(textBlock, firstChar, numChars, charStyle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextVerticalAlignment(CALLBACKPTR, MCObjectHandle textBlock, short verticalAlignment)
{
	GET_CB_UPP(SetTextVerticalAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextVerticalAlignmentPtr)(MCObjectHandle textBlock, CBSignedShort verticalAlignment);
		CALL_PROC(SetTextVerticalAlignment)(textBlock, verticalAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextVerticalSpacing(CALLBACKPTR, MCObjectHandle textBlock, short spacing, WorldCoord height)
{
	GET_CB_UPP(SetTextVerticalSpacing);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextVerticalSpacingPtr)(MCObjectHandle textBlock, CBSignedShort spacing, CBWorldCoord_param height);
		CALL_PROC(SetTextVerticalSpacing)(textBlock, spacing, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextWidth(CALLBACKPTR, MCObjectHandle textBlock, WorldCoord width)
{
	GET_CB_UPP(SetTextWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextWidthPtr)(MCObjectHandle textBlock, CBWorldCoord_param width);
		CALL_PROC(SetTextWidth)(textBlock, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextWrap(CALLBACKPTR, MCObjectHandle textBlock, Boolean wrapped)
{
	GET_CB_UPP(SetTextWrap);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextWrapPtr)(MCObjectHandle textBlock, CBBoolean wrapped);
		CALL_PROC(SetTextWrap)(textBlock, wrapped);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SpellCheckTextBuffer(CALLBACKPTR, GSHandle charsHandle, Boolean textChanged)
{
	GET_CB_UPP(SpellCheckTextBuffer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SpellCheckTextBufferPtr)(GSHandle charsHandle, CBBoolean textChanged);
		CALL_PROC(SpellCheckTextBuffer)(charsHandle, textChanged);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Textures
///////////////////////////////////////////


void GS_CALLBACK GS_AttachDefaultTextureSpace(CALLBACKPTR, MCObjectHandle object, short multiPartID)
{
	GET_CB_UPP(AttachDefaultTextureSpace);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AttachDefaultTextureSpacePtr)(MCObjectHandle object, CBSignedShort multiPartID);
		CALL_PROC(AttachDefaultTextureSpace)(object, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_CreateShaderRecord(CALLBACKPTR, MCObjectHandle texture, Sint32 family, Sint32 prototype)
{
	GET_CB_UPP(CreateShaderRecord);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateShaderRecordPtr)(MCObjectHandle texture, Sint32 family, Sint32 prototype);
		MCObjectHandle gsResult = CALL_PROC(CreateShaderRecord)(texture, family, prototype);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateTexture(CALLBACKPTR)
{
	GET_CB_UPP(CreateTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateTexturePtr)();
		MCObjectHandle gsResult = CALL_PROC(CreateTexture)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateTextureBitmap(CALLBACKPTR)
{
	GET_CB_UPP(CreateTextureBitmap);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateTextureBitmapPtr)();
		MCObjectHandle gsResult = CALL_PROC(CreateTextureBitmap)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateTextureBitmapFromPaintNode(CALLBACKPTR, MCObjectHandle paintNodeObject)
{
	GET_CB_UPP(CreateTextureBitmapFromPaintNode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateTextureBitmapFromPaintNodePtr)(MCObjectHandle paintNodeObject);
		MCObjectHandle gsResult = CALL_PROC(CreateTextureBitmapFromPaintNode)(paintNodeObject);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DeleteTextureSpace(CALLBACKPTR, MCObjectHandle object, short multiPartID)
{
	GET_CB_UPP(DeleteTextureSpace);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteTextureSpacePtr)(MCObjectHandle object, CBSignedShort multiPartID);
		CALL_PROC(DeleteTextureSpace)(object, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_EditShaderRecord(CALLBACKPTR, MCObjectHandle shaderRecord)
{
	GET_CB_UPP(EditShaderRecord);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EditShaderRecordPtr)(MCObjectHandle shaderRecord);
		Boolean gsResult = CALL_PROC(EditShaderRecord)(shaderRecord);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_EditTexture(CALLBACKPTR, MCObjectHandle texture)
{
	GET_CB_UPP(EditTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EditTexturePtr)(MCObjectHandle texture);
		Boolean gsResult = CALL_PROC(EditTexture)(texture);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return kFalse;
}

Boolean GS_CALLBACK GS_EditTextureSpace(CALLBACKPTR, MCObjectHandle texturedObject, short multiPartID)
{
	GET_CB_UPP(EditTextureSpace);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EditTextureSpacePtr)(MCObjectHandle texturedObject, CBSignedShort multiPartID);
		Boolean gsResult = CALL_PROC(EditTextureSpace)(texturedObject, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


InternalIndex GS_CALLBACK GS_GetClGenTexture(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClGenTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetClGenTexturePtr)(InternalIndex index);
		InternalIndex gsResult = CALL_PROC(GetClGenTexture)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetClRoofTextures(CALLBACKPTR, InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer)
{
	GET_CB_UPP(GetClRoofTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClRoofTexturesPtr)(InternalIndex index, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		CALL_PROC(GetClRoofTextures)(index, top, edge, dormer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetClUseTexture(CALLBACKPTR, InternalIndex index)
{
	GET_CB_UPP(GetClUseTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetClUseTexturePtr)(InternalIndex index);
		Boolean gsResult = CALL_PROC(GetClUseTexture)(index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetClWallTextures(CALLBACKPTR, InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center)
{
	GET_CB_UPP(GetClWallTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetClWallTexturesPtr)(InternalIndex index, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		CALL_PROC(GetClWallTextures)(index, right, left, center);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetShaderRecord(CALLBACKPTR, MCObjectHandle parentNode, Sint32 family)
{
	GET_CB_UPP(GetShaderRecord);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetShaderRecordPtr)(MCObjectHandle parentNode, Sint32 family);
		MCObjectHandle gsResult = CALL_PROC(GetShaderRecord)(parentNode, family);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


InternalIndex GS_CALLBACK GS_GetTextureRef(CALLBACKPTR, MCObjectHandle object, short multiPartID, Boolean resolveByClass)
{
	GET_CB_UPP(GetTextureRef);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetTextureRefPtr)(MCObjectHandle object, CBSignedShort multiPartID, CBBoolean resolveByClass);
		InternalIndex gsResult = CALL_PROC(GetTextureRef)(object, multiPartID, resolveByClass);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetTextures(CALLBACKPTR, MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture)
{
	GET_CB_UPP(GetTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetTexturesPtr)(MCObjectHandle h, InternalIndex& primaryTexture, InternalIndex& secondaryTexture, InternalIndex& tertiaryTexture);
		CALL_PROC(GetTextures)(h, primaryTexture, secondaryTexture, tertiaryTexture);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetTextureSpace(CALLBACKPTR, MCObjectHandle object, short multiPartID)
{
	GET_CB_UPP(GetTextureSpace);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetTextureSpacePtr)(MCObjectHandle object, CBSignedShort multiPartID);
		MCObjectHandle gsResult = CALL_PROC(GetTextureSpace)(object, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


InternalIndex GS_CALLBACK GS_GetVPClassGenTexture(CALLBACKPTR, MCObjectHandle viewport, InternalIndex classIndex)
{
	GET_CB_UPP(GetVPClassGenTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef InternalIndex (*GetVPClassGenTexturePtr)(MCObjectHandle viewport, InternalIndex classIndex);
		InternalIndex gsResult = CALL_PROC(GetVPClassGenTexture)(viewport, classIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetVPClassRoofTextures(CALLBACKPTR, MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer)
{
	GET_CB_UPP(GetVPClassRoofTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetVPClassRoofTexturesPtr)(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& top, InternalIndex& edge, InternalIndex& dormer);
		CALL_PROC(GetVPClassRoofTextures)(viewport, classIndex, top, edge, dormer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetVPClassWallTextures(CALLBACKPTR, MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center)
{
	GET_CB_UPP(GetVPClassWallTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetVPClassWallTexturesPtr)(MCObjectHandle viewport, InternalIndex classIndex, InternalIndex& right, InternalIndex& left, InternalIndex& center);
		CALL_PROC(GetVPClassWallTextures)(viewport, classIndex, right, left, center);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClGenTexture(CALLBACKPTR, InternalIndex index, InternalIndex texture)
{
	GET_CB_UPP(SetClGenTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClGenTexturePtr)(InternalIndex index, InternalIndex texture);
		CALL_PROC(SetClGenTexture)(index, texture);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClRoofTextures(CALLBACKPTR, InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer)
{
	GET_CB_UPP(SetClRoofTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClRoofTexturesPtr)(InternalIndex index, InternalIndex top, InternalIndex edge, InternalIndex dormer);
		CALL_PROC(SetClRoofTextures)(index, top, edge, dormer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClUseTexture(CALLBACKPTR, InternalIndex index, Boolean use)
{
	GET_CB_UPP(SetClUseTexture);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClUseTexturePtr)(InternalIndex index, CBBoolean use);
		CALL_PROC(SetClUseTexture)(index, use);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetClWallTextures(CALLBACKPTR, InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center)
{
	GET_CB_UPP(SetClWallTextures);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetClWallTexturesPtr)(InternalIndex index, InternalIndex right, InternalIndex left, InternalIndex center);
		CALL_PROC(SetClWallTextures)(index, right, left, center);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDefaultTextureSpace(CALLBACKPTR, MCObjectHandle object, MCObjectHandle space, short multiPartID)
{
	GET_CB_UPP(SetDefaultTextureSpace);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDefaultTextureSpacePtr)(MCObjectHandle object, MCObjectHandle space, CBSignedShort multiPartID);
		CALL_PROC(SetDefaultTextureSpace)(object, space, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextureRef(CALLBACKPTR, MCObjectHandle object, InternalIndex textureRef, short multiPartID)
{
	GET_CB_UPP(SetTextureRef);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextureRefPtr)(MCObjectHandle object, InternalIndex textureRef, CBSignedShort multiPartID);
		CALL_PROC(SetTextureRef)(object, textureRef, multiPartID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Tool Utilities
///////////////////////////////////////////


MCObjectHandleID GS_CALLBACK GS_AddToolPersistentDraw(CALLBACKPTR, GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv)
{
	GET_CB_UPP(AddToolPersistentDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandleID (*AddToolPersistentDrawPtr)(GS_PersistentDrawProcPtr drawProcPtr, void *drawEnv);
		MCObjectHandleID gsResult = CALL_PROC(AddToolPersistentDraw)(drawProcPtr, drawEnv);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


MCObjectHandleID GS_CALLBACK GS_AddToolSnapGeometry(CALLBACKPTR, MCObjectHandle inSnapGeometry)
{
	GET_CB_UPP(AddToolSnapGeometry);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandleID (*AddToolSnapGeometryPtr)(MCObjectHandle inSnapGeometry);
		MCObjectHandleID gsResult = CALL_PROC(AddToolSnapGeometry)(inSnapGeometry);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_BoxToolDraw(CALLBACKPTR)
{
	GET_CB_UPP(BoxToolDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*BoxToolDrawPtr)();
		CALL_PROC(BoxToolDraw)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_ClearAllToolPts(CALLBACKPTR)
{
	GET_CB_UPP(ClearAllToolPts);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*ClearAllToolPtsPtr)();
		Boolean gsResult = CALL_PROC(ClearAllToolPts)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ClearDataDisplayBar(CALLBACKPTR)
{
	GET_CB_UPP(ClearDataDisplayBar);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ClearDataDisplayBarPtr)();
		CALL_PROC(ClearDataDisplayBar)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_ClickDragToolStatus(CALLBACKPTR)
{
	GET_CB_UPP(ClickDragToolStatus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*ClickDragToolStatusPtr)();
		Sint32 gsResult = CALL_PROC(ClickDragToolStatus)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_CustomBarCreate(CALLBACKPTR, short inNumFields, CustomBarRefID& outCustomBarRefID)
{
	GET_CB_UPP(CustomBarCreate);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarCreatePtr)(CBSignedShort inNumFields, CustomBarRefID& outCustomBarRefID);
		Boolean gsResult = CALL_PROC(CustomBarCreate)(inNumFields, outCustomBarRefID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarGetFieldInfo(CALLBACKPTR, CustomBarRefID inCustomBarID, short inFieldIndex, CustomBarFieldInfo& inFieldInfo)
{
	GET_CB_UPP(CustomBarGetFieldInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarGetFieldInfoPtr)(CustomBarRefID inCustomBarID, CBSignedShort inFieldIndex, CustomBarFieldInfo& inFieldInfo);
		Boolean gsResult = CALL_PROC(CustomBarGetFieldInfo)(inCustomBarID, inFieldIndex, inFieldInfo);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarInstall(CALLBACKPTR, CustomBarRefID inCustomBarID)
{
	GET_CB_UPP(CustomBarInstall);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarInstallPtr)(CustomBarRefID inCustomBarID);
		Boolean gsResult = CALL_PROC(CustomBarInstall)(inCustomBarID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarRelease(CALLBACKPTR, CustomBarRefID inCustomBarRefID)
{
	GET_CB_UPP(CustomBarRelease);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarReleasePtr)(CustomBarRefID inCustomBarRefID);
		Boolean gsResult = CALL_PROC(CustomBarRelease)(inCustomBarRefID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarSetFieldAngle(CALLBACKPTR, CustomBarRefID inCustomBarID, short inFieldIndex, const double& inDegrees)
{
	GET_CB_UPP(CustomBarSetFieldAngle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarSetFieldAnglePtr)(CustomBarRefID inCustomBarID, CBSignedShort inFieldIndex, const double& inDegrees);
		Boolean gsResult = CALL_PROC(CustomBarSetFieldAngle)(inCustomBarID, inFieldIndex, inDegrees);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarSetFieldInfo(CALLBACKPTR, CustomBarRefID inCustomBarID, short inFieldIndex, const CustomBarFieldInfo& inFieldInfo)
{
	GET_CB_UPP(CustomBarSetFieldInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarSetFieldInfoPtr)(CustomBarRefID inCustomBarID, CBSignedShort inFieldIndex, const CustomBarFieldInfo& inFieldInfo);
		Boolean gsResult = CALL_PROC(CustomBarSetFieldInfo)(inCustomBarID, inFieldIndex, inFieldInfo);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_CustomBarSetFieldWorldCoord(CALLBACKPTR, CustomBarRefID inCustomBarID, short inFieldIndex, const WorldCoord& inCoordVal)
{
	GET_CB_UPP(CustomBarSetFieldWorldCoord);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CustomBarSetFieldWorldCoordPtr)(CustomBarRefID inCustomBarID, CBSignedShort inFieldIndex, const WorldCoord& inCoordVal);
		Boolean gsResult = CALL_PROC(CustomBarSetFieldWorldCoord)(inCustomBarID, inFieldIndex, inCoordVal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_Default2DToolDraw(CALLBACKPTR)
{
	GET_CB_UPP(Default2DToolDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Default2DToolDrawPtr)();
		CALL_PROC(Default2DToolDraw)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Default3DToolDraw(CALLBACKPTR)
{
	GET_CB_UPP(Default3DToolDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Default3DToolDrawPtr)();
		CALL_PROC(Default3DToolDraw)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawCoordArcN(CALLBACKPTR, const WorldRect& theBox, double_param startAngle, double_param sweepAngle)
{
	GET_CB_UPP(DrawCoordArcN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawCoordArcNPtr)(const WorldRect& theBox, CBDouble_param startAngle, CBDouble_param sweepAngle);
		CALL_PROC(DrawCoordArcN)(theBox, startAngle, sweepAngle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawCoordEllipse(CALLBACKPTR, WorldRect& theBox)
{
	GET_CB_UPP(DrawCoordEllipse);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawCoordEllipsePtr)(WorldRect& theBox);
		CALL_PROC(DrawCoordEllipse)(theBox);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawCoordLine(CALLBACKPTR, const WorldPt& p1, const WorldPt& p2)
{
	GET_CB_UPP(DrawCoordLine);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawCoordLinePtr)(const WorldPt& p1, const WorldPt& p2);
		CALL_PROC(DrawCoordLine)(p1, p2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawCoordLine3D(CALLBACKPTR, const WorldPt3& p1, const WorldPt3& p2)
{
	GET_CB_UPP(DrawCoordLine3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawCoordLine3DPtr)(const WorldPt3& p1, const WorldPt3& p2, bool bUseLegacyZ);
		CALL_PROC(DrawCoordLine3D)(p1, p2, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawCoordRect(CALLBACKPTR, const WorldRect& theBox)
{
	GET_CB_UPP(DrawCoordRect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawCoordRectPtr)(const WorldRect& theBox);
		CALL_PROC(DrawCoordRect)(theBox);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawDataDisplayBar(CALLBACKPTR, Boolean drawFramesFirst)
{
	GET_CB_UPP(DrawDataDisplayBar);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawDataDisplayBarPtr)(CBBoolean drawFramesFirst);
		CALL_PROC(DrawDataDisplayBar)(drawFramesFirst);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawNurbsObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(DrawNurbsObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawNurbsObjectPtr)(MCObjectHandle h);
		CALL_PROC(DrawNurbsObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DrawObject(CALLBACKPTR, MCObjectHandle h, Boolean doSelect)
{
	GET_CB_UPP(DrawObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawObjectPtr)(MCObjectHandle h, CBBoolean doSelect);
		CALL_PROC(DrawObject)(h, doSelect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetCoords(CALLBACKPTR, WorldPt& p, ViewPt& m)
{
	GET_CB_UPP(GetCoords);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetCoordsPtr)(WorldPt& p, ViewPt& m);
		CALL_PROC(GetCoords)(p, m);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_GetNumToolPts(CALLBACKPTR)
{
	GET_CB_UPP(GetNumToolPts);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetNumToolPtsPtr)();
		Sint32 gsResult = CALL_PROC(GetNumToolPts)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


const ICoreToolAccess* GS_CALLBACK GS_GetToolCoreInterface(CALLBACKPTR)
{
	GET_CB_UPP(GetToolCoreInterface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef const ICoreToolAccess* (*GetToolCoreInterfacePtr)();
		const ICoreToolAccess* gsResult = CALL_PROC(GetToolCoreInterface)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


Boolean GS_CALLBACK GS_GetToolPt2D(CALLBACKPTR, Sint32 inIndex, WorldPt& outToolPoint)
{
	GET_CB_UPP(GetToolPt2D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPt2DPtr)(Sint32 inIndex, WorldPt& outToolPoint);
		Boolean gsResult = CALL_PROC(GetToolPt2D)(inIndex, outToolPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPt3D(CALLBACKPTR, Sint32 inIndex, WorldPt3& outToolPoint)
{
	GET_CB_UPP(GetToolPt3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPt3DPtr)(Sint32 inIndex, WorldPt3& outToolPoint, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(GetToolPt3D)(inIndex, outToolPoint, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtCurrent2D(CALLBACKPTR, WorldPt& outToolPoint)
{
	GET_CB_UPP(GetToolPtCurrent2D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtCurrent2DPtr)(WorldPt& outToolPoint);
		Boolean gsResult = CALL_PROC(GetToolPtCurrent2D)(outToolPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtCurrent3D(CALLBACKPTR, WorldPt3& outToolPt)
{
	GET_CB_UPP(GetToolPtCurrent3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtCurrent3DPtr)(WorldPt3& outToolPt, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(GetToolPtCurrent3D)(outToolPt, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtCurrentViewPt(CALLBACKPTR, ViewPt& outToolPt)
{
	GET_CB_UPP(GetToolPtCurrentViewPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtCurrentViewPtPtr)(ViewPt& outToolPt);
		Boolean gsResult = CALL_PROC(GetToolPtCurrentViewPt)(outToolPt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtCurrentWorkingPlane(CALLBACKPTR, WorldPt3& outToolPt)
{
	GET_CB_UPP(GetToolPtCurrentWorkingPlane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtCurrentWorkingPlanePtr)(WorldPt3& outToolPt);
		Boolean gsResult = CALL_PROC(GetToolPtCurrentWorkingPlane)(outToolPt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtViewPoint(CALLBACKPTR, Sint32 inIndex, ViewPt& outToolPoint)
{
	GET_CB_UPP(GetToolPtViewPoint);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtViewPointPtr)(Sint32 inIndex, ViewPt& outToolPoint);
		Boolean gsResult = CALL_PROC(GetToolPtViewPoint)(inIndex, outToolPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_GetToolPtWorkingPlane(CALLBACKPTR, Sint32 inIndex, WorldPt3& outToolPoint)
{
	GET_CB_UPP(GetToolPtWorkingPlane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetToolPtWorkingPlanePtr)(Sint32 inIndex, WorldPt3& outToolPoint);
		Boolean gsResult = CALL_PROC(GetToolPtWorkingPlane)(inIndex, outToolPoint);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_InstallConstraintAlong3DLine(CALLBACKPTR, const Ray& inConstraintDescription)
{
	GET_CB_UPP(InstallConstraintAlong3DLine);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InstallConstraintAlong3DLinePtr)(const Ray& inConstraintDescription);
		CALL_PROC(InstallConstraintAlong3DLine)(inConstraintDescription);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_Interactive2DDraw(CallBackPtr cbp, short options, short shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env)
{
	GET_CB_UPP(Interactive2DDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*Interactive2DDrawPtr)(CBSignedShort options, CBSignedShort shiftConsMode, GS_I2DDrawProcPtr drawProc, void *env, CallBackPtr cbp);
		CALL_PROC(Interactive2DDraw)(options, shiftConsMode, drawProc, env, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_OnePointToolStatus(CALLBACKPTR)
{
	GET_CB_UPP(OnePointToolStatus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*OnePointToolStatusPtr)();
		Sint32 gsResult = CALL_PROC(OnePointToolStatus)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Sint32 GS_CALLBACK GS_PolyToolStatus(CALLBACKPTR)
{
	GET_CB_UPP(PolyToolStatus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*PolyToolStatusPtr)();
		Sint32 gsResult = CALL_PROC(PolyToolStatus)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_PopLastToolPt(CALLBACKPTR)
{
	GET_CB_UPP(PopLastToolPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*PopLastToolPtPtr)();
		Boolean gsResult = CALL_PROC(PopLastToolPt)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_RemoveHotSpot(CALLBACKPTR, HotSpotRefID inHotSpotID)
{
	GET_CB_UPP(RemoveHotSpot);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveHotSpotPtr)(HotSpotRefID inHotSpotID);
		CALL_PROC(RemoveHotSpot)(inHotSpotID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RemoveToolPersistentDraw(CALLBACKPTR, MCObjectHandleID persistentDrawRefID)
{
	GET_CB_UPP(RemoveToolPersistentDraw);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveToolPersistentDrawPtr)(MCObjectHandleID persistentDrawRefID);
		CALL_PROC(RemoveToolPersistentDraw)(persistentDrawRefID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_RemoveToolSnapGeometry(CALLBACKPTR, MCObjectHandleID inSnapGeometryID)
{
	GET_CB_UPP(RemoveToolSnapGeometry);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RemoveToolSnapGeometryPtr)(MCObjectHandleID inSnapGeometryID);
		CALL_PROC(RemoveToolSnapGeometry)(inSnapGeometryID);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}

void GS_CALLBACK GS_SetCursorMode(CALLBACKPTR)
{
	GET_CB_UPP(SetCursorMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetCursorModePtr)();
		CALL_PROC(SetCursorMode)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDataDisplayBarField(CALLBACKPTR, short fieldNum, BarNumberType barType, const TXString& barLabel)
{
	GET_CB_UPP(SetDataDisplayBarField);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDataDisplayBarFieldPtr)(CBSignedShort fieldNum, BarNumberType barType, const TXString& barLabel);
		CALL_PROC(SetDataDisplayBarField)(fieldNum, barType, barLabel);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetDimUserBarValue(CALLBACKPTR, short fieldNum, WorldCoord dimVal)
{
	GET_CB_UPP(SetDimUserBarValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetDimUserBarValuePtr)(CBSignedShort fieldNum, CBWorldCoord_param dimVal);
		CALL_PROC(SetDimUserBarValue)(fieldNum, dimVal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetFloatUserBarValueN(CALLBACKPTR, short fieldNum, double_param floatVal, short numPlaces)
{
	GET_CB_UPP(SetFloatUserBarValueN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetFloatUserBarValueNPtr)(CBSignedShort fieldNum, CBDouble_param floatVal, CBSignedShort numPlaces);
		CALL_PROC(SetFloatUserBarValueN)(fieldNum, floatVal, numPlaces);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTextUserBarValue(CALLBACKPTR, short fieldNum, const TXString& textVal)
{
	GET_CB_UPP(SetTextUserBarValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTextUserBarValuePtr)(CBSignedShort fieldNum, const TXString& textVal);
		CALL_PROC(SetTextUserBarValue)(fieldNum, textVal);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_SetToolProperty(CALLBACKPTR, Sint32 inCodeRefID, Sint32 inToolPropID, Boolean inValue)
{
	GET_CB_UPP(SetToolProperty);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetToolPropertyPtr)(Sint32 inCodeRefID, Sint32 inToolPropID, CBBoolean inValue);
		Boolean gsResult = CALL_PROC(SetToolProperty)(inCodeRefID, inToolPropID, inValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SetToolPropertyChar(CALLBACKPTR, Sint32 inCodeRefID, Sint32 inToolPropID, char inValue)
{
	GET_CB_UPP(SetToolPropertyChar);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetToolPropertyCharPtr)(Sint32 inCodeRefID, Sint32 inToolPropID, CBSignedByte inValue);
		Boolean gsResult = CALL_PROC(SetToolPropertyChar)(inCodeRefID, inToolPropID, inValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_ThreePointToolStatus(CALLBACKPTR)
{
	GET_CB_UPP(ThreePointToolStatus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*ThreePointToolStatusPtr)();
		Sint32 gsResult = CALL_PROC(ThreePointToolStatus)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


HotSpotRefID GS_CALLBACK GS_TrackHotSpot(CALLBACKPTR, Boolean& outIs3d, WorldPt3& outLocation)
{
	GET_CB_UPP(TrackHotSpot);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef HotSpotRefID (*TrackHotSpotPtr)(Boolean& outIs3d, WorldPt3& outLocation, bool bUseLegacyZ);
		HotSpotRefID gsResult = CALL_PROC(TrackHotSpot)(outIs3d, outLocation, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_TrackTool(CALLBACKPTR, MCObjectHandle& overObject, short& overPart, SintptrT& code)
{
	GET_CB_UPP(TrackTool);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*TrackToolPtr)(MCObjectHandle& overObject, short& overPart, SintptrT& code);
		CALL_PROC(TrackTool)(overObject, overPart, code);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_TwoPointToolStatus(CALLBACKPTR)
{
	GET_CB_UPP(TwoPointToolStatus);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*TwoPointToolStatusPtr)();
		Sint32 gsResult = CALL_PROC(TwoPointToolStatus)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}




///////////////////////////////////////////
//  Tree Walking & Manipulation
///////////////////////////////////////////


void GS_CALLBACK GS_AddObjectToContainer(CALLBACKPTR, MCObjectHandle h, MCObjectHandle container)
{
	GET_CB_UPP(AddObjectToContainer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AddObjectToContainerPtr)(MCObjectHandle h, MCObjectHandle container);
		CALL_PROC(AddObjectToContainer)(h, container);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_AuxOwner(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AuxOwner);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*AuxOwnerPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(AuxOwner)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DeleteObject(CALLBACKPTR, MCObjectHandle h, Boolean useUndo)
{
	GET_CB_UPP(DeleteObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteObjectPtr)(MCObjectHandle h, CBBoolean useUndo);
		CALL_PROC(DeleteObject)(h, useUndo);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_FindHandleDeep(CALLBACKPTR, MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused)
{
	GET_CB_UPP(FindHandleDeep);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*FindHandleDeepPtr)(MCObjectHandle handleToFind, MCObjectHandle firstObjectInSearchList, MCObjectHandle& unused);
		Boolean gsResult = CALL_PROC(FindHandleDeep)(handleToFind, firstObjectInSearchList, unused);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


MCObjectHandle GS_CALLBACK GS_FirstMemberObj(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(FirstMemberObj);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*FirstMemberObjPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(FirstMemberObj)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetDefaultContainer(CALLBACKPTR)
{
	GET_CB_UPP(GetDefaultContainer);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetDefaultContainerPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetDefaultContainer)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetDrawingHeader(CALLBACKPTR)
{
	GET_CB_UPP(GetDrawingHeader);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetDrawingHeaderPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetDrawingHeader)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetHatchListHeader(CALLBACKPTR)
{
	GET_CB_UPP(GetHatchListHeader);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetHatchListHeaderPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetHatchListHeader)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetSymbolLibraryHeader(CALLBACKPTR)
{
	GET_CB_UPP(GetSymbolLibraryHeader);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetSymbolLibraryHeaderPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetSymbolLibraryHeader)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_InsertObjectAfter(CALLBACKPTR, MCObjectHandle h, MCObjectHandle afterObject)
{
	GET_CB_UPP(InsertObjectAfter);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InsertObjectAfterPtr)(MCObjectHandle h, MCObjectHandle afterObject);
		CALL_PROC(InsertObjectAfter)(h, afterObject);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_InsertObjectBefore(CALLBACKPTR, MCObjectHandle h, MCObjectHandle beforeObject)
{
	GET_CB_UPP(InsertObjectBefore);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InsertObjectBeforePtr)(MCObjectHandle h, MCObjectHandle beforeObject);
		CALL_PROC(InsertObjectBefore)(h, beforeObject);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_LastMemberObj(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(LastMemberObj);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*LastMemberObjPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(LastMemberObj)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_NextObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(NextObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*NextObjectPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(NextObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_ParentObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(ParentObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ParentObjectPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(ParentObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_PrevObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(PrevObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*PrevObjectPtr)(MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(PrevObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_SearchForAncestorType(CALLBACKPTR, CBSignedShort objectType, MCObjectHandle h)
{
	GET_CB_UPP(SearchForAncestorType);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*SearchForAncestorTypePtr)(CBSignedShort objectType, MCObjectHandle h);
		MCObjectHandle gsResult = CALL_PROC(SearchForAncestorType)(objectType, h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_SetPageBounds(CALLBACKPTR, const WorldRect& bounds)
{
	GET_CB_UPP(SetPageBounds);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPageBoundsPtr)(const WorldRect& bounds);
		CALL_PROC(SetPageBounds)(bounds);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  <Unclassified>
///////////////////////////////////////////


Boolean GS_CALLBACK GS_AcquireExportPDFSettingsAndLocation(CALLBACKPTR, Boolean inbSeparateDocuments)
{
	GET_CB_UPP(AcquireExportPDFSettingsAndLocation);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AcquireExportPDFSettingsAndLocationPtr)(CBBoolean inbSeparateDocuments);
		Boolean gsResult = CALL_PROC(AcquireExportPDFSettingsAndLocation)(inbSeparateDocuments);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ClosePDFDocument(CALLBACKPTR)
{
	GET_CB_UPP(ClosePDFDocument);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ClosePDFDocumentPtr)();
		CALL_PROC(ClosePDFDocument)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_ExportPDFPages(CALLBACKPTR, const TXString& inSavedViewNameStr)
{
	GET_CB_UPP(ExportPDFPages);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*ExportPDFPagesPtr)(const TXString& inSavedViewNameStr);
		short gsResult = CALL_PROC(ExportPDFPages)(inSavedViewNameStr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 2;
}


Boolean GS_CALLBACK GS_OpenPDFDocument(CALLBACKPTR, const TXString& inFileNameStr)
{
	GET_CB_UPP(OpenPDFDocument);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*OpenPDFDocumentPtr)(const TXString& inFileNameStr);
		Boolean gsResult = CALL_PROC(OpenPDFDocument)(inFileNameStr);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Undo
///////////////////////////////////////////


Boolean GS_CALLBACK GS_AddAfterMoveObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AddAfterMoveObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddAfterMoveObjectPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(AddAfterMoveObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddAfterSwapObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AddAfterSwapObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddAfterSwapObjectPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(AddAfterSwapObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddBeforeMoveObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AddBeforeMoveObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddBeforeMoveObjectPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(AddBeforeMoveObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddBeforeSwapObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AddBeforeSwapObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddBeforeSwapObjectPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(AddBeforeSwapObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddBothSwapObject(CALLBACKPTR, MCObjectHandle h)
{
	GET_CB_UPP(AddBothSwapObject);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddBothSwapObjectPtr)(MCObjectHandle h);
		Boolean gsResult = CALL_PROC(AddBothSwapObject)(h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddCoordMoveObject2D(CALLBACKPTR, MCObjectHandle h, WorldCoord dx, WorldCoord dy)
{
	GET_CB_UPP(AddCoordMoveObject2D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddCoordMoveObject2DPtr)(MCObjectHandle h, CBWorldCoord_param dx, CBWorldCoord_param dy);
		Boolean gsResult = CALL_PROC(AddCoordMoveObject2D)(h, dx, dy);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_AddCoordMoveObject3D(CALLBACKPTR, MCObjectHandle h, WorldCoord dx, WorldCoord dy, WorldCoord dz)
{
	GET_CB_UPP(AddCoordMoveObject3D);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*AddCoordMoveObject3DPtr)(MCObjectHandle h, CBWorldCoord_param dx, CBWorldCoord_param dy, CBWorldCoord_param dz);
		Boolean gsResult = CALL_PROC(AddCoordMoveObject3D)(h, dx, dy, dz);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_EndUndoEvent(CALLBACKPTR)
{
	GET_CB_UPP(EndUndoEvent);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*EndUndoEventPtr)();
		Boolean gsResult = CALL_PROC(EndUndoEvent)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_NameUndoEvent(CALLBACKPTR, const TXString& name)
{
	GET_CB_UPP(NameUndoEvent);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*NameUndoEventPtr)(const TXString& name);
		CALL_PROC(NameUndoEvent)(name);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_NonUndoableActionOK(CALLBACKPTR)
{
	GET_CB_UPP(NonUndoableActionOK);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*NonUndoableActionOKPtr)();
		Boolean gsResult = CALL_PROC(NonUndoableActionOK)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetUndoMethod(CALLBACKPTR, short undoType)
{
	GET_CB_UPP(SetUndoMethod);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetUndoMethodPtr)(CBSignedShort undoType);
		CALL_PROC(SetUndoMethod)(undoType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SupportUndoAndRemove(CALLBACKPTR)
{
	GET_CB_UPP(SupportUndoAndRemove);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SupportUndoAndRemovePtr)();
		CALL_PROC(SupportUndoAndRemove)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_UndoAndRemove(CALLBACKPTR)
{
	GET_CB_UPP(UndoAndRemove);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UndoAndRemovePtr)();
		CALL_PROC(UndoAndRemove)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Utility
///////////////////////////////////////////


void GS_CALLBACK GS_AngleToStringN(CALLBACKPTR, double_param angle, TXString&  s)
{
	GET_CB_UPP(AngleToStringN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AngleToStringNPtr)(CBDouble_param angle, TXString&  s);
		CALL_PROC(AngleToStringN)(angle, s);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_AssociateLinearDimension(CALLBACKPTR, MCObjectHandle h, CBBoolean selectedObjectsMode)
{
	GET_CB_UPP(AssociateLinearDimension);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AssociateLinearDimensionPtr)(MCObjectHandle h, CBBoolean selectedObjectsMode);
		CALL_PROC(AssociateLinearDimension)(h, selectedObjectsMode);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_CallPluginLibrary(CALLBACKPTR, const TXString& routineName, PluginLibraryArgTable* argumentTable, Sint32 status)
{
	GET_CB_UPP(CallPluginLibrary);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CallPluginLibraryPtr)(const TXString& routineName, void* argumentTable, Sint32 status);
		Boolean gsResult = CALL_PROC(CallPluginLibrary)(routineName, argumentTable, status);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ClipSurface(CALLBACKPTR, MCObjectHandle h1, MCObjectHandle h2)
{
	GET_CB_UPP(ClipSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ClipSurfacePtr)(MCObjectHandle h1, MCObjectHandle h2);
		CALL_PROC(ClipSurface)(h1, h2);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_CombineIntoSurface(CALLBACKPTR, const WorldPt& insidePt)
{
	GET_CB_UPP(CombineIntoSurface);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CombineIntoSurfacePtr)(const WorldPt& insidePt);
		MCObjectHandle gsResult = CALL_PROC(CombineIntoSurface)(insidePt);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_CoordToDimString(CALLBACKPTR, WorldCoord c, TXString&  s)
{
	GET_CB_UPP(CoordToDimString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*CoordToDimStringPtr)(CBWorldCoord_param c, TXString&  s);
		CALL_PROC(CoordToDimString)(c, s);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBSignedShort GS_CALLBACK GS_CStringCompare(CALLBACKPTR, ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags)
{
	GET_CB_UPP(CStringCompare);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*CStringComparePtr)(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		CBSignedShort gsResult = CALL_PROC(CStringCompare)(cStr1, cStr2, compareFlags);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_CStringEqual(CALLBACKPTR, ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags)
{
	GET_CB_UPP(CStringEqual);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*CStringEqualPtr)(ConstGSCStrPtr cStr1, ConstGSCStrPtr cStr2, const short compareFlags);
		CBBoolean gsResult = CALL_PROC(CStringEqual)(cStr1, cStr2, compareFlags);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_DisableModules(CALLBACKPTR, Sint32 modules)
{
	GET_CB_UPP(DisableModules);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisableModulesPtr)(Sint32 modules);
		CALL_PROC(DisableModules)(modules);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DisplayContextHelpOfCurrentPlugin(CALLBACKPTR)
{
	GET_CB_UPP(DisplayContextHelpOfCurrentPlugin);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisplayContextHelpOfCurrentPluginPtr)();
		CALL_PROC(DisplayContextHelpOfCurrentPlugin)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_DisplayContextualHelp(CALLBACKPTR, const char* inIdentifier)
{
	GET_CB_UPP(DisplayContextualHelp);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*DisplayContextualHelpPtr)(const char* inIdentifier);
		Boolean gsResult = CALL_PROC(DisplayContextualHelp)(inIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_DisplayOrganizationDialog(CALLBACKPTR, short tabToSelect)
{
	GET_CB_UPP(DisplayOrganizationDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DisplayOrganizationDialogPtr)(CBSignedShort tabToSelect);
		CALL_PROC(DisplayOrganizationDialog)(tabToSelect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_DoMenuName(CALLBACKPTR, const TXString& name, short chunkIndex)
{
	GET_CB_UPP(DoMenuName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*DoMenuNamePtr)(const TXString& name, CBSignedShort chunkIndex);
		short gsResult = CALL_PROC(DoMenuName)(name, chunkIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -99;
}


Sint32 GS_CALLBACK GS_DoProgramAction(CALLBACKPTR, short actionSelector, void* actionEnv)
{
	GET_CB_UPP(DoProgramAction);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*DoProgramActionPtr)(CBSignedShort actionSelector, void* actionEnv);
		Sint32 gsResult = CALL_PROC(DoProgramAction)(actionSelector, actionEnv);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_DoubleToString(CALLBACKPTR, TNumStyleClass inNumStyle, Byte inAccuracy, Byte inFormat, double_param inDouble, TXString&  outString)
{
	GET_CB_UPP(DoubleToString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DoubleToStringPtr)(TNumStyleClass inNumStyle, CBUnsignedByte inAccuracy, CBUnsignedByte inFormat, CBDouble_param inDouble, TXString&  outString);
		CALL_PROC(DoubleToString)(inNumStyle, inAccuracy, inFormat, inDouble, outString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


#if !_WIN_EXTERNAL_ && !_GSWINSDK_
void GS_CALLBACK GS_DoUpdateOrActivate(CALLBACKPTR, EventRecord& theEvent)
{
	GET_CB_UPP(DoUpdateOrActivate);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DoUpdateOrActivatePtr)(EventRecord& theEvent);
		CALL_PROC(DoUpdateOrActivate)(theEvent);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}
#endif


void GS_CALLBACK GS_DrawScreen(CALLBACKPTR, const ViewRect& clipRect, Boolean isLastFrame)
{
	GET_CB_UPP(DrawScreen);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DrawScreenPtr)(const ViewRect& clipRect, CBBoolean isLastFrame);
		CALL_PROC(DrawScreen)(clipRect, isLastFrame);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_EllipseEllipseIntersect(CALLBACKPTR, const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects)
{
	GET_CB_UPP(EllipseEllipseIntersect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EllipseEllipseIntersectPtr)(const WorldRect& e1, const WorldRect& e2, Sect4Struct& sects);
		CALL_PROC(EllipseEllipseIntersect)(e1, e2, sects);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Sint32 GS_CALLBACK GS_ExternalNameToID(CALLBACKPTR, const TXString& fnName)
{
	GET_CB_UPP(ExternalNameToID);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*ExternalNameToIDPtr)(const TXString& fnName);
		Sint32 gsResult = CALL_PROC(ExternalNameToID)(fnName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_FontIndexFromName(CALLBACKPTR, const TXString& fontName)
{
	GET_CB_UPP(FontIndexFromName);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*FontIndexFromNamePtr)(const TXString& fontName);
		short gsResult = CALL_PROC(FontIndexFromName)(fontName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_FontNameFromIndex(CALLBACKPTR, short fontIndex, TXString&  fontName, Boolean useMappingTable)
{
	GET_CB_UPP(FontNameFromIndex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*FontNameFromIndexPtr)(CBSignedShort fontIndex, TXString&  fontName, CBBoolean useMappingTable);
		CALL_PROC(FontNameFromIndex)(fontIndex, fontName, useMappingTable);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetActiveClassicSerialNumber(CALLBACKPTR, short inSerialNumberStyle, char* serialNumber)
{
	GET_CB_UPP(GetActiveClassicSerialNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetActiveClassicSerialNumberPtr)(CBSignedShort inSerialNumberStyle, char* serialNumber);
		Boolean gsResult = CALL_PROC(GetActiveClassicSerialNumber)(inSerialNumberStyle, serialNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetActiveSerialNumber(CALLBACKPTR, char* serialNumber)
{
	GET_CB_UPP(GetActiveSerialNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetActiveSerialNumberPtr)(char* serialNumber);
		CALL_PROC(GetActiveSerialNumber)(serialNumber);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetCallBackInval(CALLBACKPTR)
{
	GET_CB_UPP(GetCallBackInval);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetCallBackInvalPtr)();
		Boolean gsResult = CALL_PROC(GetCallBackInval)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return true;
}


short GS_CALLBACK GS_GetCurrentMode(CALLBACKPTR)
{
	GET_CB_UPP(GetCurrentMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetCurrentModePtr)();
		short gsResult = CALL_PROC(GetCurrentMode)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Sint32 GS_CALLBACK GS_GetDataBarCursorVisState(CALLBACKPTR)
{
	GET_CB_UPP(GetDataBarCursorVisState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetDataBarCursorVisStatePtr)();
		Sint32 gsResult = CALL_PROC(GetDataBarCursorVisState)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_GetEnabledModules(CALLBACKPTR)
{
	GET_CB_UPP(GetEnabledModules);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*GetEnabledModulesPtr)();
		Sint32 gsResult = CALL_PROC(GetEnabledModules)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetHostInfo(CALLBACKPTR, short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& productName, TXString& productVersion)
{
	GET_CB_UPP(GetHostInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetHostInfoPtr)(short& hostID, Byte& version, Byte& majorRev, Byte& minorRev, TXString& productName, TXString& productVersion);
		CALL_PROC(GetHostInfo)(hostID, version, majorRev, minorRev, productName, productVersion);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetModifierFlags(CALLBACKPTR, Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag)
{
	GET_CB_UPP(GetModifierFlags);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetModifierFlagsPtr)(Boolean& optionFlag, Boolean& cmdFlag, Boolean& shiftFlag);
		CALL_PROC(GetModifierFlags)(optionFlag, cmdFlag, shiftFlag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetProduct(CALLBACKPTR, short& product, Sint32& modules)
{
	GET_CB_UPP(GetProduct);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetProductPtr)(short& product, Sint32& modules);
		CALL_PROC(GetProduct)(product, modules);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_GetSavedSetting(CALLBACKPTR, const TXString& category, const TXString& setting, TXString&  value)
{
	GET_CB_UPP(GetSavedSetting);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetSavedSettingPtr)(const TXString& category, const TXString& setting, TXString&  value);
		Boolean gsResult = CALL_PROC(GetSavedSetting)(category, setting, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_HandlePendingUpdatesAndActivates(CALLBACKPTR)
{
	GET_CB_UPP(HandlePendingUpdatesAndActivates);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*HandlePendingUpdatesAndActivatesPtr)();
		CALL_PROC(HandlePendingUpdatesAndActivates)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_HilitePalettesAndTopDocument(CALLBACKPTR, Boolean doHilite)
{
	GET_CB_UPP(HilitePalettesAndTopDocument);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*HilitePalettesAndTopDocumentPtr)(CBBoolean doHilite);
		CALL_PROC(HilitePalettesAndTopDocument)(doHilite);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_IntersectObjects(CALLBACKPTR, MCObjectHandle obj1, MCObjectHandle obj2, Boolean onlyOnObjs)
{
	GET_CB_UPP(IntersectObjects);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*IntersectObjectsPtr)(MCObjectHandle obj1, MCObjectHandle obj2, CBBoolean onlyOnObjs);
		MCObjectHandle gsResult = CALL_PROC(IntersectObjects)(obj1, obj2, onlyOnObjs);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_Kludge(CALLBACKPTR, short selector, void* in, void* out)
{
	GET_CB_UPP(Kludge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*KludgePtr)(CBSignedShort selector, void* in, void* out, bool bUseLegacyZ);
		Boolean gsResult = CALL_PROC(Kludge)(selector, in, out, true);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_LineEllipseIntersect(CALLBACKPTR, const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects)
{
	GET_CB_UPP(LineEllipseIntersect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*LineEllipseIntersectPtr)(const WorldPt& a1, const WorldPt& a2, const WorldRect& r, Sect2Struct& sects);
		CALL_PROC(LineEllipseIntersect)(a1, a2, r, sects);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_LineLineIntersect(CALLBACKPTR, const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect)
{
	GET_CB_UPP(LineLineIntersect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*LineLineIntersectPtr)(const WorldPt& a1, const WorldPt& a2, const WorldPt& b1, const WorldPt& b2, Boolean& parallel, Boolean& intOnLines, WorldPt& sect);
		CALL_PROC(LineLineIntersect)(a1, a2, b1, b2, parallel, intOnLines, sect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_ObjectNearCoordPt(CALLBACKPTR, const WorldPt& p)
{
	GET_CB_UPP(ObjectNearCoordPt);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*ObjectNearCoordPtPtr)(const WorldPt& p);
		MCObjectHandle gsResult = CALL_PROC(ObjectNearCoordPt)(p);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


CBBoolean GS_CALLBACK GS_PlaySoundResource(CALLBACKPTR, Handle soundResource, CBBoolean async, CBBoolean forcePlay)
{
	GET_CB_UPP(PlaySoundResource);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*PlaySoundResourcePtr)(Handle soundResource, CBBoolean async, CBBoolean forcePlay);
		CBBoolean gsResult = CALL_PROC(PlaySoundResource)(soundResource, async, forcePlay);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_PointInsidePoly(CALLBACKPTR, const WorldPt& checkPt, MCObjectHandle h)
{
	GET_CB_UPP(PointInsidePoly);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*PointInsidePolyPtr)(const WorldPt& checkPt, MCObjectHandle h);
		Boolean gsResult = CALL_PROC(PointInsidePoly)(checkPt, h);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_PointOnPolyEdge(CALLBACKPTR, const WorldPt& checkPt, MCObjectHandle h, WorldCoord checkRadius)
{
	GET_CB_UPP(PointOnPolyEdge);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*PointOnPolyEdgePtr)(const WorldPt& checkPt, MCObjectHandle h, CBWorldCoord_param checkRadius);
		Boolean gsResult = CALL_PROC(PointOnPolyEdge)(checkPt, h, checkRadius);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Sint32 GS_CALLBACK GS_RegisterExternal(CALLBACKPTR, const TXString& fileName, short codeResID, OSType codeResType)
{
	GET_CB_UPP(RegisterExternal);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Sint32 (*RegisterExternalPtr)(const TXString& fileName, CBSignedShort codeResID, OSType codeResType);
		Sint32 gsResult = CALL_PROC(RegisterExternal)(fileName, codeResID, codeResType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


Boolean GS_CALLBACK GS_RegisterNotificationProcedure(CALLBACKPTR, StatusProcPtr proc, OSType whichChange)
{
	GET_CB_UPP(RegisterNotificationProcedure);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*RegisterNotificationProcedurePtr)(StatusProcPtr proc, OSType whichChange);
		Boolean gsResult = CALL_PROC(RegisterNotificationProcedure)(proc, whichChange);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_SetCallBackInval(CALLBACKPTR, Boolean turnInvalOn)
{
	GET_CB_UPP(SetCallBackInval);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetCallBackInvalPtr)(CBBoolean turnInvalOn);
		CALL_PROC(SetCallBackInval)(turnInvalOn);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetPersistentHighlight(CALLBACKPTR, MCObjectHandle theObject, Boolean highlightState)
{
	GET_CB_UPP(SetPersistentHighlight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetPersistentHighlightPtr)(MCObjectHandle theObject, CBBoolean highlightState);
		CALL_PROC(SetPersistentHighlight)(theObject, highlightState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetSavedSetting(CALLBACKPTR, const TXString& category, const TXString& setting, const TXString& value)
{
	GET_CB_UPP(SetSavedSetting);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetSavedSettingPtr)(const TXString& category, const TXString& setting, const TXString& value);
		CALL_PROC(SetSavedSetting)(category, setting, value);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_StringToAngleN(CALLBACKPTR, const TXString& s, double_gs& angle)
{
	GET_CB_UPP(StringToAngleN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*StringToAngleNPtr)(const TXString& s, double_gs& angle);
		Boolean gsResult = CALL_PROC(StringToAngleN)(s, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_StringToDouble(CALLBACKPTR, TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble)
{
	GET_CB_UPP(StringToDouble);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*StringToDoublePtr)(TNumStyleClass inNumStyle, const TXString& inString, double_gs& outDouble);
		Boolean gsResult = CALL_PROC(StringToDouble)(inNumStyle, inString, outDouble);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_SymbolContainsLight(CALLBACKPTR, MCObjectHandle symbol)
{
	GET_CB_UPP(SymbolContainsLight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SymbolContainsLightPtr)(MCObjectHandle symbol);
		Boolean gsResult = CALL_PROC(SymbolContainsLight)(symbol);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_ToggleObjectHighlight(CALLBACKPTR, MCObjectHandle theObject)
{
	GET_CB_UPP(ToggleObjectHighlight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ToggleObjectHighlightPtr)(MCObjectHandle theObject);
		CALL_PROC(ToggleObjectHighlight)(theObject);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_UnregisterNotificationProcedure(CALLBACKPTR, StatusProcPtr proc, OSType whichChange)
{
	GET_CB_UPP(UnregisterNotificationProcedure);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*UnregisterNotificationProcedurePtr)(StatusProcPtr proc, OSType whichChange);
		CALL_PROC(UnregisterNotificationProcedure)(proc, whichChange);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_VerifyPluginLibrary(CALLBACKPTR, const TXString& routineName)
{
	GET_CB_UPP(VerifyPluginLibrary);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*VerifyPluginLibraryPtr)(const TXString& routineName);
		Boolean gsResult = CALL_PROC(VerifyPluginLibrary)(routineName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  View Manipulation
///////////////////////////////////////////


void GS_CALLBACK GS_GetPerspectiveInfo(CALLBACKPTR, MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect)
{
	GET_CB_UPP(GetPerspectiveInfo);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetPerspectiveInfoPtr)(MCObjectHandle theLayer, WorldCoord& perspectiveDistance, WorldCoord& clipDistance, WorldRect& clipRect);
		CALL_PROC(GetPerspectiveInfo)(theLayer, perspectiveDistance, clipDistance, clipRect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_GetProjection(CALLBACKPTR, MCObjectHandle theLayer)
{
	GET_CB_UPP(GetProjection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetProjectionPtr)(MCObjectHandle theLayer);
		short gsResult = CALL_PROC(GetProjection)(theLayer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetRenderMode(CALLBACKPTR, MCObjectHandle theLayer)
{
	GET_CB_UPP(GetRenderMode);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetRenderModePtr)(MCObjectHandle theLayer);
		short gsResult = CALL_PROC(GetRenderMode)(theLayer);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_GetScreenDPI(CALLBACKPTR)
{
	GET_CB_UPP(GetScreenDPI);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*GetScreenDPIPtr)();
		short gsResult = CALL_PROC(GetScreenDPI)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


void GS_CALLBACK GS_GetViewCenter(CALLBACKPTR, WorldPt& center)
{
	GET_CB_UPP(GetViewCenter);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetViewCenterPtr)(WorldPt& center);
		CALL_PROC(GetViewCenter)(center);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetViewMatrix(CALLBACKPTR, MCObjectHandle theLayer, TransformMatrix& theMat)
{
	GET_CB_UPP(GetViewMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetViewMatrixPtr)(MCObjectHandle theLayer, TransformMatrix& theMat);
		CALL_PROC(GetViewMatrix)(theLayer, theMat);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorkingPlane(CALLBACKPTR, Axis &theAxis)
{
	GET_CB_UPP(GetWorkingPlane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorkingPlanePtr)(Axis &theAxis);
		CALL_PROC(GetWorkingPlane)(theAxis);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_NewCurrentViewMatrix(CALLBACKPTR, const TransformMatrix& theMat, Boolean interactive)
{
	GET_CB_UPP(NewCurrentViewMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*NewCurrentViewMatrixPtr)(const TransformMatrix& theMat, CBBoolean interactive);
		CALL_PROC(NewCurrentViewMatrix)(theMat, interactive);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_NewWorkingPlane(CALLBACKPTR, const Axis &theAxis)
{
	GET_CB_UPP(NewWorkingPlane);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*NewWorkingPlanePtr)(const Axis &theAxis);
		CALL_PROC(NewWorkingPlane)(theAxis);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PreviewDrawFrame(CALLBACKPTR, Handle thisPreview, Boolean selectedOnly)
{
	GET_CB_UPP(PreviewDrawFrame);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PreviewDrawFramePtr)(Handle thisPreview, CBBoolean selectedOnly);
		CALL_PROC(PreviewDrawFrame)(thisPreview, selectedOnly);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_PreviewFinish(CALLBACKPTR, Handle& thisPreview)
{
	GET_CB_UPP(PreviewFinish);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*PreviewFinishPtr)(Handle& thisPreview);
		CALL_PROC(PreviewFinish)(thisPreview);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Handle GS_CALLBACK GS_PreviewSetup(CALLBACKPTR, Boolean doDynamicSpeedups, double_param targetFPS, Boolean drawGroundPlane, Boolean drawPage, Boolean drawCropRect)
{
	GET_CB_UPP(PreviewSetup);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef Handle (*PreviewSetupPtr)(CBBoolean doDynamicSpeedups, CBDouble_param targetFPS, CBBoolean drawGroundPlane, CBBoolean drawPage, CBBoolean drawCropRect);
		Handle gsResult = CALL_PROC(PreviewSetup)(doDynamicSpeedups, targetFPS, drawGroundPlane, drawPage, drawCropRect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_RedrawRect(CALLBACKPTR, const WorldRect& redrawR)
{
	GET_CB_UPP(RedrawRect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RedrawRectPtr)(const WorldRect& redrawR);
		CALL_PROC(RedrawRect)(redrawR);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetViewCenter(CALLBACKPTR, const WorldPt& center)
{
	GET_CB_UPP(SetViewCenter);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetViewCenterPtr)(const WorldPt& center);
		CALL_PROC(SetViewCenter)(center);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetViewMatrix(CALLBACKPTR, MCObjectHandle theLayer, const TransformMatrix& theMatrix)
{
	GET_CB_UPP(SetViewMatrix);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetViewMatrixPtr)(MCObjectHandle theLayer, const TransformMatrix& theMatrix);
		CALL_PROC(SetViewMatrix)(theLayer, theMatrix);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorkingPlaneAxis(CALLBACKPTR, const Vector &si, const Vector &sj, const Vector &sk)
{
	GET_CB_UPP(SetWorkingPlaneAxis);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorkingPlaneAxisPtr)(const Vector &si, const Vector &sj, const Vector &sk);
		CALL_PROC(SetWorkingPlaneAxis)(si, sj, sk);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorkingPlaneVertex(CALLBACKPTR, const WorldPt3 &v)
{
	GET_CB_UPP(SetWorkingPlaneVertex);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorkingPlaneVertexPtr)(const WorldPt3 &v);
		CALL_PROC(SetWorkingPlaneVertex)(v);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetZoomFactorN(CALLBACKPTR, double_param zoomFac)
{
	GET_CB_UPP(SetZoomFactorN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetZoomFactorNPtr)(CBDouble_param zoomFac);
		CALL_PROC(SetZoomFactorN)(zoomFac);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ViewRotWorldZN(CALLBACKPTR, double_param angle, Boolean interactive)
{
	GET_CB_UPP(ViewRotWorldZN);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ViewRotWorldZNPtr)(CBDouble_param angle, CBBoolean interactive);
		CALL_PROC(ViewRotWorldZN)(angle, interactive);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_WorldRect2ViewRect(CALLBACKPTR, const WorldRect& wRect, ViewRect& vRect)
{
	GET_CB_UPP(WorldRect2ViewRect);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WorldRect2ViewRectPtr)(const WorldRect& wRect, ViewRect& vRect);
		Boolean gsResult = CALL_PROC(WorldRect2ViewRect)(wRect, vRect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Walls
///////////////////////////////////////////


short GS_CALLBACK GS_AddBreak(CALLBACKPTR, MCObjectHandle theWall, WorldCoord off, short breakType, void* breakData)
{
	GET_CB_UPP(AddBreak);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*AddBreakPtr)(MCObjectHandle theWall, CBWorldCoord_param off, CBSignedShort breakType, void* breakData);
		short gsResult = CALL_PROC(AddBreak)(theWall, off, breakType, breakData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_DeleteBreak(CALLBACKPTR, MCObjectHandle theWall, short index)
{
	GET_CB_UPP(DeleteBreak);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteBreakPtr)(MCObjectHandle theWall, CBSignedShort index);
		CALL_PROC(DeleteBreak)(theWall, index);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ForEachBreak(CallBackPtr cbp, MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv)
{
	GET_CB_UPP(ForEachBreak);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ForEachBreakPtr)(MCObjectHandle theWall, GS_ForEachBreakProcPtr action, void* actionEnv, CallBackPtr cbp);
		CALL_PROC(ForEachBreak)(theWall, action, actionEnv, cbp);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


WorldCoord GS_CALLBACK GS_GetLayerDeltaZOffset(CALLBACKPTR, MCObjectHandle theWall)
{
	GET_CB_UPP(GetLayerDeltaZOffset);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef WorldCoord (*GetLayerDeltaZOffsetPtr)(MCObjectHandle theWall);
		WorldCoord gsResult = CALL_PROC(GetLayerDeltaZOffset)(theWall);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return 0;
}


CBBoolean GS_CALLBACK GS_GetLinkHeightToLayerDeltaZ(CALLBACKPTR, MCObjectHandle theWall)
{
	GET_CB_UPP(GetLinkHeightToLayerDeltaZ);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetLinkHeightToLayerDeltaZPtr)(MCObjectHandle theWall);
		CBBoolean gsResult = CALL_PROC(GetLinkHeightToLayerDeltaZ)(theWall);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetPolyBreakGeometry(CALLBACKPTR, MCObjectHandle theWall, short breakIndex, MCObjectHandle& polyline)
{
	GET_CB_UPP(GetPolyBreakGeometry);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetPolyBreakGeometryPtr)(MCObjectHandle theWall, CBSignedShort breakIndex, MCObjectHandle& polyline);
		CALL_PROC(GetPolyBreakGeometry)(theWall, breakIndex, polyline);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWallCaps(CALLBACKPTR, MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round)
{
	GET_CB_UPP(GetWallCaps);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWallCapsPtr)(MCObjectHandle theWall, Boolean &leftCap, Boolean &rightCap, Boolean &round);
		CALL_PROC(GetWallCaps)(theWall, leftCap, rightCap, round);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWallCapsOffsets(CALLBACKPTR, MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset)
{
	GET_CB_UPP(GetWallCapsOffsets);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWallCapsOffsetsPtr)(MCObjectHandle theWall, WorldCoord &leftCapLeftOffset, WorldCoord &leftCapRightOffset, WorldCoord &rightCapLeftOffset, WorldCoord &rightCapRightOffset);
		CALL_PROC(GetWallCapsOffsets)(theWall, leftCapLeftOffset, leftCapRightOffset, rightCapLeftOffset, rightCapRightOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWallHeights(CALLBACKPTR, MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom)
{
	GET_CB_UPP(GetWallHeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWallHeightsPtr)(MCObjectHandle theWall, WorldCoord& startHeightTop, WorldCoord& startHeightBottom, WorldCoord& endHeightTop, WorldCoord& endHeightBottom);
		CALL_PROC(GetWallHeights)(theWall, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_JoinWalls(CALLBACKPTR, MCObjectHandle firstWall, MCObjectHandle secondWall, const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, Boolean capped, Boolean showAlerts)
{
	GET_CB_UPP(JoinWalls);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*JoinWallsPtr)(MCObjectHandle firstWall, MCObjectHandle secondWall, const WorldPt& firstWallPt, const WorldPt& secondWallPt, JoinModifierType joinModifier, CBBoolean capped, CBBoolean showAlerts);
		Boolean gsResult = CALL_PROC(JoinWalls)(firstWall, secondWall, firstWallPt, secondWallPt, joinModifier, capped, showAlerts);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_MoveWallByOffset(CALLBACKPTR, MCObjectHandle theWall, WorldCoord& offset)
{
	GET_CB_UPP(MoveWallByOffset);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*MoveWallByOffsetPtr)(MCObjectHandle theWall, WorldCoord& offset);
		CALL_PROC(MoveWallByOffset)(theWall, offset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ReverseWallSides(CALLBACKPTR, MCObjectHandle theWall)
{
	GET_CB_UPP(ReverseWallSides);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ReverseWallSidesPtr)(MCObjectHandle theWall);
		CALL_PROC(ReverseWallSides)(theWall);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetAsPolyBreak(CALLBACKPTR, MCObjectHandle& thePolyline, MCObjectHandle theWall, short breakIndex)
{
	GET_CB_UPP(SetAsPolyBreak);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetAsPolyBreakPtr)(MCObjectHandle& thePolyline, MCObjectHandle theWall, CBSignedShort breakIndex);
		CALL_PROC(SetAsPolyBreak)(thePolyline, theWall, breakIndex);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetBreak(CALLBACKPTR, MCObjectHandle theWall, short index, WorldCoord off, short breakType, void* breakData)
{
	GET_CB_UPP(SetBreak);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetBreakPtr)(MCObjectHandle theWall, CBSignedShort index, CBWorldCoord_param off, CBSignedShort breakType, void* breakData);
		CALL_PROC(SetBreak)(theWall, index, off, breakType, breakData);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


CBBoolean GS_CALLBACK GS_SetLayerDeltaZOffset(CALLBACKPTR, MCObjectHandle theWall, WorldCoord layerDeltaZOffset)
{
	GET_CB_UPP(SetLayerDeltaZOffset);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLayerDeltaZOffsetPtr)(MCObjectHandle theWall, CBWorldCoord_param layerDeltaZOffset);
		CBBoolean gsResult = CALL_PROC(SetLayerDeltaZOffset)(theWall, layerDeltaZOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetLinkHeightToLayerDeltaZ(CALLBACKPTR, MCObjectHandle theWall, CBBoolean linkToLayerDeltaZ)
{
	GET_CB_UPP(SetLinkHeightToLayerDeltaZ);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetLinkHeightToLayerDeltaZPtr)(MCObjectHandle theWall, CBBoolean linkToLayerDeltaZ);
		CBBoolean gsResult = CALL_PROC(SetLinkHeightToLayerDeltaZ)(theWall, linkToLayerDeltaZ);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallCaps(CALLBACKPTR, MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round)
{
	GET_CB_UPP(SetWallCaps);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallCapsPtr)(MCObjectHandle theWall, const Boolean &leftCap, const Boolean &rightCap, const Boolean &round);
		CBBoolean gsResult = CALL_PROC(SetWallCaps)(theWall, leftCap, rightCap, round);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallCapsOffsets(CALLBACKPTR, MCObjectHandle theWall, WorldCoord leftCapLeftOffset, WorldCoord leftCapRightOffset, WorldCoord rightCapLeftOffset, WorldCoord rightCapRightOffset)
{
	GET_CB_UPP(SetWallCapsOffsets);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallCapsOffsetsPtr)(MCObjectHandle theWall, CBWorldCoord_param leftCapLeftOffset, CBWorldCoord_param leftCapRightOffset, CBWorldCoord_param rightCapLeftOffset, CBWorldCoord_param rightCapRightOffset);
		CBBoolean gsResult = CALL_PROC(SetWallCapsOffsets)(theWall, leftCapLeftOffset, leftCapRightOffset, rightCapLeftOffset, rightCapRightOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallHeights(CALLBACKPTR, MCObjectHandle theWall, WorldCoord startHeightTop, WorldCoord startHeightBottom, WorldCoord endHeightTop, WorldCoord endHeightBottom)
{
	GET_CB_UPP(SetWallHeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallHeightsPtr)(MCObjectHandle theWall, CBWorldCoord_param startHeightTop, CBWorldCoord_param startHeightBottom, CBWorldCoord_param endHeightTop, CBWorldCoord_param endHeightBottom);
		CBBoolean gsResult = CALL_PROC(SetWallHeights)(theWall, startHeightTop, startHeightBottom, endHeightTop, endHeightBottom);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallStyle(CALLBACKPTR, MCObjectHandle theWall, InternalIndex wallStyle, WorldCoord selectedOffset, WorldCoord replacingOffset)
{
	GET_CB_UPP(SetWallStyle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallStylePtr)(MCObjectHandle theWall, InternalIndex wallStyle, CBWorldCoord_param selectedOffset, CBWorldCoord_param replacingOffset);
		CBBoolean gsResult = CALL_PROC(SetWallStyle)(theWall, wallStyle, selectedOffset, replacingOffset);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


CBBoolean GS_CALLBACK GS_SetWallWidth(CALLBACKPTR, MCObjectHandle theWall, WorldCoord newWidth)
{
	GET_CB_UPP(SetWallWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*SetWallWidthPtr)(MCObjectHandle theWall, CBWorldCoord_param newWidth);
		CBBoolean gsResult = CALL_PROC(SetWallWidth)(theWall, newWidth);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_WrapGetWallWidth(CALLBACKPTR, MCObjectHandle theWall, double_gs& outCoordLen)
{
	GET_CB_UPP(WrapGetWallWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*WrapGetWallWidthPtr)(MCObjectHandle theWall, double_gs& outCoordLen);
		CALL_PROC(WrapGetWallWidth)(theWall, outCoordLen);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}




///////////////////////////////////////////
//  Windows
///////////////////////////////////////////


#if _WINDOWS
void GS_CALLBACK GS_EnterMoveableWindow(CALLBACKPTR, HWND hDialog)
{
	GET_CB_UPP(EnterMoveableWindow);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*EnterMoveableWindowPtr)(HWND hDialog);
		CALL_PROC(EnterMoveableWindow)(hDialog);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}
#endif


#if _WINDOWS
void GS_CALLBACK GS_ExitMoveableWindow(CALLBACKPTR, HWND hDialog)
{
	GET_CB_UPP(ExitMoveableWindow);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ExitMoveableWindowPtr)(HWND hDialog);
		CALL_PROC(ExitMoveableWindow)(hDialog);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}
#endif


#if _WINDOWS
HWND GS_CALLBACK GS_GetMainHWND(CALLBACKPTR)
{
	GET_CB_UPP(GetMainHWND);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef HWND (*GetMainHWNDPtr)();
		HWND gsResult = CALL_PROC(GetMainHWND)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}
#endif


Boolean GS_CALLBACK GS_GetScreenSize(CALLBACKPTR, ViewRect& screenRect)
{
	GET_CB_UPP(GetScreenSize);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetScreenSizePtr)(ViewRect& screenRect);
		Boolean gsResult = CALL_PROC(GetScreenSize)(screenRect);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Worksheets
///////////////////////////////////////////


void GS_CALLBACK GS_AutoFitWorksheetRowHeights(CALLBACKPTR, MCObjectHandle worksheet, short fromRow, short toRow)
{
	GET_CB_UPP(AutoFitWorksheetRowHeights);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*AutoFitWorksheetRowHeightsPtr)(MCObjectHandle worksheet, CBSignedShort fromRow, CBSignedShort toRow);
		CALL_PROC(AutoFitWorksheetRowHeights)(worksheet, fromRow, toRow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ClearWorksheetCells(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
{
	GET_CB_UPP(ClearWorksheetCells);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ClearWorksheetCellsPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		CALL_PROC(ClearWorksheetCells)(worksheet, topLeftCell, bottomRightCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_CreateWorksheet(CALLBACKPTR, const InternalName& name, short rows, short columns)
{
	GET_CB_UPP(CreateWorksheet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateWorksheetPtr)(const InternalName& name, CBSignedShort rows, CBSignedShort columns);
		MCObjectHandle gsResult = CALL_PROC(CreateWorksheet)(name, rows, columns);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_CreateWorksheetImage(CALLBACKPTR, MCObjectHandle worksheet, const WorldPt& topLeftCorner)
{
	GET_CB_UPP(CreateWorksheetImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*CreateWorksheetImagePtr)(MCObjectHandle worksheet, const WorldPt& topLeftCorner);
		MCObjectHandle gsResult = CALL_PROC(CreateWorksheetImage)(worksheet, topLeftCorner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_DeleteWorksheetColumns(CALLBACKPTR, MCObjectHandle worksheet, short startColumn, short numColumns)
{
	GET_CB_UPP(DeleteWorksheetColumns);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteWorksheetColumnsPtr)(MCObjectHandle worksheet, CBSignedShort startColumn, CBSignedShort numColumns);
		CALL_PROC(DeleteWorksheetColumns)(worksheet, startColumn, numColumns);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_DeleteWorksheetRows(CALLBACKPTR, MCObjectHandle worksheet, short startRow, short numRows)
{
	GET_CB_UPP(DeleteWorksheetRows);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*DeleteWorksheetRowsPtr)(MCObjectHandle worksheet, CBSignedShort startRow, CBSignedShort numRows);
		CALL_PROC(DeleteWorksheetRows)(worksheet, startRow, numRows);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetTopVisibleWorksheet(CALLBACKPTR)
{
	GET_CB_UPP(GetTopVisibleWorksheet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetTopVisibleWorksheetPtr)();
		MCObjectHandle gsResult = CALL_PROC(GetTopVisibleWorksheet)();
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


void GS_CALLBACK GS_GetWkSheetSubrowCellActualString(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow, TXString&  cellString)
{
	GET_CB_UPP(GetWkSheetSubrowCellActualString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWkSheetSubrowCellActualStringPtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow, TXString&  cellString);
		CALL_PROC(GetWkSheetSubrowCellActualString)(worksheet, cell, subrow, cellString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellAlignment(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment)
{
	GET_CB_UPP(GetWorksheetCellAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellAlignmentPtr)(MCObjectHandle worksheet, const ViewPt& cell, short& cellAlignment);
		CALL_PROC(GetWorksheetCellAlignment)(worksheet, cell, cellAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellBorder(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right)
{
	GET_CB_UPP(GetWorksheetCellBorder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellBorderPtr)(MCObjectHandle worksheet, const ViewPt& cell, Boolean& top, Boolean& left, Boolean& bottom, Boolean& right);
		CALL_PROC(GetWorksheetCellBorder)(worksheet, cell, top, left, bottom, right);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellFill(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern)
{
	GET_CB_UPP(GetWorksheetCellFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellFillPtr)(MCObjectHandle worksheet, const ViewPt& cell, short& style, ColorRef& bgcolor, ColorRef& fgcolor, short& fillpattern);
		CALL_PROC(GetWorksheetCellFill)(worksheet, cell, style, bgcolor, fgcolor, fillpattern);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellFormula(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, TXString&  formula)
{
	GET_CB_UPP(GetWorksheetCellFormula);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellFormulaPtr)(MCObjectHandle worksheet, const ViewPt& cell, TXString&  formula);
		CALL_PROC(GetWorksheetCellFormula)(worksheet, cell, formula);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellNumberFormat(CALLBACKPTR, MCObjectHandle worksheet, 
	const ViewPt& cell, short& style, short& accuracy, TXString & leaderString, TXString & trailerString)
{
	GET_CB_UPP(GetWorksheetCellNumberFormat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellNumberFormatPtr)(MCObjectHandle worksheet, const ViewPt& cell, short& style, short& accuracy, TXString & leaderString, TXString & trailerString);
		CALL_PROC(GetWorksheetCellNumberFormat)(worksheet, cell, style, accuracy, leaderString, trailerString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellString(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, TXString&  cellString)
{
	GET_CB_UPP(GetWorksheetCellString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellStringPtr)(MCObjectHandle worksheet, const ViewPt& cell, TXString&  cellString);
		CALL_PROC(GetWorksheetCellString)(worksheet, cell, cellString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellTextFormat(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style)
{
	GET_CB_UPP(GetWorksheetCellTextFormat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellTextFormatPtr)(MCObjectHandle worksheet, const ViewPt& cell, short& fontIndex, short& size, short& style);
		CALL_PROC(GetWorksheetCellTextFormat)(worksheet, cell, fontIndex, size, style);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellTextAngle(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short& angle)
{
	GET_CB_UPP(GetWorksheetCellTextAngle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellTextAnglePtr)(MCObjectHandle worksheet, const ViewPt& cell, short& angle);
		CALL_PROC(GetWorksheetCellTextAngle)(worksheet, cell, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellTextColor(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color)
{
	GET_CB_UPP(GetWorksheetCellTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellTextColorPtr)(MCObjectHandle worksheet, const ViewPt& cell, ColorRef& color);
		CALL_PROC(GetWorksheetCellTextColor)(worksheet, cell, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellValue(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, double& cellValue)
{
	GET_CB_UPP(GetWorksheetCellValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellValuePtr)(MCObjectHandle worksheet, const ViewPt& cell, double& cellValue);
		CALL_PROC(GetWorksheetCellValue)(worksheet, cell, cellValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellVertAlignment(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment)
{
	GET_CB_UPP(GetWorksheetCellVertAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellVertAlignmentPtr)(MCObjectHandle worksheet, const ViewPt& cell, short& vAlignment);
		CALL_PROC(GetWorksheetCellVertAlignment)(worksheet, cell, vAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetCellWrapTextFlag(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag)
{
	GET_CB_UPP(GetWorksheetCellWrapTextFlag);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetCellWrapTextFlagPtr)(MCObjectHandle worksheet, const ViewPt& cell, Boolean& wrapTextFlag);
		CALL_PROC(GetWorksheetCellWrapTextFlag)(worksheet, cell, wrapTextFlag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetColumnOperators(CALLBACKPTR, MCObjectHandle worksheet, short databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3)
{
	GET_CB_UPP(GetWorksheetColumnOperators);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetColumnOperatorsPtr)(MCObjectHandle worksheet, CBSignedShort databaseRow, short& sort1, short& sort2, short& sort3, short& sum1, short& sum2, short& sum3);
		CALL_PROC(GetWorksheetColumnOperators)(worksheet, databaseRow, sort1, sort2, sort3, sum1, sum2, sum3);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetColumnWidth(CALLBACKPTR, MCObjectHandle worksheet, short column, short& width)
{
	GET_CB_UPP(GetWorksheetColumnWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetColumnWidthPtr)(MCObjectHandle worksheet, CBSignedShort column, short& width);
		CALL_PROC(GetWorksheetColumnWidth)(worksheet, column, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


MCObjectHandle GS_CALLBACK GS_GetWorksheetFromImage(CALLBACKPTR, MCObjectHandle worksheetImage)
{
	GET_CB_UPP(GetWorksheetFromImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetWorksheetFromImagePtr)(MCObjectHandle worksheetImage);
		MCObjectHandle gsResult = CALL_PROC(GetWorksheetFromImage)(worksheetImage);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


MCObjectHandle GS_CALLBACK GS_GetWorksheetImage(CALLBACKPTR, MCObjectHandle worksheet)
{
	GET_CB_UPP(GetWorksheetImage);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef MCObjectHandle (*GetWorksheetImagePtr)(MCObjectHandle worksheet);
		MCObjectHandle gsResult = CALL_PROC(GetWorksheetImage)(worksheet);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return nil;
}


Boolean GS_CALLBACK GS_GetWorksheetMergedCellRange(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell)
{
	GET_CB_UPP(GetWorksheetMergedCellRange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*GetWorksheetMergedCellRangePtr)(MCObjectHandle worksheet, const ViewPt& cell, ViewPt& topLeftCell, ViewPt& bottomRightCell);
		Boolean gsResult = CALL_PROC(GetWorksheetMergedCellRange)(worksheet, cell, topLeftCell, bottomRightCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_GetWorksheetPlacement(CALLBACKPTR, MCObjectHandle worksheet, ViewRect& windowPosition)
{
	GET_CB_UPP(GetWorksheetPlacement);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetPlacementPtr)(MCObjectHandle worksheet, ViewRect& windowPosition);
		CALL_PROC(GetWorksheetPlacement)(worksheet, windowPosition);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetRowColumnCount(CALLBACKPTR, MCObjectHandle worksheet, short& numRows, short& numColumns)
{
	GET_CB_UPP(GetWorksheetRowColumnCount);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetRowColumnCountPtr)(MCObjectHandle worksheet, short& numRows, short& numColumns);
		CALL_PROC(GetWorksheetRowColumnCount)(worksheet, numRows, numColumns);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetRowHeight(CALLBACKPTR, MCObjectHandle worksheet, short row, short& height)
{
	GET_CB_UPP(GetWorksheetRowHeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetRowHeightPtr)(MCObjectHandle worksheet, CBSignedShort row, short& height);
		CALL_PROC(GetWorksheetRowHeight)(worksheet, row, height);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetRowHLockState(CALLBACKPTR, MCObjectHandle worksheet, short row, Boolean& lockState)
{
	GET_CB_UPP(GetWorksheetRowHLockState);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetRowHLockStatePtr)(MCObjectHandle worksheet, CBSignedShort row, Boolean& lockState);
		CALL_PROC(GetWorksheetRowHLockState)(worksheet, row, lockState);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetSelection(CALLBACKPTR, MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow)
{
	GET_CB_UPP(GetWorksheetSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetSelectionPtr)(MCObjectHandle worksheet, ViewPt& currentCell, ViewPt& topLeftRangeCell, short& topRangeSubrow, ViewPt& bottomRightRangeCell, short& bottomRangeSubrow);
		CALL_PROC(GetWorksheetSelection)(worksheet, currentCell, topLeftRangeCell, topRangeSubrow, bottomRightRangeCell, bottomRangeSubrow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetSubrowCellString(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short subrow, TXString&  cellString)
{
	GET_CB_UPP(GetWorksheetSubrowCellString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetSubrowCellStringPtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow, TXString&  cellString);
		CALL_PROC(GetWorksheetSubrowCellString)(worksheet, cell, subrow, cellString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetSubrowCellValue(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short subrow, double& cellValue)
{
	GET_CB_UPP(GetWorksheetSubrowCellValue);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetSubrowCellValuePtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow, double& cellValue);
		CALL_PROC(GetWorksheetSubrowCellValue)(worksheet, cell, subrow, cellValue);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_GetWorksheetSubrowCount(CALLBACKPTR, MCObjectHandle worksheet, short databaseRow, short& numSubrows)
{
	GET_CB_UPP(GetWorksheetSubrowCount);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetWorksheetSubrowCountPtr)(MCObjectHandle worksheet, CBSignedShort databaseRow, short& numSubrows);
		CALL_PROC(GetWorksheetSubrowCount)(worksheet, databaseRow, numSubrows);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



void GS_CALLBACK GS_InsertWorksheetColumns(CALLBACKPTR, MCObjectHandle worksheet, short beforeColumn, short numColumns)
{
	GET_CB_UPP(InsertWorksheetColumns);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InsertWorksheetColumnsPtr)(MCObjectHandle worksheet, CBSignedShort beforeColumn, CBSignedShort numColumns);
		CALL_PROC(InsertWorksheetColumns)(worksheet, beforeColumn, numColumns);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_InsertWorksheetRows(CALLBACKPTR, MCObjectHandle worksheet, short beforeRow, short numRows)
{
	GET_CB_UPP(InsertWorksheetRows);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*InsertWorksheetRowsPtr)(MCObjectHandle worksheet, CBSignedShort beforeRow, CBSignedShort numRows);
		CALL_PROC(InsertWorksheetRows)(worksheet, beforeRow, numRows);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_IsValidWorksheetCell(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell)
{
	GET_CB_UPP(IsValidWorksheetCell);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsValidWorksheetCellPtr)(MCObjectHandle worksheet, const ViewPt& cell);
		Boolean gsResult = CALL_PROC(IsValidWorksheetCell)(worksheet, cell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsValidWorksheetRange(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
{
	GET_CB_UPP(IsValidWorksheetRange);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsValidWorksheetRangePtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		Boolean gsResult = CALL_PROC(IsValidWorksheetRange)(worksheet, topLeftCell, bottomRightCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsValidWorksheetSubrowCell(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short subrow)
{
	GET_CB_UPP(IsValidWorksheetSubrowCell);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsValidWorksheetSubrowCellPtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow);
		Boolean gsResult = CALL_PROC(IsValidWorksheetSubrowCell)(worksheet, cell, subrow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetCellNumber(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell)
{
	GET_CB_UPP(IsWorksheetCellNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetCellNumberPtr)(MCObjectHandle worksheet, const ViewPt& cell);
		Boolean gsResult = CALL_PROC(IsWorksheetCellNumber)(worksheet, cell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetCellString(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell)
{
	GET_CB_UPP(IsWorksheetCellString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetCellStringPtr)(MCObjectHandle worksheet, const ViewPt& cell);
		Boolean gsResult = CALL_PROC(IsWorksheetCellString)(worksheet, cell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetDatabaseRow(CALLBACKPTR, MCObjectHandle worksheet, short databaseRow)
{
	GET_CB_UPP(IsWorksheetDatabaseRow);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetDatabaseRowPtr)(MCObjectHandle worksheet, CBSignedShort databaseRow);
		Boolean gsResult = CALL_PROC(IsWorksheetDatabaseRow)(worksheet, databaseRow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetSubrowCellNumber(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short subrow)
{
	GET_CB_UPP(IsWorksheetSubrowCellNumber);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetSubrowCellNumberPtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow);
		Boolean gsResult = CALL_PROC(IsWorksheetSubrowCellNumber)(worksheet, cell, subrow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetSubrowCellString(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& cell, short subrow)
{
	GET_CB_UPP(IsWorksheetSubrowCellString);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetSubrowCellStringPtr)(MCObjectHandle worksheet, const ViewPt& cell, CBSignedShort subrow);
		Boolean gsResult = CALL_PROC(IsWorksheetSubrowCellString)(worksheet, cell, subrow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_IsWorksheetVisible(CALLBACKPTR, MCObjectHandle worksheet)
{
	GET_CB_UPP(IsWorksheetVisible);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*IsWorksheetVisiblePtr)(MCObjectHandle worksheet);
		Boolean gsResult = CALL_PROC(IsWorksheetVisible)(worksheet);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


void GS_CALLBACK GS_RecalculateWorksheet(CALLBACKPTR, MCObjectHandle worksheet)
{
	GET_CB_UPP(RecalculateWorksheet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*RecalculateWorksheetPtr)(MCObjectHandle worksheet);
		CALL_PROC(RecalculateWorksheet)(worksheet);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetTopVisibleWorksheet(CALLBACKPTR, MCObjectHandle worksheet)
{
	GET_CB_UPP(SetTopVisibleWorksheet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetTopVisibleWorksheetPtr)(MCObjectHandle worksheet);
		CALL_PROC(SetTopVisibleWorksheet)(worksheet);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellAlignment(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short cellAlignment)
{
	GET_CB_UPP(SetWorksheetCellAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellAlignmentPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort cellAlignment);
		CALL_PROC(SetWorksheetCellAlignment)(worksheet, topLeftCell, bottomRightCell, cellAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellBorder(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline)
{
	GET_CB_UPP(SetWorksheetCellBorder);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellBorderPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBBoolean top, CBBoolean left, CBBoolean bottom, CBBoolean right, CBBoolean outline);
		CALL_PROC(SetWorksheetCellBorder)(worksheet, topLeftCell, bottomRightCell, top, left, bottom, right, outline);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellBorders(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean top, Boolean left, Boolean bottom, Boolean right, Boolean outline, Boolean insideHorz, Boolean insideVert)
{
	GET_CB_UPP(SetWorksheetCellBorders);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellBordersPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBBoolean top, CBBoolean left, CBBoolean bottom, CBBoolean right, CBBoolean outline, CBBoolean insideHorz, CBBoolean insideVert);
		CALL_PROC(SetWorksheetCellBorders)(worksheet, topLeftCell, bottomRightCell, top, left, bottom, right, outline, insideHorz, insideVert);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellFill(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, ColorRef bgcolor, ColorRef fgcolor, short fillpattern)
{
	GET_CB_UPP(SetWorksheetCellFill);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellFillPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort style, ColorRef bgcolor, ColorRef fgcolor, CBSignedShort fillpattern);
		CALL_PROC(SetWorksheetCellFill)(worksheet, topLeftCell, bottomRightCell, style, bgcolor, fgcolor, fillpattern);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellFormula(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula)
{
	GET_CB_UPP(SetWorksheetCellFormula);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellFormulaPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, const TXString& formula);
		CALL_PROC(SetWorksheetCellFormula)(worksheet, topLeftCell, bottomRightCell, formula);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellNumberFormat(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short style, short accuracy, const TXString& leaderString, const TXString& trailerString)
{
	GET_CB_UPP(SetWorksheetCellNumberFormat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellNumberFormatPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort style, CBSignedShort accuracy, const TXString& leaderString, const TXString& trailerString);
		CALL_PROC(SetWorksheetCellNumberFormat)(worksheet, topLeftCell, bottomRightCell, style, accuracy, leaderString, trailerString);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellTextFormat(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short fontIndex, short size, short style)
{
	GET_CB_UPP(SetWorksheetCellTextFormat);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellTextFormatPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort fontIndex, CBSignedShort size, CBSignedShort style);
		CALL_PROC(SetWorksheetCellTextFormat)(worksheet, topLeftCell, bottomRightCell, fontIndex, size, style);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellTextAngle(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short angle)
{
	GET_CB_UPP(SetWorksheetCellTextAngle);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellTextAnglePtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort angle);
		CALL_PROC(SetWorksheetCellTextAngle)(worksheet, topLeftCell, bottomRightCell, angle);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellTextColor(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color)
{
	GET_CB_UPP(SetWorksheetCellTextColor);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellTextColorPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, ColorRef color);
		CALL_PROC(SetWorksheetCellTextColor)(worksheet, topLeftCell, bottomRightCell, color);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellVertAlignment(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, short vAlignment)
{
	GET_CB_UPP(SetWorksheetCellVertAlignment);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellVertAlignmentPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBSignedShort vAlignment);
		CALL_PROC(SetWorksheetCellVertAlignment)(worksheet, topLeftCell, bottomRightCell, vAlignment);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCellWrapTextFlag(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, Boolean wrapTextFlag)
{
	GET_CB_UPP(SetWorksheetCellWrapTextFlag);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCellWrapTextFlagPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell, CBBoolean wrapTextFlag);
		CALL_PROC(SetWorksheetCellWrapTextFlag)(worksheet, topLeftCell, bottomRightCell, wrapTextFlag);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetColumnOperators(CALLBACKPTR, MCObjectHandle worksheet, short databaseRow, short sort1, short sort2, short sort3, short sum1, short sum2, short sum3)
{
	GET_CB_UPP(SetWorksheetColumnOperators);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetColumnOperatorsPtr)(MCObjectHandle worksheet, CBSignedShort databaseRow, CBSignedShort sort1, CBSignedShort sort2, CBSignedShort sort3, CBSignedShort sum1, CBSignedShort sum2, CBSignedShort sum3);
		CALL_PROC(SetWorksheetColumnOperators)(worksheet, databaseRow, sort1, sort2, sort3, sum1, sum2, sum3);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetColumnWidth(CALLBACKPTR, MCObjectHandle worksheet, short fromColumn, short toColumn, short width)
{
	GET_CB_UPP(SetWorksheetColumnWidth);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetColumnWidthPtr)(MCObjectHandle worksheet, CBSignedShort fromColumn, CBSignedShort toColumn, CBSignedShort width);
		CALL_PROC(SetWorksheetColumnWidth)(worksheet, fromColumn, toColumn, width);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetCurrentCell(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& currentCell)
{
	GET_CB_UPP(SetWorksheetCurrentCell);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetCurrentCellPtr)(MCObjectHandle worksheet, const ViewPt& currentCell);
		CALL_PROC(SetWorksheetCurrentCell)(worksheet, currentCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetPlacement(CALLBACKPTR, MCObjectHandle worksheet, const ViewRect& windowPosition)
{
	GET_CB_UPP(SetWorksheetPlacement);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetPlacementPtr)(MCObjectHandle worksheet, const ViewRect& windowPosition);
		CALL_PROC(SetWorksheetPlacement)(worksheet, windowPosition);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetRowsHeight(CALLBACKPTR, MCObjectHandle worksheet, short fromRow, short toRow, short height, Boolean updatePalette, Boolean lockHeight)
{
	GET_CB_UPP(SetWorksheetRowsHeight);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetRowsHeightPtr)(MCObjectHandle worksheet, CBSignedShort fromRow, CBSignedShort toRow, CBSignedShort height, CBBoolean updatePalette, CBBoolean lockHeight);
		CALL_PROC(SetWorksheetRowsHeight)(worksheet, fromRow, toRow, height, updatePalette, lockHeight);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_SetWorksheetSelection(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, short topRangeSubrow, const ViewPt& bottomRightRangeCell, short bottomRangeSubrow)
{
	GET_CB_UPP(SetWorksheetSelection);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorksheetSelectionPtr)(MCObjectHandle worksheet, const ViewPt& currentCell, const ViewPt& topLeftRangeCell, CBSignedShort topRangeSubrow, const ViewPt& bottomRightRangeCell, CBSignedShort bottomRangeSubrow);
		CALL_PROC(SetWorksheetSelection)(worksheet, currentCell, topLeftRangeCell, topRangeSubrow, bottomRightRangeCell, bottomRangeSubrow);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}



void GS_CALLBACK GS_ShowWorksheet(CALLBACKPTR, MCObjectHandle worksheet, Boolean show)
{
	GET_CB_UPP(ShowWorksheet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ShowWorksheetPtr)(MCObjectHandle worksheet, CBBoolean show);
		CALL_PROC(ShowWorksheet)(worksheet, show);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


void GS_CALLBACK GS_ShowWorksheetDialog(CALLBACKPTR, short dialogType)
{
	GET_CB_UPP(ShowWorksheetDialog);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*ShowWorksheetDialogPtr)(CBSignedShort dialogType);
		CALL_PROC(ShowWorksheetDialog)(dialogType);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_WorksheetMergeCells(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
{
	GET_CB_UPP(WorksheetMergeCells);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WorksheetMergeCellsPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		Boolean gsResult = CALL_PROC(WorksheetMergeCells)(worksheet, topLeftCell, bottomRightCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WorksheetSplitCells(CALLBACKPTR, MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell)
{
	GET_CB_UPP(WorksheetSplitCells);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WorksheetSplitCellsPtr)(MCObjectHandle worksheet, const ViewPt& topLeftCell, const ViewPt& bottomRightCell);
		Boolean gsResult = CALL_PROC(WorksheetSplitCells)(worksheet, topLeftCell, bottomRightCell);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}




///////////////////////////////////////////
//  Workspaces
///////////////////////////////////////////


//void GS_CALLBACK GS_CloseResFile(CALLBACKPTR, short inFileID)
//{
//	GET_CB_UPP(CloseResFile);
//	if (f) {
//		CallBackPtr saveCBP = gCBP;
//		#if GS_USE_D0_RETURNS
//		#pragma pointers_in_D0
//		#endif
//		typedef void (*CloseResFilePtr)(CBSignedShort inFileID);
//		CALL_PROC(CloseResFile)(inFileID);
//		#if GS_USE_D0_RETURNS
//		#pragma pointers_in_A0
//		#endif
//		gCBP = saveCBP;
//	}
//}


void GS_CALLBACK GS_GetCurrentWorkspaceFile(CALLBACKPTR, TXString&  outFileName)
{
	GET_CB_UPP(GetCurrentWorkspaceFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*GetCurrentWorkspaceFilePtr)(TXString&  outFileName);
		CALL_PROC(GetCurrentWorkspaceFile)(outFileName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


short GS_CALLBACK GS_OpenExternalResFile(CALLBACKPTR, const TXString& inFileName, Byte fileAccessPerm)
{
	GET_CB_UPP(OpenExternalResFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*OpenExternalResFilePtr)(const TXString& inFileName, CBUnsignedByte fileAccessPerm);
		short gsResult = CALL_PROC(OpenExternalResFile)(inFileName, fileAccessPerm);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


short GS_CALLBACK GS_OpenWorkspaceResFile(CALLBACKPTR, const TXString& inFileName, Boolean createNewFile, Byte fileAccessPerm)
{
	GET_CB_UPP(OpenWorkspaceResFile);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBSignedShort (*OpenWorkspaceResFilePtr)(const TXString& inFileName, CBBoolean createNewFile, CBUnsignedByte fileAccessPerm);
		short gsResult = CALL_PROC(OpenWorkspaceResFile)(inFileName, createNewFile, fileAccessPerm);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return -1;
}


void GS_CALLBACK GS_SetWorkspaceFileToReload(CALLBACKPTR, const TXString& inFileName)
{
	GET_CB_UPP(SetWorkspaceFileToReload);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef void (*SetWorkspaceFileToReloadPtr)(const TXString& inFileName);
		CALL_PROC(SetWorkspaceFileToReload)(inFileName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
	}
}


Boolean GS_CALLBACK GS_WSAddMenu(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName)
{
	GET_CB_UPP(WSAddMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSAddMenuPtr)(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuName);
		Boolean gsResult = CALL_PROC(WSAddMenu)(inWorkspaceReference, inMenuIdentifier, inMenuName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSAddMenuItem(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, char inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier)
{
	GET_CB_UPP(WSAddMenuItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSAddMenuItemPtr)(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName, CBSignedByte inShortcutKey, Uint32 inShortcutKeyModifiers, const TXString& inSubMenuIdentifier);
		Boolean gsResult = CALL_PROC(WSAddMenuItem)(inWorkspaceReference, inMenuIdentifier, inMenuItemsUniversalName, inShortcutKey, inShortcutKeyModifiers, inSubMenuIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSAddTool(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolIdentifier, char inShortcutKey, Uint32 inKeyModifiers)
{
	GET_CB_UPP(WSAddTool);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSAddToolPtr)(Sint32 inWorkspaceReference, const TXString& inToolIdentifier, CBSignedByte inShortcutKey, Uint32 inKeyModifiers);
		Boolean gsResult = CALL_PROC(WSAddTool)(inWorkspaceReference, inToolIdentifier, inShortcutKey, inKeyModifiers);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSAddToolPalette(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier)
{
	GET_CB_UPP(WSAddToolPalette);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSAddToolPalettePtr)(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier);
		Boolean gsResult = CALL_PROC(WSAddToolPalette)(inWorkspaceReference, inToolPaletteIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSAddToolSet(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize)
{
	GET_CB_UPP(WSAddToolSet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSAddToolSetPtr)(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		Boolean gsResult = CALL_PROC(WSAddToolSet)(inWorkspaceReference, inToolSetIdentifier, inIconData, inIconDataSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSGetVersion(CALLBACKPTR, Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion)
{
	GET_CB_UPP(WSGetVersion);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSGetVersionPtr)(Sint32 inWorkspaceReference, Sint32* outWorkspaceVersion);
		Boolean gsResult = CALL_PROC(WSGetVersion)(inWorkspaceReference, outWorkspaceVersion);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSMenuAddMenuItem(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName)
{
	GET_CB_UPP(WSMenuAddMenuItem);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSMenuAddMenuItemPtr)(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier, const TXString& inMenuItemsUniversalName);
		Boolean gsResult = CALL_PROC(WSMenuAddMenuItem)(inWorkspaceReference, inMenuIdentifier, inMenuItemsUniversalName);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSMenuBarAddMenu(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inMenuIdentifier)
{
	GET_CB_UPP(WSMenuBarAddMenu);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSMenuBarAddMenuPtr)(Sint32 inWorkspaceReference, const TXString& inMenuIdentifier);
		Boolean gsResult = CALL_PROC(WSMenuBarAddMenu)(inWorkspaceReference, inMenuIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSOpen(CALLBACKPTR, const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference)
{
	GET_CB_UPP(WSOpen);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSOpenPtr)(const TXString& inWorkspaceFileToOpen, Sint32 inFilePermissions, Sint32* outWorkspaceReference);
		Boolean gsResult = CALL_PROC(WSOpen)(inWorkspaceFileToOpen, inFilePermissions, outWorkspaceReference);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSPaletteGetHomeCorner(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner)
{
	GET_CB_UPP(WSPaletteGetHomeCorner);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSPaletteGetHomeCornerPtr)(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, short* outWindowHomeCorner);
		Boolean gsResult = CALL_PROC(WSPaletteGetHomeCorner)(inWorkspaceReference, inToolPaletteIdentifier, outWindowHomeCorner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSPaletteSetHomeCorner(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, short inWindowHomeCorner)
{
	GET_CB_UPP(WSPaletteSetHomeCorner);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSPaletteSetHomeCornerPtr)(Sint32 inWorkspaceReference, const TXString& inPaletteIdentifier, CBSignedShort inWindowHomeCorner);
		Boolean gsResult = CALL_PROC(WSPaletteSetHomeCorner)(inWorkspaceReference, inPaletteIdentifier, inWindowHomeCorner);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSSetVersion(CALLBACKPTR, Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion)
{
	GET_CB_UPP(WSSetVersion);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSSetVersionPtr)(Sint32 inWorkspaceReference, Sint32 inWorkspaceVersion);
		Boolean gsResult = CALL_PROC(WSSetVersion)(inWorkspaceReference, inWorkspaceVersion);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSToolPaletteAddToolSet(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier)
{
	GET_CB_UPP(WSToolPaletteAddToolSet);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSToolPaletteAddToolSetPtr)(Sint32 inWorkspaceReference, const TXString& inToolPaletteIdentifier, const TXString& inToolSetIdentifier);
		Boolean gsResult = CALL_PROC(WSToolPaletteAddToolSet)(inWorkspaceReference, inToolPaletteIdentifier, inToolSetIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSToolSetAddTool(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize)
{
	GET_CB_UPP(WSToolSetAddTool);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSToolSetAddToolPtr)(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, void* inIconData, Uint32 inIconDataSize);
		Boolean gsResult = CALL_PROC(WSToolSetAddTool)(inWorkspaceReference, inToolSetIdentifier, inIconData, inIconDataSize);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


Boolean GS_CALLBACK GS_WSToolSetAddToolChildToTool(CALLBACKPTR, Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier)
{
	GET_CB_UPP(WSToolSetAddToolChildToTool);
	if (f) {
		CallBackPtr saveCBP = gCBP;
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_D0
		#endif
		typedef CBBoolean (*WSToolSetAddToolChildToToolPtr)(Sint32 inWorkspaceReference, const TXString& inToolSetIdentifier, const TXString& inParentToolIdentifier, const TXString& inChildToolIdentifier);
		Boolean gsResult = CALL_PROC(WSToolSetAddToolChildToTool)(inWorkspaceReference, inToolSetIdentifier, inParentToolIdentifier, inChildToolIdentifier);
		#if GS_USE_D0_RETURNS
		#pragma pointers_in_A0
		#endif
		gCBP = saveCBP;
		return gsResult;
	}
	else return false;
}


#endif


//#undef XCALL
//#undef XFN

}
