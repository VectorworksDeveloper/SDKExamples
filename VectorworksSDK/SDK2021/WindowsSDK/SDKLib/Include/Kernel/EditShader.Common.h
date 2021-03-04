//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "MiniCadCallBacks.h"

#pragma once


const short kShaderMenuItemTextSize = 64;


////// ShaderWidgetType

typedef enum {
	kNoWidget = 0,
	kColorWidget,
	kScaleWidget,
	kPopupWidget,
	kImageWidget,
	kBooleanWidget,
	kCoordLengthWidget,
	kFloatNormalizedEdit,
	kFloatRange0To10Edit,
	kFloatRange0To100Edit,
	kFloatRangeNeg10To10Edit,
	kLongRange0To10Edit,
	kLongRange0To1000Edit,
	kRefractionSlider, 	// 1..3
	kFloatNormalizedSlider,
	kFloatNormalizedNegativeSlider,
	kFloatRange0ToPoint2Slider,
	kFloatRange0ToPoint5Slider,
	kFloatRange0To5Slider,
	kFloatRange0To10Slider,
	kFloatRange0To100Slider,
	kLongRange0To10Slider,
	kLongRange0To20Slider,
	kLongRange1To6Slider,
	kFloatNormalizedPercentEdit,
	kRefractionEdit // 1...3

} EShaderWidgetType;


typedef union
{
	GSColor fColor;
	float fFloat;
	Sint32 fLong;
	bool fBool;
	WorldCoord fCoord;
	
} ShaderParamValue;


class ShaderParameter
{
	public:
		ShaderParameter(const TXString& prompt, const TXString& help, EShaderWidgetType type, ShaderParamValue value)
			:fPrompt(prompt), fHelp(help), fType(type), fValue(value) {}
		ShaderParameter() { fType = kNoWidget; }
		
		TXString GetPrompt() { return fPrompt; }
		TXString GetHelp() { return fHelp; }
		EShaderWidgetType GetType() { return fType; }
		ShaderParamValue GetValue() { return fValue; }
		
		void SetValue(const GSColor& color) { fValue.fColor = color; }
		void SetValue(float floatValue) { fValue.fFloat = floatValue; }
		void SetValue(Sint32 longValue) { fValue.fLong = longValue; }
		void SetValue(bool boolValue) { fValue.fBool = boolValue; }
		void SetValue(WorldCoord coordValue) { fValue.fCoord = coordValue; }
		
	protected:
		TXString fPrompt;
		TXString fHelp;
		EShaderWidgetType fType;
		ShaderParamValue fValue;
};

typedef ShaderParameter* ShaderParameterList;


struct ShaderParams
{
	short fNumParams;
	ShaderParameterList fParam;

	ShaderParams() { fNumParams = 0; fParam = nil; }
	ShaderParams(short numParams, ShaderParameterList param) 
				{ fNumParams = numParams; fParam = param; }
};


