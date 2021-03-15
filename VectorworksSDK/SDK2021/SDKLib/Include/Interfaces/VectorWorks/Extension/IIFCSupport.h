//
//	IIFCSupport.h
//
//	Copyright (c) Nemetschek North America, Inc  2005.
//	All Rights Reserved.

#pragma once

// fake out the VCOM for VW12.5.x
#ifdef _VWFC_FOR_VW125x


#	ifndef VCOM_CALLTYPE
#		define		VCOM_CALLTYPE
#	endif

#	define VCOMPtr		FakeVCOMPtr

	template<class T> class FakeVCOMPtr
	{
	public:
						FakeVCOMPtr()						{ fPtr = NULL; }
						FakeVCOMPtr(T* p)					{ fPtr = p; if ( fPtr ) { fPtr->AddRef(); } }
						FakeVCOMPtr(const VWIID& iid)		{ fPtr = NULL; this->Query( iid ); }
						FakeVCOMPtr(const FakeVCOMPtr& p)	{ fPtr = p.fPtr; if ( fPtr ) { fPtr->AddRef(); } }
						~FakeVCOMPtr()						{ if ( fPtr ) { fPtr->Release(); } this->IFC_ReleaseInterfaces(); }

		FakeVCOMPtr&	operator=(T* ptr)					{ if ( fPtr ) { fPtr->Release(); } fPtr = ptr; if ( fPtr ) { fPtr->AddRef(); } return *this; }
		FakeVCOMPtr&	operator=(const FakeVCOMPtr& p)		{ if ( fPtr ) { fPtr->Release(); } fPtr = p.fPtr; if ( fPtr ) { fPtr->AddRef(); } return *this; }

		T*				operator->() const					{ return fPtr; }
		T**				operator&()							{ return & fPtr; }
						operator T*() const 				{ return fPtr; }

	private:
		void		Query(const VWIID& iid)
		{
			PluginLibraryArgTable	callTable;
			callTable.args[0].argType		= kVoidPtr;
			callTable.args[0].voidData		= (void*) gCBP;
			callTable.args[1].argType		= kVoidPtr;
			callTable.args[1].voidData		= (void*) & iid;
			if ( ::GS_CallPluginLibrary( gCBP, TXString("IFC_QueryInterface"), (PluginLibraryArgTable*) & callTable, 0 ) ) {
				fPtr	= (T*) callTable.functionResult.voidData;
				if ( fPtr ) {
					fPtr->AddRef();
				}
			}
		}

		void		IFC_ReleaseInterfaces()
		{
			if ( fPtr && fPtr->Release() == 0 ) {
				PluginLibraryArgTable	callTable;
				callTable.args[0].argType		= kVoidPtr;
				callTable.args[0].voidData		= (void*) gCBP;
				callTable.args[1].argType		= kVoidPtr;
				callTable.args[1].voidData		= (void*) fPtr;
				VERIFYN( kVStanev, ::GS_CallPluginLibrary( gCBP, TXString("IFC_ReleaseInterfaces"), (PluginLibraryArgTable*) & callTable, 0 ) );
			}
		}
	private:
		T*		fPtr;
	};



	// ------------------------------------------------------------------------------------------------------------------------
	static const VWIID IID_ProgressDialog = { 0x7E8C933D, 0xCC09, 0x4202, { 0xB1, 0x4F, 0xEF, 0xFB, 0x04, 0xFA, 0x42, 0x20 } };
	class DYNAMIC_ATTRIBUTE IProgressDialog : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE	Open(const TXString& title)						= 0;
		virtual VCOMError VCOM_CALLTYPE Close()											= 0;

		virtual VCOMError VCOM_CALLTYPE	AllowUserCancel(bool bAllow)					= 0;
		virtual VCOMError VCOM_CALLTYPE	ResetMeter(Uint16 meter)						= 0;
		virtual VCOMError VCOM_CALLTYPE	SetTopText(const TXString& szTopText)			= 0;
		virtual VCOMError VCOM_CALLTYPE	SetBottomText(const TXString& szBottomText)		= 0;
		virtual VCOMError VCOM_CALLTYPE	SetMeterText(const TXString& szMeterText)		= 0;

		virtual VCOMError VCOM_CALLTYPE	HasUserCanceled(bool& bUserCanceled)			= 0;
		virtual VCOMError VCOM_CALLTYPE	DoYield()										= 0;
		virtual VCOMError VCOM_CALLTYPE	IncrementMeter(Uint16 step)						= 0;
		
	};

	// ------------------------------------------------------------------------------------------------------------------------
	static const VWIID IID_FileIdentifier = { 0xB4B088B1, 0x3793, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };
	class DYNAMIC_ATTRIBUTE IFileIdentifier : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE	SetFileFullPath(const TXString& path) = 0;
		virtual VCOMError VCOM_CALLTYPE	GetFileFullPath(TXString& outPath) = 0;
		virtual VCOMError VCOM_CALLTYPE	GetFileExtension(TXString& outExtension) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------
	static const VWIID IID_RawOSFile = { 0x4F7F77DD, 0x3796, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };
	class DYNAMIC_ATTRIBUTE IRawOSFile : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE	Open(IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting) = 0;
		virtual VCOMError VCOM_CALLTYPE	Close() = 0;
		virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer) = 0;
		virtual VCOMError VCOM_CALLTYPE	Write(Uint64 position, Uint64 size, const void* pBuffer) = 0;
	};

	// ------------------------------------------------------------------------------------------------------------------------
	static const VWIID IID_FileChooserDialog = { 0x885F311B, 0x3795, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };
	class DYNAMIC_ATTRIBUTE IFileChooserDialog : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE	SetTitle(const TXString& title) = 0;
		virtual VCOMError VCOM_CALLTYPE	SetDefaultFileName(const TXString& name) = 0;
		virtual VCOMError VCOM_CALLTYPE	GetSelectedFileName(Uint32 fileIndex, IFileIdentifier** ppOutFileID) = 0;
		virtual VCOMError VCOM_CALLTYPE	AddFilterAllFiles() = 0;
		virtual VCOMError VCOM_CALLTYPE	AddFilter(const TXString& filterExt, const TXString& filterDesc) = 0;

		virtual VCOMError VCOM_CALLTYPE	RunOpenDialog() = 0;
		virtual VCOMError VCOM_CALLTYPE	RunSaveDialog() = 0;
	};
