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
			enum class ETextureStyle
			{
				  None
				, Texture
				, RetainOriginal	// leave the texture unchanged
			};

			// ----------------------------------------------
			enum class EDropShadowStyle
			{
				  None
				, DropShadow
				, RetainOriginal	// leave the drop shadow unchanged
			};

			// ----------------------------------------------
			struct SAttrOverride
			{
				EFillStyle		fFillStyle = EFillStyle::RetainOriginal;
				ObjectColorType	fFillColor;
				bool			fFillColorBackOverride = false;	// fFillColor applicable for hatch, tile resources, and retain original
				bool			fFillColorForeOverride = false;	// fFillColor applicable for hatch, tile resources, and retain original
				short			fFillPattern = 0;
				InternalIndex	fFillResource = 0;
				bool			fFillOpacityOverride = false;
				OpacityRef		fFillOpacity = kMaxOpacity;

				EPenStyle		fPenStyle = EPenStyle::RetainOriginal;
				ObjectColorType	fPenColor;
				short			fPenPattern = 0;
				bool			fPenColorForeOverride = false;	// fPenColor applicable for line type resources
				bool			fPenColorBackOverride = false;	// fPenColor applicable for retain original
				InternalIndex	fPenLineType = 0;
				bool			fPenOpacityOverride = false;
				OpacityRef		fPenOpacity = kMaxOpacity;
				
				short			fLineWeight = 0;

				ETextureStyle	fTextureStyle = ETextureStyle::None;
				InternalIndex	fTextureResource = 0;

				EDropShadowStyle fDropShadowStyle = EDropShadowStyle::RetainOriginal;
				SDropShadowData fDropShadowSettings;
			};

			typedef std::vector<SAttrOverride>			TAttrOverrideArray;

			// ----------------------------------------------
			enum class EDrawAllOthers
			{
				  Normally
				, Grayed
			};

			// ------------------------------------------------------------------------------------------------------------------------------------
			// T01943 — Live Data Visualization
			// {47BBD866-DE59-483F-A578-796DE5369A91}
			static const VWIID IID_AttrByDataOverride = { 0x47bbd866, 0xde59, 0x483f,{ 0xa5, 0x78, 0x79, 0x6d, 0xe5, 0x36, 0x9a, 0x91 } };

			typedef std::pair<TXString, SAttrOverride> TColorEntry;
			enum class ESelectionParams {
				espAll = 0,
				espApplied
			};

			class DYNAMIC_ATTRIBUTE IAttrByDataOverride : public IVWSingletonUnknown
			{
			public:
				virtual void VCOM_CALLTYPE AddContext(MCObjectHandle hViewport) = 0;
				virtual void VCOM_CALLTYPE RemoveContext() = 0;
				virtual void VCOM_CALLTYPE Pause() = 0;		// Pauses the GetObjectOverride function from working and makes it return false always for the current context
															// This function uses counter, so it can be called recursively. A corresponding Resume should be made for each Pause
				virtual void VCOM_CALLTYPE Resume() = 0;	// Resume a Pause call
				virtual bool VCOM_CALLTYPE IsPaused() = 0;	// Checks if override is paused

															// these functions work on the last added context 'AddContext'
				virtual bool 			VCOM_CALLTYPE GetOverrideEnabled() = 0;

				virtual bool VCOM_CALLTYPE GetObjectOverride(MCObjectHandle hObject, SAttrOverride& outAttrOverride) = 0;
				virtual bool VCOM_CALLTYPE GetObjectGrayed(MCObjectHandle hObject) = 0;

				// eyedropper like copy-paste support
				virtual bool VCOM_CALLTYPE	CopyPick(MCObjectHandle hViewportSource) = 0;
				virtual bool VCOM_CALLTYPE	CopyInto(MCObjectHandle hViewportDest) = 0;

				virtual void VCOM_CALLTYPE	GetDataVisInfo(const UuidStorage& schemeID, ESelectionParams inParams, TXString& outSchemeName, std::vector<TColorEntry>& outSchemesInfo) const = 0;
				

				virtual bool VCOM_CALLTYPE	GetIncludeGroup() const = 0;
				virtual bool VCOM_CALLTYPE	GetIncludeSymbols() const = 0;

				virtual void VCOM_CALLTYPE	PushDataVisContainer(MCObjectHandle inhObject) = 0;
				virtual void VCOM_CALLTYPE	PopDataVisContainer() = 0;

				// if the viewport does not have a scheme applied this method returns an empty ID
				virtual UuidStorage VCOM_CALLTYPE GetViewportSchemeID(MCObjectHandle inhViewport) = 0;

				// This is to be used by swatches to override the fill (problem exists if the DataVis overrides back/fore colors for tiles and hatches )
				virtual bool VCOM_CALLTYPE	OverrideObjectFill(MCObjectHandle inhObject, const SAttrOverride& inAttrOverride) = 0;

			};

			typedef VCOMPtr<IAttrByDataOverride>	IAttrByDataOverridePtr;
		};
	}
}


