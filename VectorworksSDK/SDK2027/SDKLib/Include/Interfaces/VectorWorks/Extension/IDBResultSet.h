//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDBVariant.h"
#include "IDBResultSetMetaData.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ---------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IDBResultSet : public IVWUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE GetMetaData(IDBResultSetMetaData** ppOutMetaData) = 0;
			virtual VCOMError	VCOM_CALLTYPE Fetch() = 0;
			virtual VCOMError	VCOM_CALLTYPE MoveNext() = 0;
			virtual VCOMError	VCOM_CALLTYPE MovePrevious() = 0;
			virtual VCOMError	VCOM_CALLTYPE MoveFirst() = 0;
			virtual VCOMError	VCOM_CALLTYPE MoveLast() = 0;

			virtual VCOMError	VCOM_CALLTYPE GetValue(Uint16 columnIndex, IDBVariant* variant) = 0;
//			virtual VCOMError	VCOM_CALLTYPE Bind(Uint16 columnIndex, IDBVariant* variant) = 0;
//			virtual VCOMError	VCOM_CALLTYPE Unbind(IDBVariant* variant) = 0;

			virtual Sint32		VCOM_CALLTYPE GetRowsCount() = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBResultSet>		IResultSetPtr;
	}
}