#endif

namespace IfcModel
{
	class CIfcDocument;
}

namespace VectorWorks
{
	namespace IFCLib
	{
		enum class EOperationStatus;
	}
}

namespace VectorWorks
{
	namespace IFCLib
	{
		// ---------------------------------------------------------------
		enum class EMappingCategory : Sint32
		{
			eCriteriaBased,
			eSymbolDef,
			ePlugInThirdParty,
			ePlugInBuiltIn
		};

		// -----------------------------------------------------------------------------------
		enum class ERecordIFCType : short
		{
			None,
			IFC,
			PSet,
			IFCTag,
		};

		// ----------------------------------------------------------------------------------------
		enum EIFCSupportSchema
		{
			kIFCSupportScheme_2x2,
			kIFCSupportScheme_2x3,
			kIFCSupportScheme_2x4
		};

		// -----------------------------------------------------------------------------------
		enum class EIFCImportMode : short
		{
			Normal,
			AsReference,
		};

		// -----------------------------------------------------------------------------------
		static const	OSType				kRefIFCDataType			 = 'RIFC';

		// -----------------------------------------------------------------------------------
		enum class ESourceValueType : short
		{
			eNotSet = -1,
			eFromInstance = 0,
			eFromMapping = 1,
		};
		inline bool operator== ( const short& v1, const ESourceValueType& v2 )
		{
			return v1 == (short)v2;
		};
		inline bool operator!= ( const short& v1, const ESourceValueType& v2 )
		{
			return !(v1 == (short)v2);
		};
		inline bool operator== ( const ESourceValueType& v1, const short& v2 )
		{
			return (short)v1 == v2;
		};
		inline bool operator!= ( const ESourceValueType& v1, const short& v2 )
		{
			return !((short)v1 == v2);
		};

		// ----------------------------------------------------------------------------------------
		enum class ELocalizationStringType : short
		{
			eEntityName,
			eEntityMemberName,
			eEntityMemberEnumValue,
			ePsetName,
			ePsetMemberName,
			ePsetMemberEnumValue
		};

		//-----------------------------------------------------------------------------------------------------------------------------------------
		namespace OIP
		{
			using TIFCPsetInfo		= std::pair<TXString /*name*/, short /*pset type*/>;
			using TIFCPsetInfoArray = std::vector<TIFCPsetInfo>;
		};

