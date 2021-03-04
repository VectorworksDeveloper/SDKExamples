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
			virtual bool					VCOM_CALLTYPE WSCustomUnitsTranslate(TXString& ioData, MCObjectHandle hFormat	, const TXString& fieldName)								{ return false; }
			virtual void					VCOM_CALLTYPE OnUserDataNodeChangedByUndo(OSType type, MCObjectHandle userNode_READ_ONLY)				{ };
		};
	}
}
