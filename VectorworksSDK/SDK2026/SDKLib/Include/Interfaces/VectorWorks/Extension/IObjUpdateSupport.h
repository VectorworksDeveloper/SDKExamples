//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License

#pragma once


namespace VectorWorks
{
	namespace Extension
	{
		// ----------------------------------------------------------------------------------------------------
		enum EWeilerClipAction
		{
			eWeilerClipAction_Clip,
			eWeilerClipAction_Union,
			eWeilerClipAction_Intersect,
		};

		// ----------------------------------------------------------------------------------------------------
		enum EWeilerOperationResult
		{
			eWeilerOperationResult_NotHandled,
			eWeilerOperationResult_HandledOk,
			eWeilerOperationResult_HandledError,
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IObjUpdateSupportContext
		{
		public:
			virtual										~IObjUpdateSupportContext()		{}

			// collection
			virtual TParametricFileIndex	VCOM_CALLTYPE	AcceptState(const TXString& objName) = 0;
			virtual void					VCOM_CALLTYPE	DenyState(TParametricFileIndex fileIndex) = 0;
			virtual TParametricFileIndex	VCOM_CALLTYPE	AcceptStateInternal(const TXString& objName) = 0;
			virtual void					VCOM_CALLTYPE	DenyStateInternal(TParametricFileIndex fileIndex) = 0;
			virtual TParametricFileIndex	VCOM_CALLTYPE	AcceptPredraw(const TXString& objName) = 0;
			virtual void 					VCOM_CALLTYPE	DenyPredraw(TParametricFileIndex fileIndex) = 0;
			virtual void 					VCOM_CALLTYPE	AcceptNotification(Uint32 whichChange) = 0;
			virtual void 					VCOM_CALLTYPE	DenyNotification(Uint32 whichChange) = 0;
			virtual TParametricFileIndex	VCOM_CALLTYPE	AcceptWeilerOperations(const TXString& objName) = 0;
			virtual void					VCOM_CALLTYPE	DenyWeilerOperations(TParametricFileIndex fileIndex) = 0;

			// context data
			virtual MCObjectHandle 			VCOM_CALLTYPE	GetObject() = 0;
			virtual TParametricFileIndex	VCOM_CALLTYPE	GetFileIndex() = 0;
			virtual bool					VCOM_CALLTYPE	GetIsPredrawBoundingCube() = 0;
			virtual size_t					VCOM_CALLTYPE	GetPredrawViewportCount() = 0;
			virtual MCObjectHandle			VCOM_CALLTYPE	GetPredrawViewport(size_t index) = 0;
			virtual void 					VCOM_CALLTYPE	SetPredrawBoundingCube(const WorldCube& boundCube) = 0;
			virtual void 					VCOM_CALLTYPE	GetNotification(StatusID& outWhichChange, StatusData& outAdditionalData) = 0;
			virtual EWeilerClipAction		VCOM_CALLTYPE	GetWeilerClipAction() = 0;

		// Vectorworks 2012
		public:
			virtual TParametricFileIndex	VCOM_CALLTYPE	AcceptState2(TDType objType) = 0;
			virtual void					VCOM_CALLTYPE	AcceptRightClick() = 0;
			virtual void					VCOM_CALLTYPE	DenyRightClick() = 0;

			// context data
			virtual short					VCOM_CALLTYPE	GetRightClickPickEvent() = 0;

		// Vectorworks 2014
		public:
			virtual void					VCOM_CALLTYPE	AcceptResourceBrowserDoubleClickOnSymbol() = 0;
			virtual void					VCOM_CALLTYPE	DenyResourceBrowserDoubleClickOnSymbol() = 0;

		// Vectorworks 2017
		public:
			virtual void					VCOM_CALLTYPE	AddDataPaneProvider(const TXString& recordFormatName, const VWIID& iid) = 0;
			virtual void					VCOM_CALLTYPE	AddShapePaneProvider(const TXString& universalParametricName, const VWIID& iid) = 0;
			virtual void					VCOM_CALLTYPE   AddReshapeProvider(const TXString& universalParametricName, const VWIID& iid) = 0;

		// Vectorworks 2020
		public:
			virtual void					VCOM_CALLTYPE   AddUserDataNodeChangedByUndo(OSType type) = 0;
			virtual IWebPaletteFrame*		VCOM_CALLTYPE   GetWebPaletteFrame(const VWIID& extensionIID) = 0;

		// Vectorworks 2023
		public:
			virtual void					VCOM_CALLTYPE	AddWorksheetRecordOverrideProvider(const TXString& universalName, const VWIID& iid) = 0;
			virtual void					VCOM_CALLTYPE	AddWorksheetVirtualRecordOverrideProvider(const TXString& formatPrefix, const TXString& formatName, const VWIID& iid) = 0;

		// Vectorworks 2025
		public:

			struct SDataTagGeometryInfo
			{
				TXString	fUnivName;
				TXString	fLocalizedName;
			};
			using TDataTagGeometryInfoArr		= std::vector<SDataTagGeometryInfo>;

			virtual void		VCOM_CALLTYPE	AcceptDataTagGeometry(const TXString& parametricUnivName, const TDataTagGeometryInfoArr& arrGeometryInfos) = 0;
			virtual void		VCOM_CALLTYPE	AcceptDataTagGeometry(TInternalID parametricID, const TDataTagGeometryInfoArr& arrGeometryInfos) = 0;
			virtual void		VCOM_CALLTYPE	AcceptDataTagGeometry(TDType objType, const TDataTagGeometryInfoArr& arrGeometryInfos) = 0;

			struct SPopupLocalizationInfo
			{
				struct SPopupNames
				{
					TXString	fUniversalName;
					TXString	fLocalizedName;
				};

				std::vector<SPopupNames>	fArrPopupNames;
			};
			using TMapPopupLocalizationInfo	= std::map<TXString/*PopupUnivName*/, SPopupLocalizationInfo>;

			// provide localized format name and localized field names for the provided format name
			// Note! This only will work for read-only formats!
			//	localizedName			- the localized name of this format
			//	arrLocalizedFields		- the localized field names matched by the field name
			//	mapPopuptLocalization	- the universal and localized popup names
			//isUIAttachable			- whether the format is attachable to trough the UI
			virtual void		VCOM_CALLTYPE	AddFormatLocalization(const TXString& formatName, const TXString& localizedName, const std::vector<TXString>& arrLocalizedFields, const TMapPopupLocalizationInfo& mapPopuptLocalization = {}, bool isUIAttachable = false) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {6340A3C4-F7A7-4a42-9050-E4964F41E6F9}
		static const VWGroupID GROUPID_ObjUpdateSupport = { 0x6340a3c4, 0xf7a7, 0x4a42, { 0x90, 0x50, 0xe4, 0x96, 0x4f, 0x41, 0xe6, 0xf9 } };

		// ----------------------------------------------------------------------------------------------------
		// Base class object update support implementations
		class DYNAMIC_ATTRIBUTE IObjUpdateSupport : public IVWUnknown
		{
		public:
			virtual void 					VCOM_CALLTYPE Init(IObjUpdateSupportContext* theContext) = 0;
			
			virtual void 					VCOM_CALLTYPE OnState(IObjUpdateSupportContext* /*theContext*/, const ObjectState& /*state*/)			{ };
			virtual void 					VCOM_CALLTYPE OnStateInternal(IObjUpdateSupportContext* /*theContext*/, const ObjectState& /*state*/)	{ };
			virtual MCObjectHandle			VCOM_CALLTYPE OnPredraw(IObjUpdateSupportContext* /*theContext*/)										{ return NULL; };
			virtual void 					VCOM_CALLTYPE OnNotification(IObjUpdateSupportContext* /*theContext*/)									{ };
			virtual EWeilerOperationResult 	VCOM_CALLTYPE OnWeilerOperation(IObjUpdateSupportContext* /*theContext*/)								{ return eWeilerOperationResult_NotHandled; };
			virtual bool					VCOM_CALLTYPE OnRightClick(IObjUpdateSupportContext* /*theContext*/)									{ return false; }
			virtual bool					VCOM_CALLTYPE OnResourceBrowserDoubleClickOnSymbol(IObjUpdateSupportContext* /*theContext*/, TXString& /*outActivateToolUniqueName*/)	{ return false; /*handled*/ };
			virtual bool					VCOM_CALLTYPE WSCustomUnitsTranslate(double& ioData, MCObjectHandle hFormat, const TXString& fieldName)									{ return false; }
			virtual bool					VCOM_CALLTYPE WSCustomUnitsTranslate(TXString& ioData, MCObjectHandle hFormat	, const TXString& fieldName)							{ return false; }
			virtual bool					VCOM_CALLTYPE WSCustomUnitsTranslateToData(double& ioData, MCObjectHandle hFormat, const TXString& fieldName)							{ return false; }
			virtual void					VCOM_CALLTYPE OnUserDataNodeChangedByUndo(OSType type, MCObjectHandle userNode_READ_ONLY)				{ };

			// notify when the theme changes, and provide if it is changed to dark mode
			virtual void					VCOM_CALLTYPE OnThemeChanged(IObjUpdateSupportContext* context, bool isDarkMode)						{ };

			// this is a callback that is only supported by internal implementations
			// under win debug/fastdebug, each dispatch will run a new Vectorworks instance. Either attach the debugger after vworks is lauched from this, or add a BuildNumber [the last number] to FILEVER in the core, so it reuses instances under debug/fastdebug builds
			virtual bool					VCOM_CALLTYPE DispatchOpenCustomURL(const TXString& key, const TXString& param)							{ return false; };

			// this callback will be called for the associated object and it's subpart (if any) when the data tag requests geometry with the given name to be displayed in the layout
			// use IObjUpdateSupport::Init
			virtual MCObjectHandle			VCOM_CALLTYPE OnDataTagGeometryRequest(MCObjectHandle h, MCObjectHandle subpart, const TXString& geometryUnivName)	{ return nullptr; }
			
			// Sends a map of object UUIDs keyed by the original object's UUID when a paste or drag duplication operation occurs.
			//
			// Paste into the same document / Drag duplication:
			//       This UUID map will only contain UUIDs for objects that are stored in the clipboard (paste) or the currently
			//       selected objects (drag duplication).  UUIDs for resources and their children objects are not included,
			//       because they were not duplicated as part of the paste.
			//
			// Paste into a different document:
			//       This UUID map will contain the UUIDs for objects that are stored in the clipboard alongside UUIDs
			//       for the necessary related items and resources (and their children).
			//
			// IMPORTANT NOTE: When pasting into a different document, if a resource that is being pasted already exists in the target
			//          document, then the target document will use the existing resource.  This means that the resource duplicated for
			//          pasting will get thrown out, and the associated UUID in the map may not refer to the expected object (or any
			//          object at all).  This is a Core limitation.  If a pasted object uses a resource that already exists in the target
			//          document, please try to use that resource to fix mappings if possible.
			virtual void	VCOM_CALLTYPE  SendUuidMapOnPasteOrDragDuplication(const UuidStorageMap& inUuidMap) { };
		};
	}
}
