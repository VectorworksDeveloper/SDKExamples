//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace VWUI
	{
#if 0
		// ---------------------------------------------------------------------------------------------------------------
		enum ECustomCtrlPenStyle {
			kCustomCtrlPenStyle_Solid,
			kCustomCtrlPenStyle_Dash,			/* -------  */
			kCustomCtrlPenStyle_Dot,			/* .......  */
			kCustomCtrlPenStyle_DashDot,		/* _._._._  */
			kCustomCtrlPenStyle_DashDotDot,		/* _.._.._  */
		};

		// ---------------------------------------------------------------------------------------------------------------
		enum ECustomCtrlBrushStyle {
			kCustomCtrlBrushStyle_Solid,
			kCustomCtrlBrushStyle_Horizontal,		/* ----- */
			kCustomCtrlBrushStyle_Vertical,			/* ||||| */
			kCustomCtrlBrushStyle_FDiagonal,		/* \\\\\ */
			kCustomCtrlBrushStyle_BDiagonal,		/* ///// */
			kCustomCtrlBrushStyle_Cross,			/* +++++ */
			kCustomCtrlBrushStyle_DiagonalCross,	/* xxxxx */
		};
#endif

		// ---------------------------------------------------------------------------------------------------------------
		class VWCustomCtrlPen
		{
		public:
								VWCustomCtrlPen();
								VWCustomCtrlPen(Uint8 red, Uint8 green, Uint8 blue);
								VWCustomCtrlPen(Uint8 red, Uint8 green, Uint8 blue, Sint16 size);
//								VWCustomCtrlPen(ECustomCtrlPenStyle style, Uint8 red, Uint8 green, Uint8 blue);
//								VWCustomCtrlPen(ECustomCtrlPenStyle style, Uint8 red, Uint8 green, Uint8 blue, Uint16 size);
								VWCustomCtrlPen(const VWCustomCtrlPen& src);
			virtual				~VWCustomCtrlPen();

			VWCustomCtrlPen&	operator=(const VWCustomCtrlPen& src);

		public:
			double				GetSize() const;
			void				SetSize(double size);
			GSColor				GetColor() const;
			void				SetColor(Uint8 red, Uint8 green, Uint8 blue);
//			ECustomCtrlPenStyle	GetStyle() const;

		private:
			double				fSize;
			GSColor				fColor;
//			ECustomCtrlPenStyle	fStyle;
		};

		// ---------------------------------------------------------------------------------------------------------------
		class VWCustomCtrlBrush
		{
		public:
								VWCustomCtrlBrush();
								VWCustomCtrlBrush(Uint8 red, Uint8 green, Uint8 blue);
								VWCustomCtrlBrush(Uint8 inPatternIndex, Uint8 red, Uint8 green, Uint8 blue, Uint8 backRed, Uint8 backGreen, Uint8 backBlue);
//								VWCustomCtrlBrush(ECustomCtrlBrushStyle style, Uint8 red, Uint8 green, Uint8 blue);
								VWCustomCtrlBrush(const VWCustomCtrlBrush& src);
			virtual				~VWCustomCtrlBrush();

			VWCustomCtrlBrush&	operator=(const VWCustomCtrlBrush& src);

		public:
			GSColor					GetColor() const;
			void					SetColor(Uint8 red, Uint8 green, Uint8 blue);
			GSColor					GetBackgroundColor() const;
			void					SetBackgroundColor(Uint8 red, Uint8 green, Uint8 blue);
			Uint8					GetPatternIndex() const;
			bool					SetPatternIndex(Uint8 inIndex);
//			ECustomCtrlBrushStyle	GetStyle() const;

		private:
//			ECustomCtrlBrushStyle	fStyle;
			GSColor					fColor;
			Uint8					fPatternIndex; // 0=None, 1-71 are patterns
			GSColor					fColorBackground;
		};

		// ---------------------------------------------------------------------------------------------------------------
		class VWCustomCtrlFont
		{
		public:
								VWCustomCtrlFont();
								VWCustomCtrlFont(const TXString& fontName, Uint32 size);
								VWCustomCtrlFont(const TXString& fontName, Uint32 size, bool bBold, bool bItalic, bool bUnderlined);
								VWCustomCtrlFont(const TXString& fontName, Uint32 size, bool bBold, bool bItalic, bool bUnderlined, bool bOutline, bool bShadow);
								VWCustomCtrlFont(const VWCustomCtrlFont& src);
			virtual				~VWCustomCtrlFont();

			VWCustomCtrlFont&	operator=(const VWCustomCtrlFont& src);

		public:
			TXString			GetFontName() const;
			Uint32				GetFontSize() const;
			void				SetFont(const TXString& name, Uint32 size);
			bool				GetBold() const;
			bool				GetItalic() const;
			bool				GetUnderlined() const;
			bool				GetOutline() const;
			bool				GetShadow() const;
			void				SetStyle(bool bold, bool italic, bool underlined);
			void				SetStyle(bool bold, bool italic, bool underlined, bool outline, bool shadow);
			double				GetRotation() const;
			void				SetRotation(double rot);
			bool				GetBaselineMirror() const;
			void				SetBaselineMirror(bool mirror);

		private:
			TXString			fFontName;
			Uint32				fSize;
			bool				fbBold;
			bool				fbItalic;
			bool				fbUnderlined;
			bool				fbOutline;
			bool				fbShadow;
			double				fdRotation;
			bool				fbBaselineMirror;
		};
	}
}