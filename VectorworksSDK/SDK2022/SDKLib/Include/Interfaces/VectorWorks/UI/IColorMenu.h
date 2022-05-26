//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

//#define USE_COLORPALETTES_MENU_IMPLEMENTATION	

#include "../IDocumentColorTable.h"

#ifdef GS_WIN
//#include "ThirdPartySource/QuickTime6WinSDK/CIncludes/quickdraw.h"
#endif

namespace VectorWorks
{
	namespace UI
	{				
		//
		// IColorMenu
		//
		// ----------------------------------------------------------------------------------------------------
		// {5f616ed0-7b07-11db-9fe1-0800200c9a66}
		//
		static const VWIID IID_ColorMenu = { 0x5f616ed0, 0x7b07, 0x11db, { 0x9f, 0xe1, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 } };
			
			
			
		enum EColorMenuFlavor
		{
			eColorMenuFlavor_ColorOnly,
			eColorMenuFlavor_ColorWithByClassOption
		};



		class IColorMenuCustom
		{
		public:
		
			static const Uint32 kColorByClassPart		= 0x00000001;
			static const Uint32 kColorPickerPart			= 0x00000002;
			static const Uint32 kPickColorPart			= 0x00000004;
			static const Uint32 kColorManagerPart		= 0x00000008;
			static const Uint32 kActivatedPalettesPart	= 0x00000010;
						
			virtual	~IColorMenuCustom( void ) {}

			virtual Sint32	ShowWhichOptionalParts( Sint32 identifier, Uint32 &outParts ) = 0;
			virtual Sint32	GetNumberOfFixedPalettes( Sint32 identifier, short &outFixedPaletteCount ) = 0;
			virtual Sint32 GetFixedPaletteName( Sint32 identifier, short inIndex, TXString &outName ) = 0;
			virtual Sint32 GetFixedPalette( Sint32 identifier, short inIndex, IColorRecordReceiver &recordReceiver ) = 0;
						
			virtual Sint32 GetAttributePaletteSwatchRGB( Sint32 identifier, short inColorIndex, TRGBColor &outColor ) = 0;
			virtual Sint32	InsertColor( Sint32 identifier, const TRGBColor &inColor, Uint16 &outIndex ) = 0;
			virtual Sint32	InsertColor( Sint32 identifier, const SColorRecord &inColor, Uint16 &outIndex ) = 0;
			virtual Sint32 GetColorRecord( Sint32 identifier, ColorRef inColorRef, SColorRecord	&outColorRecord ) = 0;
		};

	
							
		class DYNAMIC_ATTRIBUTE IColorMenu : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	ColorPopupMenuSelect( ViewRect				&inParentBounds,
																  ViewRect				&inDisplayBounds,
																  EColorMenuFlavor		inMenuFlavor,
																  IDocumentColorTable	*pColorTableAPI, 
																  ColorRef				&ioColorRef,
																  bool					&outColorByClass ) = 0;
																		
			virtual VCOMError VCOM_CALLTYPE GetColorPaletteOpen( bool &isOpen ) = 0;
		};
		
		//
		// IColorServices
		//
		static const VWIID IID_ColorServices = { 0x1798db00, 0xf7fe, 0x11db, { 0x83, 0x14, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 } };

		enum EViewAsPreference {		
			eViewAsPreference_Grid				= 0,
			eViewAsPreference_List				= 1,
		};

		enum ESortOrder {		
			eSortOrder_Manual					= 0,
			eSortOrder_HSV						= 1,
			eSortOrder_AscendingAlphabetical	= 2,
			eSortOrder_DecendingAlphabetical	= 3,
		};
		
		enum EPlacement {		
			ePlacement_Top						= 0,
			ePlacement_Bottom					= 1,
		};
		
