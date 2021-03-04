//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IManifest.h"
#include "ICatalogFile.h"

namespace VectorWorks
{
	namespace DataCatalog
	{
		class DYNAMIC_ATTRIBUTE ICatalogAccessor;

		// ------------------------------------------------------------------------------------------------------
		struct SContentFile
		{
			EFolderSpecifier	fFolderSpec;
			TXString			fFileNameID;
		};

		// ------------------------------------------------------------------------------------------------------
		struct SCatalogDefinition
		{
			ICatalogAccessor*				fAccessor;
			SContentFile					fDefinitionFile_CatalogID;
			SCatalogDefinition*				fPerformanceDataDef;
			TXString						fPerformanceDataParamName;
			SContentFile					fSymbolFile_ContentID;
			bool							fIrrigationCatalog;
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		enum class EFilterOperation
		{
			Equal,
			EqualNot,
			Like,
			LikeNot,
			Lesser,
			Greater,
			LesserOrEqual,
			GreaterOrEqual,
		};

		// ------------------------------------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICatalogAccessor
		{
		public:
			virtual		~ICatalogAccessor() {}

			virtual void		Clear() = 0;

			virtual const SCatalogDefinition& 	GetDefinition() const = 0;
			virtual const IManifest&			GetManifest() const = 0;

			virtual ICatalogFile&				LoadCatalogFile() = 0;

			virtual const ICatalogAccessor*			GetPerformanceData() const = 0;
			virtual const ICatalogPerformanceFile*	LoadPerformanceDataFile() = 0;

		public:
			virtual bool	GetFromCatalogUI(VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;
			virtual bool	SaveInCatalogUI(VWFC::Tools::CGenericParamProvider& paramsProvider, std::function<void(TCatalogLinesArray&)> performanceLinesCallback = nullptr) = 0;

			virtual void	ApplyCatalogDataToSelection(VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;

			virtual void	LoadDataLine(TCatalogLine& outLine, VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;
			virtual bool	SaveDataLine(const TCatalogLine* line, VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;

			virtual void	ClearCatalogData(VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;
			virtual void	ApplyFirstCatalogItem(VWFC::Tools::CGenericParamProvider& paramsProvider) = 0;

		public:
			virtual bool	GetType(const char* univName, VectorWorks::Extension::EIrrigationUnitDimSize& outUnit) const = 0;
			virtual bool	GetType(const char* univName, VectorWorks::Extension::EIrrigationUnitDimDistance& outUnit) const = 0;
			virtual bool	GetType(const char* univName, VectorWorks::Extension::EIrrigationUnitFlow& outUnit) const = 0;
			virtual bool	GetType(const char* univName, VectorWorks::Extension::EIrrigationUnitPressure& outUnit) const = 0;
			virtual bool	GetType(const char* univName, VectorWorks::Extension::EIrrigationUnitVelocity& outUnit) const = 0;

		public:
			virtual MCObjectHandle	ImportDefaultNoUI_Symbol(const TXString& symName, const TXString& symFolderName) = 0;
			virtual MCObjectHandle	ImportDefaultNoUI_Symbol(const TXString& symSetName, const TXString& symFolderName, const TXString& key) = 0;
			virtual MCObjectHandle	ImportDefaultNoUI_Symbol(const TXString& symSetName, Sint32 rangeValue, bool importEntireSymSetName, const TXString& symFolderName) = 0;
			virtual MCObjectHandle	GetDocument_Symbol(const TXString& symSetName, Sint32 rangeValue) = 0;

		public:
			virtual bool	IsSymbolFromCatalog(const TXString& symName, const TXString& key) = 0;
		};
	}
}
