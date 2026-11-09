//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDBConnectionString.h"
#include "IDBResultSet.h"

namespace VectorWorks
{
	namespace Extension
	{
		// -----------------------------------------------------------------------------------
		enum ECursorType
		{
			eCursorType_Dynamic,
			eCursorType_Static,
			eCursorType_Keysetdriven,
			eCursorType_Forwardonly,
		};

		// ------------------------------------------------------------------------
		enum ECommitMode
		{
			eCommitMode_Default,
			eCommitMode_Auto,
			eCommitMode_Manual,
		};

		// ------------------------------------------------------------------------
		struct SDBTableColumn
		{
			TXString				fName;
			TXString				fType;
			bool					fCanBeKey;
			bool					fIsKey;
		};

		typedef TXGenericArray< SDBTableColumn >		TVWArray_DBTableColumn;

		// ---------------------------------------------------------------------------------------------------
		// {CDB4EBE8-D45C-42bf-83D3-0C0313BE26CE}
		static const VWIID IID_DBDatabase	= { 0xcdb4ebe8, 0xd45c, 0x42bf, { 0x83, 0xd3, 0xc, 0x3, 0x13, 0xbe, 0x26, 0xce } };

		class DYNAMIC_ATTRIBUTE IDBDatabase : public IVWUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE Connect(const TXString& dsn, const TXString& user, const TXString& password) = 0;
			virtual VCOMError	VCOM_CALLTYPE ConnectWithBrowser(IDBConnectionString** outConnectionString) = 0;
			virtual	VCOMError	VCOM_CALLTYPE ConnectDriver(IDBConnectionString* inOutConnectionString) = 0;
			
			virtual	VCOMError	VCOM_CALLTYPE GetQueryBuilderInfo(IDBConnectionString* inOutQueryBuilder) = 0;

			virtual VCOMError	VCOM_CALLTYPE GetNumRows(const TXString& tableName, size_t& outCnt) = 0;
			virtual VCOMError	VCOM_CALLTYPE ListTables(bool includeViews, bool includeSystemTables, TXStringArray& outArrTables) = 0;
			virtual VCOMError	VCOM_CALLTYPE ListAvailableDataSources(TXStringArray& dataSources) = 0;
			virtual VCOMError	VCOM_CALLTYPE ListAllDrivers(TXStringArray& drivers) = 0;
			virtual VCOMError	VCOM_CALLTYPE ListAllColumns(const TXString& tableName, bool identifyKeyColumns, TVWArray_DBTableColumn& outArrColumns) = 0;

			virtual VCOMError	VCOM_CALLTYPE Execute(const TXString& sql) = 0;
			virtual VCOMError	VCOM_CALLTYPE Execute(const TXString& sql, Sint32& outResultCount) = 0;
			virtual VCOMError	VCOM_CALLTYPE ExecuteQuery(const TXString& sql, IDBResultSet** ppOutResultSet) = 0;
			virtual VCOMError	VCOM_CALLTYPE ExecuteQuery(const TXString& sql, ECursorType cursorType, bool bScrollable, IDBResultSet** ppOutResultSet) = 0;

			virtual VCOMError	VCOM_CALLTYPE Commit() = 0;
			virtual VCOMError	VCOM_CALLTYPE Rollback() = 0;

			virtual bool		VCOM_CALLTYPE IsOpened() = 0;
			virtual void		VCOM_CALLTYPE SetTimeout(Sint32 timeOut) = 0;
			virtual Sint32		VCOM_CALLTYPE GetTimeout() = 0;

			virtual TXString	VCOM_CALLTYPE GetLastErrorMessage() = 0;
			virtual TXString	VCOM_CALLTYPE GetLastErrorState() = 0;
			virtual Sint32		VCOM_CALLTYPE GetLastErrorCode() = 0;
			virtual TXString	VCOM_CALLTYPE GetLastErrorInternalDesc() = 0;

		// Vectorworks 2012
		public:
			virtual VCOMError	VCOM_CALLTYPE ConnectWithBrowserN(TXString& outConnectionString) = 0;
			virtual	VCOMError	VCOM_CALLTYPE ConnectDriverN(const TXString& connectionString) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetDriverInfo(TXString& outDriverName, TXString& outDriverID, TXString& outServer, TXString& outDatabase) = 0;
			virtual VCOMError	VCOM_CALLTYPE ListAllColumnsN(const TXString& inTableName, bool inIdentifyKeyColumns, Sint32 driverNotToDoTheJob, TVWArray_DBTableColumn& outArrColumns) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetNumRowsN(const TXString& inTableName, Sint32 driverNoToDoTheJob, size_t& outCnt) = 0;
			virtual VCOMError	VCOM_CALLTYPE ExecuteQueryN(const TXString& sql, Sint32 driverNoToDoTheJob, IDBResultSet** ppOutResultSet) = 0;

		// Vectorworks 2013
		public:
			virtual VCOMError	VCOM_CALLTYPE SetTransactionMode(ECommitMode commitMode) = 0;
			virtual bool		VCOM_CALLTYPE IsInTransactionMode() = 0;
			virtual bool		VCOM_CALLTYPE DoTableExists(const TXString& table) = 0;

		// Vectorworks 2015
		public:
			virtual VCOMError	VCOM_CALLTYPE CloseConnection() = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBDatabase>		IDBDatabasePtr;
	}
}