		enum EStringSelector {
			eStringSelector_Measured						= 1,
			eStringSelector_StandardColorPickerHelpShort	= 2,
			eStringSelector_StandardColorPickerHelpExpanded	= 3,
			eStringSelector_PickColorHelpShort				= 4,
			eStringSelector_PickColorHelpExpanded			= 5,
			eStringSelector_ColorPaletteManagerHelpShort	= 6,
			eStringSelector_ColorPaletteManagerHelpExpanded	= 7,
			eStringSelector_ByClassHelpShort				= 8,
			eStringSelector_ByClassHelpExpanded				= 9,
			eStringSelector_TextAreaHelpShort				= 10,
			eStringSelector_TextAreaHelpExpanded			= 11,
			eStringSelector_PaletteButtonPrefixHelpShort	= 12,
			eStringSelector_PaletteButtonPrefixHelpExpanded	= 13,
			eStringSelector_MenuPreferencesHelpShort		= 14,
			eStringSelector_MenuPreferencesHelpExpanded		= 15,
			eStringSelector_ByClass							= 16,
			eStringSelector_Color							= 17,
			eStringSelector_ColorName						= 18,
			eStringSelector_Grid							= 19,
			eStringSelector_List							= 20,
			eStringSelector_Manual							= 21,
			eStringSelector_ByColor							= 22,
			eStringSelector_AscendingAlphabetical			= 23,
			eStringSelector_DecendingAlphabetical			= 24,
			eStringSelector_TopOfMenu						= 25,
			eStringSelector_BottomOfMenu					= 26,
			eStringSelector_ViewColorPaletteAs				= 27,
			eStringSelector_SortColorPaletteBy				= 28,
			eStringSelector_PlaceColorPalettesAt			= 29,
			eStringSelector_ShrinkToFit						= 30,
			eStringSelector_PaletteReadError				= 31,
			eStringSelector_PaletteReadErrorAdvicePrefix	= 32,
			eStringSelector_PaletteReadErrorAdviceSuffix	= 33,
			eStringSelector_ActiveDocument					= 34,
		};
		
		enum EPaletteActivation
		{
			ePaletteActivation_Active	= 0,
			ePaletteActivation_Inactive	= 1
			
		};
		
		class DYNAMIC_ATTRIBUTE IColorServices : public IVWSingletonUnknown
		{
		public:	
			//
			// ReducePalette accepts a set of colors and then finds a smaller
			// set of colors which is a good fit.
			//
			// reducedPalette should must be allocated by the caller and
			// be of size reducedPaletteSize. reducedPaletteSize will contain 
			// the actual size of the reduced palette upon exit. This may be 
			// smaller then the size passed in, but cannot be larger.
			//
			virtual VCOMError VCOM_CALLTYPE ReducePalette( const TGSColorV2 *fullPalette, Uint32 fullPaletteSize, TGSColorV2 *reducedPalette, Uint32 &ioReducedPaletteSize ) = 0;																						
			
			//
			// These functions allow one to manipulate color palette files.
			//
			virtual VCOMError VCOM_CALLTYPE CreatePalette( const SColorRecord *inColorRecords, const Uint32 inCColors, const TXString &inPaletteFilename ) = 0;																						
			virtual VCOMError VCOM_CALLTYPE GetColorsForPalette( const TXString &inPaletteFilename, IColorRecordReceiver *colorReceiver ) = 0;	
			virtual VCOMError VCOM_CALLTYPE PaletteExists( const TXString &inPaletteFilename, bool &outExists ) = 0;																						
			virtual VCOMError VCOM_CALLTYPE DuplicatePalette( const TXString &inPaletteFilename, TXString &outName ) = 0;																						
			virtual VCOMError VCOM_CALLTYPE RenamePalette( const TXString &inPaletteFilename, const TXString &inNewName ) = 0;																						
			virtual VCOMError VCOM_CALLTYPE DeletePalette( const TXString &inPaletteFilename ) = 0;	
		
			//
			// These functions obtains information about the activated color palettes
			//
			virtual VCOMError VCOM_CALLTYPE GetNumberOfActivatedPalettes( Uint32 &outNActivatedPalettes ) = 0;	
			virtual VCOMError VCOM_CALLTYPE GetPaletteFilename( Uint32 paletteIndex, TXString &outName ) = 0;	
			virtual VCOMError VCOM_CALLTYPE GetPaletteName( Uint32 paletteIndex, TXString &outName ) = 0;	
			virtual VCOMError VCOM_CALLTYPE IsDocumentColorPaletteActive( bool &isActive, TXString &outPaletteName ) = 0;

