//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "Control.h"

namespace VWFC
{
	namespace VWUI
	{
		// -----------------------------------------------------------------------------
		enum EItemTextJustification {
			kItemTextJustificationLeft		= 1,
			kItemTextJustificationCenter	= 2,
			kItemTextJustificationRight		= 3
		};

		// -----------------------------------------------------------------------------
		enum EItemTextStyle {
			kItemTextStylePlain				= 0,
			kItemTextStyleBold				= 1,
			kItemTextStyleItalic			= 2,
			kItemTextStyleBoldAndItalic		= 3,
			kItemTextStyleUnderline			= 4,
			kItemTextStyleInvalid			= 8
		};

		// -----------------------------------------------------------------------------
		class VWListBrowserCtrl;

		// -----------------------------------------------------------------------------
		class VWListBrowserItem
		{
		friend class VWListBrowserCtrl;
		protected:
										VWListBrowserItem(TControlID dialogID, TControlID controlID, short columnID, short rowID);
		public:
										VWListBrowserItem (const VWListBrowserItem& item);
										~VWListBrowserItem();

			VWListBrowserItem&			operator=(const VWListBrowserItem& item);

		// item specific function
		public:
			void						SetItemText(const TXString& text);
			void						SetItemImage(size_t imageIndex);
			void						SetItemInfo(const TXString& text, size_t imageIndex);
			TXString					GetItemText() const;
			size_t						GetItemImage() const;
			bool						GetItemInfo(TXString& outText, size_t& outImage) const;
			bool						SetItemData( const Sint32 userData );
			bool						GetItemData( Sint32 &outUserData );

			void						SetItemToolTip(const TXString& text);
			void						SetItemToolTip(const TXString& text, const TXString& subText);

			bool						EnsureItemVisible() const;

			void						SetItemTextStyle(EItemTextStyle textStyle);
			EItemTextStyle				GetItemTextStyle();

			void						SetItemTextJustification(EItemTextJustification justification);
			EItemTextJustification		GetItemTextJustification();

			void						SetMultImageIndexes(size_t imageIndex0, size_t imageIndex1 = (size_t) -1, size_t imageIndex2 = (size_t) -1);
			bool						GetMultImageIndexes(size_t& outImageIndex0, size_t& outImageIndex1, size_t& outImageIndex2);

			void						SetOwnerDrawnType(EListBrowserOwnerDrawnType ownerDrawnType);
			EListBrowserOwnerDrawnType	GetOwnerDrawnType();

			void						SetItemUsingColumnDataItem(size_t columnDataItemIndex);
			bool						GetColumnDataItemInfo();

		// attributes
		public:
			void						SetItemTextColor(const CRGBColor& color);
			void						SetItemTextColor(size_t redIndex, size_t greenIndex, size_t blueIndex);
			void						SetItemTextColorN(EUiControlTextTint colorTint);
			bool						GetItemTextColor(CRGBColor& outColor);

			void						SetItemDashStyle(InternalIndex styleIndex, size_t lineWeight);
			bool						GetItemDashStyle(InternalIndex& outStyleIndex, size_t& outLineWeight);
			
			void						SetItemMarkerChoice(const SMarkerStyle& markerStyle);
			bool						GetItemMarkerChoice(SMarkerStyle& markerStyle) const;
			void						ShowItemMarkerByClass(bool bShowByClass);
			void						ShowItemMarkerEditList(bool bShowEditList);
			void						SetItemMarkerByClass(bool bByClass);
			bool						GetItemMarkerByClass(bool& bByClass) const;
			
			void						SetItemFillForeColor(const CRGBColor& color);
			void						SetItemFillForeColor(const TGSColorV2& color);
			void						SetItemFillForeColor(size_t redIndex, size_t greenIndex, size_t blueIndex);
			void						SetItemNoFillForeColor();
			bool						GetItemFillForeColor( size_t &redIndex, size_t &greenIndex, size_t &blueIndex );
			bool						GetItemFillForeColor(CRGBColor& outColor);
			bool						GetItemFillForeColor(TGSColorV2& outColor);

			void						SetItemFillBackColor(const CRGBColor& color);
			void						SetItemFillBackColor(const TGSColorV2& color);
			void						SetItemFillBackColor(size_t redIndex, size_t greenIndex, size_t blueIndex);
			bool						GetItemFillBackColor(CRGBColor& outColor);
			bool						GetItemFillBackColor(TGSColorV2& outColor);

			void						SetItemPenForeColor(const CRGBColor& color);
			void						SetItemPenForeColor(size_t redIndex, size_t greenIndex, size_t blueIndex);
			bool						GetItemPenForeColor(CRGBColor& outColor);

			void						SetItemPenBackColor(const CRGBColor& color);
			void						SetItemPenBackColor(size_t redIndex, size_t greenIndex, size_t blueIndex);
			bool						GetItemPenBackColor(CRGBColor& outColor);

			void						SetItemGradientOrImageRefNumber(size_t refNumber);
			size_t						GetItemGradientOrImageRefNumber();

			void						SetItemTileRefNumber(size_t refNumber);
			size_t						GetItemTileRefNumber();
			
			void						SetItemHatchRefNumber(size_t refNumber);
			size_t						GetItemHatchRefNumber();

			void						SetItemPatternIndex(short patternIndex);
			short						GetItemPatternIndex();

			void						SetItemCheckState( CGSMultiStateValueChange::EStateValue state );
			bool						GetItemCheckState( CGSMultiStateValueChange::EStateValue& outState ) const;

			void						Enable3StateCheckbox( bool enable );
			bool						Is3StateCheckboxEnabled() const;

			void						SetItemInteractionType(EListBrowserItemInteractionType interactionType);
			void						EnableItemDirectEdit(bool enable);	
			bool						IsItemDirectEditEnabled();
            
            void                        SetItemResourceOnlyCurrentDocument(bool bOnlyCurrentDoc);
            bool                        IsItemResourceOnlyCurrentDocument();

		protected:
			short						fRowID;
			short						fColumnID;
			TControlID					fControlID;
			TControlID					fDialogID;
		};
	}
}
