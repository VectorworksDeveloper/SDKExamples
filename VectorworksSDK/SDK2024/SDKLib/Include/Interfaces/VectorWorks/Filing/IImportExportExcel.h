//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		enum EExportWSFileFormat
		{
			eXLSX,
			eXLS,
			eCSV,			// comma delimited
			eCSV2,			// semicolon delimited
			eTabDelim,
			eMergeFormat,	// comma delimited
			eMergeFormat2,	// semicolon delimited
			eDif,
			eSylk,
		};

		enum class EExportWSWriteFileMode
		{
			// (file exists)  ? (open) : (create)
			// (sheet exists) ? (new/increment) : (create) 
			Append,
			// (file exists)  ? (delete then create) : (create)
			// (sheet exists) ? (delete then create) : (create) 
			Overwrite,
			// (file exists)  ? (open) : (do nothing)
			// (sheet exists) ? (update rows) : (do nothing) 
			Update,
		};

		struct SExportWSOptions 
		{
			EExportWSFileFormat	fFileFormat;
			bool				fAllRows;
			bool				fRecalculate;
			bool				fOpenInViewer;
		};

		struct SExportWSLink
		{
			SExportWSOptions			fExportWSOptions;
			TXGenericArray<TXString>	fArrWSNames;
		};

		// ----------------------------------------------------------------------------------------------------
		// {D33E675E-A71A-4CD8-BA0F-5047DB7D5FD7}
		static const VWIID IID_IImportExportExcel = { 0xd33e675e, 0xa71a, 0x4cd8, { 0xba, 0xf, 0x50, 0x47, 0xdb, 0x7d, 0x5f, 0xd7 } };
		
		class DYNAMIC_ATTRIBUTE IImportExportExcel : public IImportReference
		{
		public:
			virtual VCOMError				VCOM_CALLTYPE	Import(IFileIdentifierPtr fileID) = 0;
			virtual VCOMError				VCOM_CALLTYPE	Import(IFileIdentifierPtr fileID, MCObjectHandle& hDestinationWorksheet) = 0;
			virtual VCOMError				VCOM_CALLTYPE	Import(IFileIdentifierPtr& pFileID, const bool bShowUI, EImportModeRef importMode = EImportModeRef::Normal) override = 0;
			virtual VCOMError				VCOM_CALLTYPE	Convert(IFileIdentifier* fileID) = 0;
			virtual VCOMError				VCOM_CALLTYPE	ExportToExcelBook( const SExportWSLink &exportWSLink, IFileIdentifier* excelWorkBookID )  = 0;
			virtual VCOMError				VCOM_CALLTYPE	Export(const SExportWSLink &exportWSLink) = 0;
			virtual VCOMError				VCOM_CALLTYPE	AddWorksheetToExcelBook( const SExportWSLink &exportWSLink, IFileIdentifier* excelWorkBookID )  = 0;
			virtual bool					VCOM_CALLTYPE	IsDoingExcelExport() = 0; // return true if the excel export is currently working
			virtual bool					VCOM_CALLTYPE	IsDoingExcelImport() = 0; // return true if the excel import is currently working
			virtual void					VCOM_CALLTYPE	SetDestinationWorksheet( MCObjectHandle hDestinationWorksheet ) = 0;
			virtual SImportRefDlgBehavior	VCOM_CALLTYPE	GetImportRefDlgBehavior() const override = 0;
			virtual bool					VCOM_CALLTYPE	CheckIfFileMatchesSubscription( IFileIdentifierPtr fileID, Sint16 subID ) const = 0;

		protected:
			virtual bool		VCOM_CALLTYPE	DetermineSettingsToUse( bool quietly ) = 0;

		public:
			static const OSType kRefExcelDataType = 'RXLS';
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IImportExportExcel>		IImportExportExcelPtr;
	}
}