			//
			// These functions get/set the preferences for how the color menu is to appear
			//
			virtual VCOMError VCOM_CALLTYPE GetViewAsPreference( EViewAsPreference &outViewAs ) = 0;	
			virtual VCOMError VCOM_CALLTYPE SetViewAsPreference( EViewAsPreference inViewAs ) = 0;	

			virtual VCOMError VCOM_CALLTYPE GetSortOrderPreference( ESortOrder &outSortOrder ) = 0;	
			virtual VCOMError VCOM_CALLTYPE SetSortOrderPreference( ESortOrder inSortOrder ) = 0;	

			virtual VCOMError VCOM_CALLTYPE GetPlacementPreference( EPlacement &outPlacement ) = 0;	
			virtual VCOMError VCOM_CALLTYPE SetPlacementPreference( EPlacement inPlacement ) = 0;	
			
			virtual VCOMError VCOM_CALLTYPE GetShrinkToFitPreference( bool &outShrinkToFit) = 0;	
			virtual VCOMError VCOM_CALLTYPE SetShrinkToFitPreference( bool inShrinkToFit ) = 0;	

			virtual VCOMError VCOM_CALLTYPE GetCurrentPaletteName( TXString &outName ) = 0;	
			virtual VCOMError VCOM_CALLTYPE SetCurrentPaletteName( const TXString &inName ) = 0;

			virtual VCOMError VCOM_CALLTYPE RunPickColorFromPaletteDialog(ColorRef& colorRef) = 0;
			virtual VCOMError VCOM_CALLTYPE RunColorPaletteManagerDialog() = 0;

			virtual VCOMError VCOM_CALLTYPE RunNewColorPaletteDialog( const std::vector<SColorRecord>& inColorRecords, const TXString& inPaletteFileName ) = 0;
						
			//
			// This function is used to obtain localized strings related to the menu
			//
			
			virtual VCOMError VCOM_CALLTYPE GetString( EStringSelector whichString, TXString &outString ) = 0; 

			//
			// This function is used to obtain strings used for color tooltips
			//
			
			 virtual VCOMError VCOM_CALLTYPE GetTooltipStrings( const SColorRecord &inColorRecord, TXString &outRGBString, TXString &outHSVString, TXString &outCMYKString ) = 0;

			//
			// This function is used to compare colors in the document color table.
			//
			// outCompareResult = -1 if a < b
			// outCompareResult =  0 if a = b
			// outCompareResult =  1 if a > b
			//
			
			virtual VCOMError VCOM_CALLTYPE CompareColors( ColorRef inA, ColorRef inB, ESortOrder inSortOrder, Sint32 &outCompareResult ) = 0;
			
			//
			// This function is called as needed to update the active palette list
			//
			virtual VCOMError VCOM_CALLTYPE UpdateActivePaletteList( Boolean forceUpdate = false ) = 0;
			
			
			virtual VCOMError VCOM_CALLTYPE SetPaletteActivation( const TXString &inPaletteFilename, EPaletteActivation activationState ) = 0;
			
			/**
			 @brief Using the OS provided functionality, gets a color from the user.
			 @param red on input, the red component shown in the OS color picker. On output, the red component selected.
			 @param green on input, the red component shown in the OS color picker. On output, the greem component selected.
			 @param blue on input, the red component shown in the OS color picker. On output, the blue component selected.
			 
			 @return true if the user selected OK and false if the user cancelled.
			 */
			virtual VCOMError VCOM_CALLTYPE GetSystemColorFromUser(Uint16& red, Uint16& green, Uint16& blue) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSystemColorFromUser(TGSColorV2& color) = 0;
		};
	};
};

// 772c5ab4-021d-11dc-8314-0800200c9a66

