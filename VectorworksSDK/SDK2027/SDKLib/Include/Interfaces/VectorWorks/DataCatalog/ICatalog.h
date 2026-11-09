//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "ICatalogAccessor.h"

namespace VectorWorks
{
	namespace DataCatalog
	{
		typedef std::function<TXString(const TXString)>						TConfigValueCallback;	// a callback to provide localization string with the specified id
		typedef std::function<TXString(const TXString id, EEmptyHandling opt)>	TCatalogInfoCallback;	// a callback to provide catalog info localization strings
		typedef std::function<void(ICatalogAccessor* catalog)>				TCatalogAccessorCallback;

		// ---------------------------------------------------------------------------------------------------
		// {A87F8AD1-B2DD-454B-BB2E-D3F29A8CF2BE}
		static const VWIID IID_DataCatalog	= { 0xa87f8ad1, 0xb2dd, 0x454b, { 0xbb, 0x2e, 0xd3, 0xf2, 0x9a, 0x8c, 0xf2, 0xbe } };

		class DYNAMIC_ATTRIBUTE IDataCatalog : public IVWSingletonUnknown
		{
		public:
			virtual void	VCOM_CALLTYPE InitIrrigation(TConfigValueCallback contentConfigValue, TConfigValueCallback catalogConfigValue, TCatalogInfoCallback catalogInfoValue) = 0;
			virtual void	VCOM_CALLTYPE SetCommonLocalizer(TCatalogInfoCallback columnNamesLocalizer) = 0;
			virtual void	VCOM_CALLTYPE Register(SCatalogDefinition& def) = 0;
			virtual void	VCOM_CALLTYPE ForEachCatalog(TCatalogAccessorCallback callback) = 0;

		// Tools
		public:
			virtual void	VCOM_CALLTYPE GetCatalogDataFileRange(ICatalogAccessor* refCatalog, TCatalogLinesArray& outLines, const TUnivName2ValueMap& keys) = 0; 

			virtual bool	VCOM_CALLTYPE Compare(Sint32 value1, Sint32 value2, EFilterOperation op) = 0;
			virtual bool	VCOM_CALLTYPE Compare(const TXString& value1, const TXString& value2, EFilterOperation op) = 0;
			virtual bool	VCOM_CALLTYPE ComparePattern(const TXString& value, const TXString& pattern) = 0;
			virtual bool	VCOM_CALLTYPE CompareWithManifest(const IManifest& manifest, size_t colIndex, const TXString& value1, const TXString& value2) = 0;
			virtual bool	VCOM_CALLTYPE CompareWithManifestLooseDeg(const IManifest& manifest, size_t colIndex, const TXString& value1, const TXString& value2) = 0;

			virtual void	VCOM_CALLTYPE SplitSymbolName(const TXString & symSetName, TXString& outSymSetName, TXString& outKey) = 0;

			virtual bool	VCOM_CALLTYPE IsCatalogRegistered( const EFolderSpecifier &folderSpec, const TXString& catalogName ) = 0;
			virtual ICatalogAccessor* VCOM_CALLTYPE GetCatalogAccessor( const EFolderSpecifier &folderSpec, const TXString& catalogName ) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDataCatalog>	IDataCatalogPtr;
	}
}
