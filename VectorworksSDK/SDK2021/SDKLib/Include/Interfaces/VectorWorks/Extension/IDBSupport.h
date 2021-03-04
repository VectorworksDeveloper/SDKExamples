//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once

#include "IDBErrorContext.h"
#include "IDBDatabase.h"

namespace VectorWorks
{
	namespace Extension
	{
		// ------------------------------------------------------------------------
		enum EDBSupportUpdateType
		{
			eDBSupportUpdateType_Manual,
			eDBSupportUpdateType_EveryRecordChange,
			eDBSupportUpdateType_OnTime,
		};

		// ---------------------------------------------------------------------------------------------------
		enum EDBSupportLinkType
		{
			eDBSupportLinkType_ReadWrite,
			eDBSupportLinkType_ReadOnly,
			eDBSupportLinkType_WriteOnly,
		};

		// ------------------------------------------------------------------------
		struct SDBSupportUpdateSettings
		{
			Uint32						fSize;
			EDBSupportUpdateType		fDBUpdateType;
			Uint32						fDBUpdateTimeMin;
			EDBSupportUpdateType		fDocUpdateType;
			Uint32						fDocUpdateTimeMin;

							SDBSupportUpdateSettings()
								{
									fSize				= sizeof(SDBSupportUpdateSettings);
									fDBUpdateType		= eDBSupportUpdateType_Manual;
									fDBUpdateTimeMin	= 5;
									fDocUpdateType		= eDBSupportUpdateType_Manual;
									fDocUpdateTimeMin	= 5;
								}
		};

		// -----------------------------------------------------------------------------------
		enum EDBSupportProblems
		{
			// DB manager
			eDBSupportProblems_DSDelete						= 1		,	// data array: <DSN>
			eDBSupportProblems_TableDelete					= 1 << 1,	// data array: <DSN>:<Table Name>
			eDBSupportProblems_ColumnDelete					= 1 << 2,	// data array: <DSN>:<Table Name>:<Column Name>
			eDBSupportProblems_ChangeKeyColumn				= 1 << 3,	// data array: <DSN>:<Table Name>:<Column Name>
			// format
			eDBSupportProblems_FormatConnChange				= 1 << 4,
			eDBSupportProblems_FormatFieldNameConnChange	= 1 << 6,
			eDBSupportProblems_FormatFieldRWChange			= 1 << 7,
		};

		// ------------------------------------------------------------------------------------------------------
		struct SDBSupportFormatConnOptions
		{
			bool	fAddRows;
			bool	fDelRows;
					
					SDBSupportFormatConnOptions()
					{
						fAddRows	= true;
						fDelRows	= true;
					}

					SDBSupportFormatConnOptions(const SDBSupportFormatConnOptions& src)
					{
						fAddRows	= src.fAddRows;
						fDelRows	= src.fDelRows;
					}
		};

		// ---------------------------------------------------------------------------------------------------
		// {266A0751-422E-48aa-9BF4-AED001C8A149}
		static const VWIID IID_DBSupport	= { 0x266a0751, 0x422e, 0x48aa, { 0x9b, 0xf4, 0xae, 0xd0, 0x1, 0xc8, 0xa1, 0x49 } };

		class DYNAMIC_ATTRIBUTE IDBSupport : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError	VCOM_CALLTYPE HasDatabaseConnections(MCObjectHandle hDocument) = 0;
			virtual VCOMError	VCOM_CALLTYPE HasDatabaseObjectConnections(MCObjectHandle hDocument) = 0;

			// Database UI support
			virtual VCOMError	VCOM_CALLTYPE ShowManageDatabases(MCObjectHandle hDocument) = 0;
			virtual VCOMError	VCOM_CALLTYPE ShowTable(MCObjectHandle hDocument, const TXString& databaseName, const TXString& tableName) = 0;
			virtual VCOMError	VCOM_CALLTYPE ShowObjectConnectionDialogs(MCObjectHandle hSelObject = nullptr) = 0;
			virtual VCOMError	VCOM_CALLTYPE ShowEditConectionDialog() = 0;
			virtual VCOMError	VCOM_CALLTYPE ShowConnectionOptionsDialog(SDBSupportFormatConnOptions& inoutConnOptionsData) = 0;
			virtual VCOMError   VCOM_CALLTYPE ShowObjectConnectionDialogsN(MCObjectHandle hSelObject, const TXString& recordName) = 0;