		// ---------------------------------------------------------------------------
		// {E2B50992-BE66-46a8-AA5E-48756374B462}
		static const VWIID IID_IFCSupport = { 0xe2b50992, 0xbe66, 0x46a8, { 0xaa, 0x5e, 0x48, 0x75, 0x63, 0x74, 0xb4, 0x62 } };

		class DYNAMIC_ATTRIBUTE IIFCSupport : public IVWSingletonUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE SetIFCScheme(EIFCSupportSchema scheme) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIFCObjectData(MCObjectHandle hObject, TXString& outIfcObjName, TXString& outIfcObjectUUID) = 0;
			virtual VCOMError VCOM_CALLTYPE UpdateVWDocumentIFCData() = 0;
			virtual VCOMError VCOM_CALLTYPE	CloseForDocument(MCObjectHandle hDocument) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowObjectIFCDataEditDlg(MCObjectHandle hObject, const TXString& strIfcObjName, bool bCreateData, bool bAllowTypeChange=true, bool bDisableIFCEntity=false, bool bDoUndo=true) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowPickIFCTypeDlg(TXString& outIfcObjName) = 0;

			virtual VCOMError VCOM_CALLTYPE ShowExportOptions(bool bExportSingleObjects) = 0;

			virtual VCOMError VCOM_CALLTYPE ImportFile(IFileIdentifier* pFileID, bool bShowUI, EIFCImportMode importMode = EIFCImportMode::Normal) = 0;
			virtual VCOMError VCOM_CALLTYPE ExportFile(IFileIdentifier* pFileID, bool bShowUI) = 0;
			

