//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDBVariant.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IDBResultSetMetaData : public IVWUnknown
		{
		public:
			virtual Uint16			VCOM_CALLTYPE GetColumnsCount() = 0;
			virtual TXString		VCOM_CALLTYPE GetColumnText(Uint16 colIndex) = 0;
			virtual EVariantType	VCOM_CALLTYPE GetColumnType(Uint16 colIndex) = 0;
			virtual TXString		VCOM_CALLTYPE GetColumnTypeString(Uint16 colIndex) = 0;
			virtual bool			VCOM_CALLTYPE GetColumnIsNullable(Uint16 colIndex) = 0;
			virtual Uint32			VCOM_CALLTYPE GetColumnSize(Uint16 colIndex) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBResultSetMetaData>		IDBResultSetMetaDataPtr;
	}
}
