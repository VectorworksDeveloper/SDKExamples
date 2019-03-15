//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------------------------------------------------------------------
		namespace ViewportVisializationOverride
		{
			// ----------------------------------------------
			enum class EFillStyle
			{
				  None
				, Solid
				, Pattern
				, Hatch
				, Tile
				, Gradient
				, Image
				, RetainOriginal	// leave the fill style unchanged
			};

			// ----------------------------------------------
			enum class EPenStyle
			{
				  None
				, Solid
				, Pattern
				, LineType
				, RetainOriginal	// leave the pen style unchanged
			};

			// ----------------------------------------------
			struct SAttrOverride
			{
				EFillStyle		fFillStyle;
				ObjectColorType	fFillColor;
				bool			fFillColorBackOverride;	// fFillColor applicable for hatch, tile resources, and retain original
				bool			fFillColorForeOverride;	// fFillColor applicable for hatch, tile resources, and retain original
				short			fFillPattern;
				InternalIndex	fFillResource;

				EPenStyle		fPenStyle;
				ObjectColorType	fPenColor;
				short			fPenPattern;
				bool			fPenColorForeOverride;	// fPenColor applicable for line type resources
				bool			fPenColorBackOverride;	// fPenColor applicable for retain original
				InternalIndex	fPenLineType;
				
				short			fLineWeight;

				SAttrOverride() { fFillStyle = EFillStyle::RetainOriginal; fPenStyle = EPenStyle::RetainOriginal; fLineWeight = 0; fFillColorBackOverride = fFillColorForeOverride = fPenColorForeOverride = fPenColorBackOverride = false; fFillPattern = fPenPattern = 0; fFillResource = fPenLineType = 0; fLineWeight = 0; }
			};

			// ----------------------------------------------
			struct SRecordInfo
			{
				TXString	fRecordName;
				TXString	fFieldName;
				bool		operator < (const SRecordInfo& src) const { return fRecordName == src.fRecordName ? fFieldName < src.fFieldName : fRecordName < src.fRecordName; };
			};

			typedef std::vector<SAttrOverride>			TAttrOverrideArray;
			typedef std::map<SRecordInfo,SAttrOverride>	TAttrOverrideMap;

			// ----------------------------------------------
			enum class EDrawAllOthers
			{
				  Normally
				, Grayed
				, GrayedNoFill
			};

			// ------------------------------------------------------------------------------------------------------------------------------------
			// {E52D9570-ECFC-4F92-936E-193FAB9B3760}
			static const VWIID IID_ViewportVisualizationOverride = { 0xe52d9570, 0xecfc, 0x4f92, { 0x93, 0x6e, 0x19, 0x3f, 0xab, 0x9b, 0x37, 0x60 } };

			class DYNAMIC_ATTRIBUTE IViewportVisualizationOverride : public IVWSingletonUnknown
			{
			public:
				virtual bool VCOM_CALLTYPE ShowEditDialogUI(MCObjectHandle hViewport) = 0;

				virtual bool VCOM_CALLTYPE HasViewportOverride(MCObjectHandle hViewport) = 0;

				virtual void VCOM_CALLTYPE AddContext(MCObjectHandle hViewport) = 0;
				virtual void VCOM_CALLTYPE RemoveContext() = 0;
				virtual void VCOM_CALLTYPE Pause() = 0;		// Pauses the GetObjectOverride function from working and makes it return false always for the current context
															// This function uses counter, so it can be called recursively. A corresponding Resume should be made for each Pause
				virtual void VCOM_CALLTYPE Resume() = 0;	// Resume a Pause call
				virtual bool VCOM_CALLTYPE IsPaused() = 0;	// Checks if override is paused

				// these functions work on the last added context 'AddContext'
				virtual bool 			VCOM_CALLTYPE GetOverrideEnabled() = 0;
				virtual bool 			VCOM_CALLTYPE GetIncludeGroup() = 0;
				virtual bool 			VCOM_CALLTYPE GetIncludeSymbols() = 0;
				virtual EDrawAllOthers	VCOM_CALLTYPE GetOverrideDrawAllOtherObjects() = 0;

				virtual bool VCOM_CALLTYPE GetObjectOverride(MCObjectHandle hObject, SAttrOverride& outAttrOverride) = 0;

				// eyedropper like copy-paste support
				virtual bool VCOM_CALLTYPE	CopyPick(MCObjectHandle hViewportSource) = 0;
				virtual bool VCOM_CALLTYPE	CopyInto(MCObjectHandle hViewportDest) = 0;

				virtual void VCOM_CALLTYPE	GetAttributes(TAttrOverrideArray& outArrUsedAttributes) = 0;
				virtual void VCOM_CALLTYPE	GetAttributesWithRecordInfo(TAttrOverrideMap& outUsedAttributes) = 0;
				virtual bool VCOM_CALLTYPE	SetAttributes(const SRecordInfo& recordInfo, const SAttrOverride& attributes) = 0;
			};

			typedef VCOMPtr<IViewportVisualizationOverride>	IViewportVisualizationOverridePtr;
		};
	}
}