			// VS/SDK support
			virtual VCOMError VCOM_CALLTYPE IFC_SetIFCEntity(MCObjectHandle hObject, const TXString& strIfcObjName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCEntity(MCObjectHandle hObject, TXString& strIfcObjName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetEntityProp(MCObjectHandle hObject, const TXString& strIfcPropName, const TXString& strIfcPropValue) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntityProp(MCObjectHandle hObject, const TXString& strIfcPropName, TXString& strIfcPropValue, short& iType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetNumPsets(MCObjectHandle hObject, short& numPsets) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPsetName(MCObjectHandle hObject, short index, TXString& strIfcPsetName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_AttachPset(MCObjectHandle hObject, const TXString& strIfcPsetName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetPsetProp(MCObjectHandle hObject, const TXString& strIfcPsetName, const TXString& strIfcPropName, const TXString& strIfcPropValue) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPsetProp(MCObjectHandle hObject, const TXString& strIfcPsetName, const TXString& strIfcPropName, TXString& strIfcPropValue, short& iType)= 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ClearIFCInfo(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetEntityColor(const TXString& strIfcName, short red, short green, short blue, short transparent) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntityColor(const TXString& strIfcName, short& red, short& green, short& blue, short& transparent) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_CopyIFCData(MCObjectHandle hSource, MCObjectHandle hDestination, short inMode) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIFCNameForSelection(TXString& outName, MCObjectHandle hSelectedObject = NULL) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowIFCDataForSelection( MCObjectHandle hSelectedObject = NULL ) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIFCProperty(MCObjectHandle hObject, const TXString& instanceProperty, TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIFCName( MCObjectHandle hObject, TXString& outName ) = 0;
			virtual VCOMError VCOM_CALLTYPE GetAllIFCNamesInDocument( TXStringArray& outArrNames ) = 0;
			virtual VCOMError VCOM_CALLTYPE ConvertUUIDToIfcGloballyUniqueId(const TXString& inUUID, TXString& outIfcGUID) = 0;
			virtual	VCOMError VCOM_CALLTYPE IFC_ImportLibrary(IFolderIdentifier* pFolderID, bool bKeepHierarchy) = 0;
			virtual VCOMError VCOM_CALLTYPE	IFC_DefPsetImport(IFolderIdentifier* pFolderID) = 0; 
			virtual VCOMError VCOM_CALLTYPE	IFC_DefPsetBegin( const TXString& psetName ) = 0; 
			virtual VCOMError VCOM_CALLTYPE	IFC_DefPsetAddMember( const TXString& psetName, const TXString& propName, const TXString& propType ) = 0;
			virtual VCOMError VCOM_CALLTYPE	IFC_DefPsetEnd( const TXString& psetName ) = 0; 

			virtual VCOMError VCOM_CALLTYPE	IFC_GetFullEntitiesList(EIFCSupportSchema scheme, TXStringArray& outArrEntities, bool buildingElemensOnly = false) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPropertiesList(EIFCSupportSchema scheme, const TXString& strIfcObjName, TXStringArray& outArrProperties, TXStringArray& outArrDefaultValues) = 0;
			virtual VCOMError VCOM_CALLTYPE	IFC_CreateFormatEntity(MCObjectHandle hDocument, const TXString& strIfcObjName) = 0;
			virtual	VCOMError VCOM_CALLTYPE IFC_GetSpaceParamForObject(MCObjectHandle hObject, const TXString& param, TXString& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetIFCProperty(MCObjectHandle hObject, const TXString& instancePropertyValue, TXString& outSetValue) = 0;

			virtual VCOMError VCOM_CALLTYPE IFC_ClearPset(MCObjectHandle hObject, const TXString& strIfcPsetName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ClearAllPsets(MCObjectHandle hObject) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetIFCScheme( EIFCSupportSchema scheme ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCScheme( EIFCSupportSchema& outScheme ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCActiveDoc( IfcModel::CIfcDocument** outDoc ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_DeleteIFCInfo( MCObjectHandle hObject, bool bDoUndo ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsPsetDefined( const TXString& psetName ) = 0;

			virtual VCOMError VCOM_CALLTYPE IFC_ResetMapToDefaults() = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_LoadMapSettings( const TXString& strMappingName ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SaveMapSettings( const TXString& strMappingName, const TXString& strObjectName, bool bFileSettings ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsObjectEnabled( const TXString& strObjectName ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_EnableObject(const TXString& strObjectName, bool bEnable, const TXString& strCondition = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsEntryEnabled(const TXString& strObjectName, const TXString& strEntryName, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_EnableEntry(const TXString& strObjectName, const TXString& strEntryName, bool bEnable, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntriesCount(const TXString& strObjectName, short& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntryName(const size_t index, const TXString& strObjectName, TXString& outEntryName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_AddEntry(const TXString& strObjectName, const TXString& strEntryName, bool bEnable, short eEntityType = 0) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_DeleteEntry(const TXString& strObjectName, const TXString& strEntryName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsFieldOptional(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const TXString& strPSetName = "" ) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetFieldOptional(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, bool bOptional, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsFieldEmpty(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetFieldEmpty(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, bool bEmpty, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsFieldEnabled(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetFieldEnabled(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, bool bEnable, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetFieldType(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, short& outType, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetFieldType(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const short& enType, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetFieldMapping(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, TXString& outValue, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetFieldMapping(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const TXString& strValue, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetFieldsCount(const TXString& strObjectName, const TXString& strEntryName, short& outCount, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetFieldName(const TXString& strObjectName, const TXString& strEntryName, const size_t index, TXString& outFieldName, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_AddField(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const short& type, bool bOptional, bool bEnable, bool bEmpty, const TXString& strPSetName = "") = 0;
			virtual	VCOMError VCOM_CALLTYPE IFC_DeleteField(const TXString& strObjectName, const TXString& strEntryName, const TXString& strFieldName, const TXString& strPSetName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ReplaceDataWithMapping(MCObjectHandle hObject, const TXString & strObjName = "") = 0;

			virtual VCOMError VCOM_CALLTYPE ShowPickIFCTypeDlg2(TXString& inOutIfcObjName) = 0;
			virtual VCOMError VCOM_CALLTYPE ShowManagePsetsDlg() = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetIFCEntity2(MCObjectHandle hObject, const TXString& strIfcObjName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetNumPsets2(MCObjectHandle hObject, bool bAllPsets, short& outNumPsets) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPsetInfoAt(MCObjectHandle hObject, bool bAllPsets, short index, TXString& outIfcPsetName, short& outType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPropertiesListOfPset(const TXString& strIfcPsetName, TXStringArray& outArrProperties) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntityProp2(MCObjectHandle hObject, const TXString& strIfcPropName, TXString& outStrIfcPropValue, short& iType, short& outMap) = 0;			
			virtual VCOMError VCOM_CALLTYPE IFC_GetPsetProp2(MCObjectHandle hObject, const TXString& strIfcPsetName, const TXString& strIfcPropName, TXString& strIfcPropValue, short& iType, short& outMap) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPropChoices(const TXString& strIfcName, const TXString& strIfcPropName, TXStringArray& outArrChoices) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetProperty(MCObjectHandle hObject, const TXString& strIfcPsetName, const TXString& strIfcPropName, const TXString& strIfcPropValue) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ResetMapToCOBieDefaults() = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetCOBieProperty(MCObjectHandle hObject, const TXString& worksheetName, const TXString& columnName, const TXString& country, const TXString& version, TXString& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetCOBieSource(MCObjectHandle hObject, const TXString& worksheetName, const TXString& columnName, const TXString& country, const TXString& version, TXString& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetCOBieProperty(MCObjectHandle hObject, const TXString& argStrings, TXString& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetCOBieSource(MCObjectHandle hObject, const TXString& argStrings, TXString& outResult) = 0;

			virtual VCOMError VCOM_CALLTYPE IFC_IsPsetCustom(const TXString& strPsetName, bool& bCustom) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_CreateObjectGUID(MCObjectHandle hObject, bool bDoUndo = true, const TXString& strIfcName = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCEntity2(MCObjectHandle hObject, short& iIfcRecordType, TXString& strIfcNameByRecord, TXString& strIfcNameByMap) = 0;

			virtual VCOMError VCOM_CALLTYPE WS_FillCOBieFixedWorksheets(MCObjectHandle worksheet, bool bIsRolledUp) = 0;
			virtual	VCOMError VCOM_CALLTYPE IFC_GetSpaceParamForObject2(MCObjectHandle hObject, const TXString& param, TXString& outResult) = 0;
			virtual VCOMError VCOM_CALLTYPE GetIFCName2(MCObjectHandle hSelectedObject, TXString& outName) = 0;
			
			// VW 2019 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// VW Record Object/Format Support
			virtual VCOMError VCOM_CALLTYPE IFC_IsIFCRecord(const TXString& recordName, ERecordIFCType& outType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetRecordLocalizedName(MCObjectHandle hFormat, TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamName(MCObjectHandle hFormat, size_t paramIndex, TXString& outParamName, ERecordIFCType recType = ERecordIFCType::None) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamIndex(MCObjectHandle hFormat, const TXString& paramName, size_t& outParamIndex, ERecordIFCType recType = ERecordIFCType::None) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamIndex(MCObjectHandle hFormat, size_t paramIndexIFC, size_t& outParamIndex, ERecordIFCType recType = ERecordIFCType::None) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamStyle(MCObjectHandle hFormat, size_t paramIndex, EFieldStyle& outFieldStyle, ERecordIFCType recType = ERecordIFCType::None) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamValue(MCObjectHandle hFormat, size_t paramIndex, TXString& outParamValue, ERecordIFCType recType = ERecordIFCType::None) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetParamsCount(MCObjectHandle hFormat, size_t& outParamsCnt, ERecordIFCType recType = ERecordIFCType::None) = 0;
			
			virtual VCOMError VCOM_CALLTYPE IFC_GetPsetsForIFCType(const TXString& strIfcType, std::vector<TXString>& outArrPsetsForType) = 0;

			// Data Mapping
			virtual VCOMError VCOM_CALLTYPE IFC_GetMapObjectsCount(size_t& outObjectsCount) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetMapObjectNameConditionAt(size_t objectIndex, TXString& outStrObjectName, TXString& outStrCondition) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetMapObjectCondition(const TXString& strObjName, TXString& outStrObjCondition) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetEntryType(const short entryAt, const TXString& strObjectName,  short& outeType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPSetsCountForEntry(const TXString& strObjectName, const TXString& strEntryName, size_t& outPSetsCount) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetPSetNameConditionForEntryAt(const TXString& strObjectName, const TXString& strEntryName, size_t psetIndex, TXString& outStrPSetName, TXString& outStrCondition) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_AddPSetForEntry(const TXString& strObjectName, const TXString& v, const TXString& strPSetName, bool bEnabled = true, const TXString& strPSetCondition = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_DeletePSetFromEntry(const TXString& strObjectName, const TXString& strEntryName, const TXString& strPSetName) = 0;

			virtual VCOMError VCOM_CALLTYPE IFC_SaveIFCActiveSchemeInDoc(const VectorWorks::IFCLib::EIFCSupportSchema& ifcSupportScheme) = 0;

			// MVD
			virtual VCOMError VCOM_CALLTYPE IFC_ImportMVD(IFileIdentifier* pFileID, short type, TXString entity = "") = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_IsMVDImported(bool& isImported) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ResetMVD() = 0;

			virtual	VCOMError VCOM_CALLTYPE IFC_GetCounter(const TXString& strObjectName, Sint32& outIndex) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ClearCounter() = 0;

			// Internal Support
			virtual VCOMError VCOM_CALLTYPE IFC_QueryHSupport(IVWUnknown** outP, const VWIID& iid) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_ReleaseHSupport(IVWUnknown** outP, const VWIID& iid) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetAccessor(const VWIID& iid, IVWUnknown** outInterface) = 0;

			// OIP
			virtual VCOMError VCOM_CALLTYPE IFC_CollectInfoAtOnce(MCObjectHandle hObject, TXString& outEntityName, bool& outHasDefaultIFCEntity, OIP::TIFCPsetInfoArray& outPsets) = 0;

			// custom pset update
			virtual VCOMError VCOM_CALLTYPE	IFC_DefPsetUpdateAddMember(const TXString& psetName, const TXString& propName, const TXString& propType, bool bDoUndo) = 0;

			// VW 2020 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			// Data Mapping
			virtual VCOMError VCOM_CALLTYPE DM_GetMapObjectCategory(const TXString& strObjectName, EMappingCategory& outMappingCategory) = 0;

			// Localization
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCLocalizedName(const TXString& ifcName, TXString& outLocalizedName, const ELocalizationStringType& eIFCStringType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCUniversalName(const TXString& ifcName, TXString& outUniversalName, const ELocalizationStringType& eIFCStringType) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_AreIFCResourcesLocalized(bool& outbAreResourcesLocalized) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_GetIFCUILanguageFromDoc(bool& outbAreResourcesLocalized) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SaveIFCUILanguageInDoc(bool bAreResourcesLocalized) = 0;
			virtual VCOMError VCOM_CALLTYPE IFC_SetIFCUILanguageInVW(bool bIsUILocalized) = 0;

			// Data Sheets
			virtual VCOMError VCOM_CALLTYPE DSH_GetDataSheetsCount(MCObjectHandle hObject, size_t& outCount) = 0;
			virtual VCOMError VCOM_CALLTYPE DSH_GetDataSheetNameAt(MCObjectHandle hObject, size_t dsIndex, TXString& outDataSheetName) = 0;
			virtual VCOMError VCOM_CALLTYPE DSH_GetDataSheetFieldsCount(MCObjectHandle hObject, const TXString& dataSheetName, size_t& outFieldsCount) = 0;
			virtual VCOMError VCOM_CALLTYPE DSH_GetDataSheetFieldNameInfoAt(MCObjectHandle hObject, const TXString& dataSheetName, size_t fieldIndex, TXString& outFieldUniversalSrc, TXString& outFieldLocalizedSrc, TXString& outFieldLabel) = 0;
			virtual VCOMError VCOM_CALLTYPE DSH_GetDataSheetFieldValue(MCObjectHandle hObject, const TXString& dataSheetName, const TXString& fieldLabel, TXString& outFieldValue, VectorWorks::IFCLib::EOperationStatus& outStatus, ESourceValueType& outType) = 0;
			virtual VCOMError VCOM_CALLTYPE DSH_SetDataSheetFieldValue(MCObjectHandle hObject, const TXString& dataSheetName, const TXString& fieldLabel, const TXString& fieldValue, VectorWorks::IFCLib::EOperationStatus& outStatus) = 0;

			virtual VCOMError VCOM_CALLTYPE	DM_GetRecFieldValue(MCObjectHandle hRecord, short index, TXString& outFieldValue, EFieldStyle& outFieldStyle) = 0;
			virtual VCOMError VCOM_CALLTYPE DM_IsRecordMapped(MCObjectHandle hRecord, bool& outMapped) = 0;

			// VW 2021 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			virtual VCOMError VCOM_CALLTYPE ConvertIfcGloballyUniqueIdToUUID(const TXString& inIfcGUID, TXString& outUUID) = 0;
			virtual VCOMError VCOM_CALLTYPE	ExportObject(TXString& outPartialModel, const std::vector<MCObjectHandle>& arrhObject) = 0;
			virtual VCOMError VCOM_CALLTYPE	IFC_ExportNoUI(IFileIdentifier* pFileID) = 0;
		};
	}
}


