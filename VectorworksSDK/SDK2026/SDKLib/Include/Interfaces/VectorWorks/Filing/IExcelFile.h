//
//	Copyright  Nemetschek Vectorworks, Inc. 2020
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		struct SCellData
		{
			bool				fInconsistencyFound;
			
			Sint16				fAlignmentH;
			Sint16				fAlignmentV;
			Sint16				fTextAngle;
			
			TCellBorderRefNum	fTopBorder;
			TCellBorderRefNum	fLeftBorder;
			TCellBorderRefNum	fBottomBorder;
			TCellBorderRefNum	fRightBorder;
			
			Sint16				fStyle;
			ColorRef			fBgcolor;
			ColorRef			fFgcolor;
			Sint16				fFillpattern;
			
			TNumStyleRef		fNumStyle;
			TXString			fLeaderString;
			TXString			fTrailerString;
			
			Sint16				fFontIndex;
			Sint16				fFontSize;
			Sint16				fFontStyle;
			
			ColorRef			fTextColor;
			
			bool				fWrapTextFlag;
			
			TXString			fFormula;
			double				fValue;
			TXString			fString;
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IExcelFileSheet : public IVWUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE GetSize(Sint16& outRows, Sint16& outColumns) = 0;
			virtual bool VCOM_CALLTYPE GetCellNumber(const Sint16& row, const Sint16& column, TXString& outFormula, TNumStyleRef& outNumStyle, TXString& outString, double& outValue, TXString& outLeaderString, TXString& outTrailerString, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE GetCellAlignment(const Sint16& row, const Sint16& column, Sint16& outAlignmentH, Sint16& outAlignmentV, Sint16& outTextAngle, bool& outWrapTextFlag, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE GetCellFont(const Sint16& row, const Sint16& column, Sint16& outFontStyle, Sint16& outFontSize, Sint16& outFontIndex, ColorRef& outTextColor, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE GetCellBorder(const Sint16& row, const Sint16& column, TCellBorderRefNum& outTopBorder, TCellBorderRefNum& outLeftBorder, TCellBorderRefNum& outBottomBorder, TCellBorderRefNum& outRightBorder, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE GetCellFill(const Sint16& row, const Sint16& column, Sint16& outStyle, ColorRef& outBgColor, ColorRef& outFgColor, Sint16& outFillpattern, bool& outInconsistencyFound) = 0;

			virtual bool VCOM_CALLTYPE GetCellFormat(const Sint16& row, const Sint16& column, VectorWorks::Filing::SCellData& outCellData) = 0;
			// Set
			virtual bool VCOM_CALLTYPE SetCellNumber( const Sint16& row, const Sint16& column, const double& number ) = 0;
			virtual bool VCOM_CALLTYPE SetCellString( const Sint16& row, const Sint16& column, const TXString& string ) = 0;
			virtual bool VCOM_CALLTYPE SetCellStringFormula( const Sint16& row, const Sint16& column, const TXString& formulaString, const TXString& formulaValue ) = 0;
			virtual bool VCOM_CALLTYPE SetCellNumericFormula( const Sint16& row, const Sint16& column, const TXString& formulaString, const double& formulaValue ) = 0;
			virtual bool VCOM_CALLTYPE SetCellFormat(const Sint16& row, const Sint16& column, VectorWorks::Filing::SCellData& ioCellData) = 0;
			virtual bool VCOM_CALLTYPE SetCellAlignment(const Sint16& row, const Sint16& column, Sint16& alignmentH, Sint16& alignmentV, Sint16& textAngle, bool& wrapTextFlag, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellFont(const Sint16& row, const Sint16& column, Sint16& fontStyle, Sint16& fontSize, Sint16& fontIndex, ColorRef& textColor, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellBorderTop(const Sint16& row, const Sint16& column, TCellBorderRefNum& border, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellBorderBottom(const Sint16& row, const Sint16& column, TCellBorderRefNum& border, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellBorderLeft(const Sint16& row, const Sint16& column, TCellBorderRefNum& border, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellBorderRight(const Sint16& row, const Sint16& column, TCellBorderRefNum& border, bool& outInconsistencyFound) = 0;
			virtual bool VCOM_CALLTYPE SetCellFill(const Sint16& row, const Sint16& column, Sint16& style, ColorRef& bgColor, ColorRef& fgColor, Sint16& fillpattern, bool& outInconsistencyFound) = 0;


		};

		//-----------------------------------------------------------------------------------------------------------------
		// {689DCC5D-A1BF-490C-9145-EE01BD0F3C76}
		static const VWIID IID_ExcelFile = { 0x689dcc5d, 0xa1bf, 0x490c, { 0x91, 0x45, 0xee, 0x1, 0xbd, 0xf, 0x3c, 0x76 } };
		
		//-----------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IExcelFile : public IVWUnknown
		{
		public:
			virtual bool VCOM_CALLTYPE Read(IFileIdentifier* fileID) = 0;
			virtual bool VCOM_CALLTYPE NewWorkbook( IFileIdentifier* fileID ) = 0;
			virtual bool VCOM_CALLTYPE SaveAndCloseWorkbook( IFileIdentifier* fileID ) = 0;
			virtual bool VCOM_CALLTYPE CloseWorkbook() = 0;
			virtual bool VCOM_CALLTYPE AddSheet( TXString& inOutSheetName ) = 0;
			virtual bool VCOM_CALLTYPE DeleteSheet( const TXString& sheetName ) = 0;
			virtual bool VCOM_CALLTYPE GetExcelFileSheetNames(TXStringArray& outSheetNamesArr) = 0;
			virtual bool VCOM_CALLTYPE GetSheet(const TXString& sheetName, IExcelFileSheet** ppOutsheet) = 0;
			virtual bool VCOM_CALLTYPE GetSheet(const Sint32& sheetIndex, IExcelFileSheet** ppOutsheet) = 0;
			virtual Sint32 VCOM_CALLTYPE GetSheetCount () = 0;
			virtual bool VCOM_CALLTYPE GetSheetIndex( const TXString& sheetName, int& outSheetIndex ) = 0;
			virtual bool VCOM_CALLTYPE GetSheetName( const int& sheetIndex, TXString& outSheetName ) = 0;
		};

		//-----------------------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IExcelFile>	IExcelFilePtr;
		typedef VCOMPtr<IExcelFileSheet> IExcelFileSheetPtr;
	}
}


