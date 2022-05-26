//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	using namespace Math;
	using namespace Tools;

	namespace VWObjects
	{
		// -----------------------------------------------------------------------------
		enum ETextStyle {
			kTextStyle_Plain			= kTextStylePlain,
			kTextStyle_Bold				= kTextStyleBold,
			kTextStyle_Italic			= kTextStyleItalic,
			kTextStyle_Underline		= kTextStyleUnderline,
			kTextStyle_Outline			= kTextStyleOutline,
			kTextStyle_Shadow			= kTextStyleShadow
		};

		// -----------------------------------------------------------------------------
		enum ETextHorzAlign
		{
			kTextHorzAlign_General		= kTextGeneralJustify,
			kTextHorzAlign_Left			= kTextLeftJustify,
			kTextHorzAlign_Center		= kTextCenterJustify,
			kTextHorzAlign_Right		= kTextRightJustify
		};

		// -----------------------------------------------------------------------------
		enum ETextVertAlign
		{
			kTextVertAlign_General			= kTextGeneralJustifyVertical,
			kTextVertAlign_TopBox			= kTextTopBox,
			kTextVertAlign_TopBaseline		= kTextTopBaseline,
			kTextVertAlign_CenterBox		= kTextCenterBox,
			kTextVertAlign_BottomBaseline	= kTextBottomBaseline,
			kTextVertAlign_BottomBox		= kTextBottomBox
		};

		// -----------------------------------------------------------------------------
		enum ETextVertSpacing
		{
			kTextVertSpacing_CustomLeading		= kTextCustomLeading,
			kTextVertSpacing_Single				= kTextSingle,
			kTextVertSpacing_ThreeHalves		= kTextThreeHalves,
			kTextVertSpacing_Double				= kTextDouble
		};

		// -----------------------------------------------------------------------------
		class VWTextBlockObj : public VWObject
		{
		public:
			// constructors and destructor
							VWTextBlockObj(const TXString& strText);
							VWTextBlockObj(const TXString& strText, const VWPoint2D& originPt);
							VWTextBlockObj(MCObjectHandle hTextBlock);
							VWTextBlockObj(const VWTextBlockObj& src);

			virtual			~VWTextBlockObj();

			VWTextBlockObj&	operator=(const VWTextBlockObj& src);

		public:
			VWPoint2D		GetOriginPt() const;
			void			SetOriginPt(const VWPoint2D& pt);

			// add / remove management
			bool			InsertText(const TXString& strAdd, size_t beforeIndex = 0);
			bool			AppendText(const TXString& strAdd);
			void			DeletePartOfText(size_t firstIndex, size_t numChars);
			void			DeleteText();
			bool			SetText(const TXString& text);

			size_t			GetTextLength() const;
			TXString		GetText() const;

			// get the nearest char to the given point
			size_t			GetNearestCharIndex(const VWPoint2D& pt) const;

			// text managment
			void			SetTextColor(const CRGBColor& color);
			void			SetTextFontIndex(short textColor);
			void			SetTextSize(double dTextSize);
			void			SetTextSizeByPoint(double dPointSize);
			void			SetTextStyle(ETextStyle style);

			// char managment
			CRGBColor		GetCharColor(size_t charNum) const;
			short			GetCharFontIndex(size_t charNum) const;
			double			GetCharSize(size_t charNum) const;
			ETextStyle		GetCharStyle(size_t charNum) const;

			// text portion managment
			void			SetCharsColor(size_t firstIndex, size_t numChars, const CRGBColor& color);
			void			SetCharsFontIndex(size_t firstIndex, size_t numChars, short fontIndex);
			void			SetCharsSize(size_t firstIndex, size_t numChars, double dCharSize);
			void			SetCharsSizeByPoint(size_t firstIndex, size_t numChars, double dPointSize);
			void			SetCharsStyle(size_t firstIndex, size_t numChars, ETextStyle style);

			// nearest char at specified point mnagment
			CRGBColor		GetNearestCharColor(const VWPoint2D& pt) const;
			short			GetNearestCharFontIndex(const VWPoint2D& pt) const;
			double			GetNearestCharSize(const VWPoint2D& pt) const;
			ETextStyle		GetNearestCharStyle(const VWPoint2D& pt) const;

			// Horizontal Alignment (justification)
			ETextHorzAlign	GetTextJustification() const;
			void			SetTextJustification(ETextHorzAlign textJust);

			// text block orientation - angle of rotation.  flipState indicates along
			// When drawing the text, the text is first flipped about the center point and then rotated around the same point.
			void			GetTextOrientation(double& outAngle, bool& outVertFlip);
			void			SetTextOrientation(double dAngle, bool bVertFlip);

			void			GetLineArray(std::vector<short>& lines) const;

			void			GetStyleArray(std::vector<TextStyleRec>& styles) const;

			void			GetRunArray(std::vector<TextRunRec>& runs) const;

			void			GetTabStopArray(std::vector<TextTabStop>& tabStops) const;

			void			GetCharWidthArray(std::vector<WorldCoord>& charWidths) const;

			// width
			double			GetTextWidth() const;
			void			SetTextWidth(double dWidth);

			// text wrapping
			bool			IsTextWrapped() const;
			void			SetTextWrap(bool bWrapped);

			// note text
			bool			IsNoteText() const;

			// tight fill
			bool			HasTightFill() const;

			// SIA elevation text
			bool			IsSIAElevationText() const;

			// Right to Left text
			bool			IsRightToLeftText() const;

			// Vertical alignment of the text block.
			ETextVertAlign	GetTextVerticalAlignment() const;
			void			SetTextVerticalAlignment(ETextVertAlign align);

			// The spacing of the entire text block:
			// If spacing is kTextVertSpacing_CustomLeading, then height is set to the custom leading value.
			// Otherwise height is unchanged.
			void			GetTextVerticalSpacing(ETextVertSpacing& outSpacing, double& outHeight);

			// If kTextVertSpacing_CustomLeading is specified, then the line height is set to the value in height.
			// Otherwise height is ignored.
			void			SetTextVerticalSpacing(ETextVertSpacing spacing, double dHeight);

			void			GetTextBoundary(WorldRectVerts& outBoxVerts);

		// Tools
		public:
			// Return true if the specified object handle is a text block
			static bool		IsTextBlockObject(MCObjectHandle hObj);

			// return the text block's symbol for new line
			static TXString	GetNewLineSymbol();

		private:
			VWPoint2D		fOriginPt;
		};
	}
}