			// Database connection support
			virtual VCOMError	VCOM_CALLTYPE AddDatabaseConnection(MCObjectHandle hDocument, const TXString& databaseName, const TXString& userName, const TXString& password) = 0;
			virtual VCOMError	VCOM_CALLTYPE RemoveDatabaseConnection(MCObjectHandle hDocument, const TXString& databaseName) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetDatabaseConnection(MCObjectHandle hDocument, const TXString& databaseName, TXString& outUserName, TXString& outPassword) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetDatabaseConnectionKeyColumn(MCObjectHandle hDocument, const TXString& databaseName, const TXString& tableName, const TXString& colName, bool isKey) = 0;

			// Database enumerate support
			virtual VCOMError	VCOM_CALLTYPE GetAvailableDatabases(MCObjectHandle hDocument, TXStringArray& outArrDatabaseNames) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetAvailableTables(MCObjectHandle hDocument, const TXString& databaseName, TXStringArray& outArrTableNames) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetAvailableTableColumns(MCObjectHandle hDocument, const TXString& databaseName, const TXString& tableName, TVWArray_DBTableColumn& outArrColumns) = 0;

			// Format support
			virtual VCOMError	VCOM_CALLTYPE GetFormatConnection(MCObjectHandle hFormat, TXString& outDatabaseName, TXString& outTableName) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetFormatConnection(MCObjectHandle hFormat, const TXString& databaseName, const TXString& tableName) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetFormatFieldConnection(MCObjectHandle hFormat, TXString& inoutfieldName, TXString& inoutColumnName, EDBSupportLinkType& outLinkType) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetFormatFieldConnection(MCObjectHandle hFormat, const TXString& fieldName, const TXString& columnName, EDBSupportLinkType linkType) = 0;
			virtual VCOMError	VCOM_CALLTYPE IsColumnUsedInFormatConnection(MCObjectHandle hDocument, const TXString& dbName, const TXString& table, const TXString& column, bool& outIsUsed, TXString& outFormatName, TXString& outFieldName) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetFormatConnectionOptions(MCObjectHandle hFormat, SDBSupportFormatConnOptions& outConnOptionsData) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetFormatConnectionOptions(MCObjectHandle hFormat, const SDBSupportFormatConnOptions& outConnOptionsData) = 0;
			virtual VCOMError	VCOM_CALLTYPE CopyFormatConnection(MCObjectHandle hOldFormat, MCObjectHandle hNewFormat) = 0;

			// Object support
			virtual VCOMError	VCOM_CALLTYPE GetWritingSQLSentence(MCObjectHandle hObject, TXString& outSqlSentence) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetWritingSQLSentence(MCObjectHandle hObject, const TXString& sqlSentence) = 0;
			virtual VCOMError	VCOM_CALLTYPE GetReadingSQLSentence(MCObjectHandle hObject, TXString& outSqlSentence) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetReadingSQLSentence(MCObjectHandle hObject, const TXString& sqlSentence) = 0;
			virtual VCOMError	VCOM_CALLTYPE ClearSQLSentences(MCObjectHandle hObject, const TXString& fieldName, const TXString& columnName) = 0;
			virtual VCOMError	VCOM_CALLTYPE RemoveObjectConnections(MCObjectHandle hDocument, bool fromSelecedObjecstOnly) = 0;

			// Database/Document update support
			virtual VCOMError	VCOM_CALLTYPE GetUpdateSettings(MCObjectHandle hDocument, SDBSupportUpdateSettings& outSettings) = 0;
			virtual VCOMError	VCOM_CALLTYPE SetUpdateSettings(MCObjectHandle hDocument, const SDBSupportUpdateSettings& settings) = 0;
			virtual VCOMError	VCOM_CALLTYPE UpdateDatabase(MCObjectHandle hDocument, bool selectionOnly, bool showProgress, bool optimizeProgress) = 0;
			virtual VCOMError	VCOM_CALLTYPE UpdateDocument(MCObjectHandle hDocument, bool selectionOnly, bool showProgress, bool optimizeProgress) = 0;

			// Sync support
			virtual VCOMError	VCOM_CALLTYPE SyncAskForOptions(Uint32& inOutOptions /*EDBSupportProblems*/) = 0;
			virtual VCOMError	VCOM_CALLTYPE SyncFixDocument(MCObjectHandle hDocument, EDBSupportProblems option, const TXStringArray& arrItems) = 0;
		};

		// ---------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IDBSupport>		IDBSupportPtr;
	}
}