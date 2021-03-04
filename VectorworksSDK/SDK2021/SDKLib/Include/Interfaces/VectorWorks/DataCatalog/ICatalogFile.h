//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IManifest.h"

namespace VectorWorks
{
	namespace DataCatalog
	{
		// ------------------------------------------------------------------------------------------------------
		typedef std::vector< TXString >				TCatalogLine;
		typedef std::vector< TCatalogLine >		TCatalogLinesArray;

		// ------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICatalogFile
		{
		public:
			virtual		~ICatalogFile() {}

			virtual const TXString&	GetFileName() const = 0;
			virtual TXString		GetFullPath() const = 0;

			virtual void		Add(const TCatalogLinesArray& arrLines) = 0;

			virtual void		Load() = 0;
			virtual void		Save() = 0;

			virtual const TCatalogLine&			GetColumns() const = 0;
			virtual const TCatalogLinesArray&	GetLines() const = 0;
			virtual TCatalogLinesArray&			GetLinesForEdit() = 0;

			virtual bool		IsLineEditable(size_t lineIndex) const = 0;
		};

		// ------------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE ICatalogPerformanceFile
		{
		public:
			virtual		~ICatalogPerformanceFile() {}

			virtual void		SaveIfChaned() = 0;

			virtual const IManifest*	GetManifest() const = 0;
			virtual const ICatalogFile*	GetFile() const = 0;

			virtual void		GetPerformanceData(TCatalogLinesArray& outPerformanceLines, const TCatalogLine& refCatalogLine) const = 0;
			virtual void		SetPerformanceData(const TCatalogLinesArray& performanceLines, const TCatalogLine& refCatalogLine) = 0;
		};
	}
}
